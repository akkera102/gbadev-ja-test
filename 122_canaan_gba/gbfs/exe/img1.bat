@echo off


rmdir /s /q img 2> nul
rmdir /s /q data 2> nul
mkdir img


rem ---------------------------------
rem gファイルをpiに変換
cd tmp
for %%f in (*.g) do python ..\..\exe\img\g_pi.py %%f %%~nf.pi
cd ..


rem ---------------------------------
rem piをpngに変換、imgフォルダに移動

..\exe\img\decomp.exe tmp\*.pi -out=png
move png\gfx\*.png img > nul


rem ---------------------------------
rem decomp.exeの作業フォルダとログ削除

rmdir /s /q data 2> nul
rmdir /s /q png 2> nul
del ..\exe\img\decomp.log 2> nul


rem ---------------------------------
rem 画像ファイル関連削除

del tmp\*.g 2> nul
del tmp\*.pi 2> nul


