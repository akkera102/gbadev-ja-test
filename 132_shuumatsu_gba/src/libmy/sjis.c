#include "sjis.h"
#include "../res.h"

//---------------------------------------------------------------------------
ST_SJIS Sjis;


//---------------------------------------------------------------------------
void SjisInit(void)
{
	_Memset(&Sjis, 0x00, sizeof(ST_SJIS));

	Sjis.pCct = (u8*)&cct_sjis_bin + SJIS_CCT_HEAD_SIZE;
	Sjis.pImg = (u16*)&fnt_k12x10Bitmap;
}
//---------------------------------------------------------------------------
IWRAM_CODE u16 SjisGetIdx(u16 code)
{
	if(code == 0x0000)
	{
		code = 0x8140;
	}
	else if(_IsSJIS(HIBYTE(code)) == false)
	{
		goto Err;
	}


	// level 1
	u32 c0 = HIBYTE(code) >> 5;
	u32 c1 = HIBYTE(code) & 0x1f;
	u32 i1;

	if(c0 == 4)
	{
		// 80-9F
		i1 = ((u16*)Sjis.pCct)[c1];
	}
	else
	{
		// E0-FF
		i1 = ((u16*)Sjis.pCct)[c1 + 32];
	}

	if(i1 == 0)
	{
		goto Err;
	}


	// level 2
	u32 c2 = LOBYTE(code) >> 6;
	u32 i2 = ((u16*)(Sjis.pCct + i1))[c2];

	if(i2 == 0)
	{
		goto Err;
	}

	ST_SJIS_XCCTENT* pXccTent = (ST_SJIS_XCCTENT*)(Sjis.pCct + i2);
	ST_SJIS_XCCT* pXcct = (ST_SJIS_XCCT*)(Sjis.pCct + i2 + sizeof(ST_SJIS_XCCTENT));


	// level 3
	u32 c3 = LOBYTE(code) & 0x3f;
	u32 i;

	for(i=0; i<pXccTent->count; i++)
	{
		if(c3 >= pXcct->start && c3 <= pXcct->end)
		{
			return pXcct->offset + (c3 - pXcct->start);
		}

		pXcct++;
	}

Err:
	TRACE("code: 0x%x\n", code);
	_ASSERT(0 && "Invaild font idx");

	return SJIS_INVALID_INDEX;
}
//---------------------------------------------------------------------------
IWRAM_CODE u16* SjisGetImgPointer(u16 code)
{
	u16 idx = SjisGetIdx(code);

	return Sjis.pImg + (SJIS_FONT_CX / 4) * SJIS_FONT_CY * idx;
}
