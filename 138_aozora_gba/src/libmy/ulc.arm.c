#include "ulc.arm.h"
#include "../libulc/ulc_Specs.h"
#include "../libulc/ulcGBA.h"
#include "mem.arm.h"

//---------------------------------------------------------------------------
ST_ULC Ulc;


//---------------------------------------------------------------------------
void UlcInit(void)
{
	_Memset(&Ulc, 0x00, sizeof(ST_ULC));

/*
	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO | SNDA_VOL_100;

	REG_DMA1CNT = 0;
	REG_DMA1DAD = (u32)&REG_FIFO_A;

	REG_TM0CNT_H = 0;
	REG_TM0CNT_L = 0x10000 - ULC_SAMPLE_TIME;

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_TM0CNT_H = TIMER_START;
*/
}
//---------------------------------------------------------------------------
void UlcPlay(u8* p, bool is)
{
	Ulc.isPlay = 0;

	asm volatile("":::"memory");

	Ulc.pNext  = p;
	Ulc.isNext = is;

	asm volatile("":::"memory");

	Ulc.isPlay = 1;
}
//---------------------------------------------------------------------------
void UlcStop(void)
{
	Ulc.isStop = 1;
}
//---------------------------------------------------------------------------
bool UlcIsPlay(void)
{
	return (ulc_State.nBlkRem != 0) ? true : false;
}
//---------------------------------------------------------------------------
// REG_VCOUNT 60 -> 89
IWRAM_CODE void UlcIntrVcount(void)
{
	if(Ulc.isStop == 1)
	{
		ulc_State.nBlkRem = 0;
		Ulc.isLoop = false;

		Ulc.isStop = 0;
	}

	if(Ulc.isPlay == 1)
	{
		Ulc.pSrc   = (u8*)Ulc.pNext;
		Ulc.isLoop = (u32)Ulc.isNext;
		Ulc.pBuf   = Ulc.buf;
		Ulc.pDma   = Ulc.buf + ULC_BUF_SIZE;
		Ulc.remain = 0;
		Ulc.idx    = 0;
		Ulc.isPlay = 0;

		ulc_StartPlayer((struct ulc_FileHeader_t*)Ulc.pSrc);
		ulc_State.nBlkRem -= 2;			// adjust
	}

	if(ulc_State.nBlkRem == 0 && Ulc.isLoop == true)
	{
		Ulc.pBuf   = Ulc.buf;
		Ulc.pDma   = Ulc.buf + ULC_BUF_SIZE;
		Ulc.remain = 0;
		Ulc.idx    = 0;

		ulc_StartPlayer((struct ulc_FileHeader_t*)Ulc.pSrc);
		ulc_State.nBlkRem -= 2;			// adjust
	}

	if(ulc_State.nBlkRem == 0)
	{
		return;
	}

	s32 src = Ulc.remain;

	if(src < ULC_BUF_SIZE)
	{
		// 持ち越し分の転送
		if(src > 0)
		{
			MemIncFast(&ulc_OutputBuffer[ULC_BLK_SIZE - src], Ulc.pBuf, src);
		}

		// 足りない分を転送
		ulc_UpdatePlayer();

		s32 dst = ULC_BUF_SIZE - src;
		MemIncFast(&ulc_OutputBuffer[0], Ulc.pBuf + src, dst);
		Ulc.remain = ULC_BLK_SIZE - dst;
	}
	else
	{
		// デコード不要
		MemIncFast(&ulc_OutputBuffer[ULC_BLK_SIZE - src], Ulc.pBuf, ULC_BUF_SIZE);
		Ulc.remain = src - ULC_BUF_SIZE;
	}

	if(Ulc.idx == 0)
	{
		Ulc.pBuf = Ulc.buf + ULC_BUF_SIZE;
		Ulc.pDma = Ulc.buf;
	}
	else
	{
		Ulc.pBuf = Ulc.buf;
		Ulc.pDma = Ulc.buf + ULC_BUF_SIZE;
	}

	Ulc.idx ^= 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void UlcIntrVblank(void)
{
	if(ulc_State.nBlkRem == 0)
	{
		REG_DMA1CNT = 0;
		REG_DMA1SAD = (u32)Ulc.clr;
		REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;
	}
	else
	{
		REG_DMA1CNT = 0;
		REG_DMA1SAD = (u32)Ulc.pDma;
		REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;
	}
}
