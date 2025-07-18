#ifndef __CUR_H__
#define __CUR_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool isExec;
	s32  spr;
	s32  cnt;
	s32  max;
	s32  wait;
	s32  blink;

} ST_CUR;

//---------------------------------------------------------------------------
void CurInit(void);
void CurExec(void);

void CurSetLf(void);
void CurSetPage(void);
void CurSetExec(void);

void CurShow(void);
void CurHide(void);

bool CurIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
