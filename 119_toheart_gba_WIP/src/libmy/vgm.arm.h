#ifndef VGM_H
#define VGM_H
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

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

} ST_VGM;

enum {
	VGM_ID_STOP,
	VGM_ID_PLAY,
	VGM_ID_PUASE,
};

//---------------------------------------------------------------------------
EWRAM_CODE void VgmInit(void);
EWRAM_CODE void VgmPlay(u8* pFile, bool isLoop);
IWRAM_CODE void VgmStop(void);
IWRAM_CODE void VgmIntrVblank(void);

EWRAM_CODE bool VgmIsEnd(void);

#ifdef __cplusplus
}
#endif
#endif
