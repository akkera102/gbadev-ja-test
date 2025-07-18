#include "snd.arm.h"

// å¯â âπÅAâπäy
// Timer0, 1
// DMA1, 2

//---------------------------------------------------------------------------
ST_SND Snd[2];


//---------------------------------------------------------------------------
void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));

	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO | SNDB_RESET_FIFO | SNDA_VOL_100 | SNDB_VOL_100 | 0x2;
//	REG_SOUNDCNT_L = 0;

	REG_FIFO_A  = 0;
	REG_DMA1CNT = 0;
	REG_DMA1DAD = (u32)&REG_FIFO_A;
	REG_FIFO_B  = 0;
	REG_DMA2CNT = 0;
	REG_DMA2DAD = (u32)&REG_FIFO_B;

	REG_TM0CNT_H = 0;
	REG_TM0CNT_L = 0x10000 - (SND_CPU_CLOCK / SND_AUDIO_RATE);
	REG_TM1CNT_H = 0;
	REG_TM1CNT_L = 0x10000 - (SND_CPU_CLOCK / SND_AUDIO_RATE);

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_TM0CNT_H = TIMER_START;
	REG_TM1CNT_H = TIMER_START;

	SndStop(0);
	SndStop(1);
}
//---------------------------------------------------------------------------
void SndPlay(s32 no, u8* pSnd, s32 size, s32 adjust, bool isLoop)
{
	Snd[no].pSnd   = pSnd;
	Snd[no].isLoop = isLoop;
	Snd[no].size   = (size * SND_FPS) / SND_AUDIO_RATE - adjust;
	Snd[no].act    = SND_ACT_START;
}
//---------------------------------------------------------------------------
void SndStop(s32 no)
{
	Snd[no].act = SND_ACT_STOP;
}
//---------------------------------------------------------------------------
bool SndIsPlay(s32 no)
{
	return (Snd[no].act != SND_ACT_DONOTHING) ? true : false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrVblank(void)
{
	if(Snd[0].act == SND_ACT_START)
	{
Start1:
		REG_DMA1CNT = 0;
		REG_DMA1SAD = (u32)Snd[0].pSnd;
		REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

		Snd[0].cnt = 0;
		Snd[0].act = SND_ACT_PLAY;
	}
	else if(Snd[0].act == SND_ACT_PLAY)
	{
		Snd[0].cnt++;

		if(Snd[0].cnt < Snd[0].size)
		{
			goto next;
		}

		if(Snd[0].isLoop == true)
		{
			goto Start1;
		}
		else
		{
			goto Stop1;
		}
	}
	else if(Snd[0].act == SND_ACT_STOP)
	{
Stop1:
		*(vu8*)(REG_BASE + 0x83) &= 0xF0;
		REG_DMA1CNT = 0;
		*(vu8*)(REG_BASE + 0x83) |= 0xFB;
		REG_FIFO_A = 0;

		Snd[0].act = SND_ACT_DONOTHING;
	}


next:


	if(Snd[1].act == SND_ACT_START)
	{
Start2:
		REG_DMA2CNT = 0;
		REG_DMA2SAD = (u32)Snd[1].pSnd;
		REG_DMA2CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

		Snd[1].cnt = 0;
		Snd[1].act = SND_ACT_PLAY;
	}
	else if(Snd[1].act == SND_ACT_PLAY)
	{
		Snd[1].cnt++;

		if(Snd[1].cnt < Snd[1].size)
		{
			return;
		}

		if(Snd[1].isLoop == true)
		{
			goto Start2;
		}
		else
		{
			goto Stop2;
		}
	}
	else if(Snd[1].act == SND_ACT_STOP)
	{
Stop2:
		*(vu8*)(REG_BASE + 0x83) &= 0x0F;
		REG_DMA2CNT = 0;
		*(vu8*)(REG_BASE + 0x83) |= 0xBF;
		REG_FIFO_B = 0;

		Snd[1].act = SND_ACT_DONOTHING;
	}
}
