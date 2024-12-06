#ifndef __KEY_H__
#define __KEY_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define KEY_REPEAT_1ST_CNT		20
#define KEY_REPEAT_2ST_CNT		2


//---------------------------------------------------------------------------

typedef struct {
	u32  cnt;					// 現在のキー
	u32  trg;					// 押されたキー
	u32  off;					// 離されたキー
	u32  rep;					// リピートキー
	s32  repCnt;				// リピートカウント
	bool isRep;					// リピートカウントの最初有無
} ST_KEY;


//---------------------------------------------------------------------------
EWRAM_CODE void KeyInit(void);
IWRAM_CODE void KeyExec(void);

EWRAM_CODE u32  KeyGetCnt(void);
EWRAM_CODE u32  KeyGetTrg(void);
EWRAM_CODE u32  KeyGetOff(void);
EWRAM_CODE u32  KeyGetRep(void);


#ifdef __cplusplus
}
#endif
#endif
