@echo off

echo ---------------------------------
echo 　- 「夢幻夜想曲」 for GBA -
echo 　インストール　バッチ処理
echo ---------------------------------
pause

cd gbfs
cd data

rem ---------------------------------
call ..\exe\chk.bat
if %ERRORLEVEL% == 0 goto next

echo ※　指定されたファイルが違います。
echo 　　再度確認をお願いします。
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
echo 　　終了しました。
pause

rem ---------------------------------
:end
cd ..
cd ..
