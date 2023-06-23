#include "mode3.h"
#include "bios.h"


// DMA3

//---------------------------------------------------------------------------
ST_MODE3 Mode3 EWRAM_BSS;


//---------------------------------------------------------------------------
EWRAM_CODE void Mode3Init(void)
{
	BiosCpuSetFixClear(&Mode3, sizeof(ST_MODE3));

	REG_DISPCNT = (MODE_3 | BG2_ON);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3Exec(void)
{
	if(Mode3.isDraw == FALSE)
	{
		return;
	}
	Mode3.isDraw = FALSE;


	BiosCpuSetFast(Mode3.buf, (u16*)VRAM, MODE3_MAX_BUFFER_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawBg(u16* pImg)
{
	LZ77UnCompVram(pImg, Mode3.buf);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawScroll(u16* pImg1, u16* pImg2)
{
	LZ77UnCompVram(pImg1, Mode3.buf);
	LZ77UnCompVram(pImg2, Mode3.buf + SCREEN_CX * SCREEN_CY);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawCrop(u32 sx, u32 sy, u32 cx, u32 cy, u16* pImg)
{
	LZ77UnCompVram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);

	u16* pS = Mode3.buf + SCREEN_CX * SCREEN_CY;
	u16* pD = Mode3.buf + (sy * SCREEN_CX) + sx;
	u32  y;

	for(y=0; y<cy; y++)
	{
		BiosCpuSet(pS, pD, cx*2);

		pS += cx;
		pD += SCREEN_CX;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawClip(u32 sx, u32 sy, u32 cx, u32 cy, u32 gx, u32 gy, u32 gs, u16* pImg)
{
	LZ77UnCompVram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);

	u16* pS = Mode3.buf + SCREEN_CX * SCREEN_CY + (gy * cx) + gx;
	u16* pD = Mode3.buf + (sy * SCREEN_CX) + sx;
	u32  x, y;

	for(y=0; y<cy-gy; y++)
	{
		for(x=0; x<gs; x++)
		{
			*pD++ = *pS++;
		}

		pS += cx - gs;
		pD += SCREEN_CX - gs;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawBlend(u32 sx, u32 sy, u32 cx, u32 cy, u16* pImg, u8* pMsk)
{
	LZ77UnCompVram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);
	LZ77UnCompWram(pMsk, Mode3.msk);

	u16* pC = Mode3.buf + SCREEN_CX * SCREEN_CY;
	u8*  pM = Mode3.msk;
	u16* pV = Mode3.buf + sy * SCREEN_CX + sx;
	u32 x, y;

	for(y=sy; y<sy+cy; y++)
	{
		for(x=sx; x<sx+cx; x++)
		{
			if(*pM == 0x00)
			{
				// EMPTY
			}
			else if(*pM == 0x1f)
			{
				*pV = *pC;
			}
			else
			{
				u32 sR = (*pC & 0x001f);
				u32 sG = (*pC & 0x03e0);
				u32 sB = (*pC & 0x7c00);

				u32 dR = (*pV & 0x001f);
				u32 dG = (*pV & 0x03e0);
				u32 dB = (*pV & 0x7c00);

				u32 r = ((sR - dR) * *pM) / 32 + dR;
				u32 g = ((sG - dG) * *pM) / 32 + dG;
				u32 b = ((sB - dB) * *pM) / 32 + dB;

				*pV = (b & 0x7c00) | (g & 0x03e0) | (r & 0x001f);
			}

			pM++;
			pC++;
			pV++;
		}

		pV += SCREEN_CX - cx;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3Scroll(u32 cnt)
{
	BiosCpuSetFast(Mode3.buf + SCREEN_CX * cnt, (u16*)VRAM, MODE3_MAX_BUFFER_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3SetDraw(void)
{
	Mode3.isDraw = TRUE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawFill(u16 col)
{
	u32 c ALIGN(4);;

	c =((u32)col << 16) | (u32)col;

	BiosCpuSetFastFix(&c, Mode3.buf, MODE3_MAX_BUFFER_SIZE);

	Mode3.isDraw = TRUE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawLineH(s32 sx)
{
	u16* d = (u16*)VRAM + sx;
	s32  x, y;

	for(y=0; y<SCREEN_CY; y++)
	{
		for(x=0; x<SCREEN_CX/8; x++)
		{
			*d = RGB5(0, 0, 0);

			d += 8;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawCopyH(s32 sx)
{
	u16* s = Mode3.buf  + sx;
	u16* d = (u16*)VRAM + sx;
	s32  x, y;

	for(y=0; y<SCREEN_CY; y++)
	{
		for(x=0; x<SCREEN_CX/8; x++)
		{
			*d = *s;

			d += 8;
			s += 8;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawFadeMask(s32 step)
{
	const s32 sx[8] = { 0, 2, 1, 3, 1, 3, 0, 2 };
	const s32 sy[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };
	s32 x, y;

	for(y=0; y<SCREEN_CY; y+=4)
	{
		u16* s1 = Mode3.buf  + sx[step] + (y + sy[step]) * SCREEN_CX;
		u16* d1 = (u16*)VRAM + sx[step] + (y + sy[step]) * SCREEN_CX;

		u16* s2 = s1 + 2 + SCREEN_CX * 2;
		u16* d2 = d1 + 2 + SCREEN_CX * 2;

		for(x=0; x<SCREEN_CX; x+=4)
		{
			*d1 = *s1;
			s1 += 4;
			d1 += 4;

			*d2 = *s2;
			s2 += 4;
			d2 += 4;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawWipeTtoB(s32 step)
{
	const s32 a[8] = { 14, 12, 10, 8, 6, 4, 2, 0 };
	s32 y;

	u16 col ALIGN(4);
	col = RGB5(0, 0, 0);

	for(y=0; y<SCREEN_CY; y++)
	{
		if((a[Mod(y,8)]+Div(y,8)) == step)
		{
			DMA3COPY(col, (u16*)VRAM + y * SCREEN_CX, SCREEN_CX*2 | DMA_SRC_FIXED);
		}
	}
}
