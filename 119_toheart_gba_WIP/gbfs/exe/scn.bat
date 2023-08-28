@echo off

rem ---------------------------------

for %%i in (*.scn) do (
    ..\exe\scn\th_scn %%i
)

del *.scn 2> nul
pause
