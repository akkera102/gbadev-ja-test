@echo off

cd tmp

rem ---------------------------------
rem âπäy

..\..\exe\snd\adp2wav RADIO.adp
..\..\exe\snd\adp2wav RADIONZ.adp
del RADIO.adp
del RADIONZ.adp
rename RADIO.wav bgm03.wav
rename RADIONZ.wav bgm11.wav


rem ---------------------------------
rem å¯â âπ

for %%i in (*.adp) do ..\..\exe\snd\adp2wav %%i

del *.adp


rem ---------------------------------
rem å¯â âπÉäÉlÅ[ÉÄ

rename TIMEBELL.wav fmx00.wav
rename OD_M.wav fmx01.wav
rename OD_P.wav fmx02.wav
rename PAPER.wav fmx03.wav
rename SD_M.wav fmx04.wav
rename SD_P.wav fmx05.wav
rename IDO.wav fmx06.wav
rename DOM.wav fmx07.wav
rename OD_WO.wav fmx08.wav
rename OD_WC.wav fmx09.wav
rename PAPERBAG.wav fmx10.wav
rename OD_MO.wav fmx11.wav


rem ---------------------------------
rem rawïœä∑

for %%i in (*.wav) do (
    echo sox... %%i
    ..\..\exe\snd\sox %%i -c1 -r21024 -B -b8 -e signed-integer %%~ni.raw
)

ren *.raw *.bin
del *.wav

cd ..


