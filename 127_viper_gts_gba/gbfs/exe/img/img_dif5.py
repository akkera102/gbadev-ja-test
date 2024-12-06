# coding: Shift_JIS
# �^�C�g���摜��p�B�����摜�ɃI���W�i�������������܂��B�p�����[�^����DAT���ɏ㏑�����܂�

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
sx    = sys.argv[2]			# ���WX
sy    = sys.argv[3]			# ���WY
file1 = sys.argv[4]			# DAT�t�@�C���i�㏑����j
file2 = sys.argv[5]			# �����摜
file3 = sys.argv[6]			# ���摜

print("img_dif5... " + pal + " " + sx + " " + sy + " " + file1 + " " + file2 + " " + file3)

sx = int(sx)
sy = int(sy)

# ��������
Diff(int(pal), sx, sy, file2, file3)

# DAT���̓ǂݍ���
f = open(file1, "rb")
d = f.read()
f.close()

# �t�@�C�������I�t�Z�b�g�ʒu�����
num = int(re.findall(r"\d+", file2)[-1]) - 1
pos = 16 + 256*2 + num*8
# v = struct.unpack("hhhh", d[pos:pos+8])
# print(v)

img = Image.open(file2)
iw, ih = img.size

p = struct.pack("hhhh", sx, sy, iw, ih)

# DAT���̍X�V
d = bytearray(d)
for i in range(0, 8):
	d[pos + i] = p[i]

f = open(file1, "wb")
f.write(d)
f.close()

