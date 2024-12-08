#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
songraw(改造lsdpackで出力した改造LSDjのAPUログ)をgPSG(vgm2gbaで出力されるbinファイルの仕様)に変換するやつ

vgm2gbaのソースをPythonに移植したものがベースです。オリジナルがCC0なのでこれもCC0で
https://github.com/akkera102/gbadev-ja-test/blob/main/116_vgm2gba_vblank/src/tool/vgm2gba/vgm2gba.c
"""

import os
import sys
import argparse
import binascii
import re

from decimal import Decimal, ROUND_HALF_UP, ROUND_HALF_EVEN
import math


def hex4(b):
    return hex(int(b))[2:]

def hex8(b):
    return hex(b)[2:].zfill(2)

# 実験中の機能、波形メモリの音をマイルドに
# def wavround(f, center, clean, shift):
#     num = int(Decimal(str(10*f)).quantize(Decimal('0'), rounding=ROUND_HALF_UP))

#     if clean: #端数切り捨て
#         if center*10 <= num:
#             # print(f"upper {num/10} -> {math.floor(num/10.0)}")
#             return hex4(math.floor(num/10)+shift)
#         else:
#             # print(f"lower {num/10} -> {math.ceil(num/10.0)}")
#             return hex4(math.ceil(num/10)+shift)
#     else: #boost 端数切り上げ
#         if center*10 <= num:
#             # print(f"upper {num/10} -> {math.ceil(num/10.0)}")
#             return hex4(math.ceil(num/10)+shift)
#         else:
#             # print(f"lower {num/10} -> {math.floor(num/10.0)}")
#             return hex4(math.floor(num/10)+shift)

def adr2gba(adr):
    match adr:
        case 0x10: adr = 0x60; # NR 10
        case 0x11: adr = 0x62; # NR 11
        case 0x12: adr = 0x63; # NR 12
        case 0x13: adr = 0x64; # NR 13
        case 0x14: adr = 0x65; # NR 14
        case 0x16: adr = 0x68; # NR 21
        case 0x17: adr = 0x69; # NR 22
        case 0x18: adr = 0x6c; # NR 23
        case 0x19: adr = 0x6d; # NR 24
        case 0x1a: adr = 0x70; # NR 30
        case 0x1b: adr = 0x72; # NR 31
        case 0x1c: adr = 0x73; # NR 32
        case 0x1d: adr = 0x74; # NR 33
        case 0x1e: adr = 0x75; # NR 34
        case 0x20: adr = 0x78; # NR 41
        case 0x21: adr = 0x79; # NR 42
        case 0x22: adr = 0x7c; # NR 43
        case 0x23: adr = 0x7d; # NR 44
        case 0x24: adr = 0x80; # NR 50
        case 0x25: adr = 0x81; # NR 51
        case 0x26: adr = 0x84; # NR 52
        # RAM
        case 0x30 | 0x31 | 0x32 | 0x33 | 0x34 | 0x35 | 0x36 | 0x37 | 0x38 | 0x39 | 0x3a | 0x3b | 0x3c | 0x3d | 0x3e | 0x3f:
            adr = 0x90 + (adr) - 0x30;
        case _:
            raise ValueError(f"Error!! adr2gba: {hex8(adr)}")
            return null

    return adr

def dat2gba(adr, dat):
    if adr == 0x70: # NR 30
        dat &= 0x80;
    if adr == 0x73: # NR 32
        dat &= 0x60;
    # RAM
    # if adr == 0x90 or adr == 0x91 or adr == 0x92 or adr == 0x93 or adr == 0x94 or adr == 0x95 or adr == 0x96 or adr == 0x97 or adr == 0x98 or adr == 0x99 or adr == 0x9a or adr == 0x9b or adr == 0x9c or adr == 0x9d or adr == 0x9e or adr == 0x9f:
    #     multiplier = 1.5 #GBAは音割れしやすいので小さめに
    #     center = 7 #波形メモリの無音状態を決める、7か8
    #     shift = -6
    #     clean = True #GBAはTrue(端数切捨)のほうがよさそう

    #     upper = wavround(((int(hex4(dat)[0], 16)-center)*multiplier)+center, center, clean, shift)
    #     lower = wavround(((int(hex4(dat)[1], 16)-center)*multiplier)+center, center, clean, shift)
    #     # print(f"{dat:02x} -> {upper}{lower}")

    #     dat = int(f"0x{upper}{lower}",16)
    if adr == 0x80 and dat & 0x08: # NR 50
        printf("Warning: no use GBA bit. NR 50(FF24) Right Flag.\n");
    if adr == 0x80 and dat & 0x80: # NR 50
        printf("Warning: no use GBA bit. NR 50(FF24) Left Flag.\n");

    return dat

def convert(songraw):
    tickcnt = 0
    inphrasecnt = 0
    tickcnt_inphrase = 2 # 今回のデータは1小節＝2phrase
    tickcnt_list = []
    datalist = []

    o_type = "none"
    p = r'\_l(.*\d)[\_\.]'  # _l???. ループ開始位置をファイル名から読み取る
    r = re.findall(p, songraw)
    if(len(r) != 0):
        if("p"==r[0][0]): # 何番目のphraseか
            o_type = "phrase"
        elif("w"==r[0][0]): # 十進でTick数を直接指定する
            o_type = "write"
        o_prm = int(r[0][1:])

    filename = songraw.split("_all_")[0]

    with open(songraw, "r") as infp:
        txt = infp.read()

        # LoopOffset
        isLoop = False
        offset = 0
        phr_cnt = 0

        for line in txt.split("\n"):
            if 0 == len(line):
                continue
            elif line.startswith(";- TICK_STAT"):
                datalist.append(0x61.to_bytes(1,"big"))
                tickcnt = tickcnt+1
                continue
            elif not line.startswith(";-"):
                _tmp = line.split(" ;-")[0].split(",")

                # Timer割込(LSDj-Tempo)用なので不要
                if "27" == _tmp[0]:
                    continue
                adr = adr2gba(int("0x"+_tmp[0], 16))
                dat = dat2gba(adr, int("0x"+_tmp[1], 16))

                # print(f"{index}: {hex8(cmd[0])} {hex8(adr)} {hex8(dat)}")
                datalist.append(0xb3.to_bytes(1,"big"))
                datalist.append(adr.to_bytes(1,"big"))
                datalist.append(dat.to_bytes(1,"big"))

                # wave adr?
                if adr >= 0x90 and adr <= 0x9f:
                    datalist.append(0xb3.to_bytes(1,"big"))
                    datalist.append(0x70.to_bytes(1,"big"))
                    datalist.append(0x40.to_bytes(1,"big"))
                continue
            elif line.startswith(";-- CH"):
                if(o_type == "phrase" and o_prm == phr_cnt):
                    offset = len(datalist)
                phr_cnt = phr_cnt+1
                if line.startswith(";-- CH01") and 0 != tickcnt:
                    inphrasecnt = inphrasecnt+1
                    if inphrasecnt == tickcnt_inphrase:
                        tickcnt_list.append(tickcnt)
                        tickcnt = 0
                        inphrasecnt = 0

                continue
            elif line.startswith(";---- PHRASE"):
                continue
            elif line.startswith(";--- STEP"):
                continue

            raise ValueError(f"Error!!: [{line}] (len: {len(line)})")

        # write end of mark
        datalist.append(0x66.to_bytes(1,"big"))

        if("write" == o_type):
            loopOffset = f"{o_prm:08X}";
        else:
            loopOffset = f"{offset:08X}";

        # write loop offset
        datalist.append(bytes.fromhex(loopOffset[6:8]))
        datalist.append(bytes.fromhex(loopOffset[4:6]))
        datalist.append(bytes.fromhex(loopOffset[2:4]))
        datalist.append(bytes.fromhex(loopOffset[0:2]))

        # zero pading
        for i in range((0x10 - len(datalist))%0x10):
            datalist.append(0x00.to_bytes(1,"big"))

        print(f"{filename}.gpsg  Offset: {loopOffset}  DataLength: {len(datalist):08X}");

        # _cnts = set(tickcnt_list)
        # if 1 == len(_cnts):
        #     print(_cnts)
        # else:
        #     print(tickcnt_list)

    with open(f"{filename}.gpsg", "wb") as outfp:
        for data in datalist:
            outfp.write(data)

def parse_argv(argv):
    p = argparse.ArgumentParser()
    p.add_argument("path")
    return p.parse_args(argv[1:])

def main(argv=None):
    args = parse_argv(argv or sys.argv)

    if(os.path.isfile(args.path)):
        convert(args.path)
    elif(os.path.isdir(args.path)):
        files = [f for f in os.listdir(args.path) if f.endswith('.songraw') == True]
        for filepath in files:
            convert(f"{args.path}/{filepath}")
    else:
        print(".songraw not found.")


if __name__ == '__main__':
    main()
