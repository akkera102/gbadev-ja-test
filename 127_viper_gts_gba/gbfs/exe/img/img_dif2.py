# coding: Shift_JIS
# �����摜�ɃI���W�i���摜���������܂��B�J�n���W��DAT��񂩂�擾���܂�

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Diff(pal, sx, sy, file1, file2):
	img1 = Image.open(file1)
	img2 = Image.open(file2)

	iw, ih = img1.size

	for y in range(0, ih):
		for x in range(0, iw):

			if(img1.getpixel((x, y)) == pal):
				img1.putpixel((x, y), img2.getpixel((sx + x, sy + y)))

	sav = img1.copy()
	img1.close()
	img2.close()

#	sav.show()
	sav.save(file1)

# ---------------------------------------------------------------------------
pal   = sys.argv[1]			# �����F
file1 = sys.argv[2]			# ���W���iDAT�j
file2 = sys.argv[3]			# �����摜
file3 = sys.argv[4]			# ���摜

print("img_dif2... " + pal + " " + file1 + " " + file2 + " " + file3)

# �J�n���W��DAT�����擾
f = open(file1, "rb")
d = f.read()
f.close()

num = int(re.findall(r'\d+', file2)[-1]) - 1
pos = 16 + 256*2 + num*8
sx  = d[pos + 0] + (d[pos + 1] << 8)
sy  = d[pos + 2] + (d[pos + 3] << 8)

# ��������
Diff(int(pal), sx, sy, file2, file3)


