#ifndef __NAVI_H__
#define __NAVI_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	bool isExec;
	s32  sel;

} ST_NAVI;

//---------------------------------------------------------------------------
void NaviInit(void);
void NaviExec(void);

void NaviSetExec(s32 sel);
void NaviShow(void);
void NaviHide(void);

bool NaviIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
