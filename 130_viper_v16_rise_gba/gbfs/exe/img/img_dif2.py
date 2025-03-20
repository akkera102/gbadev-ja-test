# coding: Shift_JIS
# ���摜�ɑ΂��č����摜�������B�ۑ���͍����ł͂Ȃ��A���摜�ifile2�j�ŕۑ����܂�

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

			if(img1.getpixel((x, y)) != pal):
				img2.putpixel((sx + x, sy + y), img1.getpixel((x, y)))

	sav = img2.copy()
	img1.close()
	img2.close()

#	sav.show()
	sav.save(file2)


# ---------------------------------------------------------------------------
file1 = sys.argv[1]			# ���W���iDAT�j
file2 = sys.argv[3]			# �����摜�i���ӁI����3���g�p�j
file3 = sys.argv[2]			# ���摜�@�i���ӁI����2���g�p�j

print("img_dif2... " + file1 + " " + file3 + " " + file2)

# �J�n���W��DAT�����擾
f = open(file1, "rb")
d = f.read()
f.close()

num = int(re.findall(r'\d+', file2)[-1]) - 1
pos = 16 + 256*2 + num*8
sx  = d[pos + 0] + (d[pos + 1] << 8)
sy  = d[pos + 2] + (d[pos + 3] << 8)

# ��������
Diff(12, sx, sy, file2, file3)


