@echo off

cd tmp

rem ---------------------------------
rem wav�o��

for %%i in (*.m) do ..\..\exe\snd\pmdplay %%i %%~ni.wav


rem ---------------------------------
rem 8ad�o�́iGBA�p�j

for %%i in (*.wav) do (
    ..\..\exe\snd\sox %%i -c1 -r13379 tmp.wav
    ..\..\exe\snd\wav28ad tmp.wav %%~ni.snd
    del tmp.wav 2> nul
    del decomp.wav 2> nul
)


del *.wav
del *.m

cd ..
