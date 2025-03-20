# coding: Shift_JIS
# �摜�t�@�C���̃T�C�Y��GBA�p�ɕύX���܂�

import os
import sys
import struct
from PIL import Image, ImageDraw

# ---------------------------------------------------------------------------
def Resize(file):
	p = Image.open(file)
	iw, ih = p.size

	iw = int(iw / 2)
	ih = int(ih / 2)
	c = p.resize((iw, ih), Image.NEAREST)
	p.close()

	# 224x160��X�N���[���T�C�Y�͕ύX
	if(iw == 224):
		t = c.copy()

		# �h��Ԃ��̓p���b�g1�Ԗڂ��g�p�B0��GBA�t�F�[�h�����œ��߂����
		d = ImageDraw.Draw(t)
		d.rectangle([(0, 0), (iw, ih)], fill=1)

		# GBA�̉��T�C�Y240�ɕύX
		t = t.resize((240, ih))
		t.paste(c, (8, 0))
		c = t

#	c.show()
	c.save(file)

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("img_size... " + file)
Resize(file)
