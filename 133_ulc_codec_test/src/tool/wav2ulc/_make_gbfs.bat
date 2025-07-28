@echo off

set PATH=C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%


for %%i in (wav\*.wav) do (
    exe\ulcencodetool %%i %%~ni.ulc -90 -blocksize:256
)

gbfs ..\..\test.gbfs *.ulc


pause


rem 8ad 13379Hz
rem 2_23_AM.8ad 1281KB
rem Morning.8ad 1080KB
