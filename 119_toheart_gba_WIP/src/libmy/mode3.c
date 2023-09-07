#include "mode3.h"
#include "mem.h"
#include "../res.h"

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


	MemInc(Mode3.buf, (u16*)VRAM, MODE3_MAX_BUF_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawBg(u16* pImg)
{
	LZ77UnCompWram(pImg, Mode3.buf);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawScroll(u16* pImg1, u16* pImg2)
{
	LZ77UnCompWram(pImg1, Mode3.buf);
	LZ77UnCompWram(pImg2, Mode3.buf + SCREEN_CX * SCREEN_CY);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawCrop(u32 sx, u32 sy, u32 cx, u32 cy, u16* pImg)
{
	LZ77UnCompWram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);

	u16* pS = Mode3.buf + SCREEN_CX * SCREEN_CY;
	u16* pD = Mode3.buf + (sy * SCREEN_CX) + sx;
	u32  y;

	for(y=0; y<cy; y++)
	{
		MemInc(pS, pD, cx*2);

		pS += cx;
		pD += SCREEN_CX;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawClip(u32 sx, u32 sy, u32 cx, u32 cy, u32 gx, u32 gy, u32 gs, u16* pImg)
{
	LZ77UnCompWram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);

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
	LZ77UnCompWram(pImg, Mode3.buf + SCREEN_CX * SCREEN_CY);
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
	MemInc(Mode3.buf + SCREEN_CX * cnt, (u16*)VRAM, MODE3_MAX_BUF_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3SetDraw(void)
{
	Mode3.isDraw = true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawFill(u16 col)
{
	u32 c ALIGN(4);

	c =((u32)col << 16) | (u32)col;

	MemFix(&c, Mode3.buf, MODE3_MAX_BUF_SIZE);

	Mode3.isDraw = true;
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
	const s32 sx1[8] = { 0, 2, 1, 3, 1, 3, 0, 2 };
	const s32 sy1[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };

	s32 x, y;

	for(y=0; y<SCREEN_CY; y+=4)
	{
		u16* s1 = Mode3.buf  + sx1[step] + (y + sy1[step]) * SCREEN_CX;
		u16* d1 = (u16*)VRAM + sx1[step] + (y + sy1[step]) * SCREEN_CX;

		for(x=0; x<SCREEN_CX; x+=4)
		{
			*d1 = *s1;
			s1 += 4;
			d1 += 4;
		}
	}

	const s32 sx2[8] = { 2, 0, 3, 1, 3, 1, 2, 0 };
	const s32 sy2[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };

	for(y=2; y<SCREEN_CY; y+=4)
	{
		u16* s1 = Mode3.buf  + sx2[step] + (y + sy2[step]) * SCREEN_CX;
		u16* d1 = (u16*)VRAM + sx2[step] + (y + sy2[step]) * SCREEN_CX;

		for(x=0; x<SCREEN_CX; x+=4)
		{
			*d1 = *s1;
			s1 += 4;
			d1 += 4;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawWipeTtoB(s32 step)
{
	const s32 a[8] = { 14, 12, 10, 8, 6, 4, 2, 0 };
	s32 y;

	u32 col ALIGN(4);
	col = (RGB5(0, 0, 0) << 16) | RGB5(0, 0, 0);

	for(y=0; y<SCREEN_CY; y++)
	{
		if((a[DivMod(y,8)]+Div(y,8)) == step)
		{
			MemFix(&col, (u16*)VRAM + y * SCREEN_CX, SCREEN_CX*2);
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawTitle(s32 step)
{
	// 上
	MemInc((u16*)&bg_logoBitmap[240*8*6 - 240*step], (u16*)VRAM, 240*8*2 + 240*2*step);
	// 下
	MemInc((u16*)&bg_logoBitmap[240*8*13], (u16*)(VRAM + (240*160*2) - (240*8*2) - (240*2*step)), 240*8*2 + 240*2*step);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawVibrate(s32 step)
{
	if(step == 0)
	{
		MemInc(&Mode3.buf, &Mode3.buf[SCREEN_CX * SCREEN_CY], MODE3_MAX_BUF_SIZE);

		return;
	}

	step--;

	// バッファを黒色で塗りつぶし
	u32 col ALIGN(4);
	col = 0;

	MemFix(&col, Mode3.buf, MODE3_MAX_BUF_SIZE);

	// 揺れ
	// 左下、右上、左上、右下、左下、左上、元ポジション
	_ASSERT(step < 7);

	const s32 sx[7] = { -8,  8, -8,  8, -8, -8,  0 };
	const s32 sy[7] = {  8, -8, -8,  8,  8, -8,  0 };
	s32 x, y;

	for(y=0; y<SCREEN_CY; y++)
	{
		for(x=0; x<SCREEN_CX; x++)
		{
			s32 dx = x - sx[step];
			s32 dy = y - sy[step];

			if(dx >= 0 && dy >= 0 && dx < SCREEN_CX && dy < SCREEN_CY)
			{
				Mode3.buf[x + y * SCREEN_CX] = Mode3.buf[dx + dy * SCREEN_CX + (SCREEN_CX * SCREEN_CY)];
			}
		}
	}

	Mode3.isDraw = true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawScaling(s32 step)
{
	REG_BG2PA =  0x100 - step;
	REG_BG2PB =  0;
	REG_BG2PC =  0;
	REG_BG2PD =  0x100 - step;

	if(step == 0)
	{
		REG_BG2X = 0;
		REG_BG2Y = 0;

		return;
	}

	REG_BG2X = 120 * step;
	REG_BG2Y =  80 * step;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawCurtain(s32 step)
{
	if(step == 0)
	{
		MemInc((u16*)bg_effect5_1Bitmap, &Mode3.buf[SCREEN_CX * SCREEN_CY], bg_effect5_1BitmapLen);

		return;
	}

	step--;

	s32 y;
	s32 sx = step * 8;
	s32 pat = 7;

	while(0 <= sx)
	{
		if(sx < SCREEN_CX)
		{
			for(y=0; y<SCREEN_CY; y++)
			{
				u16* pM = (u16*)&Mode3.buf[SCREEN_CX * SCREEN_CY];
				u32* pS = (u32*)&pM[pat * 8 + y * 64];
				u32* pD = (u32*)&Mode3.buf[sx + y * SCREEN_CX];

				*pD++ &= *pS++;
				*pD++ &= *pS++;
				*pD++ &= *pS++;
				*pD++ &= *pS++;
			}
		}

		if(pat > 0)
		{
			pat--;
		}

		sx -= 8;
	}

	Mode3.isDraw = true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawCurtain2(s32 step)
{
	if(step == 0)
	{
		MemInc((u16*)bg_effect5_2Bitmap, &Mode3.buf[SCREEN_CX * SCREEN_CY], bg_effect5_2BitmapLen);

		return;
	}

	step--;

	s32 y;
	s32 sx = step * 8;
	s32 pat = 7;

	while(0 <= sx)
	{
		if(sx < SCREEN_CX)
		{
			for(y=0; y<SCREEN_CY; y++)
			{
				u16* pM = (u16*)&Mode3.buf[SCREEN_CX * SCREEN_CY];
				u32* pS = (u32*)&pM[pat * 8 + y * 64];

				u32* pD = (u32*)&Mode3.buf[sx + y * SCREEN_CX];

				u16* pR = (u16*)VRAM;
				u32* pV = (u32*)&pR[sx + y * SCREEN_CX];

				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;

//				_ASSERT(pV <= VRAM + SCREEN_CX * SCREEN_CY * 2);
			}
		}

		if(pat > 0)
		{
			pat--;
		}

		sx -= 8;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawDiamond(s32 step)
{
	if(step == 0)
	{
		MemInc((u16*)bg_effect4_1Bitmap, &Mode3.buf[SCREEN_CX * SCREEN_CY], bg_effect4_1BitmapLen);

		return;
	}

	step--;

	s32 y;
	s32 sx = step * 16;
	s32 pat = 7;

	while(0 <= sx)
	{
		if(sx < SCREEN_CX)
		{
			for(y=0; y<SCREEN_CY; y++)
			{
				u16* pM = (u16*)&Mode3.buf[SCREEN_CX * SCREEN_CY];
				u32* pS = (u32*)&pM[pat * 16 + y * 128];
				u32* pD = (u32*)&Mode3.buf[sx + y * SCREEN_CX];

				*pD++ &= *pS++;
				*pD++ &= *pS++;
				*pD++ &= *pS++;
				*pD++ &= *pS++;

				*pD++ &= *pS++;
				*pD++ &= *pS++;
				*pD++ &= *pS++;
				*pD++ &= *pS++;
			}
		}

		if(pat > 0)
		{
			pat--;
		}

		sx -= 16;
	}

	Mode3.isDraw = true;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawDiamond2(s32 step)
{
	if(step == 0)
	{
		MemInc((u16*)bg_effect4_2Bitmap, &Mode3.buf[SCREEN_CX * SCREEN_CY], bg_effect4_2BitmapLen);

		return;
	}

	step--;

	s32 y;
	s32 sx = step * 16;
	s32 pat = 7;

	while(0 <= sx)
	{
		if(sx < SCREEN_CX)
		{
			for(y=0; y<SCREEN_CY; y++)
			{
				u16* pM = (u16*)&Mode3.buf[SCREEN_CX * SCREEN_CY];
				u32* pS = (u32*)&pM[pat * 16 + y * 128];

				u32* pD = (u32*)&Mode3.buf[sx + y * SCREEN_CX];

				u16* pR = (u16*)VRAM;
				u32* pV = (u32*)&pR[sx + y * SCREEN_CX];

				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;

				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;

//				_ASSERT(pV <= VRAM + SCREEN_CX * SCREEN_CY * 2);
			}
		}

		if(pat > 0)
		{
			pat--;
		}

		sx -= 16;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawTopScroll(s32 step)
{
	if(step == 0)
	{
		MemClear(&Mode3.buf[SCREEN_CX * SCREEN_CY], SCREEN_CX * SCREEN_CY * 2);

		return;
	}

	step--;

	MemInc((u16*)&Mode3.buf[SCREEN_CX * step], (u16*)VRAM, SCREEN_CX * SCREEN_CY * 2);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawSlide(s32 step)
{
	REG_BG2PA =  0x100;
	REG_BG2PB =  0;
	REG_BG2PC =  0;
	REG_BG2PD =  0x100 + step * 10;

	REG_BG2X =  0;
	REG_BG2Y =  -80 * step * 10;
}
