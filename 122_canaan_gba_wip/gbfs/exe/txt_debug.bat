@echo off

cd txt


rem ---------------------------------
rem scnファイルをログ出力
for %%f in (*.scn) do ..\..\exe\txt\scn2log %%f


rem ---------------------------------
rem ログを正規表現テキスト出力
for %%f in (*.log) do python ..\..\exe\txt\log2txt.py %%f %%~nf.txt


rem ---------------------------------
rem 一部特殊フォントをバイナリ化
for %%f in (*.txt) do python ..\..\exe\txt\txt2txt.py %%f


rem del *.s 2>nul
rem del *.scn 2>nul
rem del *.log 2>nul

cd ..

rem ..\exe\rom\gbfs test1.gbfs rom1\*.img rom1\*.msk rom1\*.snd txt\*.txt ..\exe\rom\savid.bin
rem copy /Y test1.gbfs ..\..\src\test.gbfs

..\exe\rom\gbfs test2.gbfs rom2\*.img rom2\*.msk rom2\*.snd txt\*.txt ..\exe\rom\savid.bin
copy /Y test2.gbfs ..\..\src\test.gbfs
