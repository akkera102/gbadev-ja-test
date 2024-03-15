@echo off
set PATH=c:\devkitPro\msys2\usr\bin;C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

cd tool\vgm2gba\
call _make_gpsg.bat
cd ..\..\

make quick

_bin\test.gba
pause
