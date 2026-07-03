@echo off

rem ---------------------------------
rem ファイル有無の確認


echo check BGM files...

if not exist AOZORA\BGM\BG_AI_NOT_FOUND.TCS goto err
if not exist AOZORA\BGM\BG_BAKED_CAKE.TCS goto err
if not exist AOZORA\BGM\BG_CAT_HOUSE.TCS goto err
if not exist AOZORA\BGM\BG_CAT_SPAWN.TCS goto err
if not exist AOZORA\BGM\BG_CRYING_TUZIO.TCS goto err
if not exist AOZORA\BGM\BG_DOTABATA.TCS goto err
if not exist AOZORA\BGM\BG_DOUKUTSU.TCS goto err
if not exist AOZORA\BGM\BG_DREAMED.TCS goto err
if not exist AOZORA\BGM\BG_ERIKO_TALK.TCS goto err
if not exist AOZORA\BGM\BG_FIRE.TCS goto err
if not exist AOZORA\BGM\BG_FUKKATSU.TCS goto err
if not exist AOZORA\BGM\BG_GAKKOU.TCS goto err
if not exist AOZORA\BGM\BG_IDO.TCS goto err
if not exist AOZORA\BGM\BG_ITAZURA.TCS goto err
if not exist AOZORA\BGM\BG_JOYFUL.TCS goto err
if not exist AOZORA\BGM\BG_KOKUHAKU.TCS goto err
if not exist AOZORA\BGM\BG_LAST_SEASON.TCS goto err
if not exist AOZORA\BGM\BG_MAFIA_PARTY.TCS goto err
if not exist AOZORA\BGM\BG_OMAKE.TCS goto err
if not exist AOZORA\BGM\BG_REQUIEM.TCS goto err
if not exist AOZORA\BGM\BG_RYOKOU.TCS goto err
if not exist AOZORA\BGM\BG_SAIDAN.TCS goto err
if not exist AOZORA\BGM\BG_SAIGA_ATTACK.TCS goto err
if not exist AOZORA\BGM\BG_SCENE6.TCS goto err
if not exist AOZORA\BGM\BG_SERIOUS.TCS goto err
if not exist AOZORA\BGM\BG_SINKOKU.TCS goto err
if not exist AOZORA\BGM\BG_SUMMER_MAJ.TCS goto err
if not exist AOZORA\BGM\BG_SUMMER_MIN.TCS goto err
if not exist AOZORA\BGM\BG_TITLE.TCS goto err
if not exist AOZORA\BGM\BG_TRANCE.TCS goto err
if not exist AOZORA\BGM\BG_TRANCE_HIDE.TCS goto err
if not exist AOZORA\BGM\BG_UMI_KOKUHAKU.TCS goto err
if not exist AOZORA\BGM\BG_UMI_THEME.TCS goto err

echo check SE files...

if not exist AOZORA\SE\SE_01.TCS goto err
if not exist AOZORA\SE\SE_02.TCS goto err
if not exist AOZORA\SE\SE_03.TCS goto err
if not exist AOZORA\SE\SE_04.TCS goto err
if not exist AOZORA\SE\SE_05.TCS goto err
if not exist AOZORA\SE\SE_06.TCS goto err
if not exist AOZORA\SE\SE_07.TCS goto err
if not exist AOZORA\SE\SE_08.TCS goto err
if not exist AOZORA\SE\SE_09.TCS goto err
if not exist AOZORA\SE\SE_10.TCS goto err
if not exist AOZORA\SE\SE_11.TCS goto err
if not exist AOZORA\SE\SE_12.TCS goto err
if not exist AOZORA\SE\SE_13.TCS goto err
if not exist AOZORA\SE\SE_14.TCS goto err
if not exist AOZORA\SE\SE_15.TCS goto err
if not exist AOZORA\SE\SE_16.TCS goto err
if not exist AOZORA\SE\SE_17.TCS goto err
if not exist AOZORA\SE\SE_18.TCS goto err
if not exist AOZORA\SE\SE_19.TCS goto err
if not exist AOZORA\SE\SE_20.TCS goto err
if not exist AOZORA\SE\SE_21.TCS goto err
if not exist AOZORA\SE\SE_22.TCS goto err
if not exist AOZORA\SE\SE_23.TCS goto err
if not exist AOZORA\SE\SE_24.TCS goto err
if not exist AOZORA\SE\SE_25.TCS goto err
if not exist AOZORA\SE\SE_26.TCS goto err
if not exist AOZORA\SE\SE_27.TCS goto err
if not exist AOZORA\SE\SE_28.TCS goto err
if not exist AOZORA\SE\SE_29.TCS goto err
if not exist AOZORA\SE\SE_30.TCS goto err
if not exist AOZORA\SE\SE_31.TCS goto err
if not exist AOZORA\SE\SE_32.TCS goto err
if not exist AOZORA\SE\SE_33.TCS goto err
if not exist AOZORA\SE\SE_34.TCS goto err
if not exist AOZORA\SE\SE_35.TCS goto err
if not exist AOZORA\SE\SE_36.TCS goto err
if not exist AOZORA\SE\SE_37.TCS goto err
if not exist AOZORA\SE\SE_38.TCS goto err
if not exist AOZORA\SE\SE_39.TCS goto err
if not exist AOZORA\SE\SE_40.TCS goto err
if not exist AOZORA\SE\SE_41.TCS goto err
if not exist AOZORA\SE\SE_42.TCS goto err
if not exist AOZORA\SE\SE_43.TCS goto err
if not exist AOZORA\SE\SE_44.TCS goto err
if not exist AOZORA\SE\SE_45.TCS goto err

echo check track_02.wav

if not exist AOZORA\track\track_02.wav goto err

echo check DATA.TCD

if not exist AOZORA\DATA.TCD goto err


rem ---------------------------------
exit /b 0

rem ---------------------------------
:err
exit /b 1
