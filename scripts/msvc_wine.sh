#!/usr/bin/env bash
set -euo pipefail

ROOT="$HOME"
WINEPREFIX="$ROOT/.gmrwine"
export WINEPREFIX

WINE="${WINE:-wine}"

mkdir -p "$ROOT/downloads"

if [[ ! -f "$ROOT/downloads/vs_buildtools.exe" ]]; then
    echo "Downloading Visual Studio Build Tools..."
    curl -L \
        -o "$ROOT/downloads/vs_buildtools.exe" \
        'https://aka.ms/vs/17/release/vs_buildtools.exe'
fi

echo "Creating Visual Studio layout..."

"$WINE" "$ROOT/downloads/vs_buildtools.exe" \
    --installPath 'C:\msvc-layout' \
    --add Microsoft.VisualStudio.Component.VC.14.38.17.8.x86.x64 \
    --add Microsoft.VisualStudio.Component.VC.14.29.16.11.x86.x64 \
    --add Microsoft.VisualStudio.Component.Windows11SDK.22621

echo "Done."