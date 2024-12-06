# coding: Shift_JIS
# 画像ファイルをcropします（ロゴとタイトル画像など）
# タイトル画像はサブタイトルを塗りつぶし処理します（GBAサイズに合わない為）

# タイトル　96 32 544 352 GTS_TIT_03.bmp
# ロゴ　　　96 40 544 360 SOGNA_01.bmp

import os
import re
import sys
import struct
from PIL import Image, ImageDraw

# ---------------------------------------------------------------------------
argv1 = sys.argv[1]			# 引数1
argv2 = sys.argv[2]			# 引数1
argv3 = sys.argv[3]			# 引数1
argv4 = sys.argv[4]			# 引数1
file  = sys.argv[5]			# 画像

print("img_cut2... " + file)

img = Image.open(file)
dst = img.copy()
dst = img.crop((int(argv1), int(argv2), int(argv3), int(argv4)))


if(file == "GTS_TIT_03.bmp"):
	dw = ImageDraw.Draw(dst)
	dw.rectangle([(80, 300), (380, 319)], fill=10)
	dw.rectangle([(126, 291), (380, 299)], fill=10)

	tm = img.crop((497, 359, 614, 378))
	dst.paste(tm, (331, 301))


img.close()

# dst.show()
# dst.save("TEST.bmp")
dst.save(file)


