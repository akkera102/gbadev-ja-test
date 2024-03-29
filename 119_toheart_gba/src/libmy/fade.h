#ifndef __FADE_H__
#define __FADE_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool isSpr;
} ST_FADE;

//---------------------------------------------------------------------------
EWRAM_CODE void FadeInit(void);
EWRAM_CODE void FadeExec(void);

EWRAM_CODE void FadeSetMode(u32 mode, u32 cnt);
EWRAM_CODE void FadeSetBlack(u32 cnt);
EWRAM_CODE void FadeSetWhite(u32 cnt);

EWRAM_CODE void FadeSetSpr(bool is);


#ifdef __cplusplus
}
#endif
#endif
