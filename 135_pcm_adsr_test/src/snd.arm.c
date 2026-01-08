#include "snd.arm.h"

//---------------------------------------------------------------------------
ST_SND Snd;


//---------------------------------------------------------------------------
void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));


	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO | SNDA_VOL_100;

	REG_FIFO_A  = 0;
	REG_DMA1CNT = 0;
	REG_DMA1DAD = (u32)&REG_FIFO_A;

	REG_TM0CNT_H = 0;
	REG_TM0CNT_L = 0x10000 - SND_SAMPLE_TIME;

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_TM0CNT_H = TIMER_START;
}
//---------------------------------------------------------------------------
void SndPlay(u32 note)
{
	s32 i;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		if(Snd.ch[i].act == 0)
		{
			Snd.ch[i].act     = 1;
			Snd.ch[i].cur     = 0;
			Snd.ch[i].end     = SND_WAVE_SIZE << SND_FP_SHIFT;
			Snd.ch[i].step    = note;

			Snd.ch[i].pSrc    = Snd.pInst;
			Snd.ch[i].vol     = 0;
			Snd.ch[i].state   = SND_ENV_ATTACK;
			Snd.ch[i].atkStep = Snd.atkStep;
			Snd.ch[i].decStep = Snd.decStep;
			Snd.ch[i].susLvl  = Snd.susLvl;
			Snd.ch[i].susStep = Snd.susStep;
			Snd.ch[i].relStep = Snd.relStep;

			if(Snd.isAdsr == false)
			{
				Snd.ch[i].state = SND_ENV_OFF;
				Snd.ch[i].vol   = 1 << 16;
			}

			return;
		}
	}
}
//---------------------------------------------------------------------------
void SndStop(void)
{
	s32 i;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		if(Snd.ch[i].act == 1)
		{
			Snd.ch[i].act = 0;
		}
	}
}
//---------------------------------------------------------------------------
void SndSetInst(s8* pInst, s32 atk, s32 dec, s32 susl, s32 suss, s32 rel)
{
	Snd.pInst   = pInst;
	Snd.atkStep = atk;
	Snd.decStep = dec;
	Snd.susLvl  = susl;
	Snd.susStep = suss;
	Snd.relStep = rel;
}
//---------------------------------------------------------------------------
void SndSetAdsr(void)
{
	Snd.isAdsr = (Snd.isAdsr == true) ? false : true;
}
//---------------------------------------------------------------------------
s32 SndGetActCnt(void)
{
	s32 i;
	s32 ret = 0;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		if(Snd.ch[i].act == 1)
		{
			ret++;
		}
	}

	return ret;
}
//---------------------------------------------------------------------------
bool SndIsAdsr(void)
{
	return Snd.isAdsr;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndMix(void)
{
	vs32 i, j;

	for(i=0; i<SND_BUF_SIZE; i++)
	{
		Snd.tmp[i] = 0;
	}

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		ST_SND_CH* p = &Snd.ch[i];

		if(p->act == 0)
		{
			continue;
		}

		for(j=0; j<SND_BUF_SIZE; j++)
		{
			switch(p->state)
			{
			case SND_ENV_ATTACK:
				p->vol += p->atkStep;

				if(p->vol >= (1 << 16))
				{
					p->vol = (1 << 16);
					p->state = SND_ENV_DECAY;
				}
				break;

			case SND_ENV_DECAY:
				p->vol -= p->decStep;

				if(p->vol <= p->susLvl)
				{
					p->vol = p->susLvl;
					p->state = SND_ENV_SUSTAIN;
				}
				break;

			case SND_ENV_SUSTAIN:
				if(p->susStep > 0)
				{
					p->susStep--;
				}
				else
				{
					p->state = SND_ENV_RELEASE;
				}
				break;

			case SND_ENV_RELEASE:
				p->vol -= p->relStep;

				if(p->vol <= 0)
				{
					p->act = 0;
					goto Next;
				}
				break;
			}

			s32 sample = p->pSrc[p->cur >> SND_FP_SHIFT];
			Snd.tmp[j] += (sample * p->vol) >> 16;

			p->cur += p->step;

			if(p->cur >= p->end)
			{
				if(Snd.isAdsr == true)
				{
					p->state = SND_ENV_RELEASE;
					p->cur -= p->end;
				}
				else
				{
					p->act = 0;
					goto Next;
				}
			}
		}
Next:
	}

	s8* pOut = Snd.buf + (Snd.act^1) * SND_BUF_SIZE;

	for(i=0; i<SND_BUF_SIZE; i++)
	{
		// >> 2で歪や濁りを考慮
		s32 s = Snd.tmp[i] >> 2;

		// クリッピング
		if(s > 127)
		{
			s = 127;
		}
		else if(s < -128)
		{
			s = -128;
		}

		pOut[i] = (s8)s;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndVSync(void)
{
	if(Snd.act == 1)
	{
		REG_DMA1CNT = 0;
		REG_DMA1SAD = (u32)Snd.buf;
		REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;
	}

	Snd.act ^= 1;
}
