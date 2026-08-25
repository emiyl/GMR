# Windows-x64-VM-Green-2024.14.4.268-c66887b7abbc804a75824c567cab4486906f298d

Compile using MSVC 19.38.33145.0 and Linker 14.29.30159.0. The PDB suggest it was compiled with SDK 10.0.26100.0, but it was also released on April 14th, 2024, which predates that SDK. So we're using 22621 instead here.

## Libraries

- libpng (unknown version)
- libzip (unknown version)
- freetype 2.8
- giflib (unknown version)
- imgui (unknown version, maybe v1.90.4)
- libjpeg (unknown version)
- spine-c (unknown version)
- zlib 1.2.3

## Building

Building won't work right now as I'm reworking the structure a bit.

You can install this with the command below. Ensure the MSVC directory exists first.

```pwsh
.\vs_buildtools.exe `
    --installPath 'C:\MSVC' `
    --add Microsoft.VisualStudio.Component.VC.14.38.17.8.x86.x64 `
    --add Microsoft.VisualStudio.Component.VC.14.29.16.11.x86.x64 `
    --add Microsoft.VisualStudio.Component.Windows11SDK.22621
```

I have a Wine script that can be used to init a prefix in the scripts folder, but no script to install the build tools. You can run the command above in Wine but I ran into a dotnet issue I couldn't be bothered to read so I just ran it in my VM and copied over the files.

Run `./scripts/export_objs.sh --exe Runner.exe --csv obj.csv --out target` to export the object files. Currently this script only targets macOS. You need Ghidra installed.

```bash
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="$PWD/scripts/wine-msvc.cmake"
cmake --build build
```