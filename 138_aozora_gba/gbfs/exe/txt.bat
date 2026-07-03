@echo off

cd tmp


rem ---------------------------------
rem 未使用ファイルの削除

del *.TSF


rem ---------------------------------
rem スクリプトファイルをデコード

for %%i in (*.TCT) do ..\..\exe\txt\tct2txt %%i

del *.TCT


rem ---------------------------------
rem 初回版をメモリアル版にアップデート

python ..\..\exe\txt\txt_ver.py SC00.txt
python ..\..\exe\txt\txt_ver.py SC01.txt
python ..\..\exe\txt\txt_ver.py SC05.txt


rem ---------------------------------
rem ラベル単位で切り出し

for %%i in (SC*.txt) do python ..\..\exe\txt\txt_cut.py %%i

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

for %%i in (tmp*.txt) do python ..\..\exe\txt\txt_re.py %%i

del tmp*.txt


rem ---------------------------------
rem 禁則文字、改ページ命令、IF文の逆ポーランド

for %%i in (*.txt) do python ..\..\exe\txt\txt_line.py %%i


rem ---------------------------------
rem メッセージにユニーク番号を付与

python ..\..\exe\txt\txt_mes.py


rem ---------------------------------
rem CRLF、SPACEを'\0'に変換

for %%i in (*.txt) do ..\..\exe\txt\txt_crlf %%i

del *.txt


rem ---------------------------------
rem 選択肢コマンドにオフセット付与

for %%i in (*.s01) do ..\..\exe\txt\txt_sel %%i

del *.s01


rem ---------------------------------
rem lz圧縮

for %%i in (*.s02) do (
    echo gbalzss... %%i
    ..\..\exe\img\gbalzss e %%i %%~ni.bin
)

del *.s02


cd ..
