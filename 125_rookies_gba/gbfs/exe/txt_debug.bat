@echo off


rem ---------------------------------
rem SCP�t�@�C��

copy PC98\1DAY_A.SCP tmp > nul
copy PC98\1DAY_B.SCP tmp > nul
copy PC98\2DAY_A.SCP tmp > nul
copy PC98\2DAY_B.SCP tmp > nul
copy PC98\3DAY_A.SCP tmp > nul
copy PC98\3DAY_B.SCP tmp > nul
copy PC98\3DAY_C.SCP tmp > nul
copy PC98\4BAD.SCP tmp > nul
copy PC98\4DAY_A.SCP tmp > nul
copy PC98\4DAY_B.SCP tmp > nul
copy PC98\4DAY_C.SCP tmp > nul
copy PC98\4DAY_D.SCP tmp > nul
copy PC98\5BAD_A.SCP tmp > nul
copy PC98\5BAD_B.SCP tmp > nul
copy PC98\5BAD_C.SCP tmp > nul
copy PC98\5BAD_D.SCP tmp > nul
copy PC98\5DAY_A.SCP tmp > nul
copy PC98\5DAY_B.SCP tmp > nul
copy PC98\5DAY_C.SCP tmp > nul
copy PC98\5DAY_D.SCP tmp > nul
copy PC98\6DAY.SCP tmp > nul
copy PC98\END.SCP tmp > nul
copy PC98\IPL.SCP tmp > nul
copy PC98\IPL2.SCP tmp > nul
copy PC98\OPENING.SCP tmp > nul
copy PC98\TAI.SCP tmp > nul


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


cd ..


..\exe\rom\gbfs test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /Y test.gbfs ..\..\src

