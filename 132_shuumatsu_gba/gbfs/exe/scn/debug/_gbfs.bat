@echo off


cd ..\..\..\data\tmp

del SCN*.bin
copy ..\..\exe\scn\debug\*.bin .

cd ..

..\exe\rom\gbfs ..\exe\rom\test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /Y ..\exe\rom\test.gbfs ..\..\src

rem pause
