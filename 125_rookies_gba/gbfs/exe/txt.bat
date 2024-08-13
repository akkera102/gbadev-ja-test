@echo off

cd tmp


rem ---------------------------------
rem スクリプトファイルをデコード

for %%i in (*.SCP) do ..\..\exe\txt\scp2txt %%i

del *.scp

rem ---------------------------------
rem 正規表現に変更

for %%i in (*.txt) do ..\..\exe\txt\txt_re.py %%i


rem ---------------------------------
rem ジャンプテーブル追加と改行を変更

for %%i in (*.txt) do ..\..\exe\txt\addlbl %%i

del *.txt


cd ..
