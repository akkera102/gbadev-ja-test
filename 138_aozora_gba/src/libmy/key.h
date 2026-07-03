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
	u32  cnt;
	u32  trg;
	u32  off;
	u32  rep;
	s32  repCnt;
	bool isRep;
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
