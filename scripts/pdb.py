#!/usr/bin/env python3
"""
pdb_reconstruct.py
===================

Recreate the original source-file tree (as stub files containing function
declarations) from the debug information embedded in a PDB.

HOW IT WORKS
------------
This does NOT parse the PDB binary format itself (that's a deep rabbit
hole -- MSF container, DBI stream, TPI/IPI streams, etc.). Instead it
shells out to LLVM's `llvm-pdbutil`, which already knows how to read
PDBs, and asks it to dump everything to YAML (`pdb2yaml --all`). That
YAML is a documented, fairly stable schema (LLVM uses it for PDB
round-trip testing), so it's a much safer foundation than depending on
undocumented internals of a python PDB-parsing library.

From the YAML we pull, per *module* (i.e. per compiled object file):
  - `DbiStream.Modules[i].SourceFiles`  -> the file(s) that went into it
  - `DbiStream.Modules[i].Modi.Subsections[*].Symbols.Records`
       -> the S_GPROC32 / S_LPROC32 records, which give each function's
          display name, address, and (if not stripped) a FunctionType
          index into the TPI stream.
  - `TpiStream.Records` -> used to do a best-effort reconstruction of
    the return type / argument types for LF_PROCEDURE / LF_MFUNCTION
    entries.

WHAT YOU GET
------------
For each module, the *first* entry in its SourceFiles list is treated
as the file that was actually compiled (later entries are usually
headers that got pulled in and aren't independently attributable to
specific functions without full line-table analysis). That file is
recreated under --out, containing a best-effort declaration for every
function symbol attributed to that module.

Any additional SourceFiles entries (headers, etc.) are created as
empty stub files at the correct relative path so the directory
structure exists, with a comment noting they were referenced but that
no function attribution is possible at this granularity.

LIMITATIONS (read this before trusting the output)
---------------------------------------------------
- Parameter *names* are usually gone in release PDBs; only types
  survive (if types weren't stripped either). Where we can't resolve a
  type we emit `/* type 0x%x */` placeholders.
- Attribution is at the *object/module* level, matching what you
  described (file paths + function names + which object they compiled
  to). It is NOT line-accurate -- a function physically defined in a
  header but inlined into this module will still show up here.
- This produces headers/declarations, not full definitions -- PDBs
  don't carry function bodies.
- Overloaded / templated / mangled C++ names are left as the
  demangled display name llvm-pdbutil provides; no attempt is made to
  re-derive an exact C++ declaration syntax (that would need a real
  demangler + full TPI resolution).

REQUIREMENTS
------------
- llvm-pdbutil on PATH (part of LLVM; `brew install llvm`,
  `apt install llvm`, or grab prebuilt LLVM release binaries on
  Windows).
- pip install pyyaml

USAGE
-----
    python pdb_reconstruct.py mything.pdb --out ./reconstructed
"""

from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
from pathlib import Path

import yaml

# --------------------------------------------------------------------------
# YAML loading: llvm-pdbutil's pdb2yaml output uses custom tags like
# !Symbols, !FileChecksums, !TypeServer2, etc. We don't care about the tag
# names themselves -- we just want the underlying mapping/sequence -- so we
# register a catch-all constructor instead of hand-listing every tag.
# --------------------------------------------------------------------------

class PdbYamlLoader(yaml.SafeLoader):
    pass


def sanitize_yaml_text(text: str) -> str:
    """llvm-pdbutil can emit control bytes that PyYAML rejects even though
    the surrounding output is otherwise valid YAML. Strip the disallowed
    bytes before loading.
    """
    if not text:
        return text
    return re.sub(r"[\x00-\x08\x0b\x0c\x0e-\x1f\x7f]", "", text)


def _construct_any(loader, tag_suffix, node):
    if isinstance(node, yaml.MappingNode):
        return loader.construct_mapping(node, deep=True)
    if isinstance(node, yaml.SequenceNode):
        return loader.construct_sequence(node, deep=True)
    return loader.construct_scalar(node)


PdbYamlLoader.add_multi_constructor("!", _construct_any)

