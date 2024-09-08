@echo off

rem cd tool/vgm2gba/
rem call _make_gpsg.bat
rem cd ../../

make quick

rem tool\\NanoBoyAdvance\\NanoBoyAdvance.exe _bin/test.gba
tool\\mGBA\\mGBA.exe _bin/test.gba