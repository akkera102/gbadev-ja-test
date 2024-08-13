#ifndef __SE_H__
#define __SE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool  isLoop;
	s32   no;

} ST_SE;

//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void);

EWRAM_CODE void SePlay(s32 no, bool isLoop);
EWRAM_CODE void SePlay2(s32 no);
EWRAM_CODE void SePlayLoad(void);
EWRAM_CODE void SeStop(void);
EWRAM_CODE bool SeIsLoopNo(s32 no);



#ifdef __cplusplus
}
#endif
#endif
