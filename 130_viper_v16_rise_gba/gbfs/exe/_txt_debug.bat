@echo off


cd tmp

rem ---------------------------------
rem �X�N���v�g�t�@�C�����f�R�[�h

for %%i in (*.WIN) do ..\..\exe\txt\win2txt %%i

rem del *.WIN

rem ---------------------------------
rem ���K�\���ŕύX

for %%i in (*.txt) do ..\..\exe\txt\txt_re.py %%i


rem ---------------------------------
rem �W�����v�e�[�u���ǉ��Ɖ��s��ύX

for %%i in (*.txt) do ..\..\exe\txt\addlbl %%i

del *.txt


rem ---------------------------------
cd ..

..\exe\rom\gbfs test.gbfs tmp\*.* ..\exe\rom\*.bin
copy /Y test.gbfs ..\..\src


