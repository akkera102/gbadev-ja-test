#ifndef __BGM_H__
#define __BGM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool  isPlay;
	bool  isLoop;
	char* p;

} ST_BGM;


//---------------------------------------------------------------------------
EWRAM_CODE void BgmInit(void);

EWRAM_CODE void BgmPlay(char* p, bool isLoop);
EWRAM_CODE void BgmPlay2(char* p, bool isLoop);
EWRAM_CODE void BgmPlayLoad(void);
EWRAM_CODE void BgmStop(void);


#ifdef __cplusplus
}
#endif
#endif
