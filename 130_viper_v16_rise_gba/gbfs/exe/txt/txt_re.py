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

	if(file == 'START.txt'):
		# 画面の注意喚起メッセージ削除
		text = re.sub('00A1:.*\n', '', text)
		text = re.sub('00AC:.*\n', '', text)
		text = re.sub('00AE:.*\n', '', text)
		text = re.sub('00BB:.*\n', '', text)
		text = re.sub('00BD:.*\n', '', text)
		text = re.sub('00C4:.*\n', '', text)
		text = re.sub('00C8:.*\n', '', text)

	if(file == 'MAIN.txt'):
		# ウェイト調整
		text = re.sub('0064: SLP 100', '0064: SLP 200', text)
		# タイトル画面後、キーウェイトと開始スタート追加
		text = re.sub('00B9: ANE\n', '00B9: EFF 2 2\nWAI\nTXC\nJMP 19\n', text)

	if(file == 'RI00.txt'):
		# 初期処理　枠削除
		text = re.sub('00A0:.*\n', '', text)
		text = re.sub('00AF:.*\n', '', text)
		text = re.sub('00B1:.*\n', '', text)
		text = re.sub('00BE:.*\n', '', text)
		text = re.sub('00C2:.*\n', '', text)
		# 場面１　ウェイト削除、枠削除、ウェイト追加
		text = re.sub('03D1: SLP 100\n', '', text)
		text = re.sub('03DB:.*\n', '03DB: SLP 60\n', text)
		text = re.sub('03EA:.*\n', '', text)
		text = re.sub('03EC:.*\n', '', text)
		text = re.sub('03F9:.*\n', '', text)
		text = re.sub('03FD:.*\n', '', text)
		text = re.sub('0402:.*\n', '', text)
		# 場面２　横スクロール調整
		text = re.sub('0429:.*\n', '', text)
		text = re.sub('0444:.*\n', '', text)
		text = re.sub('0454:.*\n', '', text)
		text = re.sub('0461: BUF 1', '0461: BUF 0', text)
		text = re.sub('0489:.*\n', '', text)
		text = re.sub('0499:.*\n', '', text)
		text = re.sub('04A6: BUF 1', '04A6: BUF 0', text)
		text = re.sub('04C7:.*\n', '', text)
		text = re.sub('04D7:.*\n', '', text)
		text = re.sub('04E4: BUF 1', '04E4: BUF 0', text)
		text = re.sub('050A:.*\n', '', text)
		text = re.sub('0521: BUF 1', '0521: BUF 0', text)
		# 場面１１　タイミング調整
		text = re.sub('0DD2: BUF 2 0 8 255 24', '0DD2: BUF 2 0 8 255 30', text)
		text = re.sub('1665: BUF 2 0 41 255 34', '1665: BUF 2 0 41 255 44', text)
		text = re.sub('1990: BUF 2 0 11 255 28', '1990: BUF 2 0 11 255 37', text)
		text = re.sub('1E02: BUF 2 0 11 255 22', '1E02: BUF 2 0 11 255 29', text)
		text = re.sub('21B2: BUF 2 0 8 255 22', '21B2: BUF 2 0 8 255 29', text)
		text = re.sub('2448: BUF 2 0 13 255 22', '2448: BUF 2 0 13 255 29', text)
		# 場面３１　ANMのダブル指定を変更
		text = re.sub('44BD:.*\n', '', text)
		text = re.sub('48C5: PAL\n', '48C5: ANM C2\nPAL\n', text)
		text = re.sub('4AA6: PAL\n', '4AA6: ANM C1\nPAL\n', text)
		# 場面３３　縦スクロール調整
		text = re.sub('56CA:.*\n', '', text)
		text = re.sub('56E1: BUF 1', '56E1: BUF 0', text)
		# 場面３４　背景アニメ削除
		text = re.sub('5A01:.*\n', '', text)
		# 場面１２２　背景アニメ削除
		text = re.sub('52BC:.*\n', '', text)
		# 場面１２３　背景アニメ削除
		text = re.sub('53B6:.*\n', '', text)
		# 場面１３２　縦スクロール調整
		text = re.sub('4193:.*\n', '', text)
		text = re.sub('41B0: BUF 1', '41B0: BUF 0', text)
		# 場面１３２　メッセージ溢れる為、バッファクリア処理
		text = re.sub('4223: CAL 337\n', '4223: VRW 254 1\nCAL 326\n', text)
		# 場面１４３　アニメーション調整、フレームを３個追加
		text = re.sub('60F1:.*\n', '', text)
		text = re.sub('60FE:.*\n', '', text)
		text = re.sub('610B: BUF 2', '610B: BUF 0', text)
		text = re.sub('61A9:.*\n', '', text)
		text = re.sub('61BA:.*\n', '', text)
		text = re.sub('61CB: BUF 2', '61CB: BUF 0', text)
		text = re.sub('62B2:.*\n', '', text)
		text = re.sub('62BF:.*\n', '', text)
		text = re.sub('62CC: BUF 2', '62CC: BUF 0', text)
		text = re.sub('6444:.*\n', '', text)
		text = re.sub('645B:.*\n', '', text)
		text = re.sub('6472:.*\n', '', text)
		text = re.sub('6483: BUF 3 2 3 23 6 24 6 25 22', '6483: BUF 2 2 6 23 6 24 6 25 6 26 6 27 6 28 6', text)
		# 場面１４６　フレーム変更
		text = re.sub('6C2C: BUF 0 16 1 1', '6C2C: BUF 0 17 1 17', text)
		text = re.sub('6DF4: BUF 0 17 1 1', '6DF4: BUF 0 17 1 17', text)
		# 場面１５１　縦スクロール調整
		text = re.sub('71F9:.*\n', '', text)
		text = re.sub('7206: BUF 1', '7206: BUF 0', text)
		# 場面１５３　アニメーション調整
		text = re.sub('752B:.*\n', '', text)
		text = re.sub('75A9:.*\n', '', text)
		text = re.sub('75BC: BUF 1', '75BC: BUF 2', text)
		text = re.sub('75D0: WAY 0', '75D0: WAY 2', text)
		# 場面１６１　アニメーション調整
		text = re.sub('7A46:.*\n', '', text)
		text = re.sub('7A53:.*\n', '', text)
		text = re.sub('7A60: BUF 2', '7A60: BUF 0', text)
		text = re.sub('7BA7:.*\n', '', text)
		text = re.sub('7BE8:.*\n', '', text)
		text = re.sub('7C0B: BUF 2', '7A60: BUF 0', text)
		# 場面１６２　アニメーション修正
		text = re.sub('7C8D: BUF 3', '7C8D: BUF 0', text)
		text = re.sub('7CB6: BUF 0', '7CB6: BUF 1', text)
		text = re.sub('7D08: BUF 3', '7D08: BUF 0', text)
		text = re.sub('7D31: BUF 0', '7D31: BUF 1', text)
		# 場面１６４　アニメーション修正
		text = re.sub('8145:.*\n', '', text)
		text = re.sub('8156:.*\n', '', text)
		text = re.sub('8167:.*\n', '', text)
		text = re.sub('8178:.*\n', '', text)
		text = re.sub('8189: BUF 4 2 3 35 6 36 6 37 6', '8189: BUF 0 2 3 1 6 2 6 3 6', text)
		text = re.sub('819A:.*\n', '', text)

		text = re.sub('81B0:.*\n', '', text)
		text = re.sub('81BD:.*\n', '', text)
		text = re.sub('81DE:.*\n', '', text)
		text = re.sub('820D:.*\n', '', text)
		text = re.sub('821A: BUF 4 3 11 38 6 39 6 40 6 41 6 42 12 43 6 44 6 45 6 46 6 47 6 48 6', '821A: BUF 0 0 18 4 6 5 6 6 6 7 6 8 6 9 6 10 6 11 6 12 6 13 6 14 6 15 6 16 6 17 6 18 6 19 6 20 6 21 6', text)

		text = re.sub('824D: BUF 6', '824D: BUF 2', text)
		text = re.sub('8338: BUF 6', '8338: BUF 2', text)
		text = re.sub('8376: WAY 4', '8376: WAY 0', text)

		text = re.sub('8378:.*\n', '', text)
		text = re.sub('83B9:.*\n', '', text)
		text = re.sub('83FA:.*\n', '', text)
		text = re.sub('843B: BUF 4 2 26 38 6 39 6 40 6 41 6 42 12 43 6 44 6 45 6 46 6 47 6 49 6 50 6 51 6 52 6 53 6 54 12 55 2 56 4 57 4 58 4 59 4 60 4 61 4 62 4 63 6 64 12', '843B: BUF 0 2 27 22 6 23 6 24 6 25 6 26 6 27 6 28 6 29 6 30 6 31 6 32 6 33 6 34 6 35 6 36 6 37 6 38 12 39 2 40 4 41 4 42 4 43 4 44 4 45 4 46 4 47 6 48 12', text)
		text = re.sub('847D: WAY 4', '847D: WAY 0', text)

		text = re.sub('847F:.*\n', '', text)
		text = re.sub('849E:.*\n', '', text)
		text = re.sub('84BD:.*\n', '', text)
		text = re.sub('84DC: BUF 4 2 5 64 30 65 6 66 6 67 6 68 12', '84DC: BUF 0 2 10 49 6 50 6 51 6 52 6 53 6 54 6 55 6 56 6 57 6 58 6', text)
		text = re.sub('84FC: WAY 4', '84FC: WAY 0', text)

		text = re.sub('84FE:.*\n', '', text)
		text = re.sub('850D: BUF 2 2 2 29 6 30 6', '850D: BUF 0 2 2 59 6 60 6', text)
		text = re.sub('851C:.*\n', '', text)
		text = re.sub('852B:.*\n', '', text)
		text = re.sub('8539: WAY 4', '8539: WAY 0', text)

		text = re.sub('853B:.*\n', '', text)
		text = re.sub('8548:.*\n', '', text)
		text = re.sub('855F:.*\n', '', text)
		text = re.sub('856C: BUF 4 10 8 71 6 72 6 73 6 74 6 75 6 76 6 77 6 78 6', '856C: BUF 0 10 8 61 6 62 6 63 6 64 6 65 6 66 6 67 6 68 6', text)
		text = re.sub('8587: BUF 5', '8587: BUF 1', text)
		# 場面１６５　縦スクロール修正
		text = re.sub('869E: BUF 0 17 1 1', '869E: BUF 0 17 1 4', text)
		text = re.sub('86C2: BUF 2', '86C2: BUF 0', text)
		text = re.sub('874F: BUF 0 17 1 1 5', '874F: BUF 0 17 1 4 1', text)
		# 場面１６６　アニメーション調整
		text = re.sub('881A: BUF 0', '881A: BUF 1', text)
		text = re.sub('882D: WAB 0', '882D: WAB 1', text)
		text = re.sub('882F: BUF 0', '881A: BUF 1', text)
		text = re.sub('89EE: BUF 0', '89EE: BUF 1', text)
		text = re.sub('8A29: WAB 0', '8A29: WAB 1', text)
		# 場面１６７　アニメーション調整
		text = re.sub('8AF0: BUF 1 2 5 255 36', '8AF0: BUF 1 2 5 255 48', text)
		text = re.sub('8B1F: BUF 1 0 1 255 12', '8B1F: BUF 1 0 1 255 15', text)
		text = re.sub('8B48: BUF 2 0 1 255 24', '8B48: BUF 2 0 1 255 32', text)
		# 場面１６８　縦スクロール修正
		text = re.sub('8BC8:.*\n', '', text)
		text = re.sub('8BE3: BUF 1', '8BE3: BUF 0', text)
		text = re.sub('8D1B:.*\n', '', text)
		text = re.sub('8D3A: BUF 1', '8D3A: BUF 0', text)

		text = re.sub('8D65:.*\n', '', text)
		text = re.sub('8D72:.*\n', '', text)
		text = re.sub('8D7F: BUF 2', '8D7F: BUF 0', text)
		text = re.sub('8DE7: WAY 2', '8DE7: WAY 0', text)

		text = re.sub('8DE9: BUF 2', '8DE9: BUF 0', text)
		text = re.sub('8E04: WAY 2', '8E04: WAY 0', text)

		text = re.sub('8E06:.*\n', '', text)
		text = re.sub('8E25: BUF 2', '8E25: BUF 0', text)

		text = re.sub('8E47:.*\n', '', text)
		text = re.sub('8E54:.*\n', '', text)
		text = re.sub('8E61: BUF 2', '8E61: BUF 0', text)
		text = re.sub('8ED4: WAY 2', '8ED4: WAY 0', text)

		text = re.sub('8ED6: BUF 0 0 2 255 4 2 16', '8ED6: BUF 1 0 2 255 4 255 16', text)
		text = re.sub('8EEB: BUF 2', '8EEB: BUF 0', text)

		text = re.sub('8F21: BUF 1', '8F21: BUF 0', text)
		text = re.sub('8F31: WAY 2', '8F31: WAY 0', text)
		text = re.sub('8F43:.*\n', '', text)
		# 場面１７３　フェードアウト追加
		text = re.sub('9928: PAL\n', '9928: PAL\nEFF 1 255\n', text)
		# 場面２０１　メッセージ削除
		text = re.sub('34DD: CAL 337', '34DD: CAL 335', text)
		# 場面２０２　メッセージ削除
		text = re.sub('3970: CAL 337', '3970: CAL 335', text)
		# 場面１００２　アニメーション調整
		text = re.sub('651D: ANM OP2B\n', '651D: ANM OP2\nEFF 1 255\n', text)
		text = re.sub('6555:.*\n', '', text)
		text = re.sub('6562: BUF 1', '6562: BUF 0', text)
		text = re.sub('658C:.*\n', '', text)
		text = re.sub('65A3: BUF 1', '65A3: BUF 0', text)
		# 場面１０２４　ANM変更
		text = re.sub('6E66: ANM B4B', '6E66: ANM B4', text)
		# 場面２０２４　ANM変更
		text = re.sub('90B9: ANM B4C', '90B9: ANM B4', text)
		text = re.sub('9348: BUA\n', '9348: BUA\nEFF 5 0\n', text)

		# サブルーチン口パク　バッファ変更
		text = re.sub('B2F5: BUF 6', 'B2F5: BUF 2', text)
		text = re.sub('B302: WAB 6', 'B302: WAB 2', text)
		# サブルーチン会話　ウェイト削除
		text = re.sub('B0D4: SLP 15\n', '', text)
		text = re.sub('B0E8: SLP 15\n', '', text)
		text = re.sub('B109: SLP 15\n', '', text)
		text = re.sub('B121: SLP 100\n', '', text)
		# サブルーチン戦闘　バッファ0無効、バッファ1でアニメーション＋背景
		text = re.sub('9A8E:.*\n', '', text)
		text = re.sub('9A9F: BUF 1 3 1 1 2', '9A9F: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9AF0:.*\n', '', text)
		text = re.sub('9B01: BUF 1 3 1 1 2', '9B01: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9B5C:.*\n', '', text)
		text = re.sub('9B6D: BUF 1 3 1 1 2', '9B6D: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9DEE:.*\n', '', text)
		text = re.sub('9DFF: BUF 1 3 1 1 2', '9DFF: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9EDA: BUF 1 3 1 1 2', '9EDA: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9F00: BUF 1 3 1 1 2', '9F00: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9F26: BUF 1 3 1 1 2', '9F26: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9F53: BUF 1 3 1 1 2', '9F53: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9F79: BUF 1 3 1 1 2', '9F79: BUF 1 3 3 1 1 32 1 33 1', text)
		text = re.sub('9F9F: BUF 1 3 1 1 2', '9F9F: BUF 1 3 3 1 1 32 1 33 1', text)
		# サブルーチン戦闘　ＢＯＳＳサイクロン、ハリケーン　アニメ修正委
		text = re.sub('A198:.*\n', '', text)
		text = re.sub('A1D3:.*\n', '', text)
		text = re.sub('A1E4: BUF 1 3 2 255 2 1 4', 'A1E4: BUF 1 3 3 30 1 32 1 33 1', text)
		text = re.sub('A232: EFF 3 1', 'A232: EFF 3 6', text)
		text = re.sub('A24B:.*\n', '', text)
		text = re.sub('A286:.*\n', '', text)
		text = re.sub('A297: BUF 1 3 2 255 2 1 4', 'A297: BUF 1 3 3 31 1 32 1 33 1', text)
		text = re.sub('A2E5: EFF 3 1', 'A2E5: EFF 3 6', text)
		# サブルーチンＨＰ表示ＯＮ、ＯＦＦ
		text = re.sub('AB66: CPY 106 102\n', 'AB66: HP0 1\nRET\n', text)
		text = re.sub('9E33: SLP 25\n', '9E33: HP0 0\nSLP 25\n', text)
		text = re.sub('9EB5: SLP 25\n', '9EB5: HP0 0\nSLP 25\n', text)


		# 場面の番号振りなおし
