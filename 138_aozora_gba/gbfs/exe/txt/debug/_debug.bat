@echo off

del *.txt
del *.bin
del *.s01
del *.s02
del ..\..\..\data\tmp\*.txt

copy org\SC00.txt . > nul
copy org\SC01.txt . > nul
copy org\SC02.txt . > nul
copy org\SC03.txt . > nul
copy org\SC04.txt . > nul
copy org\SC05.txt . > nul
copy org\SC06.txt . > nul
copy org\SC07.txt . > nul

rem ---------------------------------
rem ラベル単位で切り出し

for %%i in (SC*.txt) do python ..\txt_cut.py %%i

del SC00.txt
del SC01.txt
del SC02.txt
del SC03.txt
del SC04.txt
del SC05.txt
del SC06.txt
del SC07.txt


rem ---------------------------------
rem 正規表現

for %%i in (tmp*.txt) do python ..\txt_re.py %%i

del tmp*.txt


rem ---------------------------------
rem 禁則文字、改ページ命令、IF文の逆ポーランド

for %%i in (*.txt) do python ..\txt_line.py %%i


rem ---------------------------------
rem メッセージにユニーク番号を付与

python ..\txt_mes.py


rem ---------------------------------
rem CRLF、SPACEを'\0'に変更

for %%i in (*.txt) do ..\txt_crlf %%i

rem del *.txt


rem ---------------------------------
rem 選択肢コマンドにオフセット付与

for %%i in (*.s01) do ..\txt_sel %%i

del *.s01


rem ---------------------------------
rem lz圧縮

for %%i in (*.s02) do (
    echo gbalzss... %%i
    ..\..\..\exe\img\gbalzss e %%i %%~ni.bin
)

rem del *.s02


del ..\..\..\data\tmp\*.bin
copy *.bin ..\..\..\data\tmp > nul


cd ..\..\..\data

..\exe\rom\gbfs ..\exe\rom\test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /Y ..\exe\rom\test.gbfs ..\..\src
