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
		# H�V�[���Ȃ�
		iw =  240
		ih =  160
	elif iw == 496 and ih == 288:
		# �w�i�A�L�����N�^�Ȃ�
		iw = 240
		ih = 140
	elif iw == 496 and ih == 576:
		# �X�N���[���iE_15A�AE_15B�AE_49C�AOP_08A�j
		iw = 240
		ih = 280
	elif iw == 496 and ih == 440:
		# �X�N���[���iOP_01A�j
		iw = 240
		ih = 214
	elif iw == 496 and ih == 560:
		# �X�N���[���iOP_02A�j
		iw = 240
		ih = 272
	elif iw == 529 and ih == 273:
		# �G���f�B���O�iED_10�AED_11�j
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
