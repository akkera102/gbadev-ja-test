# coding: Shift_JIS
# 画像のカットします

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Cut(f, x, y, cx, cy):
	s = Image.open(f)
	d = s.crop((x, y, x+cx, y+cy))
	s.close()

	d.save(f)

# ---------------------------------------------------------------------------
f  = sys.argv[1]
x  = int(sys.argv[2])
y  = int(sys.argv[3])
cx = int(sys.argv[4])
cy = int(sys.argv[5])

print("img_cut... " + f)
Cut(f, x, y, cx, cy)
