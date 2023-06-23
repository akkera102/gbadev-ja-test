#include "snd.h"

// Timer1 SE
// DMA2   SE

//---------------------------------------------------------------------------
ST_SND Snd;


//---------------------------------------------------------------------------
EWRAM_CODE void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));

//	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
//	REG_SOUNDCNT_L = 0;
	REG_SOUNDCNT_H |= SNDB_VOL_50 | DSOUNDCTRL_BTIMER(1) | SNDB_RESET_FIFO;

	REG_TM1CNT_L   = 0x10000 - (SND_CPU_CLOCK / SND_AUDIO_RATE);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndPlay(u8* data, u32 size, s32 adjust, bool isLoop)
{
	SndStop();

	Snd.cnt       = 0;
	Snd.data      = data;
	Snd.size      = size;
	Snd.frameSize = (size * 60) / SND_AUDIO_RATE + adjust;
	Snd.isLoop    = isLoop;
	Snd.act       = SND_ACT_START;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndStop(void)
{
	REG_SOUNDCNT_H &= ~(SNDB_R_ENABLE | SNDB_L_ENABLE);
	REG_TM1CNT_H    = 0;
	REG_DMA2CNT     = 0;
	REG_SOUNDCNT_H |=  (SNDB_RESET_FIFO);

	Snd.cnt = 0;
	Snd.act = SND_ACT_STOP;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrVblank(void)
{
	if(SND_ACT_STOP == Snd.act)
	{
		return;
	}

	switch(Snd.act)
	{
	case SND_ACT_START:
		SndIntrStart();
		break;

	case SND_ACT_PLAY:
		Snd.cnt--;

		if(Snd.cnt <= 0)
		{
			if(Snd.isLoop == TRUE)
			{
				SndIntrStart();
			}
			else
			{
				SndStop();
			}
		}
		break;

	default:
		SystemError("[Err] SndIntrSe");
		break;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrStart(void)
{
	REG_TM1CNT_H = 0;
	REG_DMA2CNT  = 0;

	DMA2COPY(Snd.data, &REG_FIFO_B, DMA_SPECIAL | DMA32 | DMA_REPEAT | DMA_SRC_INC | DMA_DST_FIXED);
	REG_TM1CNT_H    = TIMER_FREQ_PER_1 | TIMER_START;
	REG_SOUNDCNT_H |= (SNDB_R_ENABLE | SNDB_L_ENABLE);

	Snd.cnt = Snd.frameSize;
	Snd.act = SND_ACT_PLAY;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SndIsEnd(void)
{
	return (Snd.act == SND_ACT_STOP) ? TRUE : FALSE;
}
