@echo off

if not exist DISK_A.CAT goto err
if not exist DISK_A.LIB goto err
if not exist DISK_B.CAT goto err
if not exist DISK_B.LIB goto err
if not exist DISK_C.CAT goto err
if not exist DISK_C.LIB goto err
if not exist DISK_D.CAT goto err
if not exist DISK_D.LIB goto err
if not exist DISK_E.CAT goto err
if not exist DISK_E.LIB goto err
if not exist DISK_F.CAT goto err
if not exist DISK_F.LIB goto err
if not exist DISK_G.CAT goto err
if not exist DISK_G.LIB goto err
if not exist DISK_H.CAT goto err
if not exist DISK_H.LIB goto err
if not exist DISK_I.CAT goto err
if not exist DISK_I.LIB goto err
if not exist DISK_J.CAT goto err
if not exist DISK_J.LIB goto err
if not exist DISK_K.CAT goto err
if not exist DISK_K.LIB goto err
if not exist DISK_L.CAT goto err
if not exist DISK_L.LIB goto err


rem ---------------------------------
exit /b 0

rem ---------------------------------
:err
exit /b 1


