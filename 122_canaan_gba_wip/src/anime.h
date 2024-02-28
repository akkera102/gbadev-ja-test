#ifndef __ANIME_H__
#define __ANIME_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define ANIME_MAX_PAT_CNT			24
#define ANIME_MAX_DAT_CNT			10
#define ANIME_MAX_STR_SIZE			10

enum {
	ANIME_ACT_END,
	ANIME_ACT_EXEC,
};

enum {
	ANIME_DAT_OPENING,
	ANIME_DAT_ENDING,
	ANIME_DAT_TITLE,
	ANIME_DAT_PATA1,		// ウルフィ→カイト
	ANIME_DAT_PATA2,		// カイト　→ウルフィ
	ANIME_DAT_PATA3,		// ウルフィ→ウルフィ
	ANIME_DAT_PATA4,		// カイト　→カイト
	ANIME_DAT_PATA5,		// ウルフィ→ラビィ
	ANIME_DAT_PATA6,		// ラビィ　→ウルフィ
	ANIME_DAT_NEXT_ROM,		// 後編ROMの入れ替えメッセージ
};

//---------------------------------------------------------------------------

typedef struct {

	s32   act;
	s32   dat;
	char* pCur;

	bool  isLoop;
	bool  isSkip;
	s32   wait;
	u32   waitBgm;
	s32   waitFontIn;
	s32   waitFontOut;
	s32   waitBlend;
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
EWRAM_CODE void AnimeExecSub(void);

EWRAM_CODE void AnimeExecPata(void);
EWRAM_CODE void AnimeExecPata2(void);
EWRAM_CODE void AnimeExecPat(void);
EWRAM_CODE void AnimeExecSet(void);
EWRAM_CODE void AnimeExecClear(void);
EWRAM_CODE void AnimeExecStr(void);
EWRAM_CODE void AnimeExecStrCls(void);
EWRAM_CODE void AnimeExecEffect(void);
EWRAM_CODE void AnimeExecBlend(void);
EWRAM_CODE void AnimeExecWait(void);
EWRAM_CODE void AnimeExecWaitBgm(void);
EWRAM_CODE void AnimeExecBgm(void);
EWRAM_CODE void AnimeExecBgmStop(void);
EWRAM_CODE void AnimeExecSsg(void);
EWRAM_CODE void AnimeExecSkip(void);
EWRAM_CODE void AnimeExecSkipMark(void);
EWRAM_CODE void AnimeExecFontCol(void);
EWRAM_CODE void AnimeExecFontIn(void);
EWRAM_CODE void AnimeExecFontOut(void);
EWRAM_CODE void AnimeExecEnd(void);
EWRAM_CODE void AnimeExecEnvSave(void);
EWRAM_CODE void AnimeExecEnvLoad(void);
EWRAM_CODE void AnimeExecEnvFade(void);

EWRAM_CODE bool AnimeIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
