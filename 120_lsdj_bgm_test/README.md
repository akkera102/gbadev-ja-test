# 120_lsdj_bgm_test

2023/10/21: I made a new one. Look here.

[121_lsdj_bgm_test2](https://github.com/akkera102/gbadev-ja-test/tree/main/121_lsdj_bgm_test2)



It is often buggy and does not work as expected. ;)

## mechanism

This software is a custom modification of the InfoGB emulator. 

When the LSDj ROM is loaded, the first song displayed on the screen is played and a log is output.

This log is GB sound log information, but it is changed to GBA and reused to produce sound.

GBA makes 6 calls per frame and outputs the log. This mechanism was based on lsdpack.

## lsdsng data

Sample data used is a file in the LSDJ resources folder. The license is MIT.

HFF command is required at the end of the song.

## conversion work

lsdj.gb(v8.5.1)

Place it in the exe folder and run lsdj2log.exe.

## link

- [lsdpack](https://github.com/jkotlinski/lsdpack)

- [InfoGB](https://github.com/jay-kumogata/InfoGB)

- [libLSDJ](https://github.com/stijnfrishert/libLSDJ)

## lisence

My source code(CC0)

InfoGB(GPL2)

libgba(LGPL2.0 dynamic link)

crt0.s(MPL2.0)

## version

v0.01 intial ver.
