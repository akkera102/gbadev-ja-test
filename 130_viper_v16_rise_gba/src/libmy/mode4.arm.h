#ifndef __MODE4_H__
#define __MODE4_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define MODE4_BUF_MAX_SIZE		(SCREEN_CX * SCREEN_CY)
#define MODE4_BUF_PAL_SIZE		(256 * 2)
#define MODE4_BUF_ADR1			((u16*)0x6000000)
#define MODE4_BUF_ADR2			((u16*)0x600A000)


//---------------------------------------------------------------------------
typedef struct {

	bool isFlip;
	u16* pFront;
	u16* pBack;

} ST_MODE4;


//---------------------------------------------------------------------------
EWRAM_CODE void Mode4Init(void);
IWRAM_CODE void Mode4Exec(void);

IWRAM_CODE void Mode4DrawFill(u8 pal);
IWRAM_CODE void Mode4DrawParts(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg);
IWRAM_CODE void Mode4DrawScrollX(s32 x, u16* pImg);
IWRAM_CODE void Mode4DrawScrollY(s32 y, u16* pImg);
IWRAM_CODE void Mode4DrawScreen(u16* pImg);

IWRAM_CODE void Mode4SetPal(u16* pPal);
IWRAM_CODE void Mode4SetCol(s32 i, s32 r, s32 g, s32 b);
IWRAM_CODE void Mode4SetFlip(void);

#ifdef __cplusplus
}
#endif
#endif
