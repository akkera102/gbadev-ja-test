#ifndef KEY_H
#define KEY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define KEY_REPEAT_CNT		10


//---------------------------------------------------------------------------
typedef struct {
	u16 cnt;					// 現在のキー
	u16 trg;					// 押されたキー
	u16 off;					// 離されたキー
	u16 rep;					// リピートキー
	s16 repCnt;					// リピートカウント
} ST_KEY;


//---------------------------------------------------------------------------
EWRAM_CODE void KeyInit(void);
IWRAM_CODE void KeyExec(void);

IWRAM_CODE u32  KeyGetCnt(void);
IWRAM_CODE u32  KeyGetTrg(void);
IWRAM_CODE u32  KeyGetOff(void);
IWRAM_CODE u32  KeyGetRep(void);


#ifdef __cplusplus
}
#endif
#endif
