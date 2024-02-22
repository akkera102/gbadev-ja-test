# coding: Shift_JIS
# パレット番号0を黒色に変える。一部は全体的に変更

import os
import sys
import struct
from PIL import Image

# エンディング　スタッフクレジット
listStaff = [
  "stl01.png", "stl02.png", "stl03.png", "stl04.png", "stl05.png",
  "stl06.png", "stl07.png", "stl08.png", "stl09.png", "stl10.png",
  "stl11.png",
]

# 無視リスト　パレット０を使用
listIgnore = [
  "e10.png", "e16.png", "e001.png", "e002a.png", "e002b.png",
  "e006.png", "e013.png", "e015a.png", "e015a2.png", "e015b.png",
  "e015c.png", "e015d.png", "e021a.png", "e021b.png", "e021c.png",
  "e022a.png", "e022b.png", "e022b2.png", "e022c.png", "e022d.png",
  "e025.png", "e026.png", "e028.png", "e030a1.png", "e030b.png",
  "e031a.png", "e031b.png", "e034a1.png", "e034a2.png", "e034a3.png",
  "e034b.png", "e036.png", "e039a.png", "e039b.png", "e040.png",
  "e043.png", "e045a.png", "e045b.png", "e45b.png", "e046a.png",
  "e046b.png", "e051.png", "e056a.png", "e056b.png", "e056c.png",
  "e061.png", "e062a.png", "e062b.png", "e063a.png", "e063b.png",
  "en01.png", "en02.png", "en03.png", "en04.png", "en06.png",
  "en07a1.png", "en07a2.png", "en07b.png",
]

# ---------------------------------------------------------------------------
def Palette(file):

  # 背景画像　一部を除いて変更しない
  if file[0] == 'b' and file[1] == 'g':
    if file != "bg15b.png" and file != "bg15c.png" and file != "bg18.png":
      return

  # 無視リスト
  if file in listIgnore:
    return

  img = Image.open(file)
  pal = img.getpalette()
  iw, ih = img.size


  # 最大画像　エンディングのニース絵(s005)は例外
  if iw == 640 and ih == 400 and file != "s005.png":
    return

  # スクロール画像
  if iw == 480 and ih == 768:
    return

  # リストにある場合はパレット1-6変更
  if file in listStaff:
    for i in range(0, 16):
      if i >= 1 and i <= 6:
        pal[i*3+0] = 255
        pal[i*3+1] = 255
        pal[i*3+2] = 255
      else:
        pal[i*3+0] = 0
        pal[i*3+1] = 0
        pal[i*3+2] = 0
  else:
  # リストにない場合はパレット0変更
    pal[0] = 0
    pal[1] = 0
    pal[2] = 0

  img.putpalette(pal)
  img.save(file)
  img.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_pal... " + file)
Palette(file)
