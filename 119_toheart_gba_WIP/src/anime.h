#ifndef __ANIME_H__
#define __ANIME_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define ANIME_MAX_PAT_CNT			16
#define ANIME_MAX_DAT_CNT			3
#define ANIME_MAX_STR_SIZE			10

enum {
	ANIME_ACT_EXEC,
	ANIME_ACT_END,
};

enum {
	ANIME_DAT_TITLE,
	ANIME_DAT_OPENING,
	ANIME_DAT_ENDING,
};

//---------------------------------------------------------------------------
typedef struct {
	u32   act;

	bool  isLoop;
	bool  isKey;
	u32   waitCnt;
	s32   var;
	char* pCur;

} ST_ANIME;


typedef struct {
	char* pStr;								// ñΩóﬂÇÃï∂éöóÒ
	void  (*pFunc)(void);					// ñΩóﬂÇÃä÷êî
} ST_ANIME_TABLE;

//---------------------------------------------------------------------------
EWRAM_CODE void AnimeInit(void);
EWRAM_CODE void AnimeSetDat(u32 no);

EWRAM_CODE void AnimeExec(void);
EWRAM_CODE void AnimeExecSub(void);
EWRAM_CODE void AnimeExecImg1(void);
EWRAM_CODE void AnimeExecImg2(void);
EWRAM_CODE void AnimeExecImg3(void);
EWRAM_CODE void AnimeExecImgLine(void);
EWRAM_CODE void AnimeExecEffect1(void);
EWRAM_CODE void AnimeExecEffect2(void);
EWRAM_CODE void AnimeExecFill(void);
EWRAM_CODE void AnimeExecWait(void);
EWRAM_CODE void AnimeExecKeyWait(void);
EWRAM_CODE void AnimeExecBgm(void);
EWRAM_CODE void AnimeExecLoop(void);
EWRAM_CODE void AnimeExecInc(void);
EWRAM_CODE void AnimeExecDec(void);
EWRAM_CODE void AnimeExecJae(void);
EWRAM_CODE void AnimeExecJbe(void);
EWRAM_CODE void AnimeExecEnd(void);

EWRAM_CODE bool AnimeIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
