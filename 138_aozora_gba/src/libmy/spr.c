#include "spr.h"
#include "mem.arm.h"
#include "sjis.h"
#include "../res.h"

// 例外処理　OAMに直接書いています（チラつき注意

//---------------------------------------------------------------------------
ST_SPR Spr;


//---------------------------------------------------------------------------
void SprInit(void)
{
	MemClr(&Spr, sizeof(ST_SPR));
	MemClr(BITMAP_OBJ_BASE_ADR, 0x20 * 512);

	// cursor chr + pal
	MemInc((u16*)spr_cursorTiles, BITMAP_OBJ_BASE_ADR + SPR_MAX_DAT_SIZE, spr_cursorTilesLen);
	MemInc((u16*)spr_cursorPal, OBJ_COLORS, spr_cursorPalLen);

	// spr 1d table
	MemInc((u8*)tbl_spr1d_bin, Spr.tbl, SPR_MAX_TBL_SIZE);

	// font buffer
	SprSetChr( 0,  18,  84, 512, ATTR0_SQUARE, ATTR1_SIZE_64);	// 8*8=64, 4*4=16
	SprSetChr( 1,  82,  84, 576, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr( 2, 146,  84, 640, ATTR0_SQUARE, ATTR1_SIZE_64);
	SprSetChr( 3, 210,  84, 704, ATTR0_TALL,   ATTR1_SIZE_32);	// 上半分
	SprSetChr( 4, 210, 116, 712, ATTR0_TALL,   ATTR1_SIZE_32);	// 下半分

	SprSetChr( 5,  18, 148, 720, ATTR0_WIDE,   ATTR1_SIZE_64);
	SprSetChr( 6,  82, 148, 752, ATTR0_WIDE,   ATTR1_SIZE_64);
	SprSetChr( 7, 146, 148, 784, ATTR0_WIDE,   ATTR1_SIZE_64);
	SprSetChr( 8, 210, 148, 816, ATTR0_TALL,   ATTR1_SIZE_32);

	// cursor
	SprSetChr( 9, 240, 160, 824, ATTR0_SQUARE, ATTR1_SIZE_16);
	// navi
	SprSetChr(10, 240, 160, 840, ATTR0_SQUARE, ATTR1_SIZE_16);

	SprSetBase();
}
//---------------------------------------------------------------------------
void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 = (y & 0x00ff) | ATTR0_COLOR_16 | ATTR0_DISABLED | shape;
	p->d1 = (x & 0x01ff) | size;
	p->d2 = ATTR2_PRIORITY(0) | tile;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprSetTile(s32 no, s32 tile)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d2 = ATTR2_PRIORITY(0) | tile;
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
IWRAM_CODE void SprClrDat(void)
{
	MemClrFast(BITMAP_OBJ_BASE_ADR, SPR_MAX_DAT_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprVramSjis(s32 x, s32 y, u16 code)
{
	u16* p  = SjisGetImgPointer(code);
	u16 msk = Spr.msk;
	s32 row = (x * 3) + (y * 624);
	s32 i;

	for(i=0; i<10; i++)
	{
		// アンローリング
		*(u16*)(BITMAP_OBJ_BASE_ADR + Spr.tbl[row + 0]) = *p++ & msk;
		*(u16*)(BITMAP_OBJ_BASE_ADR + Spr.tbl[row + 1]) = *p++ & msk;
		*(u16*)(BITMAP_OBJ_BASE_ADR + Spr.tbl[row + 2]) = *p++ & msk;

		row += 52;
	}
}
//---------------------------------------------------------------------------
void SprSetBase(void)
{
	Spr.msk = SPR_FONT_MASK_BASE;
}
//---------------------------------------------------------------------------
void SprSetGray(void)
{
	Spr.msk = SPR_FONT_MASK_GRAY;
}
//---------------------------------------------------------------------------
void SprSetRead(void)
{
	Spr.msk = SPR_FONT_MASK_READ;
}
//---------------------------------------------------------------------------
void SprSetColBase(u16 no)
{
	if(no == 0) SPRITE_PALETTE[7] = RGB5(31,31,31);	// 白
	if(no == 1) SPRITE_PALETTE[7] = RGB5( 0,31,31);	// 水
	if(no == 2) SPRITE_PALETTE[7] = RGB5(31,31, 0);	// 黄
	if(no == 3) SPRITE_PALETTE[7] = RGB5(12,31,12);	// 緑
	if(no == 4) SPRITE_PALETTE[7] = RGB5(31,19,17);	// 赤
}
//---------------------------------------------------------------------------
void SprSetColRead(u16 no)
{
	if(no == 0) SPRITE_PALETTE[3] = RGB5(31,31,31);	// 白
	if(no == 1) SPRITE_PALETTE[3] = RGB5( 0,31,31);	// 水
	if(no == 2) SPRITE_PALETTE[3] = RGB5(31,31, 0);	// 黄
	if(no == 3) SPRITE_PALETTE[3] = RGB5(12,31,12);	// 緑
	if(no == 4) SPRITE_PALETTE[3] = RGB5(31,19,17);	// 赤
}
//---------------------------------------------------------------------------
void SprShowMsg(void)
{
	s32 i;

	for(i=0; i<9; i++)
	{
		SprShow(i);
	}
}
//---------------------------------------------------------------------------
void SprShowCur(s32 no)
{
	SprSetTile(9, 824 + no);
	SprShow(9);
}
//---------------------------------------------------------------------------
void SprShowNavi(void)
{
	SprShow(10);
}
//---------------------------------------------------------------------------
void SprHideMsg(void)
{
	s32 i;

	for(i=0; i<9; i++)
	{
		SprHide(i);
	}
}
//---------------------------------------------------------------------------
void SprHideCur(void)
{
	SprHide(9);
}
//---------------------------------------------------------------------------
void SprHideNavi(void)
{
	SprHide(10);
}
//---------------------------------------------------------------------------
void SprMoveCur(s32 x, s32 y)
{
	s32 sx = 18 + x * (SPR_FONT_IMG_CX);
	s32 sy = 84 + y * (SPR_FONT_IMG_CY + SPR_FONT_IMG_BLANK_CY);

	SprMove(9, sx, sy);
}
//---------------------------------------------------------------------------
void SprMoveNavi(s32 y)
{
	s32 sy = 84 + y * (SPR_FONT_IMG_CY + SPR_FONT_IMG_BLANK_CY);

	SprMove(10, 6, sy);
}
