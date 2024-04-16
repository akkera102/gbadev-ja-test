#ifndef __ANIME_H__
#define __ANIME_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define ANIME_MAX_PAT_CNT			11
#define ANIME_MAX_DAT_CNT			3
#define ANIME_MAX_STR_SIZE			10

enum {
	ANIME_ACT_END,
	ANIME_ACT_EXEC,
};

enum {
	ANIME_DAT_ENDING,
	ANIME_DAT_TITLE,
	ANIME_DAT_PATCH,
};

//---------------------------------------------------------------------------

typedef struct {

	s32   act;
	s32   dat;
	char* pCur;

	bool  isLoop;
	bool  isSkip;
	s32   wait;
	s32   arg;
	s32   var[4];

	s32   envFadeWait;
	s32   envSelCol;
} ST_ANIME;


typedef struct {
	char* pStr;
	void  (*pFunc)(void);

} ST_ANIME_TABLE;

//---------------------------------------------------------------------------
EWRAM_CODE void AnimeInit(void);
EWRAM_CODE void AnimeSetDat(s32 num);
EWRAM_CODE void AnimeSetArg(s32 num);

EWRAM_CODE void AnimeExec(void);
EWRAM_CODE void AnimeExecChk(void);

EWRAM_CODE void AnimeExecSet(void);
EWRAM_CODE void AnimeExecClear(void);
EWRAM_CODE void AnimeExecStr(void);
EWRAM_CODE void AnimeExecStrCls(void);
EWRAM_CODE void AnimeExecEffect(void);
EWRAM_CODE void AnimeExecWait(void);
EWRAM_CODE void AnimeExecBgm(void);
EWRAM_CODE void AnimeExecBgmStop(void);
EWRAM_CODE void AnimeExecSkip(void);
EWRAM_CODE void AnimeExecSkipMark(void);
EWRAM_CODE void AnimeExecEnd(void);

EWRAM_CODE bool AnimeIsExec(void);
EWRAM_CODE bool AnimeIsSkip(void);


#ifdef __cplusplus
}
#endif
#endif