# A small table of common MSVC "simple" (builtin) TPI type names, keyed by
# the numeric type index llvm-pdbutil prints for T_* builtins. Not
# exhaustive -- extend as needed.
SIMPLE_TYPES = {
    0x0003: "void",
    0x0010: "signed char",
    0x0020: "unsigned char",
    0x0070: "char",
    0x0071: "wchar_t",
    0x0074: "int32_t",
    0x0075: "uint32_t",
    0x0068: "int8_t",
    0x0069: "uint8_t",
    0x0072: "int16_t",
    0x0073: "uint16_t",
    0x0076: "int64_t",
    0x0077: "uint64_t",
    0x0040: "float",
    0x0041: "double",
    0x0030: "bool",
}


def run_pdbutil(pdb_path: Path, llvm_pdbutil: str, cache_yaml: Path | None) -> dict:
    if cache_yaml and cache_yaml.exists():
        print(f"[status] Using cached YAML dump: {cache_yaml}")
        text = sanitize_yaml_text(cache_yaml.read_text(errors="replace"))
    else:
        print(f"[status] Exporting PDB to YAML with llvm-pdbutil: {pdb_path}")
        cmd = [llvm_pdbutil, "pdb2yaml", "--all", str(pdb_path)]
        try:
            result = subprocess.run(cmd, capture_output=True, text=True, check=True)
        except FileNotFoundError:
            sys.exit(
                f"error: '{llvm_pdbutil}' not found on PATH. Install LLVM "
                f"(brew install llvm / apt install llvm) or pass --llvm-pdbutil."
            )
        except subprocess.CalledProcessError as e:
            sys.exit(f"error: llvm-pdbutil failed:\n{e.stderr}")
        text = sanitize_yaml_text(result.stdout)
        if cache_yaml:
            print(f"[status] Writing intermediate YAML cache to {cache_yaml}")
            cache_yaml.write_text(text)

    print("[status] Loading YAML data structure...")
    return yaml.load(text, Loader=PdbYamlLoader)


def build_type_index(data: dict) -> dict:
    """Map numeric TPI type index -> raw record dict, for lookup."""
    types = {}
    tpi = data.get("TpiStream", {}) or {}
    records = tpi.get("Records", []) or []
    # TPI indices start at 0x1000; records are in order.
    start = 0x1000
    for i, rec in enumerate(records):
        types[start + i] = rec
    return types


def resolve_type_name(type_index, type_index_map) -> str:
    if type_index is None:
        return "void"
    if isinstance(type_index, str):
        m = re.match(r"0x?([0-9a-fA-F]+)", type_index)
        type_index = int(m.group(1), 16) if m else None
    if type_index is None:
        return "/* unknown type */"
    if type_index in SIMPLE_TYPES:
        return SIMPLE_TYPES[type_index]
    if type_index < 0x1000:
        return f"/* type 0x{type_index:x} */"

    rec = type_index_map.get(type_index)
    if not rec:
        return f"/* type 0x{type_index:x} */"

    kind = rec.get("Kind", "")
    if kind == "LF_POINTER":
        inner = rec.get("PointerType", {})
        referent = inner.get("ReferentType")
        return resolve_type_name(referent, type_index_map) + " *"
    if kind in ("LF_STRUCTURE", "LF_CLASS"):
        name = rec.get(kind[3:].capitalize() + "Type", {}) or rec
        return name.get("Name", f"/* struct 0x{type_index:x} */")
    if kind == "LF_MODIFIER":
        mod = rec.get("ModifierType", {})
        base = resolve_type_name(mod.get("ModifiedType"), type_index_map)
        prefix = "const " if mod.get("Const") else ""
        return prefix + base

    return f"/* type 0x{type_index:x} ({kind}) */"


