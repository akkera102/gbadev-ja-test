# coding: Shift_JIS

import os
import sys
import struct
from PIL import Image

# ---------------------------------------------------------------------------
def Resize(file):
  p = Image.open(file)
  iw, ih = p.size

  if iw == 96 and ih == 96:
    # 顔
    iw =  56
    ih =  56
  elif iw == 480 and ih == 176:
    # 小背景
    iw = 240
    ih =  88
  elif iw == 480 and ih == 768:
    # スクロール背景
    iw = 240
    ih = 384
  elif iw == 480 and ih == 288:
    # 大背景
    iw = 240
    ih = 144
  elif iw == 640 and ih == 400:
    # フルサイズ
    iw = 240
    ih = 160
  elif iw == 96 and ih == 128:
    # パタパタアニメ
    iw =  64
    ih =  84
  elif iw == 96 and ih == 160:
    # パーティ編成表
    return
  elif iw == 320 and ih == 112:
    # エンディング会社名（stl）
    iw = 240
    ih =  76
  elif iw == 480 and ih == 304:
    # ティティ立ち絵（ca020a）
    iw = 240
    ih = 152
  elif iw == 536 and ih == 256:
    # エンディング背景（en00）
    iw = 240
    ih = 114
  elif iw == 536 and ih == 400:
    # エンディング背景（en4）
    iw = 240
    ih = 160
  elif iw == 480 and ih == 320:
    # 最終ボス変形背景（bg15b,c）
    iw = 240
    ih = 160
  elif iw == 240 and ih == 160:
    # GBA枠用（waku06b）
    return
  elif iw == 240 and ih == 288:
    # 左半分画像の加工済
    iw = 120
    ih = 144
  elif iw == 480 and ih == 432:
    # 抱擁(e050)
    iw = 240
    ih = 216
  else:
    print("Error Size : %s %d %d" % (file, iw, ih))
    return

  p = p.convert("RGB")
  p = p.resize((iw, ih), Image.LANCZOS)
  p.save(file)
  p.close()

# ---------------------------------------------------------------------------
file = sys.argv[1]

print ("png_size... " + file)
Resize(file)
