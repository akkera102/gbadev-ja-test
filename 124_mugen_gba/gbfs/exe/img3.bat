@echo off

cd img

rem ---------------------------------
rem ���T�C�Y
for %%i in (*.png) do python ..\..\exe\img\png_size.py %%i


rem ---------------------------------
rem �A���t�@�u�����h�摜���o�C�i���ɕύX
for %%i in (*_m.png) do python ..\..\exe\img\png_msk.py %%i

del *_m.png


rem ---------------------------------
rem GBA mode3�ɕϊ�
for %%i in (*.png) do (
    echo grit %%i
    ..\..\exe\img\grit %%i -gb -gB16 -ftb -gu16 -fh!
)

ren *.img.bin *.


rem ---------------------------------
rem �摜�@�p�����[�^�t�^
for %%i in (*.img) do (
    python ..\..\exe\img\png_para.py %%i
)

del *.png


cd ..
