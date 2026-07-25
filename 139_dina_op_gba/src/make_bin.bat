@echo off
set PATH=c:\devkitPro\msys2\usr\bin;C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

:loop
del test.gba
make
if exist test.gba goto run

:miss
pause
cls
goto loop

:run
if exist test.gbfs goto run2
test.gba
goto end

:run2
copy /b test.gba+test.gbfs test2.gba
gbafix.exe test2.gba -tTest -cTest


test2.gba


:end
pause
goto loop

