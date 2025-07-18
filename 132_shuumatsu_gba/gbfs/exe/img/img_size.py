# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Size(f):
	s = Image.open(f)
	s = s.convert("RGB")

	iw, ih = s.size

	assert iw == 640
	assert ih == 480 or ih == 482		# DOMKANA 482

	# ���E2�h�b�g�Â؂���
	s = s.crop((2, 0, 638, 480))

	# 636/3, 480/3�Ƀ��T�C�Y
	s = s.resize((212, 160), Image.LANCZOS)

	s.save(f[:-4] + ".png")


# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_size... " + f)
Size(f)
