#include "spr.h"
#include "bios_arm.h"
#include "../res.h"

// Mode3     BITMAP_OBJ_BASE_ADR
// Mode3à»äO OBJ_BASE_ADR


//---------------------------------------------------------------------------
ST_SPR Spr;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	BiosCpuSetFixClear(&Spr, sizeof(ST_SPR));
	BiosCpuSetFixClear(BITMAP_OBJ_BASE_ADR, 1024 * 32);


	SprSetDatItem();
	SprSetChrItem();
	SprSetFontItem();
	SprSetImgWhite();

	REG_DISPCNT |= (OBJ_ON | OBJ_2D_MAP);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprExec(void)
{
	if(Spr.isDrawChr == TRUE)
	{
//		BiosCpuSet(Spr.attr, OAM, sizeof(ST_SPR_ATTR) * SPR_MAX_ATTR_CNT);
		dmaCopy(Spr.attr, OAM, sizeof(ST_SPR_ATTR) * SPR_MAX_ATTR_CNT);
		Spr.isDrawChr = FALSE;
	}

	if(Spr.isDrawDat == TRUE)
	{
//		BiosCpuSet(Spr.dat, BITMAP_OBJ_BASE_ADR, SPR_MAX_DAT_SIZE);
		dmaCopy(Spr.dat, BITMAP_OBJ_BASE_ADR, SPR_MAX_DAT_SIZE);
		Spr.isDrawDat = FALSE;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetDatItem(void)
{
	SprSetDat((u16*)spr_itemTiles, spr_itemTilesLen, (u16*)spr_itemPal, spr_itemPalLen);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetChrItem(void)
{
	// 0Å`7 Font
	// 8Å`9 Cursor

	SprSetChr(0,  18,  22,  512, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(1,  18,  86,  768, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(2,  82,  22,  520, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(3,  82,  86,  776, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(4, 146,  22,  528, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(5, 146,  86,  784, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(6, 210,  22,  536, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(7, 210,  86,  792, ATTR0_SQUARE, ATTR1_SIZE_64);

	SprSetChr(8, 240, 160, 1020, ATTR0_WIDE,   ATTR1_SIZE_8);
	SprSetChr(9, 240, 160, 1022, ATTR0_WIDE,   ATTR1_SIZE_8);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetFontItem(void)
{
	Spr.pImg = (u16*)&fnt_k12x10Bitmap;
	Spr.pCct = (u8*)&cct_sjis_bin + SPR_FONT_CCT_HEAD_SIZE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetDat(u16* pTile, u32 tileSize, u16* pPal, u32 palSize)
{
	BiosCpuSet(pTile, BITMAP_OBJ_BASE_ADR, tileSize);
	BiosCpuSet(pPal, OBJ_COLORS, palSize);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetChr(u32 no, u32 x, u32 y, u16 tile, u16 shape, u16 size)
{
	Spr.attr[no].d0 = (y & 0x00ff) | ATTR0_COLOR_16 | shape;
	Spr.attr[no].d1 = (x & 0x01ff) | size;
	Spr.attr[no].d2 = tile | ATTR2_PRIORITY(0);

	Spr.isDrawChr = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShow(u32 no)
{
	Spr.attr[no].d0 &= ~ATTR0_DISABLED;

	Spr.isDrawChr = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHide(u32 no)
{
	Spr.attr[no].d0 |= ATTR0_DISABLED;

	Spr.isDrawChr = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprMove(u32 no, u32 x, u32 y)
{
	Spr.attr[no].d0 &= 0xff00;
	Spr.attr[no].d1 &= 0xfe00;

	Spr.attr[no].d0 |= (y & 0x00ff);
	Spr.attr[no].d1 |= (x & 0x01ff);

	Spr.isDrawChr = TRUE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprClearDat(void)
{
	BiosCpuSetFastFixClear(Spr.dat, SPR_MAX_DAT_SIZE);
	Spr.isDrawDat = TRUE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprDrawDatChr(u32 x, u32 y, u16 code)
{
	u16 idx = SprGetSjisIdx(code);
	u8 flag = 0x00;

	if(x & 0x01)
	{
		flag |= 0x01;
	}

	if(y & 0x01)
	{
		flag |= 0x10;
	}

	switch(flag)
	{
	case 0x00:
		SprDrawDatChrSub1(x, y, idx);
		break;

	case 0x01:
		SprDrawDatChrSub2(x, y, idx);
		break;

	case 0x10:
		SprDrawDatChrSub3(x, y, idx);
		break;

	case 0x11:
		SprDrawDatChrSub4(x, y, idx);
		break;
	}

	Spr.isDrawDat = TRUE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprDrawDatChrSub1(u32 x, u32 y, u16 code)
{
	u16* pSrc1 = (u16*)&Spr.dat + (y * 768) + (x * 24);
	u16* pSrc2 = pSrc1 + 16;
	u16* pSrc3 = pSrc1 + 512;
	u16* pSrc4 = pSrc1 + 512 + 16;
	u16* pDst  = Spr.pImg + ((SPR_FONT_IMG_CX / 4) * SPR_FONT_IMG_CY) * code;
	u32  i;

	for(i=0; i<8; i++)
	{
		*pSrc1++ = *pDst++ & Spr.mask;
		*pSrc1++ = *pDst++ & Spr.mask;
		*pSrc2++ = *pDst++ & Spr.mask;

		pSrc2++;
	}

	for(i=0; i<2; i++)
	{
		*pSrc3++ = *pDst++ & Spr.mask;
		*pSrc3++ = *pDst++ & Spr.mask;
		*pSrc4++ = *pDst++ & Spr.mask;

		pSrc4++;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprDrawDatChrSub2(u32 x, u32 y, u16 code)
{
	u16* pSrc1 = (u16*)&Spr.dat + (16+1) + (y * 768) + ((x-1) * 24);
	u16* pSrc2 = pSrc1 + 16 - 1;
	u16* pSrc3 = pSrc1 + 512;
	u16* pSrc4 = pSrc2 + 512;
	u16* pDst  = Spr.pImg + ((SPR_FONT_IMG_CX / 4) * SPR_FONT_IMG_CY) * code;
	u32  i;

	for(i=0; i<8; i++)
	{
		*pSrc1++ = *pDst++ & Spr.mask;
		*pSrc2++ = *pDst++ & Spr.mask;
		*pSrc2++ = *pDst++ & Spr.mask;

		pSrc1++;
	}

	for(i=0; i<2; i++)
	{
		*pSrc3++ = *pDst++ & Spr.mask;
		*pSrc4++ = *pDst++ & Spr.mask;
		*pSrc4++ = *pDst++ & Spr.mask;

		pSrc3++;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprDrawDatChrSub3(u32 x, u32 y, u16 code)
{
	u16* pSrc1 = (u16*)&Spr.dat + (512 + 8) + ((y-1) * 768) + (x * 24);
	u16* pSrc2 = pSrc1 + 16;
	u16* pSrc3 = pSrc1 + 512 - 8;
	u16* pSrc4 = pSrc2 + 512 - 8;
	u16* pDst  = Spr.pImg + ((SPR_FONT_IMG_CX / 4) * SPR_FONT_IMG_CY) * code;
	u32  i;

	for(i=0; i<4; i++)
	{
		*pSrc1++ = *pDst++ & Spr.mask;
		*pSrc1++ = *pDst++ & Spr.mask;
		*pSrc2++ = *pDst++ & Spr.mask;

		pSrc2++;
	}

	for(i=0; i<6; i++)
	{
		*pSrc3++ = *pDst++ & Spr.mask;
		*pSrc3++ = *pDst++ & Spr.mask;
		*pSrc4++ = *pDst++ & Spr.mask;

		pSrc4++;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprDrawDatChrSub4(u32 x, u32 y, u16 code)
{
	u16* pSrc1 = (u16*)&Spr.dat + (528 + 8 + 1) + ((y-1) * 768) + ((x-1) * 24);
	u16* pSrc2 = pSrc1 +  16 - 1;
	u16* pSrc3 = pSrc1 + 512 - 8;
	u16* pSrc4 = pSrc3 +  16 - 1;
	u16* pDst  = Spr.pImg + ((SPR_FONT_IMG_CX / 4) * SPR_FONT_IMG_CY) * code;
	u32  i;

	for(i=0; i<4; i++)
	{
		*pSrc1++ = *pDst++ & Spr.mask;
		*pSrc2++ = *pDst++ & Spr.mask;
		*pSrc2++ = *pDst++ & Spr.mask;

		pSrc1++;
	}

	for(i=0; i<6; i++)
	{
		*pSrc3++ = *pDst++ & Spr.mask;
		*pSrc4++ = *pDst++ & Spr.mask;
		*pSrc4++ = *pDst++ & Spr.mask;

		pSrc3++;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE u16 SprGetSjisIdx(u16 code)
{
	if(code == 0x0000)
	{
		code = 0x8140;
	}
	else if(_IsSJIS(HIBYTE(code)) == FALSE)
	{
		goto Err;
	}


	// level 1
	u16 c0 = HIBYTE(code) >> 5;
	u16 c1 = HIBYTE(code) & 0x1f;
	u16 i1;

	if(c0 == 4)
	{
		// 80-9F
		i1 = ((u16*)Spr.pCct)[c1];
	}
	else
	{
		// E0-FF
		i1 = ((u16*)Spr.pCct)[c1 + 32];
	}

	if(i1 == 0)
	{
		goto Err;
	}


	// level 2
	u16 c2 = LOBYTE(code) >> 6;
	u16 i2 = ((u16*)(Spr.pCct + i1))[c2];

	if(i2 == 0)
	{
		goto Err;
	}

	ST_XCCTENT* pXccTent = (ST_XCCTENT*)(Spr.pCct + i2);
	ST_XCCT* pXcct = (ST_XCCT*)(Spr.pCct + i2 + sizeof(ST_XCCTENT));


	// level 3
	u16 c3 = LOBYTE(code) & 0x3f;
	u16 i;

	for(i=0; i<pXccTent->count; i++)
	{
		if(c3 >= pXcct->start && c3 <= pXcct->end)
		{
			return pXcct->offset + (c3 - pXcct->start);
		}

		pXcct++;
	}


Err:
	TRACEOUT("code: 0x%x\n", code);
	_ASSERT(0 && "Invaild font idx");
	return SPR_FONT_INVALID_INDEX;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetImgWhite(void)
{
	Spr.mask = SPR_FONT_MASK_WHITE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetImgGray(void)
{
	Spr.mask = SPR_FONT_MASK_GRAY;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SprIsImgWhite(void)
{
	return (Spr.mask == SPR_FONT_MASK_WHITE) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShowCursor(void)
{
	SprShow(8);
	SprShow(9);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHideCursor(void)
{
	SprHide(8);
	SprHide(9);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprMoveCursor(u32 x, u32 y)
{
	u32 sx = 18 + x * (SPR_FONT_IMG_CX);
	u32 sy = 22 + y * (SPR_FONT_IMG_CY + SPR_FONT_IMG_BLANK_CY);

	SprMove(8, sx, sy);
	SprMove(9, sx, sy+8);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShowWindow(void)
{
	s32 i;

	for(i=0; i<8; i++)
	{
		SprShow(i);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHideWindow(void)
{
	s32 i;

	for(i=0; i<8; i++)
	{
		SprHide(i);
	}
}
