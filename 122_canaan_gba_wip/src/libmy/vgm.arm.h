#ifndef __VGM_H__
#define __VGM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define VGM_CMD_WAIT 0x61			// wait vblank
#define VGM_CMD_EOM  0x66			// end of mark
#define VGM_CMD_WREG 0xb3			// write register



//---------------------------------------------------------------------------

enum {
	VGM_ACT_STOP,
	VGM_ACT_PLAY,
};

typedef struct {

	s32 act;
	u8* pCur;
	u8* pTop;
	u8* pNext;

} ST_VGM;

//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void);
IWRAM_CODE void VgmPlay(u8* p);
IWRAM_CODE void VgmStop(void);
IWRAM_CODE void VgmIntrVCount(void);

EWRAM_CODE bool VgmIsPlay(void);
EWRAM_CODE bool VgmIsPlayNext(void);

#ifdef __cplusplus
}
#endif
#endif
