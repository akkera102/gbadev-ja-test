#ifndef __SE_H__
#define __SE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	s32 no;
	s32 cnt;

} ST_SE;

//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void);

EWRAM_CODE void SePlay(s32 cnt);
EWRAM_CODE void SeStop(void);
EWRAM_CODE void SeSetNo(s32 no);
EWRAM_CODE s32  SeGetNo(void);
EWRAM_CODE bool SeIsEnd(void);
EWRAM_CODE bool SeIsEnd2(void);


#ifdef __cplusplus
}
#endif
#endif
