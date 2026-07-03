# coding: Shift_JIS
# キャラクタ画像の左右空白をカット。アルファブレンド画像をバイナリに変更。バイナリは1ドット1バイト形式

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
base = sys.argv[1]

alp = base + "_m.png"
chr = base + ".png"
msk = base + ".msk.bin"

print("img_chr... " + base)

# 左右空白をカット
x1 = CalL(alp)
x2 = CalR(alp)

# 奇数cxの場合、パディング
if((x2 - x1) % 2 == 1):
	x2 = x2 + 1

# キャラリサイズ
p = Image.open(chr)
iw, ih = p.size

m = p.crop((x1, 0, x2, ih))
p.close()
m.save(chr)

# マスクをbinファイルで保存
p = Image.open(alp)
iw, ih = p.size
list = []

for y in range(0, ih):
	for x in range(x1, x2):

		(r, g, b) = p.getpixel((x, y))
		list.append((int)(r / 8))

p.close()

p = open(msk, "wb")
p.write(bytearray(list))
p.close()
