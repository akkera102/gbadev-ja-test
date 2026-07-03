#ifndef __MUS_H__
#define __MUS_H__
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

} ST_MUS;


//---------------------------------------------------------------------------
void MusInit(void);
void MusPlay(s32 no, bool isLoop);
void MusLock(void);
void MusLoad(void);

void MusStop(void);


#ifdef __cplusplus
}
#endif
#endif
