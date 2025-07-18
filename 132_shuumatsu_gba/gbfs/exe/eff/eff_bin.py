# coding: Shift_JIS
# エフェクト画像を212x160にリサイズし、1ドット1バイトのバイナリデータを出力します


import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Bin(f):
	s = Image.open(f)
	iw, ih = s.size

	assert iw == 160
	assert ih == 120

	d = s.resize((212, 160), Image.LANCZOS)

	iw, ih = d.size
	list = []

	for y in range(0, ih):
		for x in range(0, iw):
			list.append(int(d.getpixel((x, y)) / 8))

	p = open(f[:-4] + ".e01", "wb")
	p.write(bytearray(list))
	p.close()

# ---------------------------------------------------------------------------
f = sys.argv[1]

print("eff_bin... " + f)
Bin(f)
