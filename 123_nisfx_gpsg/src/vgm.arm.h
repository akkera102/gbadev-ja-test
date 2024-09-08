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



//---------------------------------------------------------------------------
typedef struct {

	u8   id;
	u8*  pCur;
	u8*  pFile;

	bool isLoop;
	u8   loopCnt;

	u8   regs[0x28];
	u8   wave[0x10];

} ST_VGM;

enum {
	VGM_ID_STOP,
	VGM_ID_PLAY,
	VGM_ID_PUASE,
};

//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void);
EWRAM_CODE void VgmPlay(u8* pFile, char* pName, u32 bias);
IWRAM_CODE void VgmSetLoop(u32 loop);
IWRAM_CODE void VgmStop(void);
IWRAM_CODE void VgmTick(void);

EWRAM_CODE u32  VgmGetOffsetPlay(void);
EWRAM_CODE u32  VgmGetIsLoop(void);
EWRAM_CODE u32  VgmGetLoopCnt(void);
EWRAM_CODE u32  VgmGetWave(u32 i);
EWRAM_CODE u32  VgmGetRegs(u32 i);

#ifdef __cplusplus
}
#endif
#endif
