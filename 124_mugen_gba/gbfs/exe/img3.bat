@echo off

cd img

rem ---------------------------------
rem リサイズ
for %%i in (*.png) do python ..\..\exe\img\png_size.py %%i


rem ---------------------------------
rem アルファブレンド画像をバイナリに変更
for %%i in (*_m.png) do python ..\..\exe\img\png_msk.py %%i

del *_m.png


rem ---------------------------------
rem GBA mode3に変換
for %%i in (*.png) do (
    echo grit %%i
    ..\..\exe\img\grit %%i -gb -gB16 -ftb -gu16 -fh!
)

ren *.img.bin *.


rem ---------------------------------
rem 画像　パラメータ付与
for %%i in (*.img) do (
    python ..\..\exe\img\png_para.py %%i
)

del *.png


cd ..
