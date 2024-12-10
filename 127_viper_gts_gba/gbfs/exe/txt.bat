@echo off

cd tmp


rem ---------------------------------
rem GBAで使わないスクリプトを削除
del GTSCG.WIN


rem ---------------------------------
rem スクリプトファイルをデコード

for %%i in (*.WIN) do ..\..\exe\txt\win2txt %%i

del *.WIN

rem ---------------------------------
rem 正規表現で変更

for %%i in (*.txt) do ..\..\exe\txt\txt_re.py %%i


rem ---------------------------------
rem ジャンプテーブル追加と改行を変更

for %%i in (*.txt) do ..\..\exe\txt\addlbl %%i

del *.txt


cd ..
