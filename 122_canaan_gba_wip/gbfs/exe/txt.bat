@echo off

rmdir /s /q txt 2> nul
mkdir txt
move tmp\*.s txt > nul

rem ---------------------------------
rem lsp�t�@�C���i�G�t�F�N�g�t�@�C���H�j���폜
cd tmp
del *.lsp 2> nul
cd ..

rem ---------------------------------
cd txt

del cannan.s 2> nul
del config.s 2> nul
del ending.s 2> nul
del nchan.s 2> nul
del nsel.s 2> nul
del omoide.s 2> nul
del open.s 2> nul
del prolog.s 2> nul
del ss.s 2> nul
del staff.s 2> nul
del wakuwaku.s 2> nul
del prologue.s 2> nul


rem ---------------------------------
rem s�t�@�C�����f�R�[�h
for %%f in (*.s) do python ..\..\exe\txt\s2scn.py %%f %%fcn

rem �ꕔ�X�N���v�g�̕ʃR�s�[���쐬
copy cs05_13.scn cs05_40.scn 2> nul
copy cs22_11.scn cs22_19.scn 2> nul
copy cs22_15.scn cs22_20.scn 2> nul
copy cs22_10.scn cs22_21.scn 2> nul


rem ---------------------------------
rem scn�t�@�C�������O�o��
for %%f in (*.scn) do ..\..\exe\txt\scn2log %%f


rem ---------------------------------
rem �I�[�v�j���O�̒ǉ���
copy ..\..\exe\rom\cs00_01.log . 2> nul


rem ---------------------------------
rem ���O�𐳋K�\���e�L�X�g�o��
for %%f in (*.log) do python ..\..\exe\txt\log2txt.py %%f %%~nf.txt


rem ---------------------------------
rem �ꕔ����t�H���g���o�C�i����
for %%f in (*.txt) do python ..\..\exe\txt\txt2txt.py %%f


del *.s 2> nul
del *.scn 2>nul
del *.log 2>nul

cd ..
