#ifndef __NV3_H__
#define __NV3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void NvExprPush(bool is);
void NvExprPop(void);
void NvExprFlip(void);
bool NvIsExpr(void);


#ifdef __cplusplus
}
#endif
#endif
