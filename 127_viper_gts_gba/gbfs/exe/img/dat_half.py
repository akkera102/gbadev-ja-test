# coding: Shift_JIS
# DAT情報の座標とサイズを２分の１に変更します

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
file = sys.argv[1]			# DATファイル

print("dat_half... " + file)


# DAT情報の読み込み
f = open(file, "rb")
dat = f.read()
f.close()

bin = bytearray(dat)


# 画像の最大数を取得
max = struct.unpack("h", dat[0:2])[0]
# print(max)


# 座標とサイズを２分の１に変更
for i in range(max):
	pos = 16 + 256*2 + i*8
	src = struct.unpack("hhhh", dat[pos:pos+8])

	sx = int(src[0] / 2)
	sy = int(src[1] / 2)
	cx = int(src[2] / 2)
	cy = int(src[3] / 2)

#	if(cx > 224):
#		print("ASSERT >240")

	# スクリーンやスクロールサイズはサイズ変更。パーツ画像は座標位置を変更します
	if(cx == 224):
		cx = 240
	else:
		sx = sx + 8

#	print(src)
#	print(" " + str(sx) + " " + str(sy) + " " + str(cx) + " " + str(cy))

	dst = struct.pack("hhhh", sx, sy, cx, cy)
	for j in range(0, 8):
		bin[pos + j] = dst[j]


# DATを上書き保存
f = open(file, "wb")
f.write(bin)
f.close()


