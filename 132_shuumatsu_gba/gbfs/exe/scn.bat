@echo off

cd tmp


rem ---------------------------------
rem SCF�t�@�C�����폜

del SCN001.SCF
del SCN002.SCF
del SCN004.SCF
del SCN005.SCF
del SCN085.SCF
del SCN086.SCF


rem ---------------------------------
rem �X�N���v�g�t�@�C�����f�R�[�h

for %%i in (*.SCF) do ..\..\exe\scn\scn2txt %%i

del *.SCF


rem ---------------------------------
rem ���K�\���ŕύX

for %%i in (*.txt) do python ..\..\exe\scn\scn_re.py %%i


rem ---------------------------------
rem �󔒂Ɖ��s��'\0'�ɕύX

for %%i in (*.txt) do ..\..\exe\scn\scn_term %%i

del *.txt


rem ---------------------------------
rem ���b�Z�[�W���ߕύX

for %%i in (*.s01) do ..\..\exe\scn\scn_msg %%i

del *.s01


rem ---------------------------------
rem �W�����v�e�[�u���ύX

for %%i in (*.s02) do ..\..\exe\scn\scn_jump %%i

del *.s02


cd ..
