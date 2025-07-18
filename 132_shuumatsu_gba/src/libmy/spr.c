#include "spr.h"
#include "mem.h"
#include "sjis.h"
#include "../res.h"

// 例外処理　OAMに直接書いています（チラつき注意

//---------------------------------------------------------------------------
ST_SPR Spr;


//---------------------------------------------------------------------------
void SprInit(void)
{
	MemClear(&Spr, sizeof(ST_SPR));
	MemClear(BITMAP_OBJ_BASE_ADR, 0x20 * 512);

	// cursor chr + pal
	MemInc((u16*)spr_cursorTiles, BITMAP_OBJ_BASE_ADR + SPR_MAX_DAT_SIZE, spr_cursorTilesLen);
	MemInc((u16*)spr_cursorPal, OBJ_COLORS, spr_cursorPalLen);

	// spr 1d table
	MemInc((u8*)tbl_spr1d_bin, Spr.tbl, SPR_MAX_TBL_SIZE);

	// font buffer
	SprSetChr(0,   18,  22,  512, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(1,   82,  22,  576, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(2,  146,  22,  640, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(3,  210,  22,  704, ATTR0_TALL,   ATTR1_SIZE_32);
	SprSetChr(4,  210,  54,  712, ATTR0_TALL,   ATTR1_SIZE_32);

	SprSetChr(5,   18,  86,  720, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(6,   82,  86,  784, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(7,  146,  86,  848, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr(8,  210,  86,  912, ATTR0_TALL,   ATTR1_SIZE_32);
	SprSetChr(9,  210, 118,  920, ATTR0_TALL,   ATTR1_SIZE_32);

	// cursor
	SprSetChr(10, 240, 160, 936, ATTR0_SQUARE, ATTR1_SIZE_16);

	SprSetWhite();
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 = (y & 0x00ff) | ATTR0_COLOR_16 | shape;
	p->d1 = (x & 0x01ff) | size;
	p->d2 = tile | ATTR2_PRIORITY(0);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprSetTile(s32 no, s32 tile)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d2 = tile | ATTR2_PRIORITY(0);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprShow(s32 no)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 &= ~ATTR0_DISABLED;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprHide(s32 no)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 |= ATTR0_DISABLED;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprMove(s32 no, s32 x, s32 y)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 &= 0xff00;
	p->d1 &= 0xfe00;

	p->d0 |= (y & 0x00ff);
	p->d1 |= (x & 0x01ff);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprClearDat(void)
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
			*(u16*)(BITMAP_OBJ_BASE_ADR + Spr.tbl[(x * 3) + ix+0 + (y * 52 * 12) + (iy * 52)]) = *pS++ & Spr.msk;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprSetWhite(void)
{
	Spr.msk = SPR_FONT_MASK_WHITE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprSetGray(void)
{
	Spr.msk = SPR_FONT_MASK_GRAY;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprSetSelect(void)
{
	Spr.msk = SPR_FONT_MASK_SELECT;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprSetSelectCol(u16 col)
{
	if(col == 0) SPRITE_PALETTE[3] = RGB5( 0,31,31);	// 水色
	if(col == 1) SPRITE_PALETTE[3] = RGB5(31,31, 0);	// 黄
	if(col == 2) SPRITE_PALETTE[3] = RGB5(31,31,31);	// 白
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprShowMsg(void)
{
	if(Spr.isMsg == true)
	{
		return;
	}

	s32 i;

	for(i=0; i<10; i++)
	{
		SprShow(i);
	}

	Spr.isMsg = true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprShowCur(s32 no)
{
	SprSetTile(10, 936 + no);
	SprShow(10);

	Spr.isCur = true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprHideMsg(void)
{
	if(Spr.isMsg == false)
	{
		return;
	}

	s32 i;

	for(i=0; i<10; i++)
	{
		SprHide(i);
	}

	Spr.isMsg = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprHideCur(void)
{
	SprHide(10);

	Spr.isCur = false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprMoveCur(s32 x, s32 y)
{
	s32 sx = 18 + x * (SPR_FONT_IMG_CX);
	s32 sy = 22 + y * (SPR_FONT_IMG_CY + SPR_FONT_IMG_BLANK_CY);

	SprMove(10, sx, sy);
}
