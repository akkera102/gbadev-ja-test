# coding: Shift_JIS
# GBA mode4変換用コマンドを生成します。対象：フォルダにあるbmpファイル

import os
import re
import sys
import glob
import struct
from PIL import Image

# ---------------------------------------------------------------------------
files = glob.glob('*.bmp')

for file in files:
	img = Image.open(file)
	iw, ih = img.size
	img.close()

	if(iw == 240 and ih == 160):
		print("..\\..\\exe\\img\\grit %s -g -gb -ftb -gzl -p! -fh!" % (file)) 
	else:
		print("python ..\\..\\exe\\img\\img_bin.py %s" % (file))