#		text = re.sub('0102: IFL 1',    '0102: IFL 1',  text)
#		text = re.sub('010D: IFL 2',    '010D: IFL 2',  text)
#		text = re.sub('0123: IFL 3',    '0123: IFL 3',  text)
#		text = re.sub('012E: IFL 4',    '012E: IFL 4',  text)
		text = re.sub('013C: IFL 11',   '013C: IFL 5',  text)
		text = re.sub('0147: IFL 12',   '0147: IFL 6',  text)
		text = re.sub('0152: IFL 13',   '0152: IFL 7',  text)
		text = re.sub('0366: IFL 201',  '0366: IFL 8',  text)
		text = re.sub('0187: IFL 22',   '0187: IFL 9',  text)
		text = re.sub('0160: IFL 14',   '0160: IFL 10', text)
		text = re.sub('0380: IFL 301',  '0380: IFL 11', text)
		text = re.sub('016E: IFL 15',   '016E: IFL 12', text)
		text = re.sub('0371: IFL 202',  '0371: IFL 13', text)
		text = re.sub('0179: IFL 21',   '0179: IFL 14', text)
		text = re.sub('0195: IFL 23',   '0195: IFL 15', text)
		text = re.sub('038B: IFL 302',  '038B: IFL 16', text)
		text = re.sub('01A3: IFL 24',   '01A3: IFL 17', text)
		text = re.sub('01F6: IFL 110',  '01F6: IFL 18', text)
		text = re.sub('0201: IFL 121',  '0201: IFL 19', text)
		text = re.sub('0228: IFL 131',  '0228: IFL 20', text)
		text = re.sub('0236: IFL 132',  '0236: IFL 21', text)
		text = re.sub('01C4: IFL 31',   '01C4: IFL 22', text)
		text = re.sub('020C: IFL 122',  '020C: IFL 23', text)
		text = re.sub('021A: IFL 123',  '021A: IFL 24', text)
		text = re.sub('01CF: IFL 32',   '01CF: IFL 25', text)
		text = re.sub('01DD: IFL 33',   '01DD: IFL 26', text)
		text = re.sub('01E8: IFL 34',   '01E8: IFL 27', text)
		text = re.sub('0396: IFL 303',  '0396: IFL 28', text)
		text = re.sub('0244: IFL 141',  '0244: IFL 29', text)
		text = re.sub('024F: IFL 142',  '024F: IFL 30', text)
		text = re.sub('025D: IFL 143',  '025D: IFL 31', text)
		text = re.sub('0118: IFL 1002', '0118: IFL 32', text)
		text = re.sub('026B: IFL 144',  '026B: IFL 33', text)
		text = re.sub('0276: IFL 145',  '0276: IFL 34', text)
		text = re.sub('0281: IFL 146',  '0281: IFL 35', text)
		text = re.sub('02CF: IFL 161',  '02CF: IFL 36', text)
		text = re.sub('02DA: IFL 162',  '02DA: IFL 37', text)
		text = re.sub('02E8: IFL 163',  '02E8: IFL 38', text)
		text = re.sub('02F6: IFL 164',  '02F6: IFL 39', text)
		text = re.sub('0304: IFL 165',  '0304: IFL 40', text)
		text = re.sub('0312: IFL 166',  '0312: IFL 41', text)
		text = re.sub('0320: IFL 167',  '0320: IFL 42', text)
		text = re.sub('032E: IFL 168',  '032E: IFL 43', text)
		text = re.sub('01AE: IFL 1024', '01AE: IFL 44', text)
		text = re.sub('028C: IFL 151',  '028C: IFL 45', text)
		text = re.sub('029A: IFL 152',  '029A: IFL 46', text)
		text = re.sub('02A8: IFL 153',  '02A8: IFL 47', text)
		text = re.sub('02B3: IFL 154',  '02B3: IFL 48', text)
		text = re.sub('02C1: IFL 155',  '02C1: IFL 49', text)
		text = re.sub('01B9: IFL 2024', '01B9: IFL 50', text)
		text = re.sub('033C: IFL 171',  '033C: IFL 51', text)
		text = re.sub('034A: IFL 172',  '034A: IFL 52', text)
		text = re.sub('0358: IFL 173',  '0358: IFL 53', text)

