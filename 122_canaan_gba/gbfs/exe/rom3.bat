@echo off

rem ---------------------------------
copy /b ..\exe\test.gba+test1.gbfs ..\..\canaan1.gba
copy /b ..\exe\test.gba+test2.gbfs ..\..\canaan2.gba


rem ---------------------------------
rmdir img /s /q 2> nul
rmdir rom1 /s /q 2> nul
rmdir rom2 /s /q 2> nul
rmdir snd /s /q 2> nul
rmdir tmp /s /q 2> nul
rmdir txt /s /q 2> nul


