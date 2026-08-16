#!/usr/bin/env bash
set -euo pipefail

ROOT="$HOME"
WINEPREFIX="$ROOT/.gmrwine"
export WINEPREFIX

WINE="${WINE:-wine}"

echo "Wine prefix: $WINEPREFIX"

if [[ ! -f "$WINEPREFIX/system.reg" ]]; then
    echo "Initializing 64-bit Wine prefix..."
    WINEARCH=win64 "$WINE" wineboot -u
fi

echo "Done."