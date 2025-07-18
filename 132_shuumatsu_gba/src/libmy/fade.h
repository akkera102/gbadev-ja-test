#ifndef __FADE_H__
#define __FADE_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FadeInit(void);

void FadeSetBlend(s32 mode, s32 cnt);
void FadeSetBlack(s32 cnt);
void FadeSetWhite(s32 cnt);


#ifdef __cplusplus
}
#endif
#endif
