@echo off

rem ---------------------------------
..\exe\rom\gbfs test1.gbfs rom1\*.img rom1\*.msk rom1\*.snd txt\*.txt ..\exe\rom\savid.bin
..\exe\rom\gbfs test2.gbfs rom2\*.img rom2\*.msk rom2\*.snd txt\*.txt ..\exe\rom\savid.bin


rem ---------------------------------
rem copy /b ..\exe\test.gba+test1.gbfs ..\..\canaan1.gba
rem copy /b ..\exe\test.gba+test1.gbfs ..\..\canaan2.gba


rem ---------------------------------
rem rmdir img /s /q 2> nul
rem rmdir rom1 /s /q 2> nul
rem rmdir rom2 /s /q 2> nul
rem rmdir snd /s /q 2> nul
rem rmdir tmp /s /q 2> nul
rem rmdir txt /s /q 2> nul

