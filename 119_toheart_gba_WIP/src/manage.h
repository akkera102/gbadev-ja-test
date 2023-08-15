#ifndef __MANAGE_H__
#define __MANAGE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

enum {
	MANAGE_ACT_INIT,
	MANAGE_ACT_TITLE,
	MANAGE_ACT_NOVEL,
	MANAGE_ACT_LOG,
	MANAGE_ACT_MENU,
	MANAGE_ACT_ANIME,
};


//---------------------------------------------------------------------------
typedef struct {
	s32 act;

} ST_MANAGE;


//---------------------------------------------------------------------------
EWRAM_CODE void ManageInit(void);
EWRAM_CODE void ManageExec(void);

EWRAM_CODE void ManageExecInit(void);
EWRAM_CODE void ManageExecTitle(void);
EWRAM_CODE void ManageExecNovel(void);
EWRAM_CODE void ManageExecLog(void);
EWRAM_CODE void ManageExecMenu(void);
EWRAM_CODE void ManageExecAnime(void);

EWRAM_CODE void ManageSetInit(void);
EWRAM_CODE void ManageSetTitle(void);
EWRAM_CODE void ManageSetNovel(void);
EWRAM_CODE void ManageSetLog(void);
EWRAM_CODE void ManageSetMenu(void);
EWRAM_CODE void ManageSetAnime(void);


#ifdef __cplusplus
}
#endif
#endif
