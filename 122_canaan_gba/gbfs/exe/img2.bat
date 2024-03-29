@echo off

rem ---------------------------------
rem 2画面用画像の修正と結合

cd img

rem 修正（乱れ表示）
python ..\..\exe\img\png_sepa.py bg12h.png
python ..\..\exe\img\png_sepa.py bg12l.png
python ..\..\exe\img\png_sepa.py e020h.png
python ..\..\exe\img\png_sepa.py e020l.png
python ..\..\exe\img\png_sepa.py e029h.png
python ..\..\exe\img\png_sepa.py e029l.png
python ..\..\exe\img\png_sepa.py e29bh.png
python ..\..\exe\img\png_sepa.py e29bl.png
python ..\..\exe\img\png_sepa.py e033h.png
python ..\..\exe\img\png_sepa.py e033l.png
python ..\..\exe\img\png_sepa.py e050h.png
python ..\..\exe\img\png_sepa.py e050l.png
python ..\..\exe\img\png_sepa.py s034h.png
python ..\..\exe\img\png_sepa.py s034l.png

rem 結合
python ..\..\exe\img\png_comb.py bg12
python ..\..\exe\img\png_comb.py e020
python ..\..\exe\img\png_comb.py e029
python ..\..\exe\img\png_comb.py e29b
python ..\..\exe\img\png_comb.py e033
python ..\..\exe\img\png_comb.py e050
python ..\..\exe\img\png_comb.py s034

del bg12h.png
del bg12l.png
del e020h.png
del e020l.png
del e029h.png
del e029l.png
del e29bh.png
del e29bl.png
del e033h.png
del e033l.png
del e050h.png
del e050l.png
del s034h.png
del s034l.png
del en04h.png
del en04l.png

rem 不要ファイルを消去
del s028h.png
del s028l.png
del s030h.png
del s030l.png
del s040h.png
del s040l.png


rem ---------------------------------
rem 不要ファイルを消去

rem アイコンの肉表示
del alphff.png
del anglff.png
del bee_ff.png
del biatff.png
del blueff.png
del dianff.png
del doraff.png
del elzaff.png
del far_ff.png
del iriaff.png
del kaitff.png
del kineff.png
del kyasff.png
del leonff.png
del liliff.png
del mie_ff.png
del minaff.png
del miraff.png
del neesff.png
del rabyff.png
del resiff.png
del roseff.png
del ruriff.png
del titiff.png
del wolfff.png
del xtraff.png

rem 画面エフェクト用
del black.png
del blackf.png
del blackf0.png
del light.png

rem オープニングのスクショ文章
del can01z.png
del can02z.png
del can03z.png
del can04z.png
del can05z.png
del can06z.png

rem 没メモ
del e048.png
del e055.png
del e057.png
del e058.png

rem エンディング地球儀(s02.pngがある為)
del s002.png

rem 代用可能
del bg03z.png
del bg12b.png

rem 本編で使われていない
del bg00c.png
del bg10b.png
del bg10c.png
del bg11c.png
del bg20b.png
del bg40.png
del bg56.png
del bg57.png
del bg58.png
del bg69.png
del bg70.png
del bg71.png
del bg72.png
del bg73.png
del bg77.png

rem エンディング文字
del cast.png
del end_t2.png
del name01.png
del name02.png
del name03.png
del name04.png
del name05.png
del name06.png
del name07.png
del name08.png
del name09.png
del name10.png
del name11.png
del name12.png
del name13.png
del name14.png
del name15.png
del name16.png
del name17.png
del name18.png
del name19.png
del name20.png
del name21.png
del name22.png
del name23.png
del name24.png
del name25.png

rem マスコット画像
del neko.png
del neko3.png
del neko4.png

rem プロローグ
del pro00.png
del pro01.png
del pro02.png
del pro03.png
del pro04.png
del pro05.png

del s029.png
del s031.png
del s032.png
del s033.png
del s035.png
del s036.png
del s037.png
del s038.png
del s039.png
del s041.png
del s042.png
del s044.png
del s045.png
del s046.png
del s047.png
del s050.png
del s053.png
del s062.png
del s063.png
del s064.png

rem エンディングスタッフ文字
del stl01.png
del stl02.png
del stl03.png
del stl04.png
del stl05.png
del stl06.png
del stl07.png
del stl08.png
del stl09.png
del stl10.png
del stl11.png


cd ..
