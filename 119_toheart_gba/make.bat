@echo off

echo ---------------------------------
echo �@- �uTo Heart�v Advance -
echo �@�C���X�g�[���@�o�b�`����
echo ---------------------------------
pause

cd gbfs
cd data

rem ---------------------------------
call ..\exe\chk.bat
if %ERRORLEVEL% == 0 goto next

echo ���@�w�肳�ꂽ�t�@�C�����Ⴂ�܂��B
echo �@�@�ēx�m�F�����肢���܂��B
pause
goto end

rem ---------------------------------
:next
call ..\exe\pak.bat
call ..\exe\dec.bat
call ..\exe\scn.bat
call ..\exe\snd.bat
call ..\exe\rom.bat

rem ---------------------------------
echo �@�@�I�����܂����B
pause

rem ---------------------------------
:end
cd ..