def resolve_function_signature(func_type_index, type_index_map) -> str:
    """Return an 'args' string, best-effort, for a FunctionType index."""
    if func_type_index is None:
        return "(...)"
    rec = type_index_map.get(func_type_index)
    if not rec:
        return "(...)"

    body = rec.get("MemberFunction") or rec.get("Procedure") or {}
    ret_type = resolve_type_name(body.get("ReturnType"), type_index_map)
    arglist_index = body.get("ArgumentList")
    arg_rec = type_index_map.get(arglist_index) if arglist_index else None

    args = []
    if arg_rec:
        arglist_body = arg_rec.get("ArgList", arg_rec)
        for idx in arglist_body.get("ArgIndices", []) or []:
            args.append(resolve_type_name(idx, type_index_map))

    args_str = ", ".join(args) if args else "void"
    return ret_type, args_str


def iter_module_functions(module: dict):
    """Yield (name, function_type_index) for proc symbols in a module.

    LLVM's YAML can place proc records either directly under Modi.Records
    or nested under Modi.Subsections[*].Symbols.Records depending on how the
    PDB was emitted. Scan both shapes and deduplicate the results.
    """
    proc_kinds = {"S_GPROC32", "S_LPROC32", "S_GPROC32_ID", "S_LPROC32_ID"}
    seen = set()

    def _extract_records(node):
        if isinstance(node, list):
            for item in node:
                yield from _extract_records(item)
            return
        if not isinstance(node, dict):
            return
        records = node.get("Records")
        if records is not None:
            yield from records
        symbols = node.get("Symbols")
        if isinstance(symbols, dict):
            yield from (symbols.get("Records") or [])

    for record in _extract_records(module.get("Modi", {})):
        if not isinstance(record, dict):
            continue
        kind = record.get("Kind", "")
        if kind not in proc_kinds:
            continue
        proc = record.get("ProcSym", record)
        name = proc.get("DisplayName") or proc.get("Name")
        if not name:
            continue
        key = (name, proc.get("FunctionType"))
        if key in seen:
            continue
        seen.add(key)
        yield name, proc.get("FunctionType")


def pick_primary_source_file(source_files: list[str]) -> str:
    """Prefer a real implementation file over a header when choosing where to
    emit declarations. This keeps generated declarations in .c/.cpp files,
    which is much more useful as a fill-in template.
    """
    code_exts = {".c", ".cc", ".cpp", ".cxx", ".c++", ".cp", ".m", ".mm"}
    for path in source_files:
        suffix = Path(path.replace("\\", "/")).suffix.lower()
        if suffix in code_exts:
            return path
    return source_files[0] if source_files else ""


def collect_named_type_declarations(data: dict) -> list[str]:
    """Best-effort extraction of named C/C++ type declarations from the TPI
    stream.

    LLVM writes the actual class/struct records under keys such as ``Class`` or
    ``Enum`` rather than ``ClassType`` / ``EnumType``. We normalize those fields
    here so the shared header contains the type names the PDB really records.
    """
    tpi = data.get("TpiStream", {}) or {}
    records = tpi.get("Records", []) or []
    decls: list[str] = []
    seen: set[str] = set()

    for rec in records:
        if not isinstance(rec, dict):
            continue
        kind = rec.get("Kind")
        if kind not in ("LF_STRUCTURE", "LF_CLASS", "LF_UNION", "LF_ENUM"):
            continue

        body = (
            rec.get("Class")
            or rec.get("Struct")
            or rec.get("Union")
            or rec.get("Enum")
            or rec.get("ClassType")
            or rec.get("StructType")
            or rec.get("UnionType")
            or rec.get("EnumType")
            or {}
        )
        if not isinstance(body, dict):
            continue

        name = body.get("Name") or rec.get("Name")
        if not name or name in seen:
            continue
        seen.add(name)

        stripped = name.strip("'\"")
        if kind == "LF_CLASS":
            decls.append(f"class {stripped};")
        elif kind == "LF_UNION":
            decls.append(f"union {stripped};")
        elif kind == "LF_ENUM":
            decls.append(f"enum {stripped};")
        else:
            decls.append(f"struct {stripped};")

    return decls