#		text = re.sub('039F: VRW 16 1',    '039F: VRW 16 1',  text)
#		text = re.sub('0419: VRW 16 2',    '0419: VRW 16 2',  text)
#		text = re.sub('059F: VRW 16 3',    '059F: VRW 16 3',  text)
#		text = re.sub('094B: VRW 16 4',    '094B: VRW 16 4',  text)
		text = re.sub('0AB4: VRW 16 11',   '0AB4: VRW 16 5',  text)
		text = re.sub('2514: VRW 16 12',   '2514: VRW 16 6',  text)
		text = re.sub('32AB: VRW 16 13',   '32AB: VRW 16 7',  text)
		text = re.sub('33E6: VRW 16 201',  '33E6: VRW 16 8',  text)
		text = re.sub('3A98: VRW 16 22',   '3A98: VRW 16 9',  text)
		text = re.sub('34F9: VRW 16 14',   '34F9: VRW 16 10', text)
		text = re.sub('3658: VRW 16 301',  '3658: VRW 16 11', text)
		text = re.sub('3671: VRW 16 15',   '3671: VRW 16 12', text)
		text = re.sub('3878: VRW 16 202',  '3878: VRW 16 13', text)
		text = re.sub('3999: VRW 16 21',   '3999: VRW 16 14', text)
		text = re.sub('3B07: VRW 16 23',   '3B07: VRW 16 15', text)
		text = re.sub('3A4E: VRW 16 302',  '3A4E: VRW 16 16', text)
		text = re.sub('3B74: VRW 16 24',   '3B74: VRW 16 17', text)
		text = re.sub('3CBD: VRW 16 110',  '3CBD: VRW 16 18', text)
		text = re.sub('3E21: VRW 16 121',  '3E21: VRW 16 19', text)
		text = re.sub('40F2: VRW 16 131',  '40F2: VRW 16 20', text)
		text = re.sub('4157: VRW 16 132',  '4157: VRW 16 21', text)
		text = re.sub('44B0: VRW 16 31',   '44B0: VRW 16 22', text)
		text = re.sub('52A0: VRW 16 122',  '52A0: VRW 16 23', text)
		text = re.sub('539A: VRW 16 123',  '539A: VRW 16 24', text)
		text = re.sub('5480: VRW 16 32',   '5480: VRW 16 25', text)
		text = re.sub('568B: VRW 16 33',   '568B: VRW 16 26', text)
		text = re.sub('599F: VRW 16 34',   '599F: VRW 16 27', text)
		text = re.sub('5ACC: VRW 16 303',  '5ACC: VRW 16 28', text)
		text = re.sub('5B26: VRW 16 141',  '5B26: VRW 16 29', text)
		text = re.sub('5D34: VRW 16 142',  '5D34: VRW 16 30', text)
		text = re.sub('60CE: VRW 16 143',  '60CE: VRW 16 31', text)
		text = re.sub('6519: VRW 16 1002', '6519: VRW 16 32', text)
		text = re.sub('6621: VRW 16 144',  '6621: VRW 16 33', text)
		text = re.sub('664C: VRW 16 145',  '664C: VRW 16 34', text)
		text = re.sub('66E9: VRW 16 146',  '66E9: VRW 16 35', text)
		text = re.sub('7A25: VRW 16 161',  '7A25: VRW 16 36', text)
		text = re.sub('7C59: VRW 16 162',  '7C59: VRW 16 37', text)
		text = re.sub('7E17: VRW 16 163',  '7E17: VRW 16 38', text)
		text = re.sub('8129: VRW 16 164',  '8129: VRW 16 39', text)
		text = re.sub('8673: VRW 16 165',  '8673: VRW 16 40', text)
		text = re.sub('8789: VRW 16 166',  '8789: VRW 16 41', text)
		text = re.sub('8A52: VRW 16 167',  '8A52: VRW 16 42', text)
		text = re.sub('8B7C: VRW 16 168',  '8B7C: VRW 16 43', text)
		text = re.sub('6E62: VRW 16 1024', '6E62: VRW 16 44', text)
		text = re.sub('719B: VRW 16 151',  '719B: VRW 16 45', text)
		text = re.sub('7334: VRW 16 152',  '7334: VRW 16 46', text)
		text = re.sub('74FD: VRW 16 153',  '74FD: VRW 16 47', text)
		text = re.sub('76E6: VRW 16 154',  '76E6: VRW 16 48', text)
		text = re.sub('780A: VRW 16 155',  '780A: VRW 16 49', text)
		text = re.sub('90B5: VRW 16 2024', '90B5: VRW 16 50', text)
		text = re.sub('9382: VRW 16 171',  '9382: VRW 16 51', text)
		text = re.sub('95D0: VRW 16 172',  '95D0: VRW 16 52', text)
		text = re.sub('9856: VRW 16 173',  '9856: VRW 16 53', text)

		# デバッグ用に変数番号を固有値に変更、合わせて条件式も変更（牢屋の選択肢）
		text = re.sub('1C4D: VRW 100',  '1C4D: VRW 21', text)
		text = re.sub('1E59: VRW 100',  '1E59: VRW 21', text)
		text = re.sub('253B: VRR 100',  '253B: VRR 21', text)


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
