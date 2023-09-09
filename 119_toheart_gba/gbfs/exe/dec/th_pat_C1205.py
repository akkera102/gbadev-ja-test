# coding: Shift_JIS
# C1205 マスクファイル修正（オリジナル画像の配色ミス）

import os
import sys
from PIL import Image

fname1 = "C1205_M.BMP"
fname2 = "C1206_M.BMP"

print ("patching " + fname1)

img1 = Image.open(fname1)
img2 = Image.open(fname2)

img1.paste(img2, (-1, -1))

img1.save("C1205_M.BMP")
