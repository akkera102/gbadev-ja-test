#ifndef __VGM_H__
#define __VGM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define VGM_CMD_WAIT		0x61			// wait vblank
#define VGM_CMD_EOM			0x66			// end of mark
#define VGM_CMD_WREG		0xb3			// write register
#define VGM_VOL_MAX_CNT		12
#define VGM_VOL_DEF_CNT		12				// 0-12


//---------------------------------------------------------------------------

enum {
	VGM_ACT_STOP,
	VGM_ACT_PLAY,
	VGM_ACT_PLAY_NEXT,
	VGM_ACT_PLAY_FADE,
	VGM_ACT_PAUSE,
};

typedef struct {

	s32  act;
	s32  vol;
	s32  fade;

	u8*  pCur;
	u8*  pFile;
	u8*  pFile2;
	bool isLoop;
	bool isLoop2;

} ST_VGM;


//---------------------------------------------------------------------------
void VgmInit(void);
void VgmInit2(void);

void VgmPlay(u8* pFile, bool isLoop);
void VgmPlayFade(void);
void VgmStop(void);

void VgmSetVolReg(s32 vol);
void VgmSetVol(s32 vol);

s32  VgmGetVol(void);
s32  VgmGetMaxVol(void);

bool VgmIsPlay(void);

IWRAM_CODE void VgmIntrVblank(void);


#ifdef __cplusplus
}
#endif
#endif
