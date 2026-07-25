@echo off

rem ---------------------------------
..\exe\rom\gbfs ..\exe\rom\test.gbfs tmp\*.*
copy /b ..\exe\rom\test.gba+..\exe\rom\test.gbfs ..\..\dina_op.gba


rem ---------------------------------
rem rmdir tmp /s /q 2> nul


