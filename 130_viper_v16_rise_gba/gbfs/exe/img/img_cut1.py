# coding: Shift_JIS
# DAT�����g�p���A�摜�t�@�C�����J�b�g���܂�
# sx, sy, cx, cy����l�̏ꍇ�A�����l�ɕύX�ADAT�������ĕύX���܂�

import os
import re
import sys
import struct
from PIL import Image, ImageDraw

# ---------------------------------------------------------------------------
file1 = sys.argv[1]			# ���W���iDAT�j
file2 = sys.argv[2]			# �摜


print("img_cut1... " + file1 + " " + file2)

# �J�n���W��DAT�����擾
f = open(file1, "rb")
d = f.read()
f.close()

idx = int(re.findall(r'\d+', file2)[-1]) - 1
pos = 16 + 256*2 + idx*8
sx  = d[pos + 0] + (d[pos + 1] << 8)
sy  = d[pos + 2] + (d[pos + 3] << 8)
cx  = d[pos + 4] + (d[pos + 5] << 8)
cy  = d[pos + 6] + (d[pos + 7] << 8)

isChange = False;

if sx % 2 == 1:
	sx = sx - 1
	isChange = True

if sy % 2 == 1:
	sy = sy - 1
	isChange = True

if cx % 2 == 1:
	cx = cx + 1
	isChange = True

if cy % 2 == 1:
	cy = cy + 1
	isChange = True


# crop
img = Image.open(file2)
dst = img.copy()
dst = img.crop((sx, sy, sx+cx, sy+cy))
img.close()

# dst.show()
# dst.save("TEST.bmp")
dst.save(file2)


if(isChange == False):
	exit()


# DAT�t�@�C���̕ύX
pos = 16 + 256*2 + idx*8
v   = struct.unpack("hhhh", d[pos:pos+8])
p   = struct.pack("hhhh", sx, sy, cx, cy)

# print(v)

# DAT���̍X�V
d = bytearray(d)
for i in range(0, 8):
	d[pos + i] = p[i]

f = open(file1, "wb")
f.write(d)
f.close()


