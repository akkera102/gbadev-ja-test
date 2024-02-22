#include "mode3.h"
#include "mem.h"
#include "../res.h"

// VRAMÇ…íºê⁄èëÇ¢ÇƒÇ¢Ç‹Ç∑ÅiÉ`ÉâÇ¬Ç´íçà”

//---------------------------------------------------------------------------
ST_MODE3 Mode3 EWRAM_BSS;


//---------------------------------------------------------------------------
EWRAM_CODE void Mode3Init(void)
{
	MemClear(&Mode3, sizeof(ST_MODE3));
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3Exec(void)
{
	if(Mode3.isDraw == false)
	{
		return;
	}
	Mode3.isDraw = false;


	MemIncFast(Mode3.buf, (u16*)VRAM, MODE3_MAX_BUF_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawFull(u16* pImg)
{
	LZ77UnCompWram(pImg, Mode3.buf);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawFull2(u16* pImg)
{
	MemIncFast(pImg, Mode3.buf, MODE3_MAX_BUF_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawCrop(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg)
{
	LZ77UnCompWram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);

	u16* pS = Mode3.buf + SCREEN_CX * SCREEN_CY;
	u16* pD = Mode3.buf + (sy * SCREEN_CX) + sx;
	s32  y;

	for(y=0; y<cy; y++)
	{
		MemInc(pS, pD, cx*2);

		pS += cx;
		pD += SCREEN_CX;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawClip(s32 sx, s32 sy, s32 cx, s32 cy, s32 gx, s32 gy, s32 gs, u16* pImg)
{
	LZ77UnCompWram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);

	u16* pS = Mode3.buf + SCREEN_CX * SCREEN_CY + (gy * cx) + gx;
	u16* pD = Mode3.buf + (sy * SCREEN_CX) + sx;
	s32  x, y;

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
IWRAM_CODE void Mode3DrawFill(u16 col)
{
	s32 c ALIGN(4);

	c =((s32)col << 16) | (s32)col;

	MemFixFast(&c, Mode3.buf, MODE3_MAX_BUF_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawBlend(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg, u8* pMsk)
{
	LZ77UnCompWram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);
	LZ77UnCompWram(pMsk, Mode3.msk);


	u16* pS = Mode3.buf + SCREEN_CX * SCREEN_CY;
	u16* pD = Mode3.buf + sy * SCREEN_CX + sx;
	u8*  pM = Mode3.msk;
	s32 x, y;

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
				*pD = *pS;
			}
			else
			{
				u32 rb = *pD & 0x7c1f;
				u32 g  = *pD & 0x03e0;
				rb    += (((*pS & 0x7c1f) - rb) * *pM) >> 5;
				g     += (((*pS & 0x03e0) - g ) * *pM) >> 5;
				*pD    = (rb & 0x7c1f) | (g & 0x03e0);
/*
				s32 sR = (*pS & 0x001f);
				s32 sG = (*pS & 0x03e0);
				s32 sB = (*pS & 0x7c00);

				s32 dR = (*pD & 0x001f);
				s32 dG = (*pD & 0x03e0);
				s32 dB = (*pD & 0x7c00);

				s32 r = ((sR - dR) * *pM) / 32 + dR;
				s32 g = ((sG - dG) * *pM) / 32 + dG;
				s32 b = ((sB - dB) * *pM) / 32 + dB;

				*pD = (b & 0x7c00) | (g & 0x03e0) | (r & 0x001f);
*/
			}

			pM++;
			pS++;
			pD++;
		}

		pD += SCREEN_CX - cx;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawPat(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg)
{
	u16* pS = pImg;
	u16* pD = Mode3.buf + (sy * SCREEN_CX) + sx;
	s32  y;

	for(y=0; y<cy; y++)
	{
		MemInc(pS, pD, cx*2);

		pS += cx;
		pD += SCREEN_CX;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramFull(u16* pImg)
{
	LZ77UnCompWram(pImg, (u16*)VRAM);
}
//---------------------------------------------------------------------------
// VRAM <- Mode3.buf
IWRAM_CODE void Mode3VramCrop(s32 sx, s32 sy, s32 cx, s32 cy, s32 ex, s32 ey)
{
	s32 x, y;

	for(y=0; y<cy; y++)
	{
		for(x=0; x<cx; x++)
		{
			((u16*)VRAM)[(ey + y) * SCREEN_CX + (ex + x)] = Mode3.buf[(sy + y) * SCREEN_CX + (sx + x)];
		}
	}
}
//---------------------------------------------------------------------------
// VRAM <- VRAM
IWRAM_CODE void Mode3VramCrop2(s32 sx, s32 sy, s32 cx, s32 cy, s32 ex, s32 ey)
{
	s32 x, y;

	for(y=0; y<cy; y++)
	{
		for(x=0; x<cx; x++)
		{
			((u16*)VRAM)[(ey + y) * SCREEN_CX + (ex + x)] = ((u16*)VRAM)[(sy + y) * SCREEN_CX + (sx + x)];
		}
	}
}
//---------------------------------------------------------------------------
// VRAM <- VRAM x minus dir
IWRAM_CODE void Mode3VramCrop2b(s32 sx, s32 sy, s32 cx, s32 cy, s32 ex, s32 ey)
{
	s32 x, y;

	for(y=0; y<cy; y++)
	{
		for(x=cx-1; x>=0; x--)
		{
			((u16*)VRAM)[(ey + y) * SCREEN_CX + (ex + x)] = ((u16*)VRAM)[(sy + y) * SCREEN_CX + (sx + x)];
		}
	}
}
//---------------------------------------------------------------------------
// VRAM <- Img
IWRAM_CODE void Mode3VramCrop3(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg)
{
	LZ77UnCompWram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);

	u16* pS = Mode3.buf + SCREEN_CX * SCREEN_CY;
	u16* pD = ((u16*)VRAM) + (sy * SCREEN_CX) + sx;
	s32  y;

	for(y=0; y<cy; y++)
	{
		MemInc(pS, pD, cx*2);

		pS += cx;
		pD += SCREEN_CX;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramBlendCopy(s32 sx, s32 sy, s32 cx, s32 cy, u8 msk)
{
	u16* pS = Mode3.buf + sy * SCREEN_CX + sx;
	u16* pD = (u16*)VRAM + sy * SCREEN_CX + sx;
	s32 x, y;

	for(y=sy; y<sy+cy; y++)
	{
		for(x=sx; x<sx+cx; x++)
		{
			if(msk == 0x00)
			{
				// EMPTY
			}
			else if(msk == 0x1f)
			{
				*pD = *pS;
			}
			else
			{
				u32 rb = *pD & 0x7c1f;
				u32 g  = *pD & 0x03e0;
				rb    += (((*pS & 0x7c1f) - rb) * msk) >> 5;
				g     += (((*pS & 0x03e0) - g ) * msk) >> 5;
				*pD    = (rb & 0x7c1f) | (g & 0x03e0);
			}

			pS++;
			pD++;
		}

		pS += SCREEN_CX - cx;
		pD += SCREEN_CX - cx;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramLine(s32 sy, u16 col)
{
	s32 x;

	for(x=0; x<SCREEN_CX; x++)
	{
		((u16*)VRAM)[sy * SCREEN_CX + x] = col;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramCopy(s32 sx, s32 sy, s32 ex, s32 ey)
{
	_ASSERT(sx < SCREEN_CX);
	_ASSERT(sy < SCREEN_CY);

	s32 x, y;

	for(y=sy; y<ey; y++)
	{
		for(x=sx; x<ex; x++)
		{
			((u16*)VRAM)[(y * SCREEN_CX) + x] = Mode3.buf[(y * SCREEN_CX) + x];
		}
	}

	_ASSERT(ex <= SCREEN_CX);
	_ASSERT(ey <= SCREEN_CY);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramScroll(u16* pImg, s32 y)
{
	MemIncFast(pImg + SCREEN_CX * y, (u16*)VRAM, MODE3_MAX_BUF_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3SetDraw(void)
{
	Mode3.isDraw = true;
}
