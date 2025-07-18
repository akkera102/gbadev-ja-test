@echo off

cd tmp

rem ---------------------------------
rem 一部KGファイルを削除

del CGMODEA.KG
del CGMODEB.KG
del CHIEJG00.KG
del CHIEJG01.KG
del CHIEJG02.KG
del CHIEJG03.KG
del CHIEJG04.KG
del CHIEJG05.KG
del CHIHIG00.KG
del CHIHIG01.KG
del CHIHIG02.KG
del CHIHIG03.KG
del CHIHIG04.KG
del CHIHIR03.KG
del CHIHIR04.KG
del IROHA02.KG
del IROHA04.KG
del KANA02.KG
del KAORI02.KG
del KAORI05.KG
del MACHI.KG
del MSMODE.KG
del PCLICK.KG
del TAHIGG00.KG
del TAHIGG01.KG
del TAHIGG02.KG
del TAHIGG03.KG
del TAHIGG04.KG
del TAHIGG05.KG
del TAHIRO05.KG


rem ---------------------------------
rem KGをBMPに変換

for %%i in (*.KG) do ..\..\exe\img\kg2bmp %%i

del *.KG


rem ---------------------------------
rem キャラクタのマスクデータ作成

..\..\exe\img\bmp2msk CHIEKO00.bmp
..\..\exe\img\bmp2msk CHIHIR00.bmp
..\..\exe\img\bmp2msk IROHA00.bmp
..\..\exe\img\bmp2msk KANA00.bmp
..\..\exe\img\bmp2msk KAORI00.bmp
..\..\exe\img\bmp2msk MIDORI00.bmp
..\..\exe\img\bmp2msk RUKI00.bmp
..\..\exe\img\bmp2msk SHIGE00.bmp
..\..\exe\img\bmp2msk TAHIRO00.bmp


rem ---------------------------------
rem ロゴを切り取り保存
python ..\..\exe\img\img_logo.py LOGO1.bmp
python ..\..\exe\img\img_logo.py LOGO2.bmp

del LOGO1.bmp
del LOGO2.bmp


rem ---------------------------------
rem タイトルのブレンド合成を生成
python ..\..\exe\img\img_titl.py

del TITLE1.bmp
del TITLE2.bmp


rem ---------------------------------
rem 曜日文字の拡大保存

python ..\..\exe\img\img_day.py MON.bmp
python ..\..\exe\img\img_day.py TUE.bmp
python ..\..\exe\img\img_day.py WED.bmp
python ..\..\exe\img\img_day.py THU.bmp
python ..\..\exe\img\img_day.py FRI.bmp
python ..\..\exe\img\img_day.py SAT.bmp
python ..\..\exe\img\img_day.py END.bmp

del MON.bmp
del TUE.bmp
del WED.bmp
del THU.bmp
del FRI.bmp
del SAT.bmp
del END.bmp


rem ---------------------------------
rem リサイズ

for %%i in (*.bmp) do python ..\..\exe\img\img_size.py %%i

del *.bmp


rem ---------------------------------
rem キャラクタの余白をカットして保存＋マスクファイルを生成

for %%i in (*_m.png) do python ..\..\exe\img\img_chr.py %%i

del *_m.png


rem ---------------------------------
rem GBA(mode3)に変換

for %%i in (*.png) do (
    echo grit... %%i
    ..\..\exe\img\grit %%i -gb -gB16 -ftb -gu16 -fh!
)

ren *.img.bin *.


rem ---------------------------------
rem 画像にパラメータを付与

for %%i in (*.img) do python ..\..\exe\img\img_para.py %%i

del *.png


rem ---------------------------------
rem リネーム（重複：17と136、15と140　未使用：133　移動：3→991）

