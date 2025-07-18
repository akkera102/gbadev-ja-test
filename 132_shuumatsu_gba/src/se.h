#ifndef __SE_H__
#define __SE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	s32  no;

} ST_SE;

//---------------------------------------------------------------------------
void SeInit(void);

void SePlay(s32 no);
void SeStop(void);


#ifdef __cplusplus
}
#endif
#endif
