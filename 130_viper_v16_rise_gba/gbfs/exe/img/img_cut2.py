# coding: Shift_JIS
# �摜�t�@�C����crop���܂�


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
img.close()

# dst.show()
# dst.save("TEST.bmp")
dst.save(file)


