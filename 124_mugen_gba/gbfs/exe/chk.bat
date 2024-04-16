@echo off

if not exist DISK_A.CAT goto err
if not exist DISK_A.LIB goto err
if not exist DISK_B.CAT goto err
if not exist DISK_B.LIB goto err
if not exist DISK_C.CAT goto err
if not exist DISK_C.LIB goto err
if not exist DISK_D.CAT goto err
if not exist DISK_D.LIB goto err


rem ---------------------------------
exit /b 0

rem ---------------------------------
:err
exit /b 1


