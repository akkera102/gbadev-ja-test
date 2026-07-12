#include "sfx.arm.h"

// Œø‰Ê‰¹
// Timer1
// DMA2

//---------------------------------------------------------------------------
ST_SFX Sfx;


//---------------------------------------------------------------------------
void SfxInit(void)
{
	_Memset(&Sfx, 0x00, sizeof(ST_SFX));

	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDB_L_ENABLE | SNDB_R_ENABLE | SNDA_RESET_FIFO | SNDB_RESET_FIFO | DSOUNDCTRL_BTIMER(1) | SNDA_VOL_100 | SNDB_VOL_100;
	REG_SOUNDCNT_L = 0;

	REG_DMA1CNT = 0;
	REG_DMA1DAD = (u32)&REG_FIFO_A;
	REG_DMA2CNT = 0;
	REG_DMA2DAD = (u32)&REG_FIFO_B;

	REG_TM0CNT_H = 0;
	REG_TM0CNT_L = 0x10000 - SFX_SAMPLE_TIME;
	REG_TM1CNT_H = 0;
	REG_TM1CNT_L = 0x10000 - SFX_SAMPLE_TIME;

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_TM0CNT_H = TIMER_START;
	REG_TM1CNT_H = TIMER_START;

	SfxStop();
}
//---------------------------------------------------------------------------
void SfxPlay(u8* pSfx, s32 size, bool isLoop)
{
	Sfx.pSfx   = pSfx;
	Sfx.isLoop = isLoop;
	Sfx.size   = (size * 60) / SFX_FREQ - 2;		// adjust -2

	asm volatile("":::"memory");

	Sfx.act = SFX_ACT_START;
}
//---------------------------------------------------------------------------
void SfxStop(void)
{
	Sfx.act = SFX_ACT_STOP;
}
//---------------------------------------------------------------------------
bool SfxIsPlay(void)
{
	return (Sfx.act != SFX_ACT_DONOTHING) ? true : false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SfxIntrVblank(void)
{
	if(Sfx.act == SFX_ACT_START)
	{
Start:
		REG_DMA2CNT = 0;
		*(vu8*)(REG_BASE + 0x83) |= 0xF0;

		REG_DMA2SAD = (u32)Sfx.pSfx;
		REG_DMA2CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

		Sfx.cnt = 0;
		Sfx.act = SFX_ACT_PLAY;
	}
	else if(Sfx.act == SFX_ACT_PLAY)
	{
		Sfx.cnt++;

		if(Sfx.cnt < Sfx.size)
		{
			return;
		}

		if(Sfx.isLoop == true)
		{
			goto Start;
		}
		else
		{
			goto Stop;
		}
	}
	else if(Sfx.act == SFX_ACT_STOP)
	{
Stop:
		REG_DMA2CNT = 0;

		Sfx.act = SFX_ACT_DONOTHING;
	}
}
