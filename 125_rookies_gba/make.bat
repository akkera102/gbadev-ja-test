@echo off

echo ---------------------------------
echo �@- �uRookies�v for GBA -
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

call ..\exe\copy.bat
call ..\exe\img1.bat
call ..\exe\img2.bat
call ..\exe\txt.bat
call ..\exe\snd.bat
call ..\exe\rom.bat

rem ---------------------------------
echo �I�����܂����B
pause

rem ---------------------------------
:end
cd ..
cd ..
