@echo off

rem ---------------------------------
..\exe\rom\gbfs test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /b ..\exe\rom\test.gba+test.gbfs ..\..\viper_v16_rise.gba


rem ---------------------------------
rem rmdir tmp /s /q 2> nul


