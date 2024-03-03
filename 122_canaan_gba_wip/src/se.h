#ifndef __SE_H__
#define __SE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool isWait;

} ST_SE;

//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void);

EWRAM_CODE void SePlay(u8* p);
EWRAM_CODE void SePlayFmx(s32 no, bool isWait);
EWRAM_CODE void SePlaySsg(s32 no, bool isWait);
EWRAM_CODE void SeStop(void);
EWRAM_CODE bool SeIsWait(void);


#ifdef __cplusplus
}
#endif
#endif
