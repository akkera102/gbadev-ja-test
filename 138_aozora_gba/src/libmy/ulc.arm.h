#ifndef __ULC_H__
#define __ULC_H__

#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define ULC_BUF_SIZE				224
#define ULC_BLK_SIZE				256
#define ULC_SAMPLE_TIME				(280896 / ULC_BUF_SIZE)


//---------------------------------------------------------------------------

typedef struct {
	u8* pSrc;
	u32 isLoop;				// u32

	s8* pDma;
	s8* pBuf;
	s32 idx;
	s32 remain;
	s8  clr[ULC_BUF_SIZE * 1] ALIGN(4);
	s8  buf[ULC_BUF_SIZE * 2] ALIGN(4);

	vu32 isPlay;			// vu32
	vu32 isStop;			// vu32
	vu8* pNext;				// *vu8
	vu32 isNext;			// vu32

} ST_ULC;

//---------------------------------------------------------------------------
void UlcInit(void);
void UlcPlay(u8* p, bool is);
void UlcStop(void);
bool UlcIsPlay(void);

IWRAM_CODE void UlcIntrVcount(void);
IWRAM_CODE void UlcIntrVblank(void);


#ifdef __cplusplus
}
#endif
#endif
