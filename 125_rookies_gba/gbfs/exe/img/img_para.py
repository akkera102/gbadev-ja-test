# coding: Shift_JIS
# img�t�@�C���̐擪�ɁA�摜�̏c�A���̃p�����[�^��ǉ�
import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Param(f):
	# ���摜�̃T�C�Y�����擾
	p = Image.open(f[:-4] + ".png")
	iw, ih = p.size
	p.close()

	# img�t�@�C����S�ēǂݍ���
	s = open(f, "rb")
	x = s.read()
	s.close()

	# �T�C�Y�����t�@�C���擪�ɕt�^
	d = open(f, 'wb')
	d.write(struct.pack('HH', iw, ih))
	d.write(x)
	d.close()

# ---------------------------------------------------------------------------
f = sys.argv[1]

print("img_para... " + f)
Param(f)
