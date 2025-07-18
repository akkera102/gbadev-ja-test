# coding: Shift_JIS
# ロゴをcrop

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Logo(f):
	s = Image.open(f)
	s = s.convert("RGB")
	iw, ih = s.size

	x1 = iw / 2 - 212 / 2
	x2 = iw / 2 + 212 / 2
	y1 = ih / 2 - 160 / 2
	y2 = ih / 2 + 160 / 2

	b = s.crop((x1, y1, x2, y2))

#	b.show()
	b.save(f[:-4] + ".png")


# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_logo... " + f)
Logo(f)
