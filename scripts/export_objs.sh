#!/usr/bin/env bash
set -u

CSV=""
EXE=""
OUT=""
PROJECT_DIR=""
PROJECT_NAME="Export Project"
GHIDRA_HOME=""
NO_ANALYZE=0

usage() {
  cat <<'EOF'
Usage:
  ./export_objs.sh --exe /path/to/game.exe --csv /path/to/mapping.csv [--out /path/to/output] [options]

Options:
  --exe <path>          Path to the EXE to import into Ghidra
  --csv <path>          CSV mapping of objects to Ghidra symbols
  --out <dir>           Optional output directory to create for compatibility
  --project-dir <dir>   Optional existing Ghidra project directory
  --project-name <name> Ghidra project name (default: Export Project)
  --ghidra-home <dir>   Path to the Ghidra installation root
  --no-analyze          Skip Ghidra auto-analysis during import
  -h, --help            Show this help
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --exe)
      EXE="$2"
      shift 2
      ;;
    --csv)
      CSV="$2"
      shift 2
      ;;
    --out)
      OUT="$2"
      shift 2
      ;;
    --project-dir)
      PROJECT_DIR="$2"
      shift 2
      ;;
    --project-name)
      PROJECT_NAME="$2"
      shift 2
      ;;
    --ghidra-home)
      GHIDRA_HOME="$2"
      shift 2
      ;;
    --no-analyze)
      NO_ANALYZE=1
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "error: unknown argument: $1" >&2
      usage >&2
      exit 1
      ;;
  esac
done

if [[ -z "$EXE" ]]; then
  echo "error: --exe is required" >&2
  usage >&2
  exit 1
fi

if [[ -z "$CSV" ]]; then
  echo "error: --csv is required" >&2
  usage >&2
  exit 1
fi

if [[ ! -f "$EXE" ]]; then
  echo "error: EXE does not exist: $EXE" >&2
  exit 1
fi

if [[ ! -f "$CSV" ]]; then
  echo "error: CSV does not exist: $CSV" >&2
  exit 1
fi

if [[ -z "$OUT" ]]; then
  OUT="$(dirname "$EXE")/out"
fi
mkdir -p "$OUT"

resolve_ghidra_bin() {
  if [[ -n "${GHIDRA_CLI_BIN:-}" ]]; then
    echo "$GHIDRA_CLI_BIN"
    return 0
  fi

  local roots=()
  if [[ -n "$GHIDRA_HOME" ]]; then
    roots+=("$GHIDRA_HOME" "$GHIDRA_HOME/libexec" "$(dirname "$GHIDRA_HOME")")
  fi

  for home in \
    /opt/homebrew/Cellar/ghidra \
    /usr/local/Cellar/ghidra \
    /opt/homebrew/opt/ghidra \
    /usr/local/opt/ghidra; do
    if [[ -d "$home" ]]; then
      roots+=("$home")
    fi
  done

  for root in "${roots[@]}"; do
    for candidate in \
      "$root/support/analyzeHeadless" \
      "$root/support/analyzeHeadless.bat" \
      "$root/libexec/support/analyzeHeadless" \
      "$root/libexec/support/analyzeHeadless.bat" \
      "$root/bin/analyzeHeadless" \
      "$root/bin/analyzeHeadless.bat"; do
      if [[ -f "$candidate" || -x "$candidate" ]]; then
        echo "$candidate"
        return 0
      fi
    done
  done

  for candidate in \
    /opt/homebrew/Cellar/ghidra/*/libexec/support/analyzeHeadless \
    /usr/local/Cellar/ghidra/*/libexec/support/analyzeHeadless \
    /opt/homebrew/Cellar/ghidra/*/support/analyzeHeadless \
    /usr/local/Cellar/ghidra/*/support/analyzeHeadless \
    /opt/homebrew/opt/ghidra/libexec/support/analyzeHeadless \
    /usr/local/opt/ghidra/libexec/support/analyzeHeadless; do
    if [[ -f "$candidate" || -x "$candidate" ]]; then
      echo "$candidate"
      return 0
    fi
  done

  for candidate in ghidra-analyzeHeadless analyzeHeadless; do
    if command -v "$candidate" >/dev/null 2>&1; then
      echo "$candidate"
      return 0
    fi
  done

  echo "error: could not find analyzeHeadless. Install Ghidra or set GHIDRA_HOME / GHIDRA_CLI_BIN to the analyzeHeadless path." >&2
  return 1
}

GHIDRA_BIN="$(resolve_ghidra_bin)" || exit 1

if [[ -z "$PROJECT_DIR" ]]; then
  PROJECT_DIR="$(pwd)/$(basename "$EXE" .exe)_ghidra"
fi
mkdir -p "$PROJECT_DIR"

PROJECT_FILE="$PROJECT_DIR/$PROJECT_NAME.gpr"

if [[ -f "$PROJECT_FILE" ]]; then
  echo "Using existing Ghidra project: $PROJECT_FILE"
  IMPORT_CMD=(
    "$GHIDRA_BIN"
    "$PROJECT_DIR"
    "$PROJECT_NAME"
    "-process"
    "$EXE"
    "-scriptPath"
    "$(dirname "$0")/ghidra"
    "-postScript"
    "ExportDelinker.java"
    "$CSV"
    "$OUT"
  )
else
  echo "Creating new Ghidra project: $PROJECT_FILE"

  IMPORT_CMD=(
    "$GHIDRA_BIN"
    "$PROJECT_DIR"
    "$PROJECT_NAME"
    "-import"
    "$EXE"
    "-scriptPath"
    "$(dirname "$0")/ghidra"
    "-postScript"
    "ExportDelinker.java"
    "$CSV"
    "$OUT"
  )
fi

echo "Running import:"
printf '%q ' "${IMPORT_CMD[@]}"
echo
"${IMPORT_CMD[@]}" || exit 1

echo "Import complete. Project: $PROJECT_DIR"
