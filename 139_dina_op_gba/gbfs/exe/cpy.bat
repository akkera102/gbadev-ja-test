@echo off

rem ---------------------------------
rem ファイルを作業フォルダにコピー

rmdir /s /q tmp 2> nul
mkdir tmp

copy DIN_OP.DBL tmp > nul
copy DIN_OP00.ST2 tmp > nul
copy SPRING.GI tmp > nul
