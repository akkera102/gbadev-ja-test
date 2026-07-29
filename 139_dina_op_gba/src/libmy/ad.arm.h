#ifndef __AD_H__
#define __AD_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define AD_BUF_SIZE					352
#define AD_SAMPLE_TIME				(280896 / AD_BUF_SIZE)

enum {
	AD_ACT_STOP,
	AD_ACT_START,
	AD_ACT_PLAY,
};

//---------------------------------------------------------------------------

typedef struct {
	s32  act;
	u32  isLoop;			// u32

	u8*  pCur;
	u8*  pTop;
	u8*  pEnd;

	s32  lastIdx;
	s32  lastSamp;

	s32  bufIdx;
	s8   clr[AD_BUF_SIZE]      ALIGN(4);
	s8   buf[2][AD_BUF_SIZE]   ALIGN(4);

	vu32 isPlay;			// vu32
	vu32 isStop;			// vu32
	vu8* pNext;				// *vu8
	vu32 nextSize;			// vu32
	vu32 nextLoop;			// vu32

} ST_AD;

//---------------------------------------------------------------------------
void AdInit(void);

IWRAM_CODE void AdPlay(u8* pDat, s32 size, bool isLoop);
IWRAM_CODE void AdStop(void);

IWRAM_CODE u32  AdGetRem(void);
IWRAM_CODE bool AdIsPlay(void);

IWRAM_CODE void AdIntrVcount(void);
IWRAM_CODE void AdIntrVblank(void);

#ifdef __cplusplus
}
#endif
#endif
