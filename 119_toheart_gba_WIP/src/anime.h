#ifndef __ANIME_H__
#define __ANIME_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define ANIME_MAX_PAT_CNT			14
#define ANIME_MAX_DAT_CNT			3
#define ANIME_MAX_STR_SIZE			10

enum {
	ANIME_ACT_END,
	ANIME_ACT_EXEC,
};

enum {
	ANIME_DAT_LOGO,
	ANIME_DAT_OPENING,
	ANIME_DAT_ENDING,
};

//---------------------------------------------------------------------------
typedef struct {
	u32   act;
	char* pCur;

	bool  isLoop;
	bool  isSkip;

	u32   wait;
	s32   var;

} ST_ANIME;


typedef struct {
	char* pStr;
	void  (*pFunc)(void);

} ST_ANIME_TABLE;

//---------------------------------------------------------------------------
EWRAM_CODE void AnimeInit(void);
EWRAM_CODE void AnimeSetDat(u32 no);

EWRAM_CODE void AnimeExec(void);
EWRAM_CODE void AnimeExecSub(void);
EWRAM_CODE void AnimeExecBg(void);
EWRAM_CODE void AnimeExecVis(void);
EWRAM_CODE void AnimeExecChr(void);
EWRAM_CODE void AnimeExecStr(void);
EWRAM_CODE void AnimeExecStrCls(void);
EWRAM_CODE void AnimeExecEffect1(void);
EWRAM_CODE void AnimeExecEffect2(void);
EWRAM_CODE void AnimeExecWait(void);
EWRAM_CODE void AnimeExecBgm(void);
EWRAM_CODE void AnimeExecBgmStop(void);
EWRAM_CODE void AnimeExecSkip(void);
EWRAM_CODE void AnimeExecMark(void);
EWRAM_CODE void AnimeExecSprMode(void);
EWRAM_CODE void AnimeExecEnd(void);

EWRAM_CODE bool AnimeIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
