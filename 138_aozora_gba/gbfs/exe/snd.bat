@echo off

cd tmp

rem ---------------------------------
rem wavïœä∑

for %%i in (*.TCS) do ..\..\exe\snd\tcs2wav %%i

del *.TCS


rem ---------------------------------
rem å¯â âπÇÕrawïœä∑

for %%i in (SE*.wav) do (
    echo sox... %%i
    ..\..\exe\snd\sox %%i -c1 -b8 -e signed-integer %%~ni.raw rate -v 13379
)

del SE*.wav


rem ---------------------------------
rem âπäyÇÕulc-codecïœä∑

for %%i in (*.wav) do (
    echo ulc... %%i
    ..\..\exe\snd\sox -D %%i -c1 -b16 tmp.wav rate -v 13379 norm -1
    ..\..\exe\snd\ulcencodetool tmp.wav %%~ni.ulc -87 -blocksize:256
    del tmp.wav
)

del *.wav


rem ---------------------------------
rem ÉäÉlÅ[ÉÄ

ren BG_AI_NOT_FOUND.ulc M001.ulc
ren BG_BAKED_CAKE.ulc M002.ulc
ren BG_CAT_HOUSE.ulc M003.ulc
ren BG_CAT_SPAWN.ulc M004.ulc
ren BG_CRYING_TUZIO.ulc M005.ulc
ren BG_DOTABATA.ulc M006.ulc
ren BG_DOUKUTSU.ulc M007.ulc
ren BG_DREAMED.ulc M008.ulc
ren BG_ERIKO_TALK.ulc M009.ulc
ren BG_FIRE.ulc M010.ulc
ren BG_FUKKATSU.ulc M011.ulc
ren BG_GAKKOU.ulc M012.ulc
ren BG_IDO.ulc M013.ulc
ren BG_ITAZURA.ulc M014.ulc
ren BG_JOYFUL.ulc M015.ulc
ren BG_KOKUHAKU.ulc M016.ulc
ren BG_LAST_SEASON.ulc M017.ulc
ren BG_MAFIA_PARTY.ulc M018.ulc
ren BG_OMAKE.ulc M019.ulc
ren BG_REQUIEM.ulc M020.ulc
ren BG_RYOKOU.ulc M021.ulc
ren BG_SAIDAN.ulc M022.ulc
ren BG_SAIGA_ATTACK.ulc M023.ulc
ren BG_SCENE6.ulc M024.ulc
ren BG_SERIOUS.ulc M025.ulc
ren BG_SINKOKU.ulc M026.ulc
ren BG_SUMMER_MAJ.ulc M027.ulc
ren BG_SUMMER_MIN.ulc M028.ulc
ren BG_TITLE.ulc M029.ulc
ren BG_TRANCE_HIDE.ulc M030.ulc
ren BG_TRANCE.ulc M031.ulc
ren BG_UMI_KOKUHAKU.ulc M032.ulc
ren BG_UMI_THEME.ulc M033.ulc
ren track_02.ulc M034.ulc

ren SE_01.raw S001.raw
ren SE_02.raw S002.raw
ren SE_03.raw S003.raw
ren SE_04.raw S004.raw
ren SE_05.raw S005.raw
ren SE_06.raw S006.raw
ren SE_07.raw S007.raw
ren SE_08.raw S008.raw
ren SE_09.raw S009.raw
ren SE_10.raw S010.raw
ren SE_11.raw S011.raw
ren SE_12.raw S012.raw
ren SE_13.raw S013.raw
ren SE_14.raw S014.raw
ren SE_15.raw S015.raw
ren SE_16.raw S016.raw
ren SE_17.raw S017.raw
ren SE_18.raw S018.raw
ren SE_19.raw S019.raw
ren SE_20.raw S020.raw
ren SE_21.raw S021.raw
ren SE_22.raw S022.raw
ren SE_23.raw S023.raw
ren SE_24.raw S024.raw
ren SE_25.raw S025.raw
ren SE_26.raw S026.raw
ren SE_27.raw S027.raw
ren SE_28.raw S028.raw
ren SE_29.raw S029.raw
ren SE_30.raw S030.raw
ren SE_31.raw S031.raw
ren SE_32.raw S032.raw
ren SE_33.raw S033.raw
ren SE_34.raw S034.raw
ren SE_35.raw S035.raw
ren SE_36.raw S036.raw
ren SE_37.raw S037.raw
ren SE_38.raw S038.raw
ren SE_39.raw S039.raw
ren SE_40.raw S040.raw
ren SE_41.raw S041.raw
ren SE_42.raw S042.raw
ren SE_43.raw S043.raw
ren SE_44.raw S044.raw
ren SE_45.raw S045.raw


cd ..
