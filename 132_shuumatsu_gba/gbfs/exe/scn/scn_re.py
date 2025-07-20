# coding: Shift_JIS

import re
import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Regex(text, file):

	# 追加　テキスト空白
	text = re.sub('Ｃｈｅｃｋｉｔｏｕｔ', 'Ｃｈｅｃｋ　ｉｔ　ｏｕｔ', text)
	text = re.sub('ＧｏｄｂｒｅａｔｈＵ', 'Ｇｏｄ　ｂｒｅａｔｈ　Ｕ', text)
	text = re.sub('ＨＡＲＤＤＡＹｚＫｎｉｇｈｔ', 'ＨＡＲＤ　ＤＡＹｚ　Ｋｎｉｇｈｔ', text)
	text = re.sub('ＨＡＲＤＤＡＹｚ', 'ＨＡＲＤ　ＤＡＹｚ', text)
	text = re.sub('ＨｅｙＪＡＭ', 'Ｈｅｙ　ＪＡＭ', text)
	text = re.sub('ｋｅｅｐｏｎｓｍｉｌｅ', 'ｋｅｅｐ　ｏｎ　ｓｍｉｌｅ', text)
	text = re.sub('ｋｅｅｐＫＡＷＬ', 'ｋｅｅｐ　ＫＡＷＬ', text)
	text = re.sub('ＮｅｘｔＷｅｅｋ', 'Ｎｅｘｔ　Ｗｅｅｋ', text)

	# 変更　画像番号のダブり指定
	text = re.sub('!g 136', '!g 17', text)
	text = re.sub('!g 140', '!g 15', text)

	# 変更　改行(_n)の数
	text = re.sub('_n_n_n', '_n_n', text)
	text = re.sub('_n_n', '_n', text)

	# 変更　改行(_n)と指アイコン(_t)の入れ替え
	text = re.sub('_n_t', '_t_n', text)

	# 削除　謎コマンド
	text = re.sub('_w', '', text)
	text = re.sub('_s', '', text)
	text = re.sub('[0-9A-F]{4} !s [0-9]+ [0-9]+\n', '', text)
	text = re.sub('[0-9A-F]{4} !p\n', '', text)
	text = re.sub('[0-9A-F]{4} !c\n', '', text)
	text = re.sub('[0-9A-F]{4} #b\n', '', text)

	# 個別対応
	if(file == 'SCN008.txt'):
		# 追加　改ページ（メッセージウィンドウに入らない）
		text = re.sub('生徒と、１０人', '生徒と、_r１０人', text)

	if(file == 'SCN010.txt'):
		# 変更　改ページ（メッセージウィンドウに入らない）
		text = re.sub('ちひろ」_t_n', 'ちひろ」_r', text)

	if(file == 'SCN013.txt'):
		# 変更　改ページ（メッセージウィンドウに入らない）
		text = re.sub('ちひろ」_t_n', 'ちひろ」_r', text)

	if(file == 'SCN014.txt'):
		# 変更　スクリプトミス
		text = re.sub('0B14 !x 49 0', '0B14 !x 51 0', text)

	if(file == 'SCN020.txt'):
		# 変更　選択肢アドレスが削除された為
		text = re.sub('0074', '006E', text)
		text = re.sub('01F9', '01F3', text)

	if(file == 'SCN032.txt'):
		# 変更　選択肢アドレスが削除された為
		text = re.sub('044F', '044B', text)

	if(file == 'SCN037.txt'):
		# 変更　スクリプトミス
		text = re.sub('05F1 !x 38 0', '05F1 !x 38 1', text)

	if(file == 'SCN051.txt'):
		# 変更　改ページ（メッセージウィンドウに入らない）
		text = re.sub('るため、彼らは', 'るため、_r彼らは', text)

	if(file == 'SCN053.txt'):
		# 変更　改ページ（メッセージウィンドウに入らない）
		text = re.sub('だけど、この放', 'だけど、_rこの放', text)

	if(file == 'SCN077.txt'):
		# 変更　改ページ（メッセージウィンドウに入らない）
		text = re.sub('る事。_t_n', 'る事。_r', text)


	return text

# ---------------------------------------------------------------------------
file = sys.argv[1]

print("scn_re... " + file)

f = open(file, 'r')
text = f.read()
f.close()


text = Regex(text, file)


f = open(file, "w")
f.write(text)
f.close()
