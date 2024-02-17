@echo off

cd img

rem ---------------------------------
rem リサイズ
pause
for %%i in (*.png) do python ..\..\exe\img\png_size.py %%i
pause

rem ---------------------------------
rem アルファブレンド画像をバイナリに変更
for %%i in (*_m.png) do python ..\..\exe\img\png_bin.py %%i

del *_m.png


rem ---------------------------------
rem アルファブレンド　LZ77
for %%i in (*.bin) do (
    echo gbalzss %%i
    ..\..\exe\img\gbalzss e %%i %%~ni.msk
)

del *.bin


rem ---------------------------------
rem GBA mode3に変換
for %%i in (*.png) do (
    echo grit %%i
    ..\..\exe\img\grit %%i -gb -gB16 -ftb -gu16 -fh!
)


rem ---------------------------------
rem LZ77しない画像をリネーム
rename bg12.img.bin bg12.img
rename e020.img.bin e020.img
rename e029.img.bin e029.img
rename e29b.img.bin e29b.img
rename e033.img.bin e033.img
rename e050.img.bin e050.img
rename s034.img.bin s034.img

rem LZ77しないフリップをリネーム
rename pata00.img.bin pata00.img
rename pata01.img.bin pata01.img
rename pata02.img.bin pata02.img
rename pata03.img.bin pata03.img
rename pata05.img.bin pata05.img
rename pata06.img.bin pata06.img
rename pata07.img.bin pata07.img
rename pata08.img.bin pata08.img
rename pata09.img.bin pata09.img
rename pata10.img.bin pata10.img
rename pata11.img.bin pata11.img
rename pata13.img.bin pata13.img
rename pata14.img.bin pata14.img
rename pata15.img.bin pata15.img
rename pata16.img.bin pata16.img
rename pata17.img.bin pata17.img
rename pata18.img.bin pata18.img
rename pata19.img.bin pata19.img
rename pata20.img.bin pata20.img

rem LZ77しない背景画像をリネーム
copy waku06b.img.bin waku.img > nul
copy waku06b.png waku.png > nul


rem ---------------------------------
rem 画像　LZ77
for %%i in (*.img.bin) do (
    echo gbalzss %%i
    ..\..\exe\img\gbalzss e %%i %%~ni
)

del *.img.bin


rem ---------------------------------
rem 画像　パラメータ付与
for %%i in (*.img) do (
    python ..\..\exe\img\png_para.py %%i
)

del *.png


cd ..
