@echo off

for %%i in (*.WIN) do win2txt %%i
pause
for %%i in (*.txt) do txt_re.py %%i
rem for %%i in (*.txt) do addlbl %%i
