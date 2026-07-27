#include "mode4.arm.h"
#include "../libbios/swi.h"
#include "mem.arm.h"


//---------------------------------------------------------------------------
ST_MODE4 Mode4;


//---------------------------------------------------------------------------
void Mode4Init(void)
{
	_Memset(&Mode4, 0x00, sizeof(ST_MODE4));

	Mode4.pFront = MODE4_BUF_ADR1;
	Mode4.pBack  = MODE4_BUF_ADR2;

	REG_BG2PA = 192;
	REG_BG2PB = 0;
	REG_BG2PC = 0;
	REG_BG2PD = 192;

	REG_BG2X = 0;
	REG_BG2Y = 0;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4Exec(void)
{
	if(Mode4.pFront == MODE4_BUF_ADR1)
	{
		Mode4.pFront = MODE4_BUF_ADR2;
		Mode4.pBack  = MODE4_BUF_ADR1;
	}
	else
	{
		Mode4.pFront = MODE4_BUF_ADR1;
		Mode4.pBack  = MODE4_BUF_ADR2;
	}

	REG_DISPCNT ^= BACKBUFFER;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4Draw(u16* pImg)
{
	SwiLZ77UnCompWrite16bit(pImg, Mode4.buf);

	u8 *src = (u8*)Mode4.buf;
	u8 *dst = (u8*)Mode4.pBack;

	s32 y;

	for(y=0; y<120; y++)
	{
		MemInc(src + y*180, dst + y*240, 180);
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4DrawClr(void)
{
	MemClr(Mode4.pBack, 180*120*2);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4Pal(u16* pPal)
{
	SwiLZ77UnCompWrite16bit(pPal, BG_PALETTE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4PalClr(void)
{
	MemClr(BG_PALETTE, 256*2);
}
