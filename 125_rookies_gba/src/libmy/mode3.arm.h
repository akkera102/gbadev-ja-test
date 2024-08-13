#ifndef __MODE3_H__
#define __MODE3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define MODE3_MAX_GBA_SIZE			(SCREEN_CX * SCREEN_CY * 2)
#define MODE3_MAX_SCR_SIZE			(SCREEN_CX * 140 * 2)


//---------------------------------------------------------------------------
typedef struct {

	bool isDraw;
	u16  buf[SCREEN_CX * SCREEN_CY * 2] ALIGN(4);		// (240x160*2) * 2

} ST_MODE3;


//---------------------------------------------------------------------------
EWRAM_CODE void Mode3Init(void);
IWRAM_CODE void Mode3Exec(void);

IWRAM_CODE void Mode3DrawScr(u16* pImg);
IWRAM_CODE void Mode3DrawFill(u16 col);
IWRAM_CODE void Mode3DrawBg(s32 cx, s32 cy, u16* pImg);
IWRAM_CODE void Mode3DrawChr(s32 sx, s32 sy, s32 cx, s32 cy, u16* pS, u8* pM);
IWRAM_CODE void Mode3VramEff5(s32 step);
IWRAM_CODE void Mode3VramEff6(s32 step);
IWRAM_CODE void Mode3VramScrY(u16* pImg, s32 y);



IWRAM_CODE void Mode3SetDraw(void);

#ifdef __cplusplus
}
#endif
#endif
