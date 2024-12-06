#ifndef __INFO_H__
#define __INFO_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void  InfoInit(void);

EWRAM_CODE s32   InfoGetVarPrev(s32 var);
EWRAM_CODE s32   InfoGetVarPrev2(s32 var);
EWRAM_CODE s32   InfoGetVarNext(s32 var);
EWRAM_CODE s32   InfoGetVarNext2(s32 var);
EWRAM_CODE char* InfoGetStr(s32 var);


#ifdef __cplusplus
}
#endif
#endif
