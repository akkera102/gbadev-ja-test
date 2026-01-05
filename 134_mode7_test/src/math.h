#ifndef __MATH_H__
#define __MATH_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void MathInit(void);

s16 MathSin(u16 theta);
s16 MathCos(u16 theta);
u32 MathDiv(u8 x);


#ifdef __cplusplus
}
#endif
#endif
