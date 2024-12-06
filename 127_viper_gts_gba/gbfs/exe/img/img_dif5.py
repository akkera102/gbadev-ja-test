# coding: Shift_JIS
# タイトル画像専用。差分画像にオリジナル元を合成します。パラメータからDAT情報に上書きします

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Diff(pal, sx, sy, file1, file2):
	img1 = Image.open(file1)
	img2 = Image.open(file2)

	iw, ih = img1.size

	for y in range(0, ih):
		for x in range(0, iw):

			if(img1.getpixel((x, y)) == pal):
				img1.putpixel((x, y), img2.getpixel((sx + x, sy + y)))

	sav = img1.copy()
	img1.close()
	img2.close()

#	sav.show()
	sav.save(file1)

# ---------------------------------------------------------------------------
pal   = sys.argv[1]			# 透明色
sx    = sys.argv[2]			# 座標X
sy    = sys.argv[3]			# 座標Y
file1 = sys.argv[4]			# DATファイル（上書き先）
file2 = sys.argv[5]			# 差分画像
file3 = sys.argv[6]			# 元画像

print("img_dif5... " + pal + " " + sx + " " + sy + " " + file1 + " " + file2 + " " + file3)

sx = int(sx)
sy = int(sy)

# 差分合成
Diff(int(pal), sx, sy, file2, file3)

# DAT情報の読み込み
f = open(file1, "rb")
d = f.read()
f.close()

# ファイル名よりオフセット位置を特定
num = int(re.findall(r"\d+", file2)[-1]) - 1
pos = 16 + 256*2 + num*8
# v = struct.unpack("hhhh", d[pos:pos+8])
# print(v)

img = Image.open(file2)
iw, ih = img.size

p = struct.pack("hhhh", sx, sy, iw, ih)

# DAT情報の更新
d = bytearray(d)
for i in range(0, 8):
	d[pos + i] = p[i]

f = open(file1, "wb")
f.write(d)
f.close()

