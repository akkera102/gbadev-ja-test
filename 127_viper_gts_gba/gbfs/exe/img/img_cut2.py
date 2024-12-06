# coding: Shift_JIS
# �摜�t�@�C����crop���܂��i���S�ƃ^�C�g���摜�Ȃǁj
# �^�C�g���摜�̓T�u�^�C�g����h��Ԃ��������܂��iGBA�T�C�Y�ɍ���Ȃ��ׁj

# �^�C�g���@96 32 544 352 GTS_TIT_03.bmp
# ���S�@�@�@96 40 544 360 SOGNA_01.bmp

import os
import re
import sys
import struct
from PIL import Image, ImageDraw

# ---------------------------------------------------------------------------
argv1 = sys.argv[1]			# ����1
argv2 = sys.argv[2]			# ����1
argv3 = sys.argv[3]			# ����1
argv4 = sys.argv[4]			# ����1
file  = sys.argv[5]			# �摜

print("img_cut2... " + file)

img = Image.open(file)
dst = img.copy()
dst = img.crop((int(argv1), int(argv2), int(argv3), int(argv4)))


if(file == "GTS_TIT_03.bmp"):
	dw = ImageDraw.Draw(dst)
	dw.rectangle([(80, 300), (380, 319)], fill=10)
	dw.rectangle([(126, 291), (380, 299)], fill=10)

	tm = img.crop((497, 359, 614, 378))
	dst.paste(tm, (331, 301))


img.close()

# dst.show()
# dst.save("TEST.bmp")
dst.save(file)


