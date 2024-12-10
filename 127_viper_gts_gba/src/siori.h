#ifndef __SIORI_H__
#define __SIORI_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SIORI_MAX_CNT				3
#define SIORI_MAX_SIZE				(0x1000 - 16 - 2)

enum {
	SIORI_TYPE_SRAM = 1,
	SIORI_TYPE_FLASH,
};

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void  SioriInit(void);

EWRAM_CODE void  SioriSave(s32 no);
EWRAM_CODE void  SioriSaveFlashHeader(void);
EWRAM_CODE void  SioriSaveFlashData(s32 no);
EWRAM_CODE void  SioriSaveSramHeader(void);
EWRAM_CODE void  SioriSaveSramData(s32 no);
EWRAM_CODE void  SioriLoad(s32 no);
EWRAM_CODE u16   SioriGetVar(s32 no);

EWRAM_CODE bool  SioriIsExist(void);
EWRAM_CODE bool  SioriIsItem(s32 no);


#ifdef __cplusplus
}
#endif
#endif
