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
#define VGM_MAX_FADE_CNT	35				// frames


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
	s32  fade;
	bool isHeadset;

	u8*  pCur;
	u8*  pFile;
	u8*  pFile2;
	bool isLoop;
	bool isLoop2;

} ST_VGM;


//---------------------------------------------------------------------------
IWRAM_CODE void VgmInit(void);
IWRAM_CODE void VgmInit2(void);
IWRAM_CODE void VgmPlay(u8* pFile, bool isLoop);
IWRAM_CODE void VgmPlayFade(void);
IWRAM_CODE void VgmStop(void);

EWRAM_CODE void VgmSetHeadset(void);
EWRAM_CODE bool VgmIsHeadset(void);
EWRAM_CODE bool VgmIsPlay(void);

IWRAM_CODE void VgmIntrVblank(void);


#ifdef __cplusplus
}
#endif
#endif
