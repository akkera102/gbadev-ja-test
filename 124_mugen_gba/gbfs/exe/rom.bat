@echo off

rem ---------------------------------
..\exe\rom\gbfs test.gbfs img\*.img img\*.msk snd\*.snd txt\*.txt ..\exe\rom\*.bin
copy /b ..\exe\test.gba+test.gbfs ..\..\mugen.gba


rem ---------------------------------
rmdir img /s /q 2> nul
rmdir snd /s /q 2> nul
rmdir tmp /s /q 2> nul
rmdir txt /s /q 2> nul