def sanitize_relpath(path_str: str) -> Path:
    """Turn an absolute Windows/Unix build path into a safe relative path."""
    p = path_str.replace("\\", "/")
    # strip drive letters like C:/
    p = re.sub(r"^[A-Za-z]:/", "", p)
    p = p.lstrip("/")
    parts = [seg for seg in p.split("/") if seg not in ("", "..")]
    return Path(*parts) if parts else Path("unknown_file.txt")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("pdb", type=Path, help="Path to the .pdb file")
    ap.add_argument("--out", type=Path, default=Path("reconstructed"), help="Output directory")
    ap.add_argument("--llvm-pdbutil", default="llvm-pdbutil", help="Path to llvm-pdbutil binary")
    ap.add_argument("--cache-yaml", type=Path, default=None,
                     help="Read/write the intermediate pdb2yaml dump here (speeds up repeat runs)")
    args = ap.parse_args()

    data = run_pdbutil(args.pdb, args.llvm_pdbutil, args.cache_yaml)
    type_index_map = build_type_index(data)

    dbi = data.get("DbiStream", {}) or {}
    modules = dbi.get("Modules", []) or []

    if not modules:
        sys.exit("No modules found -- is this really a PDB with private symbols "
                  "(not a stripped /PDBSTRIPPED one)?")

    print(f"[status] Found {len(modules)} modules in the PDB. Reconstructing source tree under {args.out}")
    args.out.mkdir(parents=True, exist_ok=True)

    shared_types = collect_named_type_declarations(data)
    shared_header = args.out / "pdb_shared_types.h"
    shared_header.write_text(
        "#pragma once\n\n"
        + "\n".join(shared_types if shared_types else ["// no named types were recovered from this PDB."])
        + "\n"
    )
    print(f"[status] Wrote shared PDB type declarations to {shared_header}")

    written = 0
    empty_stubs = 0
    total = len(modules)

    for idx, module in enumerate(modules, 1):
        source_files = module.get("SourceFiles") or []
        obj_name = module.get("Module") or module.get("ObjFile") or "<unknown>"

        funcs = list(iter_module_functions(module))
        if not source_files:
            continue

        primary_source = pick_primary_source_file(source_files)
        if not primary_source:
            continue

        print(f"[status] [{idx}/{total}] {obj_name} -> {len(funcs)} function symbol(s) ; target: {primary_source}")
        primary = sanitize_relpath(primary_source)
        out_path = args.out / primary
        out_path.parent.mkdir(parents=True, exist_ok=True)

        include_rel = os.path.relpath(shared_header, out_path.parent).replace(os.sep, "/")
        lines = [
            f"// Reconstructed from PDB debug info.",
            f"// Original path : {primary_source}",
            f"// Compiled into : {obj_name}",
            f"// {len(funcs)} function symbol(s) attributed to this object.",
            f"// NOTE: signatures are best-effort (see script docstring for limitations).",
            "",
        ]
        if out_path.suffix.lower() not in {".h", ".hpp", ".hh"}:
            lines.extend([
                f'#include "{include_rel}"',
                "",
            ])

        for name, func_type_index in funcs:
            ret_type, arg_str = "void", "..."
            if func_type_index is not None:
                resolved = resolve_function_signature(func_type_index, type_index_map)
                if isinstance(resolved, tuple):
                    ret_type, arg_str = resolved
            lines.append(f"{ret_type} {name}({arg_str});")

        out_path.write_text("\n".join(lines) + "\n")
        written += 1

        # Any additional listed source files (usually headers) get an
        # empty stub so the tree at least exists, unless already created
        # by another module referencing the same header.
        for extra in source_files:
            if extra == primary_source:
                continue
            extra_path = args.out / sanitize_relpath(extra)
            if extra_path.exists():
                continue
            extra_path.parent.mkdir(parents=True, exist_ok=True)
            extra_path.write_text(
                f"// Referenced by object '{obj_name}' but no function\n"
                f"// attribution is possible for included/header files\n"
                f"// at object-level granularity.\n// Original path: {extra}\n"
            )
            empty_stubs += 1

    print(f"[status] Finished reconstruction.")
    print(f"Wrote {written} source file(s) with function declarations.")
    print(f"Wrote {empty_stubs} empty header/reference stub(s).")
    print(f"Output directory: {args.out.resolve()}")


if __name__ == "__main__":
    main()