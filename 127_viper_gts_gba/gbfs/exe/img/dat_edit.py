# coding: Shift_JIS
# DAT情報の座標、画像サイズを変更します

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
idx  = sys.argv[1]			# インデックス
sx   = sys.argv[2]			# 座標X
sy   = sys.argv[3]			# 座標Y
cx   = sys.argv[4]			# サイズCX
cy   = sys.argv[5]			# サイズCY
file = sys.argv[6]			# DATファイル

print("dat_edit... " + idx + " " + sx + " " + sy + " " + cx + " " + cy + " " + file)

idx = int(idx) - 1
sx  = int(sx)
sy  = int(sy)
cx  = int(cx)
cy  = int(cy)

# DAT情報の読み込み
f = open(file, "rb")
d = f.read()
f.close()

# ファイル名よりオフセット位置を特定
pos = 16 + 256*2 + idx*8
v   = struct.unpack("hhhh", d[pos:pos+8])
p   = struct.pack("hhhh", sx, sy, cx, cy)

# print(v)

# DAT情報の更新
d = bytearray(d)
for i in range(0, 8):
	d[pos + i] = p[i]

f = open(file, "wb")
f.write(d)
f.close()


