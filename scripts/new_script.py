#!/usr/bin/env python3

import json
import sys
from pathlib import Path


def iter_obj_files(root):
    root = Path(root)
    if not root.exists():
        raise FileNotFoundError(f"Object directory does not exist: {root}")

    return sorted(
        path for path in root.rglob("*")
        if path.is_file() and path.suffix.lower() == ".obj"
    )


def build_objdiff_units(obj_dir, target_dir=None, base_dir=None):
    obj_dir = Path(obj_dir)
    target_dir = Path(target_dir) if target_dir is not None else obj_dir
    base_dir = Path(base_dir) if base_dir is not None else None

    units = []
    for obj_file in iter_obj_files(obj_dir):
        name = obj_file.stem

        target_path = (target_dir / f"{name}.obj").as_posix()
        base_path = None
        if base_dir is not None:
            base_path = (base_dir / f"{name}.obj").as_posix()

        units.append(
            {
                "name": name,
                "target_path": target_path,
                "base_path": base_path,
                "metadata": {},
            }
        )

    return units


def write_objdiff(units, output):
    objdiff = {
        "$schema": (
            "https://raw.githubusercontent.com/encounter/"
            "objdiff/main/config.schema.json"
        ),
        "build_target": False,
        "build_base": False,
        "units": units,
    }

    output = Path(output)
    output.parent.mkdir(parents=True, exist_ok=True)

    with open(output, "w", encoding="utf-8") as f:
        json.dump(objdiff, f, indent=2)
        f.write("\n")


def main():
    if len(sys.argv) not in (3, 4, 5):
        print(
            f"usage: {sys.argv[0]} obj_dir output.json [target_dir] [base_dir]",
            file=sys.stderr,
        )
        sys.exit(1)

    obj_dir = Path(sys.argv[1])
    output_file = Path(sys.argv[2])
    target_dir = Path(sys.argv[3]) if len(sys.argv) >= 4 else None
    base_dir = Path(sys.argv[4]) if len(sys.argv) >= 5 else None

    try:
        units = build_objdiff_units(obj_dir, target_dir, base_dir)
    except FileNotFoundError as exc:
        print(f"error: {exc}", file=sys.stderr)
        sys.exit(1)

    write_objdiff(units, output_file)

    print(
        f"Wrote {len(units)} objdiff units from {obj_dir} to {output_file}",
        file=sys.stderr,
    )


if __name__ == "__main__":
    main()