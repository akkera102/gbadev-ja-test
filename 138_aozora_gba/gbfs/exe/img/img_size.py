# coding: Shift_JIS
# リサイズ
import os
import sys
import struct
from PIL import Image


f = sys.argv[1]
print("img_size... " + f)

img = Image.open(f)
iw, ih = img.size

if(ih == 532):
	# 背景、イベント絵、立ち絵
	iw = iw / 3.325
	ih = ih / 3.325
elif(iw == 480 and ih == 320):
	# エンドクレジット
	iw = iw / 2
	ih = ih / 2
else:
	# しおりアイコン（リサイズせず使用）
	assert iw == 200
	assert ih == 80

iw = int(iw)
ih = int(ih)

if iw % 2 == 1:
	iw = iw + 1

# print(f"iw={iw} ih={ih}")

dst = img.resize((iw, ih), Image.LANCZOS)
dst.save(f)
