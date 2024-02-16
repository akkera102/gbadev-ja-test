# coding: cp932
# 特殊文字コードを置換、スペースと改行を'\0'に置換
import sys
import os
import re

# ---------------------------------------------------------------------------
# テキスト16進数を変換
def chr2num(x):
	if(x == 0x30): return 0
	if(x == 0x31): return 1
	if(x == 0x32): return 2
	if(x == 0x33): return 3
	if(x == 0x34): return 4
	if(x == 0x35): return 5
	if(x == 0x36): return 6
	if(x == 0x37): return 7
	if(x == 0x38): return 8
	if(x == 0x39): return 9
	if(x == 0x61): return 0xa
	if(x == 0x62): return 0xb
	if(x == 0x63): return 0xc
	if(x == 0x64): return 0xd
	if(x == 0x65): return 0xe
	return 0xf

# ---------------------------------------------------------------------------

if len(sys.argv) < 2:
	print("Usage: {} input.txt".format(sys.argv[0]))
	sys.exit(1)

print("txt2txt... " + os.path.basename(sys.argv[1]))

with open(sys.argv[1], "rb") as f:
	src = f.read()
f.close()

i = 0
dst = []
chr = [0, 0, 0, 0]
isTxt = False

while i < len(src):

	chr[0] = chr[1]
	chr[1] = chr[2]
	chr[2] = chr[3]
	chr[3] = src[i]

	# MSG+0x20 or SEL+0x20
	if( (chr[0] == 0x4D and chr[1] == 0x53 and chr[2] == 0x47 and chr[3] == 0x20) or
	    (chr[0] == 0x53 and chr[1] == 0x45 and chr[2] == 0x4C and chr[3] == 0x20) ):
		isTxt = True

	# 改行
	if(chr[3] == 0x0A and chr[2] == 0x0D):
		isTxt = False

	# テキストの場合
	if(isTxt == True):

		# SJIS
		if(src[i]>=0x81 and src[i]<=0x9f) or (src[i]>=0xe0 and src[i]<=0xef):
			dst.append(src[i+0])
			dst.append(src[i+1])
			i += 2
			continue

		# \文字（特殊文字マーク）
		if(src[i] == 0x5c):
			c1  = chr2num(src[i+1]) << 4
			c1 += chr2num(src[i+2])

			assert src[i+3] == 0x5c

			c2  = chr2num(src[i+4]) << 4
			c2 += chr2num(src[i+5])

#			print("%04x: %2x%2x" % (i, c1, c2))
#			print("%2x%2x" % (c1, c2))

			# カナンフォントコード以外の謎コード。cs20_07内で使用
			if(c1 == 0x86 and c2 == 0xa2):
				# 「―」で代用
				dst.append(0x81)
				dst.append(0x5c)
			else:
				dst.append(c1)
				dst.append(c2)

			i += 6
			continue

	# その他の処理
	dst.append(src[i])
	i += 1

# ---------------------------------------------------------------------------
i = 0
dst2 = []
chr = [0, 0, 0, 0]
isTxt = False

while i < len(dst):

	chr[0] = chr[1]
	chr[1] = chr[2]
	chr[2] = chr[3]
	chr[3] = dst[i]

	# MSG+0x20 or SEL+0x20
	if( (chr[0] == 0x4D and chr[1] == 0x53 and chr[2] == 0x47 and chr[3] == 0x20) or
	    (chr[0] == 0x53 and chr[1] == 0x45 and chr[2] == 0x4C and chr[3] == 0x20) ):
		dst2.append(0x00)
		i += 1
		isTxt = True
		continue

	# 改行
	if(chr[2] == 0x0D and chr[3] == 0x0A):
		dst2.pop()
		dst2.append(0x00)
		i += 1
		isTxt = False
		continue

	# 空白
	if(chr[3] == 0x20 and isTxt == False):
		dst2.append(0x00)
		i += 1
		continue

	# その他の処理
	dst2.append(dst[i])
	i += 1

# ---------------------------------------------------------------------------


with open(sys.argv[1], "wb") as f:
	f.write(bytes(dst2))
f.close()
