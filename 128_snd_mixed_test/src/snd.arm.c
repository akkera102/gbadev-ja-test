#include "snd.arm.h"

//---------------------------------------------------------------------------
ST_SND Snd;


//---------------------------------------------------------------------------
EWRAM_CODE void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));

	SndClear();

	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO | SNDA_VOL_100;

	REG_TM0CNT_L   = 0x10000 - SND_SAMPLE_TIME;
	REG_TM0CNT_H   = TIMER_START;

	REG_DMA1CNT    = 0;
	REG_DMA1DAD    = (u32)&REG_FIFO_A;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndMix(void)
{
	s8* p[SND_MAX_CHANNEL];
	s32 i;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		ST_SND_CH* c = (ST_SND_CH*)&Snd.ch[i];

		p[i] = c->pCur;

		if(c->pCur != Snd.nulBuf)
		{
			c->pCur += SND_BUF_SIZE;

			if(c->pCur >= c->pEnd)
			{
				c->pCur = Snd.nulBuf;
			}
		}
	}

	for(i=0; i<SND_BUF_SIZE; i++)
	{
		s32 tmp;

		tmp = 0;
		tmp += *p[0]++ * Snd.ch[0].vol;
		tmp += *p[1]++ * Snd.ch[1].vol;
		tmp += *p[2]++ * Snd.ch[2].vol;
		tmp += *p[3]++ * Snd.ch[3].vol;
		tmp += *p[4]++ * Snd.ch[4].vol;
		tmp += *p[5]++ * Snd.ch[5].vol;
		tmp += *p[6]++ * Snd.ch[6].vol;
		tmp += *p[7]++ * Snd.ch[7].vol;

		// >>6 to divide off the volume
		// >>3 to divide by 8 channels
		Snd.pBuf[i] = tmp >> 9;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndPlay(s8* pDat, u32 size, u16 vol)
{
	s32 i;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		if(Snd.ch[i].pCur == Snd.nulBuf)
		{
			Snd.ch[i].pCur = pDat;
			Snd.ch[i].pSrc = pDat;
			Snd.ch[i].pEnd = pDat + size - SND_BUF_SIZE;
			Snd.ch[i].vol  = vol;

			return;
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SndClear(void)
{
	s32 i;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		Snd.ch[i].pCur = Snd.nulBuf;
	}

	Snd.active = 1;
	Snd.pBuf = Snd.mixBuf;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 SndGetMax(void)
{
	return SND_MAX_CHANNEL;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 SndGetReg(void)
{
	s32 i, c = 0;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		if(Snd.ch[i].pCur != Snd.nulBuf)
		{
			c++;
		}
	}

	return c;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 SndGetCur(s32 no)
{
	if(Snd.ch[no].pCur == Snd.nulBuf)
	{
		return 0;
	}

	return Snd.ch[no].pEnd - Snd.ch[no].pCur;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndVSync(void)
{
	if(Snd.active == 1)
	{
		// Start playing buffer 0
		REG_DMA1CNT = 0;
		REG_DMA1SAD = (u32)Snd.mixBuf;
		REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

		// Set the current buffer pointer to the start of buffer 1
		Snd.pBuf = Snd.mixBuf + SND_BUF_SIZE;
	}
	else
	{
		// DMA points to buffer 1 already, so don't bother stopping and resetting it
		// Set the current buffer pointer to the start of buffer 0
		Snd.pBuf = Snd.mixBuf;
	}

	Snd.active ^= 1;
}
