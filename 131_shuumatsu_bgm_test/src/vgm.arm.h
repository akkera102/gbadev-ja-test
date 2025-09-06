#ifndef VGM_H
#define VGM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define VGM_CMD_WAIT 0x61	// wait vblank
#define VGM_CMD_EOM  0x66	// end of mark
#define VGM_CMD_WREG 0xb3	// write register


#define PLAYER_SOUNDCNT_H 0x02 // REG_SOUNDCNT_H
#define PLAYER_FADE_CNT 80	// frames


#define GPREG_START  0x10

#define GPREG_NR10   0x10 // AGB 0x60
#define GPREG_NR11   0x11 // AGB 0x62
#define GPREG_NR12   0x12 // AGB 0x63
#define GPREG_NR13   0x13 // AGB 0x64
#define GPREG_NR14   0x14 // AGB 0x65

#define GPREG_NR21   0x16 // AGB 0x68
#define GPREG_NR22   0x17 // AGB 0x69
#define GPREG_NR23   0x18 // AGB 0x6c
#define GPREG_NR24   0x19 // AGB 0x6d

#define GPREG_NR30   0x1a // AGB 0x70
#define GPREG_NR31   0x1b // AGB 0x72
#define GPREG_NR32   0x1c // AGB 0x73
#define GPREG_NR33   0x1d // AGB 0x74
#define GPREG_NR34   0x1e // AGB 0x75

#define GPREG_NR41   0x20 // AGB 0x78
#define GPREG_NR42   0x21 // AGB 0x79
#define GPREG_NR43   0x22 // AGB 0x7c
#define GPREG_NR44   0x23 // AGB 0x7d

#define GPREG_NR50   0x24 // AGB 0x80
#define GPREG_NR51   0x25 // AGB 0x81
#define GPREG_NR52   0x26 // AGB 0x84

#define GPREG_WAVE   0x30 // AGB 0x90

#define WAVE_LEN     0x10


#define AGREG_START  0x60

#define AGREG_NR10   0x60 // DMG 0x10
#define AGREG_NR11   0x62 // DMG 0x11
#define AGREG_NR12   0x63 // DMG 0x12
#define AGREG_NR13   0x64 // DMG 0x13
#define AGREG_NR14   0x65 // DMG 0x14

#define AGREG_NR21   0x68 // DMG 0x16
#define AGREG_NR22   0x69 // DMG 0x17
#define AGREG_NR23   0x6c // DMG 0x18
#define AGREG_NR24   0x6d // DMG 0x19

#define AGREG_NR30   0x70 // DMG 0x1a
#define AGREG_NR31   0x72 // DMG 0x1b
#define AGREG_NR32   0x73 // DMG 0x1c
#define AGREG_NR33   0x74 // DMG 0x1d
#define AGREG_NR34   0x75 // DMG 0x1e

#define AGREG_NR41   0x78 // DMG 0x20
#define AGREG_NR42   0x79 // DMG 0x21
#define AGREG_NR43   0x7c // DMG 0x22
#define AGREG_NR44   0x7d // DMG 0x23

#define AGREG_NR50   0x80 // DMG 0x24
#define AGREG_NR51   0x81 // DMG 0x25
#define AGREG_NR52   0x84 // DMG 0x26

#define AGREG_RESAMP 0x82 // AGB only
#define AGREG_BIAS_L 0x88 // AGB only
#define AGREG_BIAS_H 0x89 // AGB only

#define AGREG_WAVE   0x90 // DMG 0x30


//---------------------------------------------------------------------------
typedef struct {

	u8*  pCur;
	u8*  pFile;

	bool isLoop;

	u8   regs[0x30];
	u8   wave[0x10];

} ST_VGM;

typedef struct {

	u8   stat;
	bool isHeadset;
	bool isFade;
	u8   fadeCnt;
  u8   trId;
  u8   trIdReserve;
	u32	 startOffset;
  u8   mute;
  u8   volume;

	bool isWaveEdit;

} ST_VGM_PLAYER;

enum {
	PLAYER_STAT_STOP,
	PLAYER_STAT_PLAY,
	PLAYER_STAT_PAUSE,
	PLAYER_STAT_RESERVE,
};

//---------------------------------------------------------------------------
IWRAM_CODE void VgmPlayerInit(void);
IWRAM_CODE void VgmInit(void);
IWRAM_CODE void VgmStop(void);
IWRAM_CODE void VgmUpdSoundcntL(u8 dat);
IWRAM_CODE void VgmUpdSoundcntH(u8 dat);
IWRAM_CODE void VgmUpdWave(u8 adr, u8 dat);
IWRAM_CODE void VgmAdjustOffset(void);
IWRAM_CODE void VgmPlay(u8 trId);
IWRAM_CODE void VgmReserve(u8 trIdReserve);
IWRAM_CODE void VgmSetWave(u32 i, u32 dat);
IWRAM_CODE void VgmSetLoop(u32 loop);
IWRAM_CODE void VgmSetWaveEdit(u32 waveedit);
IWRAM_CODE void VgmSetHeadset(u32 headset);
IWRAM_CODE void VgmSetFade(u32 fade);
IWRAM_CODE void VgmSetStartOffset(u32 offset);
IWRAM_CODE void VgmSetMute(u8 mute);
IWRAM_CODE void VgmSetVolume(u8 volume);
IWRAM_CODE void VgmTick(void);

IWRAM_CODE u32  VgmGetOffsetPlay(void);
IWRAM_CODE u32  VgmGetIsLoop(void);
IWRAM_CODE u32  VgmGetAgReg(u32 i);
IWRAM_CODE u32  VgmGetWave(u32 i);

IWRAM_CODE u32  VgmGetStat(void);
IWRAM_CODE u32  VgmGetIsWaveEdit(void);
IWRAM_CODE u32  VgmGetIsHeadset(void);
IWRAM_CODE u32  VgmGetIsFade(void);
IWRAM_CODE u32  VgmGetFadeCnt(void);
IWRAM_CODE u32  VgmGetTrId(void);


#ifdef __cplusplus
}
#endif
#endif
