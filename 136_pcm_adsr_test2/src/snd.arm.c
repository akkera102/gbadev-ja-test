#include "snd.arm.h"
#include "mem.h"

//---------------------------------------------------------------------------
// Generated for 13379Hz, Table Size: 256
// Pitch Step Values (16.16 Fixed Point)
const u32 SndPitTbl[] = {
    0x00014063,		// C2	  65.406 Hz
    0x00015370,		// CS2	  69.296 Hz
    0x000167A0,		// D2	  73.416 Hz
    0x00017D02,		// DS2	  77.782 Hz
    0x000193AA,		// E2	  82.407 Hz
    0x0001ABAB,		// F2	  87.307 Hz
    0x0001C519,		// FS2	  92.499 Hz
    0x0001E00A,		// G2	  97.999 Hz
    0x0001FC96,		// GS2	 103.826 Hz
    0x00021AD4,		// A2	 110.000 Hz
    0x00023ADE,		// AS2	 116.541 Hz
    0x00025CD0,		// B2	 123.471 Hz
    0x000280C7,		// C3	 130.813 Hz
    0x0002A6E1,		// CS3	 138.591 Hz
    0x0002CF3F,		// D3	 146.832 Hz
    0x0002FA04,		// DS3	 155.563 Hz
    0x00032754,		// E3	 164.814 Hz
    0x00035755,		// F3	 174.614 Hz
    0x00038A32,		// FS3	 184.997 Hz
    0x0003C014,		// G3	 195.998 Hz
    0x0003F92B,		// GS3	 207.652 Hz
    0x000435A7,		// A3	 220.000 Hz
    0x000475BC,		// AS3	 233.082 Hz
    0x0004B9A0,		// B3	 246.942 Hz
    0x0005018D,		// C4	 261.626 Hz
    0x00054DC2,		// CS4	 277.183 Hz
    0x00059E7F,		// D4	 293.665 Hz
    0x0005F408,		// DS4	 311.127 Hz
    0x00064EA8,		// E4	 329.628 Hz
    0x0006AEAB,		// F4	 349.228 Hz
    0x00071464,		// FS4	 369.994 Hz
    0x00078029,		// G4	 391.995 Hz
    0x0007F257,		// GS4	 415.305 Hz
    0x00086B4E,		// A4	 440.000 Hz
    0x0008EB78,		// AS4	 466.164 Hz
    0x00097340,		// B4	 493.883 Hz
    0x000A031B,		// C5	 523.251 Hz
    0x000A9B84,		// CS5	 554.365 Hz
    0x000B3CFD,		// D5	 587.330 Hz
    0x000BE810,		// DS5	 622.254 Hz
    0x000C9D4F,		// E5	 659.255 Hz
    0x000D5D56,		// F5	 698.456 Hz
    0x000E28C7,		// FS5	 739.989 Hz
    0x000F0052,		// G5	 783.991 Hz
    0x000FE4AD,		// GS5	 830.609 Hz
    0x0010D69D,		// A5	 880.000 Hz
    0x0011D6EF,		// AS5	 932.328 Hz
    0x0012E680,		// B5	 987.767 Hz
    0x00140636,		// C6	1046.502 Hz
    0x00153708,		// CS6	1108.731 Hz
    0x001679FA,		// D6	1174.659 Hz
    0x0017D020,		// DS6	1244.508 Hz
    0x00193A9F,		// E6	1318.510 Hz
    0x001ABAAC,		// F6	1396.913 Hz
    0x001C518E,		// FS6	1479.978 Hz
    0x001E00A3,		// G6	1567.982 Hz
    0x001FC95A,		// GS6	1661.219 Hz
    0x0021AD39,		// A6	1760.000 Hz
    0x0023ADDE,		// AS6	1864.655 Hz
    0x0025CCFF,		// B6	1975.533 Hz
    0x00280C6C		// C7	2093.005 Hz
};

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
void SndPlay(u32 note, s8* pWav, s32 atkS, s32 decS, s32 susS, s32 relS, s32 atkL, s32 susL)
{
	s32 i;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		if(Snd.ch[i].act == SND_ACT_IDLE)
		{
			Snd.ch[i].pWav    = pWav;
			Snd.ch[i].cur     = 0;
			Snd.ch[i].step    = SndPitTbl[note];
			Snd.ch[i].act     = SND_ACT_ATTACK;
			Snd.ch[i].vol     = 0;
			Snd.ch[i].note    = note;
			Snd.ch[i].atkStep = atkS;
			Snd.ch[i].decStep = decS;
			Snd.ch[i].susStep = susS;
			Snd.ch[i].relStep = relS;
			Snd.ch[i].atkLvl  = atkL;
			Snd.ch[i].susLvl  = susL;
			Snd.cnt++;

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
		if(Snd.ch[i].act != SND_ACT_IDLE)
		{
			Snd.ch[i].act = SND_ACT_IDLE;
			Snd.cnt--;
		}
	}
}
//---------------------------------------------------------------------------
s32 SndGetCnt(void)
{
	return Snd.cnt;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndMix(void)
{
	MemClearFast(Snd.tmp, sizeof(Snd.tmp));

	s32 i;

	for(i=0; i<SND_MAX_CHANNEL; i++)
	{
		ST_SND_CH* p = &Snd.ch[i];

		if(p->act == SND_ACT_IDLE)
		{
			continue;
		}

		switch(p->act)
		{
		case SND_ACT_ATTACK:
			p->vol += p->atkStep;

			if(p->vol >= p->atkLvl)
			{
				p->vol = p->atkLvl;
				p->act = SND_ACT_DECAY;
			}
			break;

		case SND_ACT_DECAY:
			p->vol -= p->decStep;

			if(p->vol <= p->susLvl)
			{
				p->vol = p->susLvl;
				p->act = SND_ACT_SUSTAIN;
			}
			break;

		case SND_ACT_SUSTAIN:
			if(p->susStep > 0)
			{
				p->susStep--;
			}
			else
			{
				p->act = SND_ACT_RELEASE;
			}
			break;

		case SND_ACT_RELEASE:
			p->vol -= p->relStep;

			if(p->vol <= 0)
			{
				p->vol = 0;
				p->act = SND_ACT_IDLE;
				Snd.cnt--;
			}
			break;

		default:
			SystemError("[Err] SndMix act=%x\n", p->act);
			break;
		}

		if(p->act == SND_ACT_IDLE)
		{
			continue;
		}

		u32 cur  = p->cur;
		u32 step = p->step;
		s32 vol  = p->vol;
		s8* pWav = p->pWav;
		s32 j;

		for(j=0; j<SND_BUF_SIZE; j++)
		{
			u32 idx  = (cur >> 16) & 0xFF;
			u32 frac = (cur & 0xFFFF) >> 8;

			s32 s1 = (s32)pWav[idx];
			s32 s2 = (s32)pWav[(idx + 1) & 0xFF];

			// 線形補間
			s32 interpolated = s1 + (((s2 - s1) * (s32)frac) >> 8);

			// ミキシング
			Snd.tmp[j] += (interpolated * vol) >> 16;

			cur += step;
		}

		p->cur = cur;
	}

	s8* pOut = Snd.buf + (Snd.act ^ 1) * SND_BUF_SIZE;

	for(i=0; i<SND_BUF_SIZE; i++)
	{
		s32 s = Snd.tmp[i] >> 1;

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
