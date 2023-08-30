#ifndef __NV3_H__
#define __NV3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
IWRAM_CODE u32  NvGetCurNum(void);
IWRAM_CODE u32  NvGetCurHex(void);
IWRAM_CODE void NvSetCurStr(void);

IWRAM_CODE void NvSetSelStr(u32 no);

IWRAM_CODE void NvSkipCurLine(void);
IWRAM_CODE void NvSkipCurLine2(s32 cnt);
IWRAM_CODE void NvSkipCurSpace(void);
IWRAM_CODE void NvSkipCurChr(u8 chr);

IWRAM_CODE void NvJumpCurAdr(u16 adr);


#ifdef __cplusplus
}
#endif
#endif
