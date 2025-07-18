# coding: Shift_JIS
# 曜日文字をcrop

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Day(f):
	s = Image.open(f)
	s = s.convert("RGB")
	iw, ih = s.size

	b = s.crop((0, 0, 212, 160))

	x = 392
	y = 176
	s = s.crop((x, y, x + 212, y + 160))
	s = s.resize((s.width // 2, s.height // 2))

	b.paste(s, (100, 50))
#	b.show()
	b.save(f[:-4] + ".png")


# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_day... " + f)
Day(f)
