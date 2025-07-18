# coding: Shift_JIS
# キャラクタ画像、アルファブレンド画像の左右空白をカット
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
def Mask(mask, base, x1, x2):
	p = Image.open(mask)
	iw, ih = p.size

	m = p.crop((x1, 0, x2, ih))
	p.close()

	iw, ih = m.size
	list = []

	for y in range(0, ih):
		for x in range(0, iw):

			(r, g, b) = m.getpixel((x, y))
			list.append((int)(r / 8))

	p = open(base + ".msk", "wb")
	p.write(struct.pack('HH', x1, 0))		# GBA画面上のsx, sy表示座標を書き込む。0は固定値
	p.write(bytearray(list))
	p.close()

# ---------------------------------------------------------------------------
def Resize(list, x1, x2):
	for f in list:
		p = Image.open(f)
		iw, ih = p.size

		m = p.crop((x1, 0, x2, ih))
		p.close()
		m.save(f)

# ---------------------------------------------------------------------------
mask = sys.argv[1]
base = mask[:-8] + "0"

list = [f for f in os.listdir() if os.path.isfile(f) and base in f]
list.remove(mask)

print("img_chr... " + base)

x1 = CalL(mask)
x2 = CalR(mask)

# 奇数cxの場合、パディング
if((x2 - x1) % 2 == 1):
	x2 = x2 + 1

Mask(mask, base, x1, x2)
Resize(list, x1, x2)
