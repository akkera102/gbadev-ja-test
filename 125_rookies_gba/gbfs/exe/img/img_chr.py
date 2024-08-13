# coding: Shift_JIS
# �L�����N�^�摜�A�A���t�@�u�����h�摜�̋󔒕������J�b�g
# �A���t�@�u�����h�摜���o�C�i���ɕύX�B�o�C�i����1�h�b�g1�o�C�g�`��

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def CalL(f):
	p = Image.open(f)
	iw, ih = p.size

	for x in range(0, iw):
		for y in range(0, ih):

			(r, g, b) = p.getpixel((x, y))

			if(r != 0):
				return x

	assert 0

# ---------------------------------------------------------------------------
def CalR(f):
	p = Image.open(f)
	iw, ih = p.size

	for x in range(iw - 1, 0, -1):
		for y in range(0, ih):

			(r, g, b) = p.getpixel((x, y))

			if(r != 0):
				return x

	assert 0

# ---------------------------------------------------------------------------
def Cut(f1, f2, x1, x2):
	p1 = Image.open(f1)
	p2 = Image.open(f2)

	iw, ih = p1.size
	m1 = p1.crop((x1, 0, x2, ih))
	m2 = p2.crop((x1, 0, x2, ih))

	p1.close()
	p2.close()

	m1.save(f1)
	m2.save(f2)


	iw, ih = m1.size

	list = []

	for y in range(0, ih):
		for x in range(0, iw):

			(r, g, b) = m1.getpixel((x, y))
			list.append((int)(r / 8))

	p = open(f1[:-6] + ".msk", "wb")
	p.write(struct.pack('HH', x1, 10))		# GBA��ʏ��sx, sy�\�����W���������ށB10�͌Œ�l
	p.write(bytearray(list))
	p.close()

# ---------------------------------------------------------------------------
f1 = sys.argv[1]		# �}�X�N�t�@�C��
f2 = f1[:-6] + ".png"	# ���摜


print("img_chr... " + f1 + " " + f2)

x1 = CalL(f1)
x2 = CalR(f1)

# �cx�̏ꍇ�A�p�f�B���O
if((x2 - x1) % 2 == 1):
	x2 = x2 + 1

Cut(f1, f2, x1, x2)
