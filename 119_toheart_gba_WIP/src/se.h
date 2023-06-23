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

} ST_SE;

//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void);

EWRAM_CODE void SePlay(s32 cnt);
EWRAM_CODE void SeStop(void);
EWRAM_CODE void SeSetNo(s32 no);
EWRAM_CODE bool SeIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
