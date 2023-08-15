#ifndef __SAKURA_H__
#define __SAKURA_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "libmy/tinymt32.h"

//---------------------------------------------------------------------------
#define SAKURA_MAX_DAT			32
#define SAKURA_MAX_WAIT			20

#define INT2FIX(n)				((n) << 7)
#define FIX2INT(n)				((n) >> 7)


//---------------------------------------------------------------------------

typedef struct {
	u8   type;
	u8   wait;
	u8   pat;
	s16  x;
	s16  y;
	s16  mx;
	s16  my;

} ST_SAKURA_DAT;

typedef struct {
	bool isEffect;

	tinymt32_t mt;
	ST_SAKURA_DAT dat[SAKURA_MAX_DAT];

} ST_SAKURA;


//---------------------------------------------------------------------------
EWRAM_CODE void SakuraInit(void);
EWRAM_CODE void SakuraInitRnd(u32 rnd);
EWRAM_CODE void SakuraExec(void);

EWRAM_CODE void SakuraStart(bool isScn);
EWRAM_CODE void SakuraRegDat(u32 no);
EWRAM_CODE void SakuraStop(void);
EWRAM_CODE s32  SakuraRnd(s32 num);
EWRAM_CODE bool SakuraIsEffect(void);


#ifdef __cplusplus
}
#endif
#endif
