@echo off

rem ---------------------------------
..\exe\rom\gbfs ..\exe\rom\test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /b ..\exe\rom\test.gba+..\exe\rom\test.gbfs ..\..\shuumatsu.gba


rem ---------------------------------
rem rmdir tmp /s /q 2> nul


