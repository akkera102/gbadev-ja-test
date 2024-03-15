@echo off

for %%f in (*.songraw) do (
	python songraw_to_gpsg.py %%f
) 