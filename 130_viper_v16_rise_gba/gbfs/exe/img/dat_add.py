# coding: Shift_JIS
# DATファイルの最大数を＋１し、末尾に座標、画像サイズを追加します

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
sx   = sys.argv[1]			# 座標X
sy   = sys.argv[2]			# 座標Y
cx   = sys.argv[3]			# サイズCX
cy   = sys.argv[4]			# サイズCY
file = sys.argv[5]			# DATファイル

print("dat_add... " + sx + " " + sy + " " + cx + " " + cy + " " + file)

sx  = int(sx)
sy  = int(sy)
cx  = int(cx)
cy  = int(cy)

f = open(file, "rb")
d = f.read()
f.close()

m  = struct.unpack("h", d[0:2])[0] + 1
d  = struct.pack("h", m) + d[2:]
d += struct.pack("hhhh", sx, sy, cx, cy)


f = open(file, "wb")
f.write(d)
f.close()


