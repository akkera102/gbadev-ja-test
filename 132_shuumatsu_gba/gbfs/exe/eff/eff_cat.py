# coding: Shift_JIS
# エフェクトバイナリファイルを結合します

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
base = sys.argv[1]
list = [f for f in os.listdir() if os.path.isfile(f) and base in f]

list.sort()

print("eff_cat... " + base)

# print(list)

d = open(base + ".bin", "wb")

d.write(struct.pack('HHHH', 212, 160, len(list), 0))

for f in list:
	b = open(f, "rb")
	d.write(b.read())
	b.close()

d.close()
