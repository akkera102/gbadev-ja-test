@echo off

rem ---------------------------------
rem スクリプトファイルをデコード

for %%i in (*.SCF) do ..\scn2txt %%i

rem del *.SCF


rem ---------------------------------
rem 正規表現で変更

for %%i in (*.txt) do python ..\scn_re.py %%i


rem ---------------------------------
rem 空白と改行を'\0'に変更

for %%i in (*.txt) do ..\scn_term %%i

rem del *.txt


rem ---------------------------------
rem メッセージ命令変更

for %%i in (*.s01) do ..\scn_msg %%i

rem del *.s01


rem ---------------------------------
rem ジャンプテーブル変更

for %%i in (*.s02) do ..\scn_jump %%i

rem del *.s02


pause
_gbfs.bat
