#ifndef __DIV_H__
#define __DIV_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"

IWRAM_CODE s32 Div(s32 Number, s32 Divisor);
IWRAM_CODE s32 Mod(s32 Number, s32 Divisor);
IWRAM_CODE u32 Abs(s32 Number, s32 Divisor);


#ifdef __cplusplus
}
#endif
#endif
