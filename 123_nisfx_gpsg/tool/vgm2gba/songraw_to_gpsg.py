#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
songraw(改造済lsdpackと改造LSDjのAPUログ)をgPSG(vgm2gbaの変換済binの拡張仕様)に変換するやつ
毎秒 360 回、HBlank割込で再生することを想定したファイルに変換します(オリジナルのvgm2gbaは 60回/秒)

vgm2gbaのソースコードをCからPythonに書き換えたやつを拡張したスクリプトで、
違いは変換元が44.1kHz(VGM)か4.19MHz(songraw)かくらい

オリジナルがCC0なのでこれもCC0
https://github.com/akkera102/gbadev-ja-test/blob/main/116_vgm2gba_vblank/src/tool/vgm2gba/vgm2gba.c
"""

import sys
import argparse
import binascii
import re
from decimal import Decimal, ROUND_HALF_UP, ROUND_HALF_EVEN
import math

exportName = [
    "BEEP_pc9801vx21",
    "SSG6_c6_slap",
    "SSG8_c1_swordbreak",
    "SSG9_c2_swordatk",
    "SSG11_c1_hithead",
    "SSG14_c1_hitwall",
    "SSG15_c1_monsterfall",
    "SSG17_c61_slap2",
    "SSG18_c1_specialatk",
    "SSG21_c122_select",
    "SSG24_c6_bomb",
    "SSG26_c5_swordatk2",
    "SSG30_c4_swordatk3",
    "SSG31_c1_autherror",
    "SSG35_c2_authclear",
    "SSG40_c3_slap3",
    "SSG41_c8_slap4",
    "SSG42_c1_voltdrop",
    "SSG43_c2_slap5",
    "SSG44_c4_collapse",
    "SSG45_c3_magic",
    "FMX1_c1_fall",
    "FMX2_c1_fall2",
    "FMX4_c1_howl",
    "NIFMX1_storm",
    "NIFMX2_slap",
    "NIFMX3_menu",
    "NIFMX4_textfx",
]

def hex4(b):
    return hex(int(b))[2:]

def hex8(b):
    return hex(b)[2:].zfill(2)

# 実験中の機能(良く分からんけどあった方がいいっぽい？たぶん)
def wavround(f, center, clean):
    num = int(Decimal(str(10*f)).quantize(Decimal('0'), rounding=ROUND_HALF_UP))

    if clean: #端数切り捨て
        if center*10 <= num:
            # print(f"upper {num/10} -> {math.floor(num/10.0)}")
            return hex4(math.floor(num/10))
        else:
            # print(f"lower {num/10} -> {math.ceil(num/10.0)}")
            return hex4(math.ceil(num/10))
    else: #boost 端数切り上げ
        if center*10 <= num:
            # print(f"upper {num/10} -> {math.ceil(num/10.0)}")
            return hex4(math.ceil(num/10))
        else:
            # print(f"lower {num/10} -> {math.floor(num/10.0)}")
            return hex4(math.floor(num/10))

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
    if adr == 0x90 or adr == 0x91 or adr == 0x92 or adr == 0x93 or adr == 0x94 or adr == 0x95 or adr == 0x96 or adr == 0x97 or adr == 0x98 or adr == 0x99 or adr == 0x9a or adr == 0x9b or adr == 0x9c or adr == 0x9d or adr == 0x9e or adr == 0x9f:
        multi = 0.75
        center = 7
        clean = True #GBAはTrueのほうがよさそう
        upper = wavround(((int(hex4(dat)[0], 16)-center)*multi)+center, center, clean)
        lower = wavround(((int(hex4(dat)[1], 16)-center)*multi)+center, center, clean)
        # print(f"{dat:02x} -> {upper}{lower}")
        dat = int(f"0x{upper}{lower}",16)
    if adr == 0x80 and dat & 0x08: # NR 50
        printf("Warning: no use GBA bit. NR 50(FF24) Right Flag.\n");
    if adr == 0x80 and dat & 0x80: # NR 50
        printf("Warning: no use GBA bit. NR 50(FF24) Left Flag.\n");

    return dat

def statfix(txt):
    targets = re.findall(";- TICK\n.*?_STAT \\[.+?\\]\n", txt, flags=re.DOTALL)
    res = txt
    for target in targets:
        _tmp = target.split("\n")
        _tmp.pop() #空白除去
        _last = _tmp.pop()
        _tmp.insert(1, _last)
        _tmp.append("") #改行追加
        res = res.replace(target, "\n".join(_tmp).replace("TICK\n_STAT","TICK_STAT"))
    return res+"\n"

def parse_argv(argv):
    p = argparse.ArgumentParser()
    p.add_argument("songraw")
    # p.add_argument("tempo")
    # p.add_argument("fqset")
    # p.add_argument("loop_top")
    # p.add_argument("loop_btm")
    # p.add_argument("kit_pitch")
    return p.parse_args(argv[1:])

def main(argv=None):
    args = parse_argv(argv or sys.argv)

    sfxid = int(args.songraw.split("_")[-2])
    tick_cnt = 0
    datalist = []

    exportDebug = False

    filename  = f"lsdj_rec2_sfx_0_{sfxid}_all"

    with open(filename+".songraw", "r") as infp:
        # 処理と改行が挟まった状態のTICK_STATを修正しつつ読込
        txt = statfix(infp.read())
        if exportDebug:
            with open(filename+".psgraw", "w") as outfp:
                outfp.write(txt)

        # LoopOffset
        isLoop = False
        loopOffset = f"{0x0:08X}";

        for line in txt.split("\n"):
            if 0 == len(line):
                continue
            elif line.startswith(";- TICK_STAT"):
                datalist.append(0x61.to_bytes(1,"big"))
                tick_cnt = tick_cnt+1
                continue
            elif not line.startswith(";-"):
                _tmp = line.split(" ;-")[0].split(",")
                # 独自拡張(LSDj-Tempo)なので無視
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
                continue
            elif line.startswith(";---- PHRASE"):
                continue
            elif line.startswith(";--- STEP"):
                continue

            raise ValueError(f"Error!!: [{line}] (len: {len(line)})")

        # write end of mark
        datalist.append(0x66.to_bytes(1,"big"))

        # write loop offset
        datalist.append(bytes.fromhex(loopOffset[6:8]))
        datalist.append(bytes.fromhex(loopOffset[4:6]))
        datalist.append(bytes.fromhex(loopOffset[2:4]))
        datalist.append(bytes.fromhex(loopOffset[0:2]))

        # zero pading
        for i in range((0x10-len(datalist))%0x10):
            datalist.append(0x00.to_bytes(1,"big"))

        print(f"ID: {sfxid:02d}  Tick: {tick_cnt:04d}  DataLength: {len(datalist):08X}");

    with open(f"{sfxid:02d}-{exportName[sfxid]}.gpsg", "wb") as outfp:
        for data in datalist:
            outfp.write(data)


if __name__ == '__main__':
    main()