rename logo1.img img000.bin
rename logo2.img img001.bin
rename black.img img002.bin
rename eds.img img004.bin
rename eds1.img img005.bin
rename mon.img img006.bin
rename back8.img img007.bin
rename back1.img img008.bin
rename jugyochi.img img009.bin
rename jugyokao.img img010.bin
rename sora.img img011.bin
rename okuiro.img img012.bin
rename okukana.img img013.bin
rename grochie.img img014.bin
rename groshige.img img015.bin
rename hokeruki.img img016.bin
rename midohon.img img017.bin
rename topfont.img img018.bin
rename kaori00.img img019.bin
rename kaori01.img img020.bin
rename kaori03.img img021.bin
rename midori00.img img022.bin
rename midori02.img img023.bin
rename chihir02.img img024.bin
rename midori03.img img025.bin
rename chihir01.img img026.bin
rename chihir00.img img027.bin
rename back7.img img028.bin
rename back4.img img029.bin
rename ruki00.img img030.bin
rename tahiro00.img img031.bin
rename tahiro02.img img032.bin
rename ruki01.img img033.bin
rename ruki02.img img034.bin
rename tahiro01.img img035.bin
rename back3.img img036.bin
rename back5.img img037.bin
rename midori04.img img038.bin
rename back9.img img039.bin
rename shige00.img img040.bin
rename chieko04.img img041.bin
rename shige01.img img042.bin
rename chieko01.img img043.bin
rename chieko00.img img044.bin
rename chieko05.img img045.bin
rename back2.img img046.bin
rename back6.img img047.bin
rename furiiro.img img048.bin
rename iroha00.img img049.bin
rename iroha01.img img050.bin
rename iroha03.img img051.bin
rename kana01.img img052.bin
rename kana03.img img053.bin
rename kokeruki.img img054.bin
rename tue.img img055.bin
rename cbbefore.img img056.bin
rename kaori04.img img057.bin
rename seitoh1.img img058.bin
rename cbafter.img img059.bin
rename midori01.img img060.bin
rename kanairo.img img061.bin
rename musatwo.img img062.bin
rename chieko03.img img063.bin
rename shige03.img img064.bin
rename shige04.img img065.bin
rename wed.img img066.bin
rename chiemogu.img img067.bin
rename madokao.img img068.bin
rename domkana.img img069.bin
rename tahiro04.img img070.bin
rename tahiro03.img img071.bin
rename ruki03.img img072.bin
rename ruki04.img img073.bin
rename rukigyu.img img074.bin
rename yubiiro.img img075.bin
rename rukih1.img img076.bin
rename rukih2.img img077.bin
rename rukih3.img img078.bin
rename rukih4.img img079.bin
rename thu.img img080.bin
rename terekao.img img081.bin
rename madomi2.img img082.bin
rename madomi1.img img083.bin
rename irhhossa.img img084.bin
rename kmiorosi.img img085.bin
rename kana00.img img086.bin
rename seitoh2.img img087.bin
rename shige02.img img088.bin
rename kouen.img img089.bin
rename chieh1.img img090.bin
rename chieh2.img img091.bin
rename chieh3.img img092.bin
rename chieh4.img img093.bin
rename chiekiss.img img094.bin
rename fri.img img095.bin
rename chieko02.img img096.bin
rename midomega.img img097.bin
rename kagiiro.img img098.bin
rename sckaiwa.img img099.bin
rename onbuchie.img img100.bin
rename kaoh1.img img101.bin
rename kaoh2.img img102.bin
rename kaoh3.img img103.bin
rename kaoh4.img img104.bin
rename kaoh4b.img img105.bin
rename kaokiss.img img106.bin
rename hizakao.img img107.bin
rename midokiss.img img108.bin
rename midoh1.img img109.bin
rename midoh2.img img110.bin
rename midoh3.img img111.bin
rename midoh4.img img112.bin
rename iroh1.img img113.bin
rename iroh2.img img114.bin
rename iroh3.img img115.bin
rename iroh4.img img116.bin
rename irokiss.img img117.bin
rename kanah1.img img118.bin
rename kanah2.img img119.bin
rename kanah3.img img120.bin
rename kanah4.img img121.bin
rename kanakiss.img img122.bin
rename sat.img img123.bin
rename rkheiwa.img img124.bin
rename chiekako.img img125.bin
rename scchie.img img126.bin
rename furikor.img img127.bin
rename midomio.img img128.bin
rename midori05.img img129.bin
rename kana04.img img130.bin
rename kana05.img img131.bin
rename rocketkn.img img132.bin
rename ksmode.img img134.bin
rename end.img img135.bin
rename kurakor.img img137.bin
rename badirh.img img138.bin
rename kurakana.img img139.bin
rename rukikiss.img img141.bin
rename kurarkth.img img142.bin
rename happykor.img img143.bin
rename happymdr.img img144.bin
rename happyirh.img img145.bin
rename kcyozora.img img146.bin

rename img900.img img900.bin
rename img901.img img901.bin
rename img902.img img902.bin
rename img903.img img903.bin
rename img904.img img904.bin
rename img905.img img905.bin
rename img906.img img906.bin
rename img907.img img907.bin
rename img908.img img908.bin
rename img909.img img909.bin
rename img910.img img910.bin
rename img911.img img911.bin
rename img912.img img912.bin
rename img913.img img913.bin
rename img914.img img914.bin
rename img915.img img915.bin
rename img916.img img916.bin
rename img917.img img917.bin
rename img918.img img918.bin
rename img919.img img919.bin
rename img920.img img920.bin
rename img921.img img921.bin
rename img922.img img922.bin
rename img923.img img923.bin
rename img924.img img924.bin
rename img925.img img925.bin
rename img926.img img926.bin
rename img927.img img927.bin
rename img928.img img928.bin
rename img929.img img929.bin
rename img930.img img930.bin
rename img931.img img931.bin
rename img932.img img932.bin
rename TITLE3.img img990.bin
rename TITLEX.img img991.bin

rename CHIEKO0.msk msk00.bin
rename CHIHIR0.msk msk01.bin
rename IROHA0.msk msk02.bin
rename KANA0.msk msk03.bin
rename KAORI0.msk msk04.bin
rename MIDORI0.msk msk05.bin
rename RUKI0.msk msk06.bin
rename SHIGE0.msk msk07.bin
rename TAHIRO0.msk msk08.bin

cd ..


