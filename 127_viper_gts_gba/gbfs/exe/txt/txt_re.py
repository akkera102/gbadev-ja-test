# coding: Shift_JIS

import re
import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
# ジャンプ命令のアドレス表記を変更します
def Label(text):
	lines = text.splitlines()
	loc = []

	for line in lines:
		list = line.split()
		elem = [l for l in list if 'loc_' in l]

		if elem:
			adr = elem[0].replace('loc_', '')

			if not adr in loc:
				loc.append(adr)

	loc = sorted(loc)

	i = 0
	for adr in loc:
		# ジャンプ元は「loc_アドレス」を「インデックス番号」に置き換え
		text = re.sub('loc_' + adr, str(i), text)
		# ジャンプ先はアドレスとLBL命令を追加
		text = re.sub(adr, adr + ' LBL ' + str(i) + '\n' + adr, text)
		i = i + 1

	return text

# ---------------------------------------------------------------------------
def Regex(text, file):

	if(file == 'GTS0.txt'):
		# 場面6  エンジン音のウェイト調整
		text = re.sub('0CE5: PCM ENGINE 2', '0CE5: PCM ENGINE 4', text)
		# 場面6  ゲーム本編に移動
		text = re.sub('0E3E: WIN MAIN\n', '0E3E: WIN GTS1\n', text)

	if(file == 'GTS1.txt'):
		# 場面8 カルラ登場スクロールのスピード変更
		text = re.sub('1\n034A:', '2\n034A:', text)
		# 場面11 スクロール指定変更、ウェイト値変更
		text = re.sub('0B15: BUF 0', '0B15: BUF 1', text)
		text = re.sub('0B38: BUF 1', '0B38: BUF 0', text)
		text = re.sub('90\n0B38:', '50\n0B38:', text)
		text = re.sub('0C2A: WAY 0', '0C2A: WAY 1', text)
		text = re.sub('0C2C: BUF 0\n', '', text)
		text = re.sub('0C39: BUF 1', '0C39: BUF 0', text)
		text = re.sub('0F59: BUF 0', '0F59: BUF 1', text)
		text = re.sub('0F70: BUF 1', '0F70: BUF 0', text)
		# 場面16 多重スクロール削除
		text = re.sub('19F3:.*\n', '', text)
		text = re.sub('1A00: BUF 1', '1A00: BUF 0', text)
 		# 場面19 多重スクロール削除
		text = re.sub('25FD:.*\n', '', text)
		text = re.sub('260A: BUF 1', '260A: BUF 0', text)
 		# 場面19 スリープ調整
		text = re.sub('263F: SLP 100', '263F: SLP 10', text)
		# 場面22 多重スクロール削除
		text = re.sub('2BE0:.*\n', '', text)
		text = re.sub('2BED: BUF 1', '260A: BUF 0', text)

	if(file == 'GTS2.txt'):
		# 場面27 召喚の音声調整
		text = re.sub('074A: PCM BIRIDON2 2', '074A: PCM BIRIDON2 4', text)
		# 場面27 召喚場面のフレームウェイト変更
		text = re.sub('0770: SLP 180', '0770: SLP 100', text)
		# 場面31 バッファ値を変更
		text = re.sub('28B9: BUF 3', '28B9: BUF 0', text)
		# 場面35 画面が残る　塗りつぶし＋フェードアウト
		text = re.sub('3784:.*\n', '3784: EFF 5 0\n', text)
		text = re.sub('3791:.*\n', '', text)
		text = re.sub('3804:.*\n', '3804: EFF 5 0\n', text)
		text = re.sub('3811:.*\n', '3811: EFF 1 255\n', text)
		# 場面35 画面が残る　塗りつぶし
		text = re.sub('3A45:.*\n', '3A45: EFF 5 0\n', text)
		# 場面36 画面が残る　塗りつぶし
		text = re.sub('2DA4:.*\n', '2DA4: EFF 5 0\n', text)
		text = re.sub('2DB1:.*\n', '', text)
		text = re.sub('2DEB: EFF 2 1\n', '2DEB: EFF 1 255\n2DEB: EFF 2 1\n', text)
		# 場面36 スクロール画像コマンドを使用時の直近に移動
		text = re.sub('30BA:.*\n', '', text)
		text = re.sub('31E0:', '31E0: BUI 0 19\n31E0:', text)
		# 場面37 フラッシュ後のウェイト調整
		text = re.sub('31C3: SLP 50', '31C3: SLP 25', text)
		text = re.sub('31CA: SLP 100', '31CA: SLP 50', text)
		text = re.sub('31D1: SLP 100', '31D1: SLP 50', text)
		text = re.sub('31D8: SLP 200', '31D8: SLP 100', text)
		# 場面37 重複スクロール削除
		text = re.sub('3221:.*\n', '', text)
		text = re.sub('3246: BUF 1', '3246: BUF 0', text)
		text = re.sub('328E:.*\n', '', text)
		text = re.sub('329B: BUF 1', '329B: BUF 0', text)
		# 場面39 画面が残る　塗りつぶし＋ホワイトイン
		text = re.sub('48F6:.*\n', '48F6: EFF 5 0\n', text)
		text = re.sub('4903:.*\n', '4903: EFF 4 2\n', text)
		# 場面132 画面が残る　塗りつぶし
		text = re.sub('32D9:.*\n', '32D9: EFF 5 0\n', text)
		text = re.sub('32E6:.*\n', '', text)
		text = re.sub('3368: EFF 2 1\n', '3368: EFF 1 255\n3368: EFF 2 1\n', text)
		# 場面137 フラッシュ後のウェイト調整
		text = re.sub('3CDA: SLP 50', '3CDA: SLP 25', text)
		text = re.sub('3CE1: SLP 100', '3CE1: SLP 50', text)
		text = re.sub('3CE8: SLP 100', '3CE8: SLP 50', text)
		text = re.sub('3CEF: SLP 200', '3CE8: SLP 100', text)
		# 場面137 重複スクロール削除
		text = re.sub('3D38:.*\n', '', text)
		text = re.sub('3D5D: BUF 1', '329B: BUF 0', text)
		text = re.sub('3DA5:.*\n', '', text)
		text = re.sub('3DB2: BUF 1', '3DB2: BUF 0', text)

	if(file == 'GTS3.txt'):
		# 場面40 召喚ANMを変更
		text = re.sub('02F1: ANM G040', '02F1: ANM G026', text)
		# 場面40 召喚の音声調整
		text = re.sub('058E: PCM BIRIDON2 2', '058E: PCM BIRIDON2 4', text)
		# 場面40 召喚のウェイト変更
		text = re.sub('05B4: SLP 180', '05B4: SLP 100', text)
		# 場面51 メッセージフェードと画面フェードが被る為、塗りつぶし対応
		text = re.sub('1C33:.*\n', '1C33: EFF 5 0\n', text)
		text = re.sub('1C40:.*\n', '', text)
		# 場面56 画面が残る　塗りつぶし＋フェードアウト
		text = re.sub('24DE:.*\n', '24DE: EFF 5 0\n', text)
		text = re.sub('24EB:.*\n', '', text)
		text = re.sub('2551: EFF 2 2\n', '2551: EFF 1 255\n2551: EFF 2 2\n', text)
		# 場面64 画面が残る　塗りつぶし＋ホワイトイン
		text = re.sub('3557:.*\n', '3557: EFF 5 0\n', text)
		text = re.sub('3564:.*\n', '3564: EFF 4 2\n', text)
		# 場面70 天使登場　重複スクロール削除
		text = re.sub('3F15:.*\n', '', text)
		text = re.sub('3F22: BUF 1', '3F22: BUF 0', text)
		text = re.sub('3F51:.*\n', '', text)
		# 場面71 画面が残る　塗りつぶし＋フェードアウト
		text = re.sub('432E:', '432E: EFF 5 0\n432E: EFF 1 255\n432E:', text)
		# 場面155 画面が残る　塗りつぶし
		text = re.sub('2A87:.*\n', '2A87: EFF 5 0\n', text)
		text = re.sub('2A94:.*\n', '', text)

	if(file == 'GTS4.txt'):
		# 場面73 画面が残る　塗りつぶし
		text = re.sub('0D59:.*\n', '0D59: EFF 5 0\n', text)
		text = re.sub('0D66:.*\n', '', text)
		# 場面74 画面が残る　塗りつぶし
		text = re.sub('0E52:.*\n', '0E52: EFF 5 0\n', text)
		text = re.sub('0E5F:.*\n', '', text)
		text = re.sub('0EF0:', '0EF0: EFF 1 255\n0EF0:', text)
		# 場面78 ウェイト調整
		text = re.sub('1857: SLP 400', '1857: SLP 200', text)
		# 場面78 PCM再生削除
		text = re.sub('1863:.*\n', '', text)
		# 場面78 画面が残る　塗りつぶし
		text = re.sub('1873:.*\n', '1873: EFF 5 0\n', text)
		text = re.sub('1880:.*\n', '', text)
		# 場面79 画面が残る　塗りつぶし
		text = re.sub('191F:.*\n', '191F: EFF 5 0\n', text)
		# 場面80 画面が残る　塗りつぶし
		text = re.sub('1B2F:.*\n', '1B2F: EFF 5 0\n', text)
		# 場面81 フェードアウト追加
		text = re.sub('1B38:', '1B38: EFF 1 255\n1B38:', text)
		# 場面81 重複スクロール削除
		text = re.sub('1B70:.*\n', '', text)
		text = re.sub('1B7D: BUF 1', '1B7D: BUF 0', text)
		# 場面82 画面が残る　塗りつぶし
		text = re.sub('1C14:', '1C14: EFF 5 0\n1C14:', text)
		# 場面82 重複描画
		text = re.sub('1C2D:.*\n', '', text)
		# 場面83 重複スクロール削除
		text = re.sub('1D9E:.*\n', '', text)
		text = re.sub('1DAB: BUF 1', '1DAB: BUF 0', text)
		# 場面84 重複スクロール削除
		text = re.sub('2083: BUF 1', '2083: BUF 0', text)
		# 場面91 メッセージフェードと画面フェードが被る為、塗りつぶし対応
		text = re.sub('25E8:.*\n', '25E8: EFF 5 0\n', text)
		# 場面92 フェードアウト追加
		text = re.sub('2620:', '2620: EFF 1 255\n2620:', text)
		# 場面92 重複スクロール削除
		text = re.sub('2668:.*\n', '', text)
		text = re.sub('2675: BUF 1', '2675: BUF 0', text)
		# 場面99 画面が残る　塗りつぶし
		text = re.sub('38D4:.*\n', '1873: EFF 5 0\n', text)
		text = re.sub('38E1:.*\n', '', text)
		# 場面99 フェードアウト追加
		text = re.sub('38FC:', '38FC: EFF 1 255\n38FC:', text)
		# 場面100 フラッシュフレームとエフェクト削除
		text = re.sub('392B:.*\n', '', text)
		text = re.sub('3955:.*\n', '', text)
		# 場面100 ウェイト調整
		text = re.sub('395E: SLP 400', '1857: SLP 200', text)
		# 場面100 PCM再生削除
		text = re.sub('3966:.*\n', '', text)
		# 場面100 画面が残る　塗りつぶし
		text = re.sub('3976:.*\n', '1873: EFF 5 0\n', text)
		text = re.sub('3983:.*\n', '', text)


	# ゲームタイトルとメニュー表示、GTS0への遷移追加
	if(file == 'MAIN.txt'):
		text = re.sub('^', 'EFF 1 255\nANM GTS_TIT\nPAL\nBUF 0 0 1 3 1\nWAB 0\nEFF 2 2\nWAI\nTXC\nEFF 1 2\nEFF 5 0\nSLP 50\nWIN GTS0\n', text)

	# ロゴ表示後はメニュー画面表示
	if(file == 'START.txt'):
		text = re.sub('00C3: WIN GTS0\n', '0E3E: WIN MAIN\n', text)

	# キー入力後のウェイトを調整
	if(file == 'GTS0.txt'):
		text = re.sub('0E4B: SLP 50', '0E4B: SLP 25', text)
	if(file == 'GTS1.txt'):
		text = re.sub('3A38: SLP 30', '3A38: SLP 5', text)
	if(file == 'GTS2.txt'):
		text = re.sub('4926: SLP 30', '4926: SLP 5', text)
	if(file == 'GTS3.txt'):
		text = re.sub('462E: SLP 30', '462E: SLP 5', text)
	if(file == 'GTS4.txt'):
		text = re.sub('4080: SLP 30', '4080: SLP 5', text)

	# 未使用のWINDOW（枠）処理を消去、エフェクト高速化
	if(file == 'GTS1.txt'):
		text = re.sub('009A:.*\n', '', text)
		text = re.sub('009C:.*\n', '', text)
		text = re.sub('00A9:.*\n', '', text)
		text = re.sub('00AB: EFF 2 2', '00AB: EFF 2 255', text)
	if(file == 'GTS2.txt'):
		text = re.sub('00AB:.*\n', '', text)
		text = re.sub('00AD:.*\n', '', text)
		text = re.sub('00BA:.*\n', '', text)
		text = re.sub('00BC: EFF 2 2', '00BC: EFF 2 255', text)
	if(file == 'GTS3.txt'):
		text = re.sub('00A9:.*\n', '', text)
		text = re.sub('00AB:.*\n', '', text)
		text = re.sub('00B8:.*\n', '', text)
		text = re.sub('00BA: EFF 2 2', '00BA: EFF 2 255', text)
	if(file == 'GTS4.txt'):
		text = re.sub('009A:.*\n', '', text)
		text = re.sub('009C:.*\n', '', text)
		text = re.sub('00A9:.*\n', '', text)
		text = re.sub('00AB: EFF 2 2', '00AB: EFF 2 255', text)
	if(file == 'START.txt'):
		text = re.sub('006E:.*\n', '', text)

	# アドレス表記は削除
	text = re.sub('[0-9A-F]{4}: \n', '', text)
	text = re.sub('[0-9A-F]{4}: ', '', text)

	return text

# ---------------------------------------------------------------------------
file = sys.argv[1]

print("txt_re... " + file)

f = open(file, 'r')
text = f.read()
f.close()


text = Label(text)
text = Regex(text, file)


f = open(file, "w")
f.write(text)
