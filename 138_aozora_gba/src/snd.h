#ifndef __SND_H__
#define __SND_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	s32  no;
	bool isLoop;
	bool isLock;

} ST_SND;

//---------------------------------------------------------------------------
void SndInit(void);
void SndPlay(s32 no, bool isLoop);
void SndLock(void);
void SndLoad(void);

void SndStop(void);


#ifdef __cplusplus
}
#endif
#endif
