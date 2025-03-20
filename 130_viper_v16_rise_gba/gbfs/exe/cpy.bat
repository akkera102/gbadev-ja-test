@echo off

rem 使用するファイルを作業フォルダにコピーします

rmdir /s /q tmp 2> nul
mkdir tmp

rem ---------------------------------
copy SGS.DAT tmp > nul

