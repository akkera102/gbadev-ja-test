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

void FadeSetBlend(s32 mode, s32 bldy, s32 l, s32 r, s32 t, s32 d);
void FadeSetBlack(s32 bldy);
void FadeSetWhite(s32 bldy);
void FadeSetMsg(s32 bldy);


#ifdef __cplusplus
}
#endif
#endif
