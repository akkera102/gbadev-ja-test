@echo off

for %%f in (*.songraw) do (
	python songraws_to_gpsg.py %%f
) 
pause
