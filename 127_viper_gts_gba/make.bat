@echo off

echo ---------------------------------
echo �@- �uViper GTS�v for GBA -
echo �@�C���X�g�[���@�o�b�`����
echo ---------------------------------

cd gbfs
cd data

rem ---------------------------------
call ..\exe\chk.bat
if %ERRORLEVEL% == 0 goto next

echo ���@�w�肳�ꂽ�t�@�C���܂��̓t�H���_���Ⴂ�܂��B�ēx�m�F�����肢���܂��B
pause
goto end

rem ---------------------------------
:next

echo �Q�[���f�[�^�̊m�F���ł��܂����B�C���X�g�[���𑱍s���܂��B
pause

call ..\exe\cpy.bat
call ..\exe\pak.bat
call ..\exe\img.bat
call ..\exe\snd.bat
call ..\exe\txt.bat
call ..\exe\rom.bat

rem ---------------------------------
echo �I�����܂����B
pause

rem ---------------------------------
:end
cd ..
cd ..
