#ifndef __ULC_H__
#define __ULC_H__

#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define ULC_BUF_SIZE				224
#define ULC_BLK_SIZE				256
#define ULC_SAMPLE_TIME				(280896 / ULC_BUF_SIZE)


//---------------------------------------------------------------------------

enum {
	ULC_ACT_DONOTHING,
	ULC_ACT_STOP,
	ULC_ACT_PLAY,
};

typedef struct {
	s32  act;
	bool isLoop;

	u8*  pSrc;
	s32  remaining;
	s32  adjust;

	s32  idx;
	s8*  pBuf;
	s8   buf[ULC_BUF_SIZE * 2] ALIGN(4);

} ST_ULC;

//---------------------------------------------------------------------------
void UlcInit(void);
void UlcPlay(u8* pSrc, bool isLoop, s32 adjust);
void UlcStop(void);

s32  UlcGetBlkRem(void);
bool UlcIsPlay(void);

IWRAM_CODE void UlcMix(void);
IWRAM_CODE void UlcVSync(void);


#ifdef __cplusplus
}
#endif
#endif
