#!/usr/bin/env python3

import csv
import re
import sys
from pathlib import Path


MODULE_RE = re.compile(
    r"^Mod\s+(\d+)\s+\|\s+`([^`]+)`:"
)

OBJNAME_RE = re.compile(
    r"S_OBJNAME.*`([^`]+)`"
)

PROC_RE = re.compile(
    r"S_(?:GPROC32|LPROC32|GPROC32_ID|LPROC32_ID).*`([^`]+)`"
)


def obj_name(module_name):
    """
    Convert:
        x64\\Release Multithreaded\\foo.obj
    to:
        foo

    Also handles paths containing /.
    """
    name = module_name.replace("\\", "/").rsplit("/", 1)[-1]

    if name.lower().endswith(".obj"):
        name = name[:-4]

    return name


def parse_dump(path):
    modules = {}
    current_module = None

    with open(path, "r", encoding="utf-8", errors="replace") as f:
        for line in f:
            module_match = MODULE_RE.match(line)

            if module_match:
                module_id = int(module_match.group(1))
                module_path = module_match.group(2)

                current_module = {
                    "id": module_id,
                    "path": module_path,
                    "name": obj_name(module_path),
                    "symbols": [],
                }

                modules[module_id] = current_module
                continue

            if current_module is None:
                continue

            proc_match = PROC_RE.search(line)

            if proc_match:
                symbol = proc_match.group(1)

                if symbol not in current_module["symbols"]:
                    current_module["symbols"].append(symbol)

    return modules


def write_csv(modules, output):
    with open(output, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)

        for module in modules.values():
            row = [module["name"]]
            row.extend(module["symbols"])
            writer.writerow(row)


def main():
    if len(sys.argv) != 3:
        print(
            f"usage: {sys.argv[0]} pdb_dump.txt output.csv",
            file=sys.stderr,
        )
        sys.exit(1)

    dump_file = Path(sys.argv[1])
    output_file = Path(sys.argv[2])

    modules = parse_dump(dump_file)
    write_csv(modules, output_file)

    module_count = len(modules)
    symbol_count = sum(
        len(module["symbols"])
        for module in modules.values()
    )

    print(
        f"Wrote {symbol_count} symbols across "
        f"{module_count} modules to {output_file}",
        file=sys.stderr,
    )


if __name__ == "__main__":
    main()