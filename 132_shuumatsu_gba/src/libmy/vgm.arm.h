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
#define VGM_VOL_MAX_CNT		9
#define VGM_VOL_DEF_CNT		6				// 0-9


//---------------------------------------------------------------------------

enum {
	VGM_ACT_STOP,
	VGM_ACT_PLAY,
};

typedef struct {

	s32  act;
	s32  vol;

	u8*  pCur;
	u8*  pFile;
	bool isLoop;

} ST_VGM;


//---------------------------------------------------------------------------
void VgmInit(void);

IWRAM_CODE void VgmPlay(u8* pFile, bool isLoop);
IWRAM_CODE void VgmStop(void);

IWRAM_CODE void VgmSetVol(s32 vol);
IWRAM_CODE s32  VgmGetVol(void);

IWRAM_CODE bool VgmIsPlay(void);

IWRAM_CODE void VgmIntrVblank(void);


#ifdef __cplusplus
}
#endif
#endif
