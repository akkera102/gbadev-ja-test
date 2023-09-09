#ifndef __REIN_H__
#define __REIN_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "libmy/tinymt32.h"

//---------------------------------------------------------------------------
#define REIN_MAX_DAT			32


//---------------------------------------------------------------------------

typedef struct {
	s16  wait;
	s16  x;
	s16  y;

} ST_REIN_DAT;

typedef struct {
	bool isEffect;

	tinymt32_t mt;
	ST_REIN_DAT dat[REIN_MAX_DAT];

} ST_REIN;


//---------------------------------------------------------------------------
EWRAM_CODE void ReinInit(void);
IWRAM_CODE void ReinExec(void);

EWRAM_CODE void ReinStart(void);
EWRAM_CODE void ReinStop(void);

IWRAM_CODE void ReinRegDat(u32 no);
EWRAM_CODE void ReinSeed(u32 rnd);
EWRAM_CODE s32  ReinRnd(s32 num);
EWRAM_CODE bool ReinIsEffect(void);


#ifdef __cplusplus
}
#endif
#endif
