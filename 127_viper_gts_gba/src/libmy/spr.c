#include "spr.h"
#include "mem.h"
#include "sjis.h"
#include "../res.h"

// 例外処理　OAMに直接書いています（チラつき注意

//---------------------------------------------------------------------------
ST_SPR Spr;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	_Memset(&Spr, 0x00, sizeof(ST_SPR));
//	MemClear(BITMAP_OBJ_BASE_ADR, 0x20 * 512);

	// cursor chr + pal
	MemInc((u16*)spr_cursorTiles, BITMAP_OBJ_BASE_ADR + SPR_MAX_MSG_SIZE, spr_cursorTilesLen);
	MemInc((u16*)spr_cursorPal, OBJ_COLORS, spr_cursorPalLen);

	// font buffer
	SprSetChr(0,   0, 160 - 8*4, 512, ATTR0_WIDE, ATTR1_SIZE_64);
	SprSetChr(1,  64, 160 - 8*4, 520, ATTR0_WIDE, ATTR1_SIZE_64);
	SprSetChr(2, 128, 160 - 8*4, 528, ATTR0_WIDE, ATTR1_SIZE_64);
	SprSetChr(3, 192, 160 - 8*4, 536, ATTR0_WIDE, ATTR1_SIZE_64);

	// cursor
	SprSetChr(4, 240 - 8, 160 - 16, 640, ATTR0_NORMAL, ATTR1_SIZE_8);

	SprSetWhite();
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

	p->d0 = (y & 0x00ff) | ATTR0_COLOR_16 | ATTR0_DISABLED | shape;
	p->d1 = (x & 0x01ff) | size;
	p->d2 = tile | ATTR2_PRIORITY(0);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetTile(s32 no, s32 tile)
{
	ST_SPR_OAM* p = (ST_SPR_OAM*)OAM + no;

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
EWRAM_CODE void SprClearMsg(void)
{
	MemClearFast(BITMAP_OBJ_BASE_ADR, SPR_MAX_MSG_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprDrawMsg(s32 x, s32 y, u16 code)
{
	u16* pS = SjisGetImgPointer(code);
	u16* pD = BITMAP_OBJ_BASE_ADR + x * 32 + y * 1024;
	s32 i;

	for(i=0; i<16; i++)
	{
		*pD++ = *pS++ & Spr.mask;
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
EWRAM_CODE void SprShowMsg(void)
{
	s32 i;

	for(i=0; i<4; i++)
	{
		SprShow(i);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprShowCur(s32 id)
{
	SprSetTile(4, 640 + id);
	SprShow(4);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHideMsg(void)
{
	s32 i;

	for(i=0; i<4; i++)
	{
		SprHide(i);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprHideCur(void)
{
	SprHide(4);
}
