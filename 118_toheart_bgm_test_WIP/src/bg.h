#ifndef __BG_H__
#define __BG_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define BG_MAX_CNT				4


//---------------------------------------------------------------------------
typedef struct {
	u32  mapBase;
	u16* mapBaseAdr;
	u32  tileBase;
	u16* tileBaseAdr;
} ST_BG;


//---------------------------------------------------------------------------
EWRAM_CODE void BgInit(void);
EWRAM_CODE void BgInitLcd(void);
EWRAM_CODE void Bg0Init(void);
EWRAM_CODE void Bg1Init(void);
EWRAM_CODE void Bg2Init(void);
EWRAM_CODE void Bg3Init(void);

IWRAM_CODE void BgDrawStr(s32 x, s32 y, char* s);
IWRAM_CODE void BgDrawPrintf(s32 sx, s32 sy, char* format, ...);


#ifdef __cplusplus
}
#endif
#endif
