# coding: Shift_JIS
# �X�N���[���摜������p�N�����𒊏o�B���W�f�[�^�����킹�ďC�����܂�

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Cut(sx, sy, cx, cy, file1, file2):
	img = Image.open(file2)
	sav = img.crop((sx, sy, sx+cx, sy+cy))

	img.close()
	sav.save(file1)
#	sav.show()

# ---------------------------------------------------------------------------
num   = sys.argv[1]			# DAT�w��ԍ�
file1 = sys.argv[2]			# ���W���iDAT�j
file2 = sys.argv[3]			# �ۑ���摜
file3 = sys.argv[4]			# ���摜

print("img_cut3... " + num + " " + file1 + " " + file2 + " " + file3)

# �J�n���W��DAT�����擾
f = open(file1, "rb")
d = f.read()
f.close()

num = int(num)
pos = 16 + 256*2 + (num - 1)*8

sx  = d[pos + 0] + (d[pos + 1] << 8)
sy  = d[pos + 2] + (d[pos + 3] << 8)
cx  = d[pos + 4] + (d[pos + 5] << 8)
cy  = d[pos + 6] + (d[pos + 7] << 8)
# print("%d %d %d %d" % (sx, sy, cx, cy))

# ��������
Cut(sx, sy, cx, cy, file2, file3)


# DAT���̍X�V
p = struct.pack("hhhh", sx, sy, cx, cy)

# �t�@�C�������I�t�Z�b�g�ʒu�����
num = int(re.findall(r"\d+", file2)[-1]) - 1
pos = 16 + 256*2 + num*8

d = bytearray(d)
for i in range(0, 8):
	d[pos + i] = p[i]

f = open(file1, "wb")
f.write(d)
f.close()


