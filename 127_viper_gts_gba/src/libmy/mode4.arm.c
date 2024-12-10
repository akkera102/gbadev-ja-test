#include "mode4.arm.h"
#include "../libbios/bios.h"
#include "mem.h"
#include "../res.h"


//---------------------------------------------------------------------------
ST_MODE4 Mode4;


//---------------------------------------------------------------------------
EWRAM_CODE void Mode4Init(void)
{
	_Memset(&Mode4, 0x00, sizeof(ST_MODE4));

	Mode4.pFront = MODE4_BUF_ADR1;
	Mode4.pBack  = MODE4_BUF_ADR2;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4Exec(void)
{
	if(Mode4.isFlip == false)
	{
		return;
	}
	Mode4.isFlip = false;


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
IWRAM_CODE void Mode4DrawFill(u8 pal)
{
	s32 c ALIGN(4);

	c =(pal << 24) | (pal << 16) | (pal << 8) | pal;

	MemFixFast(&c, Mode4.pBack, MODE4_BUF_MAX_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4DrawParts(s32 sx, s32 sy, s32 cx, s32 cy, s32 vy, u16* pImg)
{
	// �͈͊O
	if(sy + cy < vy || vy + 160 < sy)
	{
		return;
	}


	s32 x, y;

	cx /= 2;
	sx /= 2;
	sy -= vy;

	for(y=0; y<cy; y++)
	{
		if(sy + y < 0 || sy + y > 160)
		{
			pImg += cx;

			continue;
		}

		for(x=0; x<cx; x++)
		{
			Mode4.pFront[(sy + y) * (SCREEN_CX/2) + (sx + x)] = *pImg++;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4DrawScroll(s32 y, u16* pImg)
{
	MemIncFast(pImg + (SCREEN_CX/2) * y, Mode4.pFront, MODE4_BUF_MAX_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4DrawScreen(u16* pImg)
{
//	LZ77UnCompVram(pImg, Mode4.pBack);
	swi_LZ77UnCompWrite16bit(pImg, Mode4.pBack);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4SetPal(u16* pPal)
{
	MemIncFast(pPal, BG_PALETTE, MODE4_BUF_PAL_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4SetCol(s32 i, s32 r, s32 g, s32 b)
{
	u16* p = BG_PALETTE + i;

	*p = RGB5(r, g, b);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode4SetFlip(void)
{
	Mode4.isFlip = true;
}
