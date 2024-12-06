# coding: Shift_JIS
# 口パクなどの画像データの余白をカット。合わせてDATファイルを更新

import os
import re
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def FuncX0(img, pal):
	iw, ih = img.size

	for x in range(0, iw):
		for y in range(0, ih):
			if(img.getpixel((x, y)) != pal):
				return x

def FuncX1(img, pal):
	iw, ih = img.size

	for x in range(iw - 1, -1, -1):
		for y in range(0, ih):
			if(img.getpixel((x, y)) != pal):
				return x

def FuncY0(img, pal):
	iw, ih = img.size

	for y in range(0, ih):
		for x in range(0, iw):
			if(img.getpixel((x, y)) != pal):
				return y

def FuncY1(img, pal):
	iw, ih = img.size

	for y in range(ih - 1, -1, -1):
		for x in range(0, iw):
			if(img.getpixel((x, y)) != pal):
				return y

# ---------------------------------------------------------------------------
pal   = sys.argv[1]			# 透明色
adj   = sys.argv[2]			# cy分の追加余白
file1 = sys.argv[3]			# 座標情報（DAT）
file2 = sys.argv[4]			# 差分画像

print("img_cut1... " + pal + " " + file1 + " " + file2)

# 画像の大きさを変更
img = Image.open(file2)
cpy = img.copy()
img.close()

pal = int(pal)

x0 = FuncX0(cpy, pal)
x1 = FuncX1(cpy, pal) + 1
y0 = FuncY0(cpy, pal)
y1 = FuncY1(cpy, pal) + 1 + int(adj)

if(y0 % 2) == 1:
	y0 = y0 - 1

cpy.crop((x0, y0, x1, y1)).save(file2)

# DAT情報の読み込み
f = open(file1, "rb")
d = f.read()
f.close()

# ファイル名よりオフセット位置を特定
num = int(re.findall(r"\d+", file2)[-1]) - 1
pos = 16 + 256*2 + num*8
v   = struct.unpack("hhhh", d[pos:pos+8])

cx = x1   - x0
cy = y1   - y0
x0 = v[0] + x0 
y0 = v[1] + y0
p = struct.pack("hhhh", x0, y0, cx, cy)

#print("0x%X" % (pos))
#print(v)
#print("%d %d %d %d" % (x0, y0, cx, cy))

# DAT情報の更新
d = bytearray(d)
for i in range(0, 8):
	d[pos + i] = p[i]

f = open(file1, "wb")
f.write(d)
f.close()
