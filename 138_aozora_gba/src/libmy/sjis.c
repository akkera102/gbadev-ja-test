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
	if(code == 0x0)
	{
		// ‘SŠp‚Ì‹ó”’
		return 0;
	}


	u32 hi = code >> 8;

	// lv1
	u32 i1_idx = (hi & 0x1f) | ((hi >> 1) & 0x20);
	u32 i1     = ((u16*)Sjis.pCct)[i1_idx];

	if(i1 == 0)
	{
		goto Err;
	}

	// lv2
	u32 lo = code & 0xff;
	u32 c2 = lo >> 6;
	u32 i2 = ((u16*)(Sjis.pCct + i1))[c2];

	if(i2 == 0)
	{
		goto Err;
	}

	// lv3
	ST_SJIS_XCCTENT* pXccTent = (ST_SJIS_XCCTENT*)(Sjis.pCct + i2);
	ST_SJIS_XCCT* pXcct = (ST_SJIS_XCCT*)(pXccTent + 1);

	u32 c3  = lo & 0x3f;
	u32 cnt = pXccTent->count;
	u32 i;

	for(i=0; i<cnt; i++)
	{
		u32 st = pXcct->start;
		u32 ed = pXcct->end;

		if(c3>=st && c3<=ed)
		{
			return pXcct->offset + (c3 - st);
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

	return Sjis.pImg + ((SJIS_FONT_CX / 4) * SJIS_FONT_CY) * idx;
}
