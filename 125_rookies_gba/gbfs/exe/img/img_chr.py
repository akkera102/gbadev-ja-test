# coding: Shift_JIS
# キャラクタ画像、アルファブレンド画像の空白部分をカット
# アルファブレンド画像をバイナリに変更。バイナリは1ドット1バイト形式

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def CalL(f):
	p = Image.open(f)
	iw, ih = p.size

	for x in range(0, iw):
		for y in range(0, ih):

			(r, g, b) = p.getpixel((x, y))

			if(r != 0):
				return x

	assert 0

# ---------------------------------------------------------------------------
def CalR(f):
	p = Image.open(f)
	iw, ih = p.size

	for x in range(iw - 1, 0, -1):
		for y in range(0, ih):

			(r, g, b) = p.getpixel((x, y))

			if(r != 0):
				return x

	assert 0

# ---------------------------------------------------------------------------
def Cut(f1, f2, x1, x2):
	p1 = Image.open(f1)
	p2 = Image.open(f2)

	iw, ih = p1.size
	m1 = p1.crop((x1, 0, x2, ih))
	m2 = p2.crop((x1, 0, x2, ih))

	p1.close()
	p2.close()

	m1.save(f1)
	m2.save(f2)


	iw, ih = m1.size

	list = []

	for y in range(0, ih):
		for x in range(0, iw):

			(r, g, b) = m1.getpixel((x, y))
			list.append((int)(r / 8))

	p = open(f1[:-6] + ".msk", "wb")
	p.write(struct.pack('HH', x1, 10))		# GBA画面上のsx, sy表示座標を書き込む。10は固定値
	p.write(bytearray(list))
	p.close()

# ---------------------------------------------------------------------------
f1 = sys.argv[1]		# マスクファイル
f2 = f1[:-6] + ".png"	# 元画像


print("img_chr... " + f1 + " " + f2)

x1 = CalL(f1)
x2 = CalR(f1)

# 奇数cxの場合、パディング
if((x2 - x1) % 2 == 1):
	x2 = x2 + 1

Cut(f1, f2, x1, x2)
