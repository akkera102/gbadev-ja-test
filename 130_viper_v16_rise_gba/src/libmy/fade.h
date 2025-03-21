#ifndef __FADE_H__
#define __FADE_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FadeInit(void);

EWRAM_CODE void FadeSetScr(s32 mode, s32 cnt);
EWRAM_CODE void FadeSetBlack(s32 cnt);
EWRAM_CODE void FadeSetWhite(s32 cnt);
EWRAM_CODE void FadeSetWin(void);


#ifdef __cplusplus
}
#endif
#endif
