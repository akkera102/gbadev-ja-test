#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "txt.h"
#include "img.h"

// Nv.pCur‚ÌŽš‹å‰ðÍ

//---------------------------------------------------------------------------
extern ST_NV Nv;


//---------------------------------------------------------------------------
IWRAM_CODE u32 NvGetCurNum(void)
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
IWRAM_CODE u32 NvGetCurHex(void)
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
IWRAM_CODE void NvSetCurStr(void)
{
	s32 i = 0;

	NvSkipCurSpace();

	do {

//		_ASSERT(i+1 < NV_MAX_STR_CNT);
		Nv.str[i++] = *Nv.pCur++;

	} while(*Nv.pCur != ' ' && *Nv.pCur != '\0' && *Nv.pCur != LF);


	_ASSERT(i+1 < NV_MAX_STR_CNT);
	Nv.str[i++] = '\0';
}
//---------------------------------------------------------------------------
IWRAM_CODE void NvSkipCurLine(void)
{
	do {

		if(*Nv.pCur == '\0')
		{
			return;
		}

	} while(*Nv.pCur++ != LF);
}
//---------------------------------------------------------------------------
IWRAM_CODE void NvSkipCurLine2(s32 cnt)
{
	s32 i;

	for(i=0; i<cnt; i++)
	{
		NvSkipCurLine();
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void NvSkipCurSpace(void)
{
	for(;;)
	{
		if(*Nv.pCur == ' ')
		{
			Nv.pCur++;

			continue;
		}

		return;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void NvSkipCurChr(u8 chr)
{
	while(*Nv.pCur != chr)
	{
		Nv.pCur++;
	}

	Nv.pCur++;
}
//---------------------------------------------------------------------------
IWRAM_CODE void NvJumpCurAdr(u16 adr)
{
	u8* p = Nv.pCur;

	while(adr != NvGetCurHex())
	{
		NvSkipCurLine();
		p = Nv.pCur;
	}

	Nv.pCur = p;
}
