# 121_lsdj_bgm_test2

## mechanism

This software is a custom modification of the LsdPack(libgambatte) emulator. 

When the LSDj ROM is loaded, Game Boy runs on DOS and outputs logs.

This logs is GB sound log information, but Convert to GBA and output sound.

GBA makes 6 calls per frame to read the log.

## lsdsng data

HFF command is required at the end of the song.

Sample data used is a file in the libLSDJ resources folder. The license is MIT.

## conversion work

lsdj.gb(v8.5.1)

Place it in the exe folder and run "lsdpack.exe -r lsdj.gb".

## link

- [lsdpack](https://github.com/jkotlinski/lsdpack)

- [libLSDJ](https://github.com/stijnfrishert/libLSDJ)

## lisence

My source code(CC0)

libgba(LGPL2.0 dynamic link)

crt0.s(MPL2.0)

## version

v0.01 intial ver.
