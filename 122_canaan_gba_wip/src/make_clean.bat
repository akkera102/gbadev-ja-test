@echo off
set PATH=c:\devkitPro\msys2\usr\bin;C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

make clean
del test2_1.gba
del test2_2.gba
del *.sav
pause
