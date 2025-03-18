#ifndef __SND_H__
#define __SND_H__

#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SND_MAX_CHANNEL				8
#define SND_BUF_SIZE				224
#define SND_SAMPLE_TIME				(280896 / SND_BUF_SIZE)

/*
	   Hz  buf
	 5734   96
	10512  176
	13379  224
	18157  304
	21024  352
	26758  448
	31536  528
	36314  608
	40137  672
	42048  704
	43959  736

	バッファサイズは1フレーム280896サイクルで割り切れる数です
*/

//---------------------------------------------------------------------------

typedef struct {
	s8* pSrc;
	s8* pCur;
	s8* pEnd;
	u16 vol;		// fixed point 10.6

} ST_SND_CH;

typedef struct {

	s32 active;
	s8* pBuf;
	s8  mixBuf[SND_BUF_SIZE * 2] ALIGN(4);
	s8  nulBuf[SND_BUF_SIZE] ALIGN(4);

	ST_SND_CH ch[SND_MAX_CHANNEL];

} ST_SND;

//---------------------------------------------------------------------------
EWRAM_CODE void SndInit(void);
EWRAM_CODE void SndPlay(s8* pDat, u32 size, u16 vol);
EWRAM_CODE void SndClear(void);

EWRAM_CODE s32 SndGetMax(void);
EWRAM_CODE s32 SndGetReg(void);
EWRAM_CODE s32 SndGetCur(s32 no);

IWRAM_CODE void SndMix(void);
IWRAM_CODE void SndVSync(void);


#ifdef __cplusplus
}
#endif
#endif
