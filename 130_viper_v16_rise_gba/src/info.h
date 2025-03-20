#ifndef __INFO_H__
#define __INFO_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define INFO_MAX_LIST_CNT				54


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void  InfoInit(void);

EWRAM_CODE s32   InfoGetPrev(s32 idx);
EWRAM_CODE s32   InfoGetPrev2(s32 idx);
EWRAM_CODE s32   InfoGetNext(s32 idx);
EWRAM_CODE s32   InfoGetNext2(s32 idx);
EWRAM_CODE char* InfoGetTxt(s32 idx);
EWRAM_CODE char* InfoGetFile(s32 idx);


#ifdef __cplusplus
}
#endif
#endif
