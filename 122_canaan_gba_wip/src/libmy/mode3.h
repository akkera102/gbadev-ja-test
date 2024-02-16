#ifndef __MODE3_H__
#define __MODE3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define MODE3_MAX_BUF_SIZE			(SCREEN_CX * SCREEN_CY * 2)
#define MODE3_MAX_MSK_SIZE			(SCREEN_CX * SCREEN_CY)


//---------------------------------------------------------------------------
typedef struct {

	bool isDraw;
	u16  buf[MODE3_MAX_BUF_SIZE] ALIGN(4);		// u16 240x160*2
	u8   msk[MODE3_MAX_MSK_SIZE] ALIGN(4);		// u8  240x160

} ST_MODE3;


//---------------------------------------------------------------------------
EWRAM_CODE void Mode3Init(void);
IWRAM_CODE void Mode3Exec(void);

IWRAM_CODE void Mode3DrawFull(u16* pImg);
IWRAM_CODE void Mode3DrawFull2(u16* pImg);
IWRAM_CODE void Mode3DrawCrop(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg);
IWRAM_CODE void Mode3DrawClip(s32 sx, s32 sy, s32 cx, s32 cy, s32 gx, s32 gy, s32 gs, u16* pImg);
IWRAM_CODE void Mode3DrawFill(u16 col);
IWRAM_CODE void Mode3DrawBlend(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg, u8* pMsk);
IWRAM_CODE void Mode3DrawPat(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg);

IWRAM_CODE void Mode3VramFull(u16* pImg);
IWRAM_CODE void Mode3VramCrop(s32 sx, s32 sy, s32 cx, s32 cy, s32 ex, s32 ey);
IWRAM_CODE void Mode3VramCrop2(s32 sx, s32 sy, s32 cx, s32 cy, s32 ex, s32 ey);
IWRAM_CODE void Mode3VramCrop3(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg);
IWRAM_CODE void Mode3VramLine(s32 sy, u16 col);
IWRAM_CODE void Mode3VramCopy(s32 sx, s32 sy, s32 cx, s32 cy);
IWRAM_CODE void Mode3VramScroll(u16* pImg, s32 y);

IWRAM_CODE void Mode3SetDraw(void);

#ifdef __cplusplus
}
#endif
#endif
