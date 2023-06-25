@echo off

rem ---------------------------------
..\exe\rom\gbfs test.gbfs *.img *.raw *.8ad *.txt

del *.img 2> nul
del *.raw 2> nul
del *.8ad 2> nul
del *.txt 2> nul

rem ---------------------------------
copy /b ..\exe\Test.gba+test.gbfs ..\..\toheart.gba
rem del test.gbfs 2> nul
