@echo off

cd txt


rem ---------------------------------
rem scnファイルをログ出力
for %%f in (0_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (1_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (2_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (3_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (4_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (5_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (6_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (7_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (8_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (9_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (a_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (b_*.scn) do ..\..\exe\txt\scn2log %%f
for %%f in (c_*.scn) do ..\..\exe\txt\scn2log %%f


rem ---------------------------------
rem 数字以外の文字を変更
move a_01b.log a_07.log > nul


rem ---------------------------------
rem ログを正規表現テキスト出力
for %%f in (*.log) do python ..\..\exe\txt\log2txt.py %%f %%~nf.txt

rmdir /s /q bak 2> nul
mkdir bak
copy *.txt bak > nul

rem ---------------------------------
rem 一部特殊フォントをバイナリ化
for %%f in (*.txt) do python ..\..\exe\txt\txt2txt.py %%f


rem ---------------------------------
cd ..
..\exe\rom\gbfs test.gbfs img\*.img img\*.msk snd\*.snd txt\*.txt ..\exe\rom\*.bin
copy /Y test.gbfs ..\..\src\test.gbfs
