@echo off

rem ---------------------------------
..\exe\rom\gbfs test.gbfs *.img *.raw *.txt ..\exe\snd\bin\*.bin

del *.img 2> nul
del *.raw 2> nul
del *.txt 2> nul

rem ---------------------------------
copy /b ..\exe\test.gba+test.gbfs ..\..\toheart.gba
rem del test.gbfs 2> nul
