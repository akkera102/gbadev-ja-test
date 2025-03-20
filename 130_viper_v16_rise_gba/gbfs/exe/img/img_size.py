# coding: Shift_JIS
# 画像ファイルのサイズをGBA用に変更します

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

	# 224x160やスクロールサイズは変更
	if(iw == 224):
		t = c.copy()

		# 塗りつぶしはパレット1番目を使用。0はGBAフェード処理で透過する為
		d = ImageDraw.Draw(t)
		d.rectangle([(0, 0), (iw, ih)], fill=1)

		# GBAの横サイズ240に変更
		t = t.resize((240, ih))
		t.paste(c, (8, 0))
		c = t

#	c.show()
	c.save(file)

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("img_size... " + file)
Resize(file)
