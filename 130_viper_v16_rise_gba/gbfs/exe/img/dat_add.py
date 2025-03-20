# coding: Shift_JIS
# DAT�t�@�C���̍ő吔���{�P���A�����ɍ��W�A�摜�T�C�Y��ǉ����܂�

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
sx   = sys.argv[1]			# ���WX
sy   = sys.argv[2]			# ���WY
cx   = sys.argv[3]			# �T�C�YCX
cy   = sys.argv[4]			# �T�C�YCY
file = sys.argv[5]			# DAT�t�@�C��

print("dat_add... " + sx + " " + sy + " " + cx + " " + cy + " " + file)

sx  = int(sx)
sy  = int(sy)
cx  = int(cx)
cy  = int(cy)

f = open(file, "rb")
d = f.read()
f.close()

m  = struct.unpack("h", d[0:2])[0] + 1
d  = struct.pack("h", m) + d[2:]
d += struct.pack("hhhh", sx, sy, cx, cy)


f = open(file, "wb")
f.write(d)
f.close()


