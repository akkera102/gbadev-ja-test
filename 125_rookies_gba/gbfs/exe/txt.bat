@echo off

cd tmp


rem ---------------------------------
rem �X�N���v�g�t�@�C�����f�R�[�h

for %%i in (*.SCP) do ..\..\exe\txt\scp2txt %%i

del *.scp

rem ---------------------------------
rem ���K�\���ɕύX

for %%i in (*.txt) do ..\..\exe\txt\txt_re.py %%i


rem ---------------------------------
rem �W�����v�e�[�u���ǉ��Ɖ��s��ύX

for %%i in (*.txt) do ..\..\exe\txt\addlbl %%i

del *.txt


cd ..
