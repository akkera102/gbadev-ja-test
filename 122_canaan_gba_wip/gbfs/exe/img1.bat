@echo off


rmdir /s /q img 2> nul
rmdir /s /q data 2> nul
mkdir img


rem ---------------------------------
rem g�t�@�C����pi�ɕϊ�
cd tmp
for %%f in (*.g) do python ..\..\exe\img\g_pi.py %%f %%~nf.pi
cd ..


rem ---------------------------------
rem pi��png�ɕϊ��Aimg�t�H���_�Ɉړ�

..\exe\img\decomp.exe tmp\*.pi -out=png
move png\gfx\*.png img > nul


rem ---------------------------------
rem decomp.exe�̍�ƃt�H���_�ƃ��O�폜

rmdir /s /q data 2> nul
rmdir /s /q png 2> nul
del ..\exe\img\decomp.log 2> nul


rem ---------------------------------
rem �摜�t�@�C���֘A�폜

del tmp\*.g 2> nul
del tmp\*.pi 2> nul


