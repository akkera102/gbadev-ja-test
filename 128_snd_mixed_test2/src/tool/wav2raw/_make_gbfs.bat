@echo off

rem for %%i in (*.wav) do (
rem     echo sox... %%i
rem     sox %%i -c1 -r13379 -B -b8 -e signed-integer %%~ni.raw
rem )



sox music_challenge_intro.wav -c1 -r13379 -B -b8 -e signed-integer 0.raw
sox se_boss_destroy_explode.wav -c1 -r13379 -B -b8 -e signed-integer 1.raw
sox se_explode_boss_shield.wav -c1 -r13379 -B -b8 -e signed-integer 2.raw  fade 0 0.8 0.1
sox se_explode_self.wav -c1 -r13379 -B -b8 -e signed-integer 3.raw fade 0 0.8 0.1
sox se_menu_cancel.wav -c1 -r13379 -B -b8 -e signed-integer 4.raw fade 0 0.2 0.1
sox se_menu_changepage.wav -c1 -r13379 -B -b8 -e signed-integer 5.raw trim 0 0.1
sox se_menu_click.wav -c1 -r13379 -B -b8 -e signed-integer 6.raw
sox se_menu_select.wav -c1 -r13379 -B -b8 -e signed-integer 7.raw


set PATH=C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%
gbfs ..\..\test.gbfs *.raw


pause
