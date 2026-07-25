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

} ST_MUS;


//---------------------------------------------------------------------------
void MusInit(void);
void MusPlay(void);
void MusStop(void);


#ifdef __cplusplus
}
#endif
#endif
