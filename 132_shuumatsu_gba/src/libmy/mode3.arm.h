#ifndef __MODE3_H__
#define __MODE3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define MODE3_MAX_SCN_SIZE			(212 * SCREEN_CY)
#define MODE3_MAX_CPY_SIZE			(SCREEN_CX * SCREEN_CY)


//---------------------------------------------------------------------------
typedef struct {

	s32 idx;
	u16 buf[MODE3_MAX_SCN_SIZE * 2] ALIGN(4);
	u16 cpy[MODE3_MAX_CPY_SIZE * 1] ALIGN(4);

} ST_MODE3;


//---------------------------------------------------------------------------
void Mode3Init(void);

IWRAM_CODE void Mode3DrawBg(u16* pImg);
IWRAM_CODE void Mode3DrawChr(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg, u8* pMsk);

IWRAM_CODE void Mode3VramEffCls(s32 cnt, u8* pEff);
IWRAM_CODE void Mode3VramEffAlpha(s32 cnt);
IWRAM_CODE void Mode3VramCpyStep1(void);
IWRAM_CODE void Mode3VramCpyStep2(void);
IWRAM_CODE void Mode3VramDpx(u16* pImg);

IWRAM_CODE void Mode3ScrollX(s32 cnt);

IWRAM_CODE void Mode3FlipBuf(void);

#ifdef __cplusplus
}
#endif
#endif
