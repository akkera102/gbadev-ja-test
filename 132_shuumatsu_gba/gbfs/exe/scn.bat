@echo off

cd tmp


rem ---------------------------------
rem SCFファイルを削除

del SCN001.SCF
del SCN002.SCF
del SCN004.SCF
del SCN005.SCF
del SCN085.SCF
del SCN086.SCF


rem ---------------------------------
rem スクリプトファイルをデコード

for %%i in (*.SCF) do ..\..\exe\scn\scn2txt %%i

del *.SCF


rem ---------------------------------
rem 正規表現で変更

for %%i in (*.txt) do python ..\..\exe\scn\scn_re.py %%i


rem ---------------------------------
rem 空白と改行を'\0'に変更

for %%i in (*.txt) do ..\..\exe\scn\scn_term %%i

del *.txt


rem ---------------------------------
rem メッセージ命令変更

for %%i in (*.s01) do ..\..\exe\scn\scn_msg %%i

del *.s01


rem ---------------------------------
rem ジャンプテーブル変更

for %%i in (*.s02) do ..\..\exe\scn\scn_jump %%i

del *.s02


cd ..
