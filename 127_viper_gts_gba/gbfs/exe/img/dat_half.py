# coding: Shift_JIS
# DAT���̍��W�ƃT�C�Y���Q���̂P�ɕύX���܂�

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
file = sys.argv[1]			# DAT�t�@�C��

print("dat_half... " + file)


# DAT���̓ǂݍ���
f = open(file, "rb")
dat = f.read()
f.close()

bin = bytearray(dat)


# �摜�̍ő吔���擾
max = struct.unpack("h", dat[0:2])[0]
# print(max)


# ���W�ƃT�C�Y���Q���̂P�ɕύX
for i in range(max):
	pos = 16 + 256*2 + i*8
	src = struct.unpack("hhhh", dat[pos:pos+8])

	sx = int(src[0] / 2)
	sy = int(src[1] / 2)
	cx = int(src[2] / 2)
	cy = int(src[3] / 2)

#	if(cx > 224):
#		print("ASSERT >240")

	# �X�N���[����X�N���[���T�C�Y�̓T�C�Y�ύX�B�p�[�c�摜�͍��W�ʒu��ύX���܂�
	if(cx == 224):
		cx = 240
	else:
		sx = sx + 8

#	print(src)
#	print(" " + str(sx) + " " + str(sy) + " " + str(cx) + " " + str(cy))

	dst = struct.pack("hhhh", sx, sy, cx, cy)
	for j in range(0, 8):
		bin[pos + j] = dst[j]


# DAT���㏑���ۑ�
f = open(file, "wb")
f.write(bin)
f.close()


