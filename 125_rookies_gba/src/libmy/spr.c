#include "spr.h"
#include "mem.h"
#include "sjis.h"
#include "../res.h"

// 例外処理　OAMに直接書いています（チラつき注意

//---------------------------------------------------------------------------
ST_SPR Spr EWRAM_BSS;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	MemClear(&Spr, sizeof(ST_SPR));
	MemClear(BITMAP_OBJ_BASE_ADR, 0x20 * 512);

	// cursor chr + pal
	MemInc((u16*)spr_cursorTiles, BITMAP_OBJ_BASE_ADR + SPR_MAX_DAT_SIZE, spr_cursorTilesLen);
	MemInc((u16*)spr_cursorPal, OBJ_COLORS, spr_cursorPalLen);

	// number chr
	MemInc((u16*)spr_numberTiles, BITMAP_OBJ_BASE_ADR + SPR_MAX_DAT_SIZE + spr_cursorTilesLen, spr_numberTilesLen);

	// spr 1d table
	MemInc((u8*)tbl_spr1d_bin, Spr.tbl, SPR_MAX_TBL_SIZE);

	// font buffer
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

	// cursor
	SprSetChr(10, 240, 160, 936, ATTR0_WIDE,   ATTR1_SIZE_8);
	SprSetChr(11, 240, 160, 938, ATTR0_WIDE,   ATTR1_SIZE_8);

	// number
	SprSetChr(12, 240, 160, 940, ATTR0_SQUARE, ATTR1_SIZE_8);
	SprSetChr(13, 240, 160, 941, ATTR0_SQUARE, ATTR1_SIZE_8);
	SprSetChr(14, 240, 160, 942, ATTR0_SQUARE, ATTR1_SIZE_8);
	SprSetChr(15, 240, 160, 943, ATTR0_SQUARE, ATTR1_SIZE_8);

	SprSetWhite();
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 = (y & 0x00ff) | ATTR0_COLOR_16 | shape;
	p->d1 = (x & 0x01ff) | size;
	p->d2 = tile | ATTR2_PRIORITY(0);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShow(s32 no)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 &= ~ATTR0_DISABLED;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHide(s32 no)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 |= ATTR0_DISABLED;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprMove(s32 no, s32 x, s32 y)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 &= 0xff00;
	p->d1 &= 0xfe00;

	p->d0 |= (y & 0x00ff);
	p->d1 |= (x & 0x01ff);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprClearDat(void)
{
	MemClearFast(BITMAP_OBJ_BASE_ADR, SPR_MAX_DAT_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprDrawDatChr(s32 x, s32 y, u16 code)
{
	u16* pS = SjisGetImgPointer(code);
	s32 ix, iy;

	for(iy=0; iy<10; iy++)
	{
		for(ix=0; ix<3; ix++)
		{
			*(u16*)(BITMAP_OBJ_BASE_ADR + Spr.tbl[(x * 3) + ix+0 + (y * 52 * 12) + (iy * 52)]) = *pS++ & Spr.mask;
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetWhite(void)
{
	Spr.mask = SPR_FONT_MASK_WHITE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetGray(void)
{
	Spr.mask = SPR_FONT_MASK_GRAY;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetSelect(void)
{
	Spr.mask = SPR_FONT_MASK_SELECT;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShowCur(void)
{
	SprShow(10);
	SprShow(11);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHideCur(void)
{
	SprHide(10);
	SprHide(11);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShowMsg(void)
{
	s32 i;

	for(i=0; i<10; i++)
	{
		SprShow(i);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHideMsg(void)
{
	s32 i;

	for(i=0; i<10; i++)
	{
		SprHide(i);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprMoveCur(s32 x, s32 y)
{
	s32 sx = 18 + x * (SPR_FONT_IMG_CX);
	s32 sy = 22 + y * (SPR_FONT_IMG_CY + SPR_FONT_IMG_BLANK_CY);

	SprMove(10, sx, sy);
	SprMove(11, sx, sy+8);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetNum(s32 ans, s32 reg)
{
	s32 x = 0;
	s32 i;

	for(i=0; i<4; i++)
	{
		SprMove(12+i, 240, 160);
	}


	if(ans > 0)
	{
		SprMove(12 + (ans - 1), 0, 0);

		return;
	}

	// 0の場合、登録数分を表示
	for(i=0; i<reg; i++)
	{
		SprMove(12+i, x, 0);
		x += 8;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShowNum(void)
{
	SprShow(12);
	SprShow(13);
	SprShow(14);
	SprShow(15);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHideNum(void)
{
	SprHide(12);
	SprHide(13);
	SprHide(14);
	SprHide(15);
}
