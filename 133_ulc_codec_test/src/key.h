#ifndef KEY_H
#define KEY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define KEY_REPEAT_CNT		10


//---------------------------------------------------------------------------
typedef struct {
	u32 cnt;					// 現在のキー
	u32 trg;					// 押されたキー
	u32 off;					// 離されたキー
	u32 rep;					// リピートキー
	s32 repCnt;					// リピートカウント
} ST_KEY;


//---------------------------------------------------------------------------
void KeyInit(void);

IWRAM_CODE void KeyExec(void);

IWRAM_CODE u32  KeyGetCnt(void);
IWRAM_CODE u32  KeyGetTrg(void);
IWRAM_CODE u32  KeyGetOff(void);
IWRAM_CODE u32  KeyGetRep(void);


#ifdef __cplusplus
}
#endif
#endif
