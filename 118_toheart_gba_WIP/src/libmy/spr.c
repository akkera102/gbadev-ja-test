#include "spr.h"
#include "bios.h"
#include "sjis.h"
#include "../res.h"

// Mode3     BITMAP_OBJ_BASE_ADR
// Mode3ˆÈŠO OBJ_BASE_ADR


//---------------------------------------------------------------------------
ST_SPR Spr;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	BiosCpuSetFixClear(&Spr, sizeof(ST_SPR));
	BiosCpuSetFixClear(BITMAP_OBJ_BASE_ADR, 1024 * 32);


	SprSetDatItem();
	SprSetChrItem();
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
	// Font Buffer
	SprSetChr(0,  18,  22,  512, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(1,  82,  22,  576, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(2, 146,  22,  640, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(3, 210,  22,  704, ATTR0_TALL,   ATTR1_SIZE_32);
	SprSetChr(4, 210,  54,  712, ATTR0_TALL,   ATTR1_SIZE_32);

	SprSetChr(5,  18,  86,  720, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(6,  82,  86,  784, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(7, 146,  86,  848, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(8, 210,  86,  912, ATTR0_TALL,   ATTR1_SIZE_32);
	SprSetChr(9, 210, 118,  920, ATTR0_TALL,   ATTR1_SIZE_32);

	// Cursor
	SprSetChr(10, 240, 160, 1020, ATTR0_WIDE,   ATTR1_SIZE_8);
	SprSetChr(11, 240, 160, 1022, ATTR0_WIDE,   ATTR1_SIZE_8);
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
	u16* pS = SjisGetImgPointer(code);
	s32 i, j;

	for(j=0; j<10; j++)
	{
		for(i=0; i<3; i++)
		{
			u16* pD = (u16*)(0x06014000 + Spr.pTbl[(x * 3) + i + (y * 52 * 12) + (j * 52)]);

			*pD++ = *pS++ & Spr.mask;
		}
	}

	Spr.isDrawDat = TRUE;
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
