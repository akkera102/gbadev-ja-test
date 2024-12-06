# coding: Shift_JIS
# �����摜�ɃI���W�i���摜���������܂��B�J�n�ʒu�̓I���W�i���摜�����ł��i���ߑł��j

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Diff(pal, file1, file2):
	img1 = Image.open(file1)
	img2 = Image.open(file2)

	iw1, ih1 = img1.size
	iw2, ih2 = img2.size

	for y in range(0, ih1):
		for x in range(0, iw1):

			if(img1.getpixel((x, y)) == pal):
				img1.putpixel((x, y), img2.getpixel((x, (ih2 - 320) + y)))

	sav = img1.copy()
	img1.close()
	img2.close()

#	sav.show()
	sav.save(file1)

# ---------------------------------------------------------------------------
pal   = sys.argv[1]			# �p���b�g�ԍ�
file1 = sys.argv[2]			# �����摜
file2 = sys.argv[3]			# ���摜

print("img_dif3... " + pal + " " + file1 + " " + file2)

Diff(int(pal), file1, file2)


