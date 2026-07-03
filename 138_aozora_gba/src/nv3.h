#ifndef __NV3_H__
#define __NV3_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	char* cmd;
	void  (*pExec)(void);

} ST_NV_JUMP_TBL;

//---------------------------------------------------------------------------
void NvExecJump(void);
void NvExecJumpSub(void);

void NvExecJumpMes(void);
void NvExecJumpMlf(void);
void NvExecJumpGfx(void);
void NvExecJumpGlb(void);
void NvExecJumpGlg(void);
void NvExecJumpClg(void);
void NvExecJumpCfr(void);
void NvExecJumpMus(void);
void NvExecJumpSnd(void);
void NvExecJumpVfl(void);
void NvExecJumpVfw(void);
void NvExecJumpIf0(void);
void NvExecJumpIfe(void);
void NvExecJumpGo0(void);
void NvExecJumpSet(void);
void NvExecJumpSel(void);
void NvExecJumpCas(void);
void NvExecJumpBrk(void);
void NvExecJumpSee(void);
void NvExecJumpWas(void);
void NvExecJumpWam(void);
void NvExecJumpEnd(void);

void NvExecJumpSjis(void);


#ifdef __cplusplus
}
#endif
#endif
