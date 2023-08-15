@echo off

rem ---------------------------------

for %%i in (*.P16) do (
    ..\exe\snd\th_p16 %%i
    ..\exe\snd\sox %%~ni.wav -c 1 -r 16384 -B -b8 -e signed-integer %%~ni.raw
)

del *.P16 2> nul
del TH_VD*.WAV 2> nul
