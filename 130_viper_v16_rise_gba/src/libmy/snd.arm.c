#include "snd.arm.h"


//---------------------------------------------------------------------------
ST_SND Snd;


//---------------------------------------------------------------------------
EWRAM_CODE void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));

	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_L = 0;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO | SNDA_VOL_100;

	REG_TM0CNT_L = 0x10000 - (SND_CPU_CLOCK / SND_AUDIO_RATE);
	REG_TM0CNT_H = TIMER_START;

	REG_DMA1CNT = 0;
	REG_DMA1DAD = (u32)&REG_FIFO_A;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndPlay(u8* pSnd, s32 size, s32 adjust, bool isLoop)
{
	Snd.pSnd   = pSnd;
	Snd.isLoop = isLoop;
	Snd.size   = (size * SND_FPS) / SND_AUDIO_RATE - adjust;

	Snd.act = SND_ACT_START;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndStop(void)
{
	Snd.act = SND_ACT_STOP;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrVblank(void)
{
	if(Snd.act == SND_ACT_START)
	{
Start:
		REG_TM0CNT_H = 0;
		REG_DMA1CNT = 0;

		REG_DMA1SAD = (u32)Snd.pSnd;
		REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

		REG_TM0CNT_H = TIMER_START;
		REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO | SNDA_VOL_100;

		Snd.cnt = 0;
		Snd.act = SND_ACT_PLAY;
	}
	else if(Snd.act == SND_ACT_PLAY)
	{
		Snd.cnt++;

		if(Snd.cnt < Snd.size)
		{
			return;
		}

		if(Snd.isLoop == true)
		{
			goto Start;
		}

		goto stop;
	}
	else if(Snd.act == SND_ACT_STOP)
	{
stop:

		REG_SOUNDCNT_H &= ~(SNDA_R_ENABLE | SNDA_L_ENABLE);
		REG_TM0CNT_H = 0;
		REG_DMA1CNT = 0;

		Snd.act = SND_ACT_DONOTHING;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SndIsPlay(void)
{
	return (Snd.act != SND_ACT_DONOTHING) ? true : false;
}
