@echo off

rem ---------------------------------
rem �X�N���v�g�t�@�C�����f�R�[�h

for %%i in (*.SCF) do ..\scn2txt %%i

rem del *.SCF


rem ---------------------------------
rem ���K�\���ŕύX

for %%i in (*.txt) do python ..\scn_re.py %%i


rem ---------------------------------
rem �󔒂Ɖ��s��'\0'�ɕύX

for %%i in (*.txt) do ..\scn_term %%i

rem del *.txt


rem ---------------------------------
rem ���b�Z�[�W���ߕύX

for %%i in (*.s01) do ..\scn_msg %%i

rem del *.s01


rem ---------------------------------
rem �W�����v�e�[�u���ύX

for %%i in (*.s02) do ..\scn_jump %%i

rem del *.s02


pause
_gbfs.bat
