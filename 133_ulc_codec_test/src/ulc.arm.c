#include "ulc.arm.h"
#include "libulc/ulc_Specs.h"
#include "libulc/ulcGBA.h"
#include "mem.h"

//---------------------------------------------------------------------------
ST_ULC Ulc;


//---------------------------------------------------------------------------
EWRAM_CODE void UlcInit(void)
{
	_Memset(&Ulc, 0x00, sizeof(ST_ULC));

	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO | SNDA_VOL_100;

	REG_FIFO_A  = 0;
	REG_DMA1CNT = 0;
	REG_DMA1DAD = (u32)&REG_FIFO_A;

	REG_TM0CNT_H = 0;
	REG_TM0CNT_L = 0x10000 - ULC_SAMPLE_TIME;

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_TM0CNT_H = TIMER_START;
}
//---------------------------------------------------------------------------
void UlcPlay(u8* pSrc, bool isLoop, s32 adjust)
{
	ulc_StartPlayer((struct ulc_FileHeader_t*)pSrc);


	_Memset(&Ulc, 0x00, sizeof(ST_ULC));

	Ulc.pSrc   = pSrc;
	Ulc.isLoop = isLoop;
	Ulc.adjust = adjust;
	Ulc.act    = ULC_ACT_PLAY;
}
//---------------------------------------------------------------------------
void UlcStop(void)
{
	Ulc.act = ULC_ACT_STOP;
}
//---------------------------------------------------------------------------
s32 UlcGetBlkRem(void)
{
	return ulc_State.nBlkRem;
}
//---------------------------------------------------------------------------
bool UlcIsPlay(void)
{
	return (ulc_State.SoundFile == NULL) ? false : true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void UlcMix(void)
{
	if(Ulc.act != ULC_ACT_PLAY)
	{
		return;
	}

	s32 bufSize = ULC_BUF_SIZE;

	while(bufSize > 0)
	{
		if(Ulc.remaining == 0)
		{
			ulc_UpdatePlayer();
			Ulc.remaining = ULC_BLK_SIZE;
		}

		s32 src = ULC_BLK_SIZE - Ulc.remaining;
		s32 dst = ULC_BUF_SIZE - bufSize;
		s32 cnt = _Min(Ulc.remaining, bufSize);

		MemInc(&ulc_OutputBuffer[src], &Ulc.pBuf[dst], cnt);

		bufSize -= cnt;
		Ulc.remaining -= cnt;
	}

	if(ulc_State.nBlkRem != 0)
	{
		return;
	}

	if(Ulc.isLoop == true)
	{
		UlcPlay(Ulc.pSrc, Ulc.isLoop, Ulc.adjust);
	}
	else
	{
		UlcStop();
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void UlcVSync(void)
{
	if(Ulc.act == ULC_ACT_PLAY)
	{
		if(Ulc.idx == 1)
		{
			// Start playing buffer 0
			REG_DMA1CNT = 0;
			REG_DMA1SAD = (u32)Ulc.buf;
			REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

			// Set the current buffer pointer to the start of buffer 1
			Ulc.pBuf = Ulc.buf + ULC_BUF_SIZE;
		}
		else
		{
			// DMA points to buffer 1 already, so don't bother stopping and resetting it
			// Set the current buffer pointer to the start of buffer 0
			Ulc.pBuf = Ulc.buf;
		}

		Ulc.idx ^= 1;
	}
	else if(Ulc.act == ULC_ACT_STOP)
	{
		*(vu8*)(REG_BASE + 0x83) = 0x00;
		REG_DMA1CNT = 0;
		*(vu8*)(REG_BASE + 0x83) = 0x0B;
		REG_FIFO_A = 0;

		ulc_State.SoundFile = NULL;

		Ulc.act = ULC_ACT_DONOTHING;
	}
}
