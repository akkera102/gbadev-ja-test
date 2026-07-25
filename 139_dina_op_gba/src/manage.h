#ifndef __MANAGE_H__
#define __MANAGE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

enum {
	MANAGE_ACT_INIT,
	MANAGE_ACT_LOGO,
	MANAGE_ACT_ANIME,
	MANAGE_ACT_EXIT,
};


//---------------------------------------------------------------------------

typedef struct {
	s32 act;

} ST_MANAGE;


//---------------------------------------------------------------------------
void ManageInit(void);

void ManageExec(void);
void ManageExecInit(void);
void ManageExecLogo(void);
void ManageExecAnime(void);
void ManageExecExit(void);


#ifdef __cplusplus
}
#endif
#endif
