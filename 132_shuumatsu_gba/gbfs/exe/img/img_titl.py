# coding: Shift_JIS
# タイトルの白黒ブレンド合成を生成（33枚）

import os
import sys
import struct
from PIL import Image


# ---------------------------------------------------------------------------
print("img_titl... ")

t1 = Image.open("TITLE1.bmp")
t2 = Image.open("TITLE2.bmp")
p1 = t1.getpalette()
p2 = t2.getpalette()

# 黒背景→白
for i in range(16):

	c = i * 16

	if(c > 255):
		c = 255

	p1[0] = c
	p1[1] = c
	p1[2] = c

	t1.putpalette(p1)
	t1.save("img%03d.bmp" % (900 + i))

# 白背景→黒
for i in range(16, -1, -1):

	c = i * 16

	if(c > 255):
		c = 255

	p1[0] = c
	p1[1] = c
	p1[2] = c
	p2[0] = c
	p2[1] = c
	p2[2] = c
	t1.putpalette(p1)
	t2.putpalette(p2)

	s1 = t1.convert("RGB")
	s2 = t2.convert("RGB")

	mask = Image.new("L", s1.size, c)
	s = Image.composite(s1, s2, mask)
	s.save("img%03d.bmp" % (900 + 16 + 16-i))


