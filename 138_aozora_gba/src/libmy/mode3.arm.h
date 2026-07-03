#ifndef __MODE3_H__
#define __MODE3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define MODE3_MAX_SCN_SIZE			(SCREEN_CX * SCREEN_CY)
#define MODE3_MAX_CHR_SIZE			(SCREEN_CX * SCREEN_CY / 2)


//---------------------------------------------------------------------------
typedef struct {

	s32 idx;
	u16 buf[MODE3_MAX_SCN_SIZE * 2] ALIGN(4);
	u16 chr[MODE3_MAX_CHR_SIZE * 1] ALIGN(4);
	u8  msk[MODE3_MAX_CHR_SIZE * 1] ALIGN(4);

} ST_MODE3;


//---------------------------------------------------------------------------
void Mode3Init(void);

IWRAM_CODE void Mode3DrawBg(u16* pImg);
IWRAM_CODE void Mode3DrawBg2(u16 col);
IWRAM_CODE void Mode3DrawChr(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg, u8* pAlp);
IWRAM_CODE void Mode3DrawIco(s32 sx, s32 sy, s32 cx, s32 cy, u32 bit, u16* pImg, u8* pAlp);

IWRAM_CODE void Mode3VramEffCopy(void);
IWRAM_CODE void Mode3VramEffZiri(s32 cnt);
IWRAM_CODE void Mode3VramEffAlpha(s32 cnt);

IWRAM_CODE void Mode3FlipBuf(void);

#ifdef __cplusplus
}
#endif
#endif
