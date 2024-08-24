@echo off

rem ---------------------------------
..\exe\rom\gbfs test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /b ..\exe\test.gba+test.gbfs ..\..\rookies.gba


rem ---------------------------------
rem rmdir tmp /s /q 2> nul


