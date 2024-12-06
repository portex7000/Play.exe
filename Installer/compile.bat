windres installer.manifest -O coff -o manifest.res
windres installer.rc -O coff -o installer.res
gcc installer.c installer.res manifest.res -o installer.exe -mwindows