@echo off

cd tmp

rem ---------------------------------
rem wav�o��

for %%i in (*.PCM) do ..\..\exe\snd\pcm2wav %%i

del *.PCM

rem ---------------------------------
rem raw�o�́iGBA�p�j

for %%i in (*.wav) do (
    echo sox... %%i
    ..\..\exe\snd\sox %%i -V1 -c1 -r10512 -B -b8 -e signed-integer %%~ni.raw
)

del *.wav


cd ..
