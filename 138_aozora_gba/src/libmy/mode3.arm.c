#include "mode3.arm.h"
#include "../libbios/swi.h"
#include "mem.arm.h"

// 例外処理　VRAMに直接書いています（チラつき注意

//---------------------------------------------------------------------------
ST_MODE3 Mode3 EWRAM_BSS;


//---------------------------------------------------------------------------
void Mode3Init(void)
{
	MemClr(&Mode3, sizeof(ST_MODE3));


	Mode3VramCol(RGB5(31,31,31));

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_DISPCNT = MODE_3 | BG2_ON | OBJ_ON | OBJ_1D_MAP | WIN0_ON;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawBg(u16* pImg)
{
	SwiLZ77UnCompWrite16bit(pImg, Mode3.buf + Mode3.idx * MODE3_MAX_SCN_SIZE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawCol(u16 col)
{
	u32 src ALIGN(4) = (col << 16) | col;

	MemFixFast(&src, Mode3.buf + Mode3.idx * MODE3_MAX_SCN_SIZE, MODE3_MAX_SCN_SIZE*2);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawChr(s32 sx, s32 sy, s32 cx, s32 cy, u16* pImg, u8* pAlp)
{
	SwiLZ77UnCompWrite16bit(pImg, Mode3.chr);
	SwiLZ77UnCompWrite16bit(pAlp, Mode3.msk);


	u16* pDst = Mode3.buf + Mode3.idx * MODE3_MAX_SCN_SIZE + sy * 240 + sx;
	u16* pSrc = Mode3.chr;
	u8*  pMsk = Mode3.msk;
	s32  x, y;

	for(y=0; y<cy; y++)
	{
		for(x=0; x<cx; x++)
		{
			u32 msk = *pMsk++;
			u32 src = *pSrc++;

			if(msk == 0x00)
			{
				pDst++;

				continue;
			}

			if(msk == 0x1f)
			{
				*pDst++ = src;

				continue;
			}

			u32 dst = *pDst;

			u32 rbSrc = src & 0x7c1f;
			u32  gSrc = src & 0x03e0;
			u32 rbDst = dst & 0x7c1f;
			u32  gDst = dst & 0x03e0;

			rbDst += ((rbSrc - rbDst) * msk) >> 5;
			 gDst += (( gSrc  - gDst) * msk) >> 5;

			*pDst++ = (rbDst & 0x7c1f) | (gDst & 0x03e0);
		}

		pDst += (240 - cx);
	}
}
//---------------------------------------------------------------------------
// クリアアイコン専用
IWRAM_CODE void Mode3DrawIco(s32 sx, s32 sy, s32 cx, s32 cy, u32 bit, u16* pImg, u8* pAlp)
{
//	TRACE("[Mode3DrawIco %04X]\n", bit);

	SwiLZ77UnCompWrite16bit(pImg, Mode3.chr);
	SwiLZ77UnCompWrite16bit(pAlp, Mode3.msk);

	s32 a, b;

	for(a=0; a<2; a++)
	{
		for(b=0; b<5; b++)
		{
			u8 c = bit & 1;
			bit >>= 1;

			if(c == 0)
			{
				continue;
			}

			s32 tx = b * 40;
			s32 ty = a * 40;
			s32 x, y;

			u16* pDst = Mode3.buf + Mode3.idx * MODE3_MAX_SCN_SIZE + (sy+ty) * 240 + (sx+tx);
			u16* pSrc = Mode3.chr + ty * cx + tx;
			u8*  pMsk = Mode3.msk + ty * cx + tx;

			for(y=ty; y<ty+40; y++)
			{
				for(x=tx; x<tx+40; x++)
				{
					u32 msk = *pMsk++;
					u32 src = *pSrc++;

					if(msk == 0x00)
					{
						pDst++;

						continue;
					}

					if(msk == 0x1f)
					{
						*pDst++ = src;

						continue;
					}

					u32 dst = *pDst;

					u32 rbSrc = src & 0x7c1f;
					u32  gSrc = src & 0x03e0;
					u32 rbDst = dst & 0x7c1f;
					u32  gDst = dst & 0x03e0;

					rbDst += ((rbSrc - rbDst) * msk) >> 5;
					 gDst += (( gSrc  - gDst) * msk) >> 5;

					*pDst++ = (rbDst & 0x7c1f) | (gDst & 0x03e0);
				}

				pDst += (240 - 40);
				pMsk += (cx  - 40);
				pSrc += (cx  - 40);
			}
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramCol(u16 col)
{
	u32 src ALIGN(4) = (col << 16) | col;

	MemFixFast(&src, (u16*)VRAM, MODE3_MAX_SCN_SIZE*2);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramCopy(void)
{
	MemIncFast(Mode3.buf + Mode3.idx * MODE3_MAX_SCN_SIZE, (u16*)VRAM, MODE3_MAX_SCN_SIZE*2);
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3VramZiri(s32 cnt)
{
	_ASSERT(cnt < 8);

	u16* pSrc = Mode3.buf + Mode3.idx * MODE3_MAX_SCN_SIZE;
	u16* pVrm = (u16*)VRAM;

	s32 ofs[8];

	ofs[0] = (cnt + 0) & 7;		// y:0 (+0) 0 1 2 3 4 5 6 7
	ofs[1] = (cnt + 5) & 7;		// y:1 (+5) 5 6 7 0 1 2 3 4
	ofs[2] = (cnt + 2) & 7;		// y:2 (+2) 2 3 4 5 6 7 0 1
	ofs[3] = (cnt + 7) & 7;		// y:3 (+7) 7 0 1 2 3 4 5 6
	ofs[4] = (cnt + 4) & 7;		// y:4 (+4) 4 5 6 7 0 1 2 3
	ofs[5] = (cnt + 1) & 7;		// y:5 (+1) 1 2 3 4 5 6 7 0
	ofs[6] = (cnt + 6) & 7;		// y:6 (+6) 6 7 0 1 2 3 4 5
	ofs[7] = (cnt + 3) & 7;		// y:7 (+3) 3 4 5 6 7 0 1 2

	s32 x, y, i;

	for(y=0; y<160; y+=8)
	{
		for(i=0; i<8; i++)
		{
			x = ofs[i];

			u16* pSrcLine = pSrc + (y + i) * 240 + x;
			u16* pVrmLine = pVrm + (y + i) * 240 + x;

			while(x < 240)
			{
				*pVrmLine = *pSrcLine;

				pSrcLine += 8;
				pVrmLine += 8;

				x += 8;
			}
		}
	}
}
//---------------------------------------------------------------------------
// アルファブレンドの代用
IWRAM_CODE void Mode3VramAlpha(s32 cnt)
{
	_ASSERT(cnt < 8);

	static const s32 sx1[8] = { 0, 2, 1, 3, 1, 3, 0, 2 };
	static const s32 sy1[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };
	static const s32 sx2[8] = { 2, 0, 3, 1, 3, 1, 2, 0 };
	static const s32 sy2[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };

	s32 x1 = sx1[cnt];
	s32 y1 = sy1[cnt];
	s32 x2 = sx2[cnt];
	s32 y2 = sy2[cnt];

	u16* pSrc = Mode3.buf + Mode3.idx * MODE3_MAX_SCN_SIZE;
	u16* pVrm = (u16*)VRAM;
	s32 x, y;

	for(y=0; y<160; y+=4)
	{
		u16* s1 = pSrc + x1 + (y + y1) * 240;
		u16* d1 = pVrm + x1 + (y + y1) * 240;

		for(x=0; x<240; x+=4)
		{
			*d1 = *s1;

			s1 += 4;
			d1 += 4;
		}
	}

	for(y=2; y<160; y+=4)
	{
		u16* s1 = pSrc + x2 + (y + y2) * 240;
		u16* d1 = pVrm + x2 + (y + y2) * 240;

		for(x=0; x<240; x+=4)
		{
			*d1 = *s1;

			s1 += 4;
			d1 += 4;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3FlipBuf(void)
{
	Mode3.idx ^= 1;
}
