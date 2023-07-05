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
EWRAM_CODE u32  NvGetCurNum2(u8* pCur)
{
	u8* pTmp = Nv.pCur;
	Nv.pCur  = pCur;

	u32 ret = NvGetCurNum();
	Nv.pCur = pTmp;

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
EWRAM_CODE u32  NvGetCurHex2(u8* pCur)
{
	u8* pTmp = Nv.pCur;
	Nv.pCur  = pCur;

	u32 ret = NvGetCurHex();
	Nv.pCur = pTmp;

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetCurStr(void)
{
	s32 i = 0;

	NvSkipCurSpace();

	do {

		_ASSERT(i+1 < NV_MAX_STR_CNT);
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
EWRAM_CODE void NvJumpCurAdr(u16 adr)
{
	u8* p;

	do {

		NvSkipCurLine();
		p = Nv.pCur;

	} while(adr != NvGetCurHex());

	Nv.pCur = p;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8* NvSeekCurChr(u8 chr)
{
	u8* p = Nv.pCur;

	while(*p != chr)
	{
		p++;
	}

	return p;
}
