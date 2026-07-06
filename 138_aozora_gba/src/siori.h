#ifndef __SIORI_H__
#define __SIORI_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SIORI_MAX_ITEM_CNT			5
#define SIORI_MAX_PAGE_CNT			8

#define SIORI_MAX_ITEM_SIZE			0x100
#define SIORI_BASE_ITEM_ADR			0x2000

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void  SioriInit(void);

void  SioriSaveHeader(void);
void  SioriSaveItem(s32 no);
void  SioriLoadItem(s32 no);
void  SioriSaveLast(void);
void  SioriLoadLast(void);
void  SioriSaveRead(void);
void  SioriLoadRead(void);

char* SioriGetTitle(s32 no);

bool  SioriIsHeader(void);
bool  SioriIsItem(s32 no);


#ifdef __cplusplus
}
#endif
#endif
