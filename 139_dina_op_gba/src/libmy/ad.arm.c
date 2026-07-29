#include "ad.arm.h"
#include "irq.arm.h"

// Timer1, DMA2

/* playad.iwram.c
   8AD decoder engine

Copyright 2003 Damian Yerrick

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/
//---------------------------------------------------------------------------
s32 AdIndiceTable[8] = {
	-1, -1, -1, -1, 2, 4, 7, 12,
};

u32 AdStepTable[89] = {
	    7,    8,    9,   10,   11,   12,   13,   14,   16,   17,
	   19,   21,   23,   25,   28,   31,   34,   37,   41,   45,
	   50,   55,   60,   66,   73,   80,   88,   97,  107,  118,
	  130,  143,  157,  173,  190,  209,  230,  253,  279,  307,
	  337,  371,  408,  449,  494,  544,  598,  658,  724,  796,
	  876,  963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
	 2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
	 5894, 6484, 7132, 7845, 8630, 9493,10442,11487,12635,13899,
	15289,16818,18500,20350,22385,24623,27086,29794,32767,
};


//---------------------------------------------------------------------------
ST_AD Ad;


//---------------------------------------------------------------------------
void AdInit(void)
{
	_Memset(&Ad, 0x00, sizeof(ST_AD));

	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDB_L_ENABLE | SNDB_R_ENABLE | SNDA_RESET_FIFO | SNDB_RESET_FIFO | DSOUNDCTRL_ATIMER(0) | DSOUNDCTRL_BTIMER(1) | SNDA_VOL_100 | SNDB_VOL_100 | 0x2;
	REG_SOUNDCNT_L = 0;

	REG_DMA2CNT = 0;
	REG_DMA2DAD = (u32)&REG_FIFO_B;

	REG_TM1CNT_H = 0;
	REG_TM1CNT_L = 0x10000 - AD_SAMPLE_TIME;

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_TM1CNT_H = TIMER_START;

	Ad.act = AD_ACT_STOP;
}
//---------------------------------------------------------------------------
IWRAM_CODE void AdPlay(u8* pDat, s32 size, bool isLoop)
{
	Ad.isPlay = 0;

	asm volatile("":::"memory");

	Ad.pNext    = pDat;
	Ad.nextSize = size;
	Ad.nextLoop = isLoop;

	asm volatile("":::"memory");

	Ad.isPlay = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void AdStop(void)
{
	Ad.isStop = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE u32 AdGetRem(void)
{
	return (Ad.pEnd > Ad.pCur) ? (Ad.pEnd - Ad.pCur) : 0;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool AdIsPlay(void)
{
	return (Ad.act == AD_ACT_PLAY) ? true : false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void AdIntrVcount(void)
{
	// VCOUNT 60 -> 72
//	TRACE("S:%d\n", REG_VCOUNT);

	if(Ad.isStop == 1)
	{
		Ad.isStop = 0;
		Ad.act = AD_ACT_STOP;
	}
	else if(Ad.isPlay == 1)
	{
		Ad.isPlay = 0;
		Ad.act = AD_ACT_PLAY;

		Ad.pCur   = (u8*)Ad.pNext;
		Ad.pTop   = (u8*)Ad.pNext;
		Ad.pEnd   = (u8*)Ad.pNext + Ad.nextSize - AD_BUF_SIZE;		// 末尾調整（バグの為）
		Ad.isLoop = Ad.nextLoop;

		Ad.lastIdx  = 0;
		Ad.lastSamp = 0;
		Ad.bufIdx   = 0; 
	}

	if(Ad.act == AD_ACT_STOP)
	{
		return;
	}

	if(Ad.pCur >= Ad.pEnd)
	{
		if(Ad.isLoop == true)
		{
			Ad.pCur     = Ad.pTop;
			Ad.lastIdx  = 0;
			Ad.lastSamp = 0;
		}
		else
		{
			Ad.act = AD_ACT_STOP;
			return;
		}
	}


	Ad.bufIdx ^= 0x01;

	u8* pSrc = Ad.pCur;
	s8* pDst = Ad.buf[Ad.bufIdx];
	s32 idx  = Ad.lastIdx;
	s32 samp = Ad.lastSamp;
	u32 len  = AD_BUF_SIZE;
	u32 by   = 0;

	Ad.pCur += AD_BUF_SIZE >> 1;

	while(len > 0)
	{
		if (idx < 0)       idx =  0;
		else if (idx > 88) idx = 88;

		s32 step = AdStepTable[idx];
		u32 code;

		if(len & 1)
		{
			code = by >> 4;
		}
		else
		{
			by   = *pSrc++;
			code = by & 0x0f;
		}

		s32 diff = step >> 3;

		if (code & 1)        diff += step >> 2;
		if (code & 2)        diff += step >> 1;
		if (code & 4)        diff += step;
		if ((code & 7) == 7) diff += step >> 1;
		if (code & 8)        diff = -diff;

		idx  += AdIndiceTable[code & 0x07];
		samp += diff;

		if (samp < -32768)     samp = -32768;
		else if (samp > 32767) samp =  32767;

		*pDst++ = (s8)(samp >> 8);
		len--;
	}

	Ad.lastIdx  = idx;
	Ad.lastSamp = samp;

//	TRACE("E:%d\n", REG_VCOUNT);
}
//---------------------------------------------------------------------------
IWRAM_CODE void AdIntrVblank(void)
{
	if(Ad.act != AD_ACT_PLAY)
	{
		REG_DMA2CNT = 0;
		REG_DMA2SAD = (u32)Ad.clr;
		REG_DMA2CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;
	}
	else
	{
		REG_DMA2CNT = 0;
		REG_DMA2SAD = (u32)&Ad.buf[Ad.bufIdx];
		REG_DMA2CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;
	}
}
