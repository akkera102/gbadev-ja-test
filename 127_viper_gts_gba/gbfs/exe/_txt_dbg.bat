@echo off


cd tmp

rem ---------------------------------
rem GBAで使わないスクリプトを削除
rem del GTSCG.WIN


rem ---------------------------------
rem スクリプトファイルをデコード

for %%i in (*.WIN) do ..\..\exe\txt\win2txt %%i

rem del *.WIN

rem ---------------------------------
rem 正規表現で変更

for %%i in (*.txt) do ..\..\exe\txt\txt_re.py %%i


rem ---------------------------------
rem ジャンプテーブル追加と改行を変更

for %%i in (*.txt) do ..\..\exe\txt\addlbl %%i

del *.txt


rem ---------------------------------
cd ..

..\exe\rom\gbfs test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /Y test.gbfs ..\..\src


