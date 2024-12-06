windres installer.rc -O coff -o installer.res
gcc installer.c installer.res -o installer.exe -mwindows