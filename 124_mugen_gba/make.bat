@echo off

echo ---------------------------------
echo �@- �u������z�ȁv for GBA -
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

call ..\exe\lib.bat
call ..\exe\img1.bat
call ..\exe\img2.bat
call ..\exe\img3.bat
call ..\exe\txt.bat
call ..\exe\snd.bat
call ..\exe\rom.bat

rem ---------------------------------
echo �@�@�I�����܂����B
pause

rem ---------------------------------
:end
cd ..
cd ..
