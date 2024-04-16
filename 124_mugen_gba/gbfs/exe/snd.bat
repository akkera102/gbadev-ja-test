@echo off

rmdir /s /q snd 2> nul
mkdir snd
move tmp\b*.m snd > nul
cd snd


rem ---------------------------------
rem wav出力
for %%i in (*.m) do ..\..\exe\snd\pmdplay %%i %%~ni.wav


rem ---------------------------------
rem 8ad出力（GBA用）
for %%i in (*.wav) do (
    ..\..\exe\snd\sox %%i -c1 -r18157 tmp.wav
    ..\..\exe\snd\wav28ad tmp.wav %%~ni.snd
    del tmp.wav 2> nul
    del decomp.wav 2> nul
)


del *.wav 2>nul
del *.m 2>nul


cd ..
