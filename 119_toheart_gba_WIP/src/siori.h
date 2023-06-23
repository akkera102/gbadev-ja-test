#ifndef __SIORI_H__
#define __SIORI_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SIORI_MAX_CNT				8
#define SIORI_MAX_SIZE				0x1000

enum {
	SIORI_TYPE_SRAM,
	SIORI_TYPE_FLASH,
};

//---------------------------------------------------------------------------

typedef struct {
	u8  type;
	s32 size;

} ST_SIORI;



//---------------------------------------------------------------------------
EWRAM_CODE void  SioriInit(void);
EWRAM_CODE void  SioriSave(u32 no);
EWRAM_CODE void  SioriSaveSram(u32 no);
EWRAM_CODE void  SioriSaveFlash(u32 no);

EWRAM_CODE bool  SioriLoad(u32 no);
EWRAM_CODE char* SioriGetStr(u32 no);

EWRAM_CODE bool  SioriIsInit(void);
EWRAM_CODE bool  SioriIsItem(u32 no);


#ifdef __cplusplus
}
#endif
#endif
