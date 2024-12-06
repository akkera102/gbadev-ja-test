#include "snd.arm.h"


//---------------------------------------------------------------------------
ST_SND Snd;


//---------------------------------------------------------------------------
EWRAM_CODE void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));


	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_L = 0;
	REG_SOUNDCNT_H = SNDA_RESET_FIFO | SNDA_VOL_100 | DSOUNDCTRL_ATIMER(0) | DSOUNDCTRL_DMG100;		// sound1-4 Vol 100%(VGMŒø‰Ê‰¹—p)

	REG_TM0CNT_L = 0x10000 - (SND_CPU_CLOCK / SND_AUDIO_RATE);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndPlay(u8* pSnd, s32 size, s32 adjust, bool isLoop)
{
	Snd.pSnd   = pSnd;
	Snd.isLoop = isLoop;
	Snd.size   = (size * SND_FPS) / SND_AUDIO_RATE - adjust;
	Snd.act    = SND_ACT_START;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndStop(void)
{
	Snd.act = SND_ACT_STOP;

	REG_SOUNDCNT_H &= ~(SNDA_R_ENABLE | SNDA_L_ENABLE | SNDA_RESET_FIFO);
	REG_TM1CNT_H    = 0;
	REG_DMA1CNT     = 0;
	REG_SOUNDCNT_H |=  (SNDA_RESET_FIFO);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrVblank(void)
{
	switch(Snd.act)
	{
	case SND_ACT_STOP:
		// EMPTY
		break;

	case SND_ACT_START:

Start:

		REG_TM0CNT_H = 0;
		REG_DMA1CNT  = 0;

		DMA1COPY(Snd.pSnd, &REG_FIFO_A, DMA_SPECIAL | DMA32 | DMA_REPEAT | DMA_SRC_INC | DMA_DST_FIXED);
		REG_TM0CNT_H    = TIMER_START;
		REG_SOUNDCNT_H |= (SNDA_R_ENABLE | SNDA_L_ENABLE | SNDA_RESET_FIFO);

		Snd.cnt = 0;
		Snd.act = SND_ACT_PLAY;
		break;

	case SND_ACT_PLAY:

		Snd.cnt++;

		if(Snd.cnt < Snd.size)
		{
			return;
		}

		if(Snd.isLoop == true)
		{
			goto Start;
		}

		SndStop();
		break;

	default:
		SystemError("[Err] SndIntrVblank %x\n", Snd.act);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SndIsPlay(void)
{
	return (Snd.act == SND_ACT_PLAY) ? true : false;
}
