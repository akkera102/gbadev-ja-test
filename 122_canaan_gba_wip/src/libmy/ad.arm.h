#ifndef __AD_H__
#define __AD_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
// 18157Hz = 304 13379Hz = 224 11468Hz = 192 10512Hz = 176 7884Hz = 128
#define AD_BUF_SIZE					224
#define AD_SAMPLE_TIME				(280896 / AD_BUF_SIZE)


enum {
	AD_ACT_STOP,
	AD_ACT_READY,
	AD_ACT_PLAY,
};

//---------------------------------------------------------------------------
typedef struct {
	s32  act;
	bool isLoop;

	u8*  pCur;
	u8*  pTop;
	u8*  pEnd;

	s32  lastSamp;
	s32  lastIdx;

	s32  bufIdx;
	s8   buf[2][AD_BUF_SIZE] ALIGN(4);
} ST_AD;


//---------------------------------------------------------------------------
EWRAM_CODE void AdInit(void);

IWRAM_CODE void AdPlay(u8* pDat, s32 size, bool isLoop);
IWRAM_CODE void AdReset(void);
IWRAM_CODE void AdStop(void);
EWRAM_CODE bool AdIsEnd(void);
EWRAM_CODE u32  AdGetOffset(void);

IWRAM_CODE void AdIntrVcount(void);
IWRAM_CODE void AdIntrVblank(void);
IWRAM_CODE void AdIntrNextBuf(void);




#ifdef __cplusplus
}
#endif
#endif
