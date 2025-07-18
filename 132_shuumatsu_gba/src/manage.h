#ifndef __MANAGE_H__
#define __MANAGE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

enum {
	MANAGE_ACT_INIT,
	MANAGE_ACT_NV,
	MANAGE_ACT_SEL,
	MANAGE_ACT_LOG,
	MANAGE_ACT_RES,
	MANAGE_ACT_MENU,
};


//---------------------------------------------------------------------------

typedef struct {
	s32 act;
	s32 prv;

} ST_MANAGE;


//---------------------------------------------------------------------------
void ManageInit(void);

void ManageExec(void);
void ManageExecInit(void);
void ManageExecNv(void);
void ManageExecSel(void);
void ManageExecLog(void);
void ManageExecRes(void);
void ManageExecMenu(void);

void ManageSetAct(s32 act);

bool ManageIsPrv(s32 act);


#ifdef __cplusplus
}
#endif
#endif
