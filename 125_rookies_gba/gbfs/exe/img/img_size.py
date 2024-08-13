# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Size(f):
	p = Image.open(f)
	iw, ih = p.size

	if iw == 640 and ih == 400:
		# Hシーンなど
		iw =  240
		ih =  160
	elif iw == 496 and ih == 288:
		# 背景、キャラクタなど
		iw = 240
		ih = 140
	elif iw == 496 and ih == 576:
		# スクロール（E_15A、E_15B、E_49C、OP_08A）
		iw = 240
		ih = 280
	elif iw == 496 and ih == 440:
		# スクロール（OP_01A）
		iw = 240
		ih = 214
	elif iw == 496 and ih == 560:
		# スクロール（OP_02A）
		iw = 240
		ih = 272
	elif iw == 529 and ih == 273:
		# エンディング（ED_10、ED_11）
		iw = 240
		ih = 124
	else:
		print("Error Size : %s %d %d" % (f, iw, ih))
		return

	p = p.convert("RGB")
	p = p.resize((iw, ih), Image.LANCZOS)
	p.save(f[:-4] + ".png")
	p.close()

# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_size... " + f)
Size(f)
