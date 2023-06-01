#include "res.h"
#include "bg.h"


//bg0 ASCII

//---------------------------------------------------------------------------
ST_BG Bg[BG_MAX_CNT];

//---------------------------------------------------------------------------
EWRAM_CODE void BgInit()
{
	BgInitLcd();

	Bg0Init();
//	Bg1Init();
//	Bg2Init();
//	Bg3Init();

	REG_DISPCNT = (MODE_0 | BG0_ON | OBJ_1D_MAP);
	REG_BG0CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
//	REG_BG1CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[1].tileBase | Bg[1].mapBase | 0);
//	REG_BG2CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[2].tileBase | Bg[2].mapBase | 2 | BG_WRAP);
//	REG_BG3CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[3].tileBase | Bg[3].mapBase | 3 | BG_WRAP);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgInitLcd()
{
	const u32 mapBase[]  = { 29, 30, 31,  0 };
	const u32 tileBase[] = {  0,  1,  3,  0 };
	volatile s32 i;

	for(i=0; i<BG_MAX_CNT; i++)
	{
		Bg[i].mapBase     = MAP_BASE(mapBase[i]);
		Bg[i].mapBaseAdr  = MAP_BASE_ADR(mapBase[i]);
		Bg[i].tileBase    = TILE_BASE(tileBase[i]);
		Bg[i].tileBaseAdr = TILE_BASE_ADR(tileBase[i]);
	}

	for(i=0; i<32*32; i++)
	{
		Bg[0].mapBaseAdr[i] = 0;
		Bg[1].mapBaseAdr[i] = 0;
		Bg[2].mapBaseAdr[i] = 0;
		Bg[3].mapBaseAdr[i] = 0;
	}

	for(i=0; i<0x2000; i++)
	{
		Bg[0].tileBaseAdr[i] = 0;
		Bg[1].tileBaseAdr[i] = 0;
		Bg[2].tileBaseAdr[i] = 0;
		Bg[3].tileBaseAdr[i] = 0;
	}
}
//---------------------------------------------------------------------------
// ASCIIƒtƒHƒ“ƒg‚ðÝ’è‚µ‚Ü‚·
EWRAM_CODE void Bg0Init()
{
	volatile s32 i;

	for(i=0; i<4096; i++)
	{
		Bg[0].tileBaseAdr[i] = font_asciiTiles[i];
	}

	for(i=0; i<16; i++)
	{
		BG_PALETTE[i]  = font_asciiPal[i];
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg1Init()
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg2Init()
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg3Init()
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgAsciiDrawStr(s32 x, s32 y, char* s)
{
	u16* map = &Bg[0].mapBaseAdr[x + y * 32];

	while(*s != NULL)
	{
		*map++ = *s++ - ' ';
	}
}
