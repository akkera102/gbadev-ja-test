#include "res.h"
#include "bg.h"

//---------------------------------------------------------------------------
ST_BG Bg[BG_MAX_CNT];

//---------------------------------------------------------------------------
void BgInit()
{
	BgInitLcd();

	Bg0Init();
	Bg1Init();
	Bg2Init();
//	Bg3Init();

	REG_DISPCNT = (MODE_1 | BG0_ON | BG1_ON | BG2_ON);
	REG_BG0CNT  = (BG_SIZE_0 | BG_256_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
	REG_BG1CNT  = (BG_SIZE_0 | BG_256_COLOR | Bg[1].tileBase | Bg[1].mapBase | 0);
	REG_BG2CNT  = (BG_SIZE_1 | BG_256_COLOR | Bg[2].tileBase | Bg[2].mapBase | 0);
//	REG_BG3CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[3].tileBase | Bg[3].mapBase | 3 | BG_WRAP);

	REG_BLDCNT  = BLEND_TOP_BG2 | BLEND_MODE_DARK;
}
//---------------------------------------------------------------------------
void BgInitLcd()
{
	const u32 mapBase[]  = { 24, 25, 26,  0 };
	const u32 tileBase[] = {  0,  0,  0,  0 };
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
void Bg0Init()
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
void Bg1Init()
{
	// Bg0—¬—p
}
//---------------------------------------------------------------------------
void Bg2Init()
{
	// Bg0—¬—p
}
//---------------------------------------------------------------------------
void Bg3Init()
{
	// EMPTY
}
//---------------------------------------------------------------------------
IWRAM_CODE void BgDrawStr(s32 x, s32 y, char* s)
{
	// ‹ô”xÀ•W‚Ì‚Ý‘Î‰ž
	_ASSERT((x & 0x1) == 0);

	u16* map = &Bg[2].mapBaseAdr[x + y * 32/2];

	while(*s != NULL)
	{
		u16 w = *s++ - ' ';

		if(*s != NULL)
		{
			w += (*s++ - ' ') << 8;
		}

		*map++ = w;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void BgDrawPrintf(s32 sx, s32 sy, char* format, ...)
{
	char s[100] ALIGN(4);

	char* ap;
	va_start(ap, format);
	_DoSprintf(s, format, ap);
	va_end(ap);

	BgDrawStr(sx, sy, s);
}
