#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "txt.h"
#include "img.h"

// Nv.pCur Žš‹å‰ðÍ

//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE u32 NvGetCurNum(void)
{
	u32 ret = 0;

	NvSkipCurSpace();

	do {
		ret *= 10;
		ret  = *Nv.pCur++ - '0';

	} while(_IsDigit(*Nv.pCur) == true);


	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 NvGetCurHex(void)
{
	u32 ret = 0;

	NvSkipCurSpace();

	do {

		ret *= 0x10;

		if(*Nv.pCur >= 'a' && *Nv.pCur <= 'f')
		{
			ret += *Nv.pCur++ - 'a' + 10;
		}
		else
		{
			ret += *Nv.pCur++ - '0';
		}

	} while(_IsXDigit(*Nv.pCur) == true);

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetCurStr(void)
{
	s32 i = 0;

	NvSkipCurSpace();

	do {

//		_ASSERT(i+1 < NV_MAX_STR_CNT);
		Nv.str[i++] = *Nv.pCur++;

	} while(*Nv.pCur != ' ' && *Nv.pCur != '\0' && *Nv.pCur != NV_LF);


	_ASSERT(i+1 < NV_MAX_STR_CNT);
	Nv.str[i++] = '\0';
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSkipCurLine(void)
{
	do {

		if(*Nv.pCur == '\0')
		{
			return;
		}

	} while(*Nv.pCur++ != NV_LF);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSkipCurLine2(s32 cnt)
{
	s32 i;

	for(i=0; i<cnt; i++)
	{
		NvSkipCurLine();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSkipCurSpace(void)
{
	for(;;)
	{
		if(*Nv.pCur == '\0')
		{
			return;
		}

		if(*Nv.pCur == ' ')
		{
			Nv.pCur++;

			continue;
		}

		return;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSkipCurChr(u8 chr)
{
	while(*Nv.pCur != chr)
	{
		Nv.pCur++;
	}

	Nv.pCur++;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvJumpCurAdr(u16 adr)
{
	u8* p = Nv.pCur;

	while(adr != NvGetCurHex())
	{
		NvSkipCurLine();
		p = Nv.pCur;
	}

	Nv.pCur = p;
}
