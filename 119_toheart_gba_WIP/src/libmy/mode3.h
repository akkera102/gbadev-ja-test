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

IWRAM_CODE void Mode3DrawBg(u16* pImg);
IWRAM_CODE void Mode3DrawScroll(u16* pImg1, u16* pImg2);
IWRAM_CODE void Mode3Draw(u32 cnt);

IWRAM_CODE void Mode3DrawCrop(u32 sx, u32 sy, u32 cx, u32 cy, u16* pImg);
IWRAM_CODE void Mode3DrawClip(u32 sx, u32 sy, u32 cx, u32 cy, u32 gx, u32 gy, u32 gs, u16* pImg);
IWRAM_CODE void Mode3DrawBlend(u32 sx, u32 sy, u32 cx, u32 cy, u16* pImg, u8* pMsk);
IWRAM_CODE void Mode3Copy(u32 sx, u32 sy, u32 cx, u32 cy);
IWRAM_CODE void Mode3Scroll(u32 cnt);

IWRAM_CODE void Mode3SetDraw(void);
IWRAM_CODE void Mode3DrawFill(u16 col);;
IWRAM_CODE void Mode3DrawLineH(s32 sx);
IWRAM_CODE void Mode3DrawCopyH(s32 sx);
IWRAM_CODE void Mode3DrawFadeMask(s32 step);
IWRAM_CODE void Mode3DrawWipeTtoB(s32 step);
IWRAM_CODE void Mode3DrawTitle(s32 step);
IWRAM_CODE void Mode3DrawVibrate(s32 step);
IWRAM_CODE void Mode3DrawScaling(s32 step);
IWRAM_CODE void Mode3DrawCurtain(s32 step);
IWRAM_CODE void Mode3DrawCurtain2(s32 step);


#ifdef __cplusplus
}
#endif
#endif
