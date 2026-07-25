@echo off

cd tmp

rem ---------------------------------
rem wav•ÏŠ·

..\..\exe\snd\st2wav DIN_OP00.ST2

del DIN_OP00.ST2


rem ---------------------------------
rem 8ad•ÏŠ·

..\..\exe\snd\sox DIN_OP00.wav -c1 -b16 tmp.wav rate -v 21024 norm -1
..\..\exe\snd\wav28ad tmp.wav DIN_OP00.8ad

del *.wav


cd ..
