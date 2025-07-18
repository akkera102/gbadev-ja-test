#ifndef __SIORI_H__
#define __SIORI_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SIORI_MAX_CNT				8
#define SIORI_MAX_SIZE				(0x1000 - 0x16)

enum {
	SIORI_TYPE_SRAM = 1,
	SIORI_TYPE_FLASH,
};

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void  SioriInit(void);

void  SioriSave(s32 no);
void  SioriSaveFlashHeader(void);
void  SioriSaveFlashData(s32 no);
void  SioriSaveSramHeader(void);
void  SioriSaveSramData(s32 no);

void  SioriLoad(s32 no);
void  SioriLoadNvRead(void);

char* SioriGetTitle(s32 no);

bool  SioriIsExist(void);
bool  SioriIsItem(s32 no);


#ifdef __cplusplus
}
#endif
#endif
