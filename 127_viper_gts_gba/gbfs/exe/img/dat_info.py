# coding: Shift_JIS
# フォルダにあるDATファイルの情報を表示します

import os
import re
import sys
import glob
import struct
from PIL import Image

# ---------------------------------------------------------------------------
files = glob.glob('*.dat')

for file in files:
	f = open(file, "rb")
	dat = f.read()
	f.close()

	max = struct.unpack("h", dat[0:2])[0]

	for i in range(max):
		pos = 16 + 256*2 + i*8
		src = struct.unpack("hhhh", dat[pos:pos+8])

		sx = int(src[0])
		sy = int(src[1])
		cx = int(src[2])
		cy = int(src[3])

#		if(cy < 160):
#			print("	{ \"%s\", %2d }," % (file[:-4], i+1))

		print("	{ \"%s\", %3d %3d, %3d, %3d, %3d }, " % (file[:-4], i+1, sx, sy, cx, cy))

