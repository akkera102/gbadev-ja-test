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
#define PLAYER_FADE_CNT 96	// frames


//---------------------------------------------------------------------------
typedef struct {

	u8*  pCur;
	u8*  pFile;

	bool isLoop;

	u8   regs[0x28];
	u8   wave[0x10];

} ST_VGM;

typedef struct {

	u8   stat;
	u8   fadeCnt;
	u8*  pNextFile;
	bool isFade;
	bool isHeadset;

} ST_VGM_PLAYER;

enum {
	PLAYER_STAT_STOP,
	PLAYER_STAT_PLAY,
	PLAYER_STAT_PAUSE,
	PLAYER_STAT_RESERVE,
};

//---------------------------------------------------------------------------
EWRAM_CODE void VgmPlayerInit(void);
EWRAM_CODE void VgmInit(void);
IWRAM_CODE void VgmStop(void);
IWRAM_CODE void VgmUpdSoundcntL(u8 dat);
IWRAM_CODE void VgmUpdSoundcntH(u8 dat);
IWRAM_CODE void VgmPatchHeadset(u8 adr, u8 dat);

EWRAM_CODE void VgmPlay(u8* pFile);
EWRAM_CODE void VgmReserve(u8* pNextFile);
IWRAM_CODE void VgmSetLoop(u32 loop);
IWRAM_CODE void VgmSetFade(u32 fade);
IWRAM_CODE void VgmSetHeadset(u32 headset);
IWRAM_CODE void VgmTick(void);

EWRAM_CODE u32  VgmGetOffsetPlay(void);
EWRAM_CODE u32  VgmGetIsLoop(void);
EWRAM_CODE u32  VgmGetWave(u32 i);
EWRAM_CODE u32  VgmGetRegs(u32 i);

EWRAM_CODE u32  VgmGetStat(void);
EWRAM_CODE u32  VgmGetIsFade(void);
EWRAM_CODE u32  VgmGetFadeCnt(void);
EWRAM_CODE u32  VgmGetIsHeadset(void);

#ifdef __cplusplus
}
#endif
#endif
