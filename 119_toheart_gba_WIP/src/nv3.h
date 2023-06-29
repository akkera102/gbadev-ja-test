#ifndef __NV3_H__
#define __NV3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE u32  NvGetCurNum(void);
EWRAM_CODE u32  NvGetCurNum2(u8* pCur);
EWRAM_CODE u32  NvGetCurHex(void);
EWRAM_CODE u32  NvGetCurHex2(u8* pCur);
EWRAM_CODE void NvSetCurStr(void);

EWRAM_CODE void NvSkipCurLine(void);
EWRAM_CODE void NvSkipCurLine2(s32 cnt);
EWRAM_CODE void NvSkipCurSpace(void);

EWRAM_CODE void NvJumpCurAdr(u16 adr);
EWRAM_CODE u8*  NvSeekCurChr(u8 chr);


#ifdef __cplusplus
}
#endif
#endif
