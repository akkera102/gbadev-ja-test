@echo off

cd txt


rem ---------------------------------
rem scn�t�@�C�������O�o��
for %%f in (*.scn) do ..\..\exe\txt\scn2log %%f


rem ---------------------------------
rem ���O�𐳋K�\���e�L�X�g�o��
for %%f in (*.log) do python ..\..\exe\txt\log2txt.py %%f %%~nf.txt


rem ---------------------------------
rem �ꕔ����t�H���g���o�C�i����
for %%f in (*.txt) do python ..\..\exe\txt\txt2txt.py %%f

cd ..

rem call ..\exe\rom1.bat
rem copy /Y test1.gbfs ..\..\src\test1.gbfs

call ..\exe\rom2.bat
copy /Y test2.gbfs ..\..\src\test2.gbfs
