#include "snd.arm.h"

//---------------------------------------------------------------------------
// Generated for 13359Hz, Table Size: 256
// Pitch Step Values (16.16 Fixed Point)
const u32 SndPitTbl[] = {
    0x000140DE,		// C2	  65.406 Hz
    0x000153F3,		// CS2	  69.296 Hz
    0x00016829,		// D2	  73.416 Hz
    0x00017D94,		// DS2	  77.782 Hz
    0x00019445,		// E2	  82.407 Hz
    0x0001AC4F,		// F2	  87.307 Hz
    0x0001C5C7,		// FS2	  92.499 Hz
    0x0001E0C2,		// G2	  97.999 Hz
    0x0001FD59,		// GS2	 103.826 Hz
    0x00021BA2,		// A2	 110.000 Hz
    0x00023BB9,		// AS2	 116.541 Hz
    0x00025DB8,		// B2	 123.471 Hz
    0x000281BC,		// C3	 130.813 Hz
    0x0002A7E5,		// CS3	 138.591 Hz
    0x0002D053,		// D3	 146.832 Hz
    0x0002FB28,		// DS3	 155.563 Hz
    0x00032889,		// E3	 164.814 Hz
    0x0003589D,		// F3	 174.614 Hz
    0x00038B8D,		// FS3	 184.997 Hz
    0x0003C184,		// G3	 195.998 Hz
    0x0003FAB1,		// GS3	 207.652 Hz
    0x00043744,		// A3	 220.000 Hz
    0x00047771,		// AS3	 233.082 Hz
    0x0004BB70,		// B3	 246.942 Hz
    0x00050379,		// C4	 261.626 Hz
    0x00054FCA,		// CS4	 277.183 Hz
    0x0005A0A6,		// D4	 293.665 Hz
    0x0005F650,		// DS4	 311.127 Hz
    0x00065113,		// E4	 329.628 Hz
    0x0006B13B,		// F4	 349.228 Hz
    0x0007171A,		// FS4	 369.994 Hz
    0x00078309,		// G4	 391.995 Hz
    0x0007F562,		// GS4	 415.305 Hz
    0x00086E88,		// A4	 440.000 Hz
    0x0008EEE3,		// AS4	 466.164 Hz
    0x000976DF,		// B4	 493.883 Hz
    0x000A06F1,		// C5	 523.251 Hz
    0x000A9F95,		// CS5	 554.365 Hz
    0x000B414C,		// D5	 587.330 Hz
    0x000BECA0,		// DS5	 622.254 Hz
    0x000CA225,		// E5	 659.255 Hz
    0x000D6275,		// F5	 698.456 Hz
    0x000E2E34,		// FS5	 739.989 Hz
    0x000F0611,		// G5	 783.991 Hz
    0x000FEAC4,		// GS5	 830.609 Hz
    0x0010DD11,		// A5	 880.000 Hz
    0x0011DDC6,		// AS5	 932.328 Hz
    0x0012EDBE,		// B5	 987.767 Hz
    0x00140DE3,		// C6	1046.502 Hz
    0x00153F29,		// CS6	1108.731 Hz
    0x00168297,		// D6	1174.659 Hz
    0x0017D941,		// DS6	1244.508 Hz
    0x0019444A,		// E6	1318.510 Hz
    0x001AC4EA,		// F6	1396.913 Hz
    0x001C5C69,		// FS6	1479.978 Hz
    0x001E0C23,		// G6	1567.982 Hz
    0x001FD589,		// GS6	1661.219 Hz
    0x0021BA22,		// A6	1760.000 Hz
    0x0023BB8B,		// AS6	1864.655 Hz
    0x0025DB7C,		// B6	1975.533 Hz
    0x00281BC5		// C7	2093.005 Hz
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
	vs32 i;

	for(i=0; i<SND_BUF_SIZE; i++)
	{
		Snd.tmp[i] = 0;
	}

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
