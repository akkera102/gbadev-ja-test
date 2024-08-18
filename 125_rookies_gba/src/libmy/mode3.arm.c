#include "mode3.arm.h"
#include "mem.h"
#include "../res.h"


// 例外処理　VRAMに直接書いています（チラつき注意

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


	MemIncFast(Mode3.buf, (u16*)VRAM, MODE3_MAX_GBA_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawScr(u16* pImg)
{
	// 上下10ドットは黒帯
	MemClear(Mode3.buf, SCREEN_CX * 10 * 2);
	MemClear(Mode3.buf + SCREEN_CX * 150, SCREEN_CX * 10 * 2);

	MemIncFast(pImg, Mode3.buf + SCREEN_CX * 10, MODE3_MAX_SCR_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawFill(u16 col)
{
	s32 c ALIGN(4);

	c =((s32)col << 16) | (s32)col;

	MemFixFast(&c, Mode3.buf, MODE3_MAX_GBA_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawBg(s32 cx, s32 cy, u16* pImg)
{
	if(cx == SCREEN_CX && cy == SCREEN_CY)
	{
		LZ77UnCompWram(pImg, Mode3.buf);

		return;
	}


	u32 size1 = SCREEN_CX * ((SCREEN_CY - cy) / 2) * 2;
	u32 size2 = cx * cy * 2;
	u32 size3 = size1 + size2;

	_ASSERT(cx == 240 && (cy == 124  || cy == 140));
	_ASSERT(size3 + size1 <= SCREEN_CX * SCREEN_CY * 2);

	MemClear(Mode3.buf, size1);
	LZ77UnCompWram(pImg, (u8*)Mode3.buf + size1);
	MemClear(Mode3.buf + size3 / 2, size1);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawChr(s32 sx, s32 sy, s32 cx, s32 cy, u16* pS, u8* pM)
{
	u16* pD = Mode3.buf + sy * SCREEN_CX + sx;
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
// 5.菱形エフェクト→表示
IWRAM_CODE void Mode3VramEff5(s32 step)
{
	if(step == 0)
	{
		MemInc((u16*)bg_effect6Bitmap, &Mode3.buf[SCREEN_CX * SCREEN_CY], bg_effect6BitmapLen);

		return;
	}

	step--;

	s32 sx, sy, y;

	for(sy=0; sy<SCREEN_CY; sy+=16)
	{
		for(sx=0; sx<SCREEN_CX; sx+=16)
		{
			for(y=0; y<16; y++)
			{
				u16* pM = (u16*)&Mode3.buf[SCREEN_CX * SCREEN_CY];
				u32* pS = (u32*)&pM[step * 16 + y * 128];

				u32* pD = (u32*)&Mode3.buf[sx + (sy + y) * SCREEN_CX];

				u16* pR = (u16*)VRAM;
				u32* pV = (u32*)&pR[sx + (sy + y) * SCREEN_CX];

				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;

				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
				*pV++ = *pD++ & *pS++;
			}
		}
	}
}
//---------------------------------------------------------------------------
// 6.菱形エフェクト→黒背景
IWRAM_CODE void Mode3VramEff6(s32 step)
{
	if(step == 0)
	{
		MemInc((u16*)bg_effect5Bitmap, &Mode3.buf[SCREEN_CX * SCREEN_CY], bg_effect5BitmapLen);
		Mode3DrawFill(RGB5(0, 0, 0));

		return;
	}

	step--;

	s32 sx, sy, y;

	for(sy=0; sy<SCREEN_CY; sy+=16)
	{
		for(sx=0; sx<SCREEN_CX; sx+=16)
		{
			for(y=0; y<16; y++)
			{
				u16* pM = (u16*)&Mode3.buf[SCREEN_CX * SCREEN_CY];
				u32* pS = (u32*)&pM[step * 16 + y * 128];

				u16* pR = (u16*)VRAM;
				u32* pV = (u32*)&pR[sx + (sy + y) * SCREEN_CX];

				*pV++ &= *pS++;
				*pV++ &= *pS++;
				*pV++ &= *pS++;
				*pV++ &= *pS++;

				*pV++ &= *pS++;
				*pV++ &= *pS++;
				*pV++ &= *pS++;
				*pV++ &= *pS++;
			}
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramScrY(u16* pImg, s32 y)
{
	MemIncFast(pImg + SCREEN_CX * y, (u16*)VRAM + SCREEN_CX * 10, MODE3_MAX_SCR_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3SetDraw(void)
{
	Mode3.isDraw = true;
}
