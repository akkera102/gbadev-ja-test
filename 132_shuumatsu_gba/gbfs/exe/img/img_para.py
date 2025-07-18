# coding: Shift_JIS
# imgファイルの先頭に、画像の縦、横のパラメータを追加
import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Param(f):
	# 元画像のサイズだけ取得
	p = Image.open(f[:-4] + ".png")
	iw, ih = p.size
	p.close()

	# imgファイルを全て読み込む
	s = open(f, "rb")
	x = s.read()
	s.close()

	# サイズ情報をファイル先頭に付与
	d = open(f, 'wb')
	d.write(struct.pack('HH', iw, ih))
	d.write(x)
	d.close()

# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_para... " + f)
Param(f)
