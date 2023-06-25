@echo off

rem ---------------------------------

for %%i in (tr*.wav) do (
    ..\exe\snd\sox %%i -c 1 -r 10512 tmp.wav
    ..\exe\snd\wav28ad tmp.wav %%~ni.8ad
    del tmp.wav 2> nul
)

del decomp.wav 2> nul

rem ---------------------------------

for %%i in (*.P16) do (
    ..\exe\snd\th_p16 %%i
    ..\exe\snd\sox %%~ni.wav -c 1 -r 8192 -B -b8 -e signed-integer %%~ni.raw
    ..\exe\snd\padbin 4 %%~ni.raw
)

del *.P16 2> nul
del TH_VD*.WAV 2> nul
