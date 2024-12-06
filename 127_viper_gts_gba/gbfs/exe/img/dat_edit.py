# coding: Shift_JIS
# DAT���̍��W�A�摜�T�C�Y��ύX���܂�

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
idx  = sys.argv[1]			# �C���f�b�N�X
sx   = sys.argv[2]			# ���WX
sy   = sys.argv[3]			# ���WY
cx   = sys.argv[4]			# �T�C�YCX
cy   = sys.argv[5]			# �T�C�YCY
file = sys.argv[6]			# DAT�t�@�C��

print("dat_edit... " + idx + " " + sx + " " + sy + " " + cx + " " + cy + " " + file)

idx = int(idx) - 1
sx  = int(sx)
sy  = int(sy)
cx  = int(cx)
cy  = int(cy)

# DAT���̓ǂݍ���
f = open(file, "rb")
d = f.read()
f.close()

# �t�@�C�������I�t�Z�b�g�ʒu�����
pos = 16 + 256*2 + idx*8
v   = struct.unpack("hhhh", d[pos:pos+8])
p   = struct.pack("hhhh", sx, sy, cx, cy)

# print(v)

# DAT���̍X�V
d = bytearray(d)
for i in range(0, 8):
	d[pos + i] = p[i]

f = open(file, "wb")
f.write(d)
f.close()


