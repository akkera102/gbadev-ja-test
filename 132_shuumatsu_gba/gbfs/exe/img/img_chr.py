# coding: Shift_JIS
# �L�����N�^�摜�A�A���t�@�u�����h�摜�̍��E�󔒂��J�b�g
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
def Mask(mask, base, x1, x2):
	p = Image.open(mask)
	iw, ih = p.size

	m = p.crop((x1, 0, x2, ih))
	p.close()

	iw, ih = m.size
	list = []

	for y in range(0, ih):
		for x in range(0, iw):

			(r, g, b) = m.getpixel((x, y))
			list.append((int)(r / 8))

	p = open(base + ".msk", "wb")
	p.write(struct.pack('HH', x1, 0))		# GBA��ʏ��sx, sy�\�����W���������ށB0�͌Œ�l
	p.write(bytearray(list))
	p.close()

# ---------------------------------------------------------------------------
def Resize(list, x1, x2):
	for f in list:
		p = Image.open(f)
		iw, ih = p.size

		m = p.crop((x1, 0, x2, ih))
		p.close()
		m.save(f)

# ---------------------------------------------------------------------------
mask = sys.argv[1]
base = mask[:-8] + "0"

list = [f for f in os.listdir() if os.path.isfile(f) and base in f]
list.remove(mask)

print("img_chr... " + base)

x1 = CalL(mask)
x2 = CalR(mask)

# �cx�̏ꍇ�A�p�f�B���O
if((x2 - x1) % 2 == 1):
	x2 = x2 + 1

Mask(mask, base, x1, x2)
Resize(list, x1, x2)
