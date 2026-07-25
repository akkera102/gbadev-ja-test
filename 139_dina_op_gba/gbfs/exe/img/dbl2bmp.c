// gcc dbl2bmp.c -s -o dbl2bmp

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//---------------------------------------------------------------------------
#define BMP_WIDTH  320
#define BMP_HEIGHT 224


//---------------------------------------------------------------------------
typedef unsigned char			 u8;
typedef char					 s8;
typedef unsigned short			u16;
typedef short					s16;
typedef unsigned int			u32;
typedef int						s32;

typedef struct {
	u8* p;
	s32 size;
	s32 pos;

} ST_BIT;

typedef struct {
	s32 tWidth;
	s32 tHeight;
	u16 map[64 * 64];

	s32 pri;

} ST_FRAME;

typedef struct {
	s32  tWidth;
	s32  tHeight;
	u16  map[64 * 64];

	bool isClr;
	s32  scrX;
	s32  scrY;
	s32  blend;

} ST_BG;

typedef struct {
	s32  tWidth;
	s32  tHeight;
	u16  map[64 * 64];

	bool isClr;
	s32  scrX;
	s32  scrY;
	s32  blend;
	s32  pri;
	s32  x;
	s32  y;

} ST_SPRITE;

typedef struct {
	u16 base[256];
	u16 work[256];

} ST_PAL;

typedef struct {
	s32 recCnt;
	s32 fileCnt;
	s32 frameCnt;

	s32 decCnt;
	u8  dec[64 * 64 * 64];
	u8  tile[0x4000 * 64];

	ST_FRAME  f[17];
	ST_BG     b[3];
	ST_SPRITE s[8];
	ST_PAL    p[4];

} ST_VRAM;

//---------------------------------------------------------------------------
ST_BIT  Bit;
ST_VRAM Vram;


//---------------------------------------------------------------------------
void BitCalloc(char* fname);
void BitFree(void);
void BitSeek(s32 pos);
u8   BitGet8(void);
u16  BitGet16(void);
u32  BitGet32(void);
s32  BitGetPos(void);
s32  BitGetSize(void);
u8*  BitGetPointer(void);
u16  BitCur16(void);

void BmpWrite8(FILE* fp, u8 h);
void BmpWrite16(FILE* fp, u16 h);
void BmpWrite32(FILE* fp, u32 h);
void BmpSave(char* fname, u16* frame);

void CutInit(void);
void CutExec(void);
void CutExecCmd1(void);
void CutExecCmd2(void);
void CutExecCmd3(void);
void CutExecCmd4(void);
void CutExecCmd5(void);
void CutExecCmd6(void);
void CutExecCmd7(void);
void CutExecCmd8(void);
void CutUpdate(s32 wait);

void CutDecMap(u8* in, u16* out);
u8*  CutDecTile(u8* in, u8* out);

s32  CutPalClip(s32 val);
void CutPalBias(s32 msk, s32 b, s32 g, s32 r);
void CutPalFade(u32 msk, s32 level);

//---------------------------------------------------------------------------
void BitCalloc(char* fname)
{
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't find file \"%s\"\n", fname);

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Bit.size = ftell(fp);

	Bit.p = (u8*)calloc(Bit.size, sizeof(u8));

	if(Bit.p == NULL)
	{
		fprintf(stderr, "calloc error\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Bit.p, 1, Bit.size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void BitFree(void)
{
	free(Bit.p);
}
//---------------------------------------------------------------------------
void BitSeek(s32 pos)
{
	Bit.pos = pos;
}
//---------------------------------------------------------------------------
u8 BitGet8(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p[Bit.pos++];
}
//---------------------------------------------------------------------------
u16 BitGet16(void)
{
	u16 b1 = BitGet8() << 8;
	u16 b2 = BitGet8();

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 BitGet32(void)
{
	u32 b1 = BitGet8() << 24;
	u32 b2 = BitGet8() << 16;
	u32 b3 = BitGet8() <<  8;
	u32 b4 = BitGet8();

	return b4 | b3 | b2 | b1;
}
//---------------------------------------------------------------------------
s32 BitGetPos(void)
{
	return Bit.pos;
}
//---------------------------------------------------------------------------
s32 BitGetSize(void)
{
	return Bit.size;
}
//---------------------------------------------------------------------------
u8* BitGetPointer(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p + Bit.pos;
}
//---------------------------------------------------------------------------
u16 BitCur16(void)
{
	u16 b1 = Bit.p[Bit.pos + 0] << 8;
	u16 b2 = Bit.p[Bit.pos + 1];

	return b2 | b1;
}
//---------------------------------------------------------------------------
void BmpWrite8(FILE* fp, u8 h)
{
	u8 buf[1];

	buf[0] = h;

	fwrite(buf, 1, 1, fp);
}
//---------------------------------------------------------------------------
void BmpWrite16(FILE* fp, u16 h)
{
	u8 buf[2];

	buf[0] = (h >> 0) & 0xFF;
	buf[1] = (h >> 8) & 0xFF;

	fwrite(buf, 2, 1, fp);
}
//---------------------------------------------------------------------------
void BmpWrite32(FILE* fp, u32 h)
{
	u8 buf[4];

	buf[0] = (h >>  0) & 0xFF;
	buf[1] = (h >>  8) & 0xFF;
	buf[2] = (h >> 16) & 0xFF;
	buf[3] = (h >> 24) & 0xFF;

	fwrite(buf, 4, 1, fp);
}
//---------------------------------------------------------------------------
void BmpSave(char* fname, u16* frame)
{
	FILE *fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		printf("couldn't open file\n");

		exit(1);
	}

	s32 offset   = 14 + 40;							// BITMAPFILEHEADER + BITMAPINFOHEADER
	s32 stride   = (BMP_WIDTH * 3 + 3) & ~3;
	s32 dataSize = stride * BMP_HEIGHT;
	s32 fileSize = offset + dataSize;

	// BITMAPFILEHEADER
	BmpWrite8(fp, 'B');
	BmpWrite8(fp, 'M');
	BmpWrite32(fp, fileSize);
	BmpWrite16(fp, 0);
	BmpWrite16(fp, 0);
	BmpWrite32(fp, offset);

	// BITMAPINFOHEADER
	BmpWrite32(fp, 40);
	BmpWrite32(fp, BMP_WIDTH);
	BmpWrite32(fp, BMP_HEIGHT);
	BmpWrite16(fp, 1);
	BmpWrite16(fp, 24);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, dataSize);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);

	// DATA
	u8 pad[3*3] = {0};

	for(s32 y=BMP_HEIGHT-1; y>=0; y--)
	{
		for(s32 x=0; x<BMP_WIDTH; x++)
		{
			u16 color = frame[y * BMP_WIDTH + x]; 

			u8 b = ( color >> 10) & 0x1F;
			u8 g = ( color >>  5) & 0x1F;
			u8 r = ( color      ) & 0x1F;

			u8 b8 = (b << 3) | (b >> 2);
			u8 g8 = (g << 3) | (g >> 2);
			u8 r8 = (r << 3) | (r >> 2);

			BmpWrite8(fp, b8);
			BmpWrite8(fp, g8);
			BmpWrite8(fp, r8);
		}

		if(stride > BMP_WIDTH * 3)
		{
			fwrite(pad, 1, stride - BMP_WIDTH * 3, fp);
		}
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
void CutInit(void)
{
	memset(&Vram, 0x00, sizeof(ST_VRAM));

	s32 i;

	for(i=0; i<3; i++)
	{
		Vram.b[i].isClr = true;
	}

	for(i=0; i<8; i++)
	{
		Vram.s[i].pri   = -1;
		Vram.s[i].isClr = true;
	}
}
//---------------------------------------------------------------------------
void CutExec(void)
{
	// "ACUT"
	if(BitGet32() != 0x41435554)
	{
		return;
	}

	for(;;)
	{
		s32 cmd = BitGet16();
		s32 len = BitGet32();
		s32 pos = BitGetPos() + len;

//		printf("\nACUT cmd:%d len:%d pos:0x%06X\n", cmd, len, pos - len - 6);
		printf("\n");

		switch(cmd)
		{
		case 0x0:
			return;

		case 0x1:
			CutExecCmd1();
			break;

		case 0x2:
			CutExecCmd2();
			break;

		case 0x3:
			CutExecCmd3();
			break;

		case 0x4:
			CutExecCmd4();
			break;

		case 0x5:
			CutExecCmd5();
			break;

		case 0x6:
			CutExecCmd6();
			break;

		case 0x7:
			CutExecCmd7();
			break;

		case 0x8:
			CutExecCmd8();
			break;

		default:
			printf("CutExec cmd:%d\n", cmd);
			exit(1);
		}

		BitSeek(pos);
	}
}
//---------------------------------------------------------------------------
// DIRECTIVE
void CutExecCmd1(void)
{
	s32 i, f, n, x, y, m, b, s, g, r;

	for(;;)
	{
		s32 cmd = BitGet16();

		// printf("DIR 0x%X ", cmd & 0xF);

		switch(cmd)
		{
		// 終了
		case 0x4000:
			printf("END\n");
			return;

		// 画面更新
		case 0x4001:
		case 0x400c:
			n = BitGet16();			// wait

			printf("UPDATE n:%d\n", n);

			CutUpdate(n);
			break;

		// スクリーンクリア
		case 0x4002:
			n = BitGet16();			// 1-3（0はなし）
			assert(n < 4);

			printf("CLR n:%d\n", n);

			if(n < 3)
			{
				Vram.b[n].isClr = true;
			}
			else
			{
				for(i=0; i<8; i++)
				{
					Vram.s[i].isClr = true;
					Vram.s[i].pri   = -1;
				}
			}
			break;

		case 0x4003:
			printf("EMPTY\n");
			// EMPTY
			break;

		// BGのフレーム設定
		case 0x4004:
			f = BitGet16();			// 0-15（フレーム）
			b = BitGet16();			// 0-2（BG）

			assert(f < 16);
			assert(b <  3);

			printf("BGFRE f:%d b:%d\n", f, b);

			memcpy(Vram.b[b].map, Vram.f[f].map, sizeof(Vram.b[b].map));

			Vram.b[b].tWidth  = Vram.f[f].tWidth;
			Vram.b[b].tHeight = Vram.f[f].tHeight;
			Vram.b[b].isClr   = false;
			break;

		// スクロール設定
		case 0x4005:
			n = BitGet16();			// 0-6（0-2:BG, 3-:SPRITE）
			x = BitGet16();
			y = BitGet16();

			assert(n < 11);

			printf("SCR n:%d x:%d y:%d\n", n, x, y);

			if(n < 3)
			{
				Vram.b[n].scrX = x & 0xF;
				Vram.b[n].scrY = y & 0xF;
			}
			else
			{
				n -= 3;

				Vram.s[n].scrX = x & 0xF;
				Vram.s[n].scrY = y & 0xF;
			}
			break;

		// 半透明の設定
		case 0x4006:
			m = BitGet16();			// 0x1, 0x2, 0x4, 0x8, 0x1ff（レイヤーマスク 0-2:BG, 3-:SPRITE）
			n = BitGet16();			// 0-31（透明度）

			printf("BLD m:0x%x n:%d\n", m, n);

			for(i=0; i<16; i++, m >>= 1)
			{
				if((m & 1) == 0)
				{
					continue;
				}

				if(i < 3)
				{
					Vram.b[i].blend = n;
				}
				else if(i < 11)
				{
					Vram.s[i - 3].blend = n;
				}
			}
			break;

		// パレット輝度設定
		case 0x4007:
			m = BitGet16();			// 0x2, 0x4, 0x18（レイヤーマスク 0-2:BG, 3-:SPRITE）
			n = BitGet16();			// 31, 15（輝度）
			b = n - 0x1F;			// 0, -16（bias）

			printf("BIAS m:0x%x n:0x%x b:%d\n", m, n, b);

			CutPalBias(m, b, b, b);

			if(n == 0x1F)
			{
				for(i=0; i<16; i++, m >>= 1)
				{
					if((m & 1) == 0)
					{
						continue;
					}

					if(i < 3)
					{
						Vram.b[i].blend = 0x3F;
					}
					else if(i < 11)
					{
						Vram.s[i - 3].blend = 0x3F;
					}
				}
			}
			else
			{
				for(i=0; i<16; i++, m >>= 1)
				{
					if((m & 1) == 0)
					{
						continue;
					}

					if(i < 3)
					{
						Vram.b[i].blend = n + 0x20;
					}
					else
					{
						Vram.s[i - 3].blend = n + 0x20;
					}
				}
			}
			break;

		// スプライト設定
		case 0x4008:
			f = BitGet16();			// 0-15, 0x8000（フレーム）
			s = BitGet16();			// 0-2（スプライト）
			x = BitGet16();
			y = BitGet16();

			assert(f < 16 || f == 0x8000);
			assert(s <  8);

			printf("SPRITE f:%d s:%d x:%d y:%d\n", f, s, x, y);

			if(f == 0x8000)
			{
				Vram.s[s].isClr = true;
			}
			else
			{
				memcpy(Vram.s[s].map, Vram.f[f].map, sizeof(Vram.s[s].map));

				Vram.s[s].x       = x * 8;
				Vram.s[s].y       = y * 8;
				Vram.s[s].tWidth  = Vram.f[f].tWidth;
				Vram.s[s].tHeight = Vram.f[f].tHeight;
				Vram.s[s].pri     = Vram.f[f].pri;
				Vram.s[s].isClr   = false;
			}
			break;

		// カラー補正（未使用の為、処理が正しいか不明）
		case 0x4009:
			m = BitGet16();
			b = BitGet16();
			g = BitGet16();
			r = BitGet16();

			printf("COL m:0x%x b:%d g:%d r:%d\n", m, b, g, r);

			CutPalBias(m, b, g, r);
			break;

		// フェード
		case 0x400a:
			m = BitGet16();			// 0x7のみ（レイヤーマスク 0-2:BG）
			n = (s16)BitGet16();	// -255～0のみ（フェード値）

			printf("FADE m:0x%x n:%d\n", m, n);

			CutPalFade(m, n);
			break;

		// 不明
		case 0x400b:
			n = BitGet16();

			printf("UNK %d\n", n);

			switch(n)
			{
			case 0x0001:
				BitGet16();
				BitGet16();
				break;

			case 0x0002:
				BitGet16();
				break;

			case 0x0003:
				BitGet16();
				BitGet16();
				BitGet16();
				break;

			default:
				printf("CutExecCmd1 0x400b %x\n", n);
				break;
			}
			break;

		default:
			printf("CutExecCmd1 %x\n", cmd);
			break;
		}
	}
}
//---------------------------------------------------------------------------
// TILE DEC
void CutExecCmd2(void)
{
	s32 tMax = BitGet16();		// タイル個数

	assert(tMax < 64 * 64);

	printf("TILE_DEC tMax:%d\n", tMax);

	CutDecTile(BitGetPointer(), Vram.dec);
	Vram.decCnt = 0;
}
//---------------------------------------------------------------------------
// TILE COPY
void CutExecCmd3(void)
{
	while(BitCur16() != 0x8000)
	{
		s32 dat = BitGet16();
		s32 idx = (dat & 0x3FFF);
		s32 cnt = (dat & 0x4000) ? BitGet16() : 1;

		idx *= 64;
		cnt *= 64;

		assert(idx + cnt   < sizeof(Vram.tile));
		assert(Vram.decCnt < sizeof(Vram.dec));

		printf("TILE_COPY adr:0x%x size:0x%x\n", idx, cnt);

		memcpy(Vram.tile + idx, Vram.dec + Vram.decCnt, cnt);
		Vram.decCnt += cnt;
	}
}
//---------------------------------------------------------------------------
// MAP DEC(BG)
void CutExecCmd4(void)
{
	s32 f  = BitGet16();	// 0-15
	s32 n  = BitGet16();	// 0, 1, 2（BG index & priority）
	s32 tw = BitGet16();
	s32 th = BitGet16();

	assert(f < 16);
	assert(n == 0 || n == 1 || n == 2);

	printf("MAP_DEC(BG) f:%d n:%d tw:%d th:%d\n", f, n, tw, th);

	CutDecMap(BitGetPointer(), Vram.f[f].map);
	Vram.f[f].tWidth  = tw;
	Vram.f[f].tHeight = th;
	Vram.f[f].pri     = n;

	memcpy(Vram.b[n].map, Vram.f[f].map, sizeof(Vram.b[n].map));
	Vram.b[n].tWidth  = tw;
	Vram.b[n].tHeight = th;
	Vram.b[n].isClr   = false;
}
//---------------------------------------------------------------------------
// PALETTE SET
void CutExecCmd5(void)
{
	s32 no   = BitGet16();
	s32 nazo = BitGet16();		// 必ず0
	s32 size = BitGet16();

	assert(no < 4);
	assert(1 <= size && size <= 256);

	printf("PAL_SET no:%d size:%d\n", no, size);

	s32 i;

	for(i=0; i<size; i++)
	{
		u16 col = BitGet16();

		Vram.p[no].base[i] = col;
		Vram.p[no].work[i] = col;
	}
}
//---------------------------------------------------------------------------
// UPDATE（未使用の為、処理が正しいか不明）
void CutExecCmd6(void)
{
	s32 wait = BitGet16();

	printf("UPDATE(cmd6) wait:%d\n", wait);

	CutUpdate(wait);
}
//---------------------------------------------------------------------------
// MAP DEC(SPRITE)
void CutExecCmd7(void)
{
	s32 f  = BitGet16();	// 0-15
	s32 n  = BitGet16();	// 0, 8, 16（sprite priority）
	s32 tw = BitGet16();
	s32 th = BitGet16();

	assert(f < 16);
	assert(n == 0 || n == 8 || n == 16);

	printf("MAP_DEC(SPR) f:%d n:%d tw:%d th:%d\n", f, n, tw, th);

	CutDecMap(BitGetPointer(), Vram.f[f].map);
	Vram.f[f].tWidth  = tw;
	Vram.f[f].tHeight = th;
	Vram.f[f].pri     = n / 8;
}
//---------------------------------------------------------------------------
// TILE COPY RAW
void CutExecCmd8(void)
{
	s32 cnt = BitGet16();

	assert(cnt < 64 * 64);

	cnt *= 64;

	printf("TILE_COPY(RAW)\n", cnt);

	memcpy(Vram.dec, BitGetPointer(), cnt);
}
//---------------------------------------------------------------------------
void CutUpdate(s32 wait)
{
	static u16 frame[BMP_WIDTH * BMP_HEIGHT];
	memset(frame, 0, sizeof(frame));

	for(s32 pri=0; pri<3; pri++)
	{
		// BG
		ST_BG* bg = &Vram.b[pri];

		if(bg->isClr == false)
		{
			printf("bg:%d scr=(%03d,%03d) size=(%03d,%03d) blend:0x%x\n", pri, bg->scrX, bg->scrY, bg->tWidth, bg->tHeight, bg->blend);

			for(s32 tileY=0; tileY < bg->tHeight; tileY++)
			{
				for(s32 tileX=0; tileX < bg->tWidth; tileX++)
				{
					for(s32 pixY=0; pixY<8; pixY++)
					{
						for(s32 pixX=0; pixX<8; pixX++)
						{
							s32 scnX = (bg->scrX * -1) + (tileX * 8) + pixX;
							s32 scnY = (bg->scrY * -1) + (tileY * 8) + pixY;

							if(scnX < 0 || scnX >= BMP_WIDTH || scnY < 0 || scnY >= BMP_HEIGHT)
							{
								continue;
							}

							u16 tileData = bg->map[tileY * bg->tWidth + tileX];
							u16 tileId   = (tileData & 0x3FFF);
							u8  flipH    = (tileData >> 14) & 1;
							u8  flipV    = (tileData >> 15) & 1;

							s32 srcX = flipH ? (7 - pixX) : pixX;
							s32 srcY = flipV ? (7 - pixY) : pixY;

							u8 palIdx = Vram.tile[tileId * 64 + srcY * 8 + srcX];

							if(palIdx == 0)
							{
								continue;
							}

							// BGは自身のパレットを参照
							u16 fgCol = Vram.p[pri].work[palIdx]; 

							if(bg->blend != 0x1F)
							{
								u16 bgCol = frame[scnY * BMP_WIDTH + scnX];
								u32 alphaFg;
								u32 alphaBg;

								if(bg->blend < 0x20)
								{
									// アルファブレンド
									alphaFg = bg->blend + 1;
									alphaBg = 31 - bg->blend;
								}
								else
								{
									// 加算合成
									alphaBg = 32;

									if(bg->blend == 0x3F)
									{
										alphaFg = 16;
									}
									else
									{
										alphaFg = bg->blend - 31;
									}
								}

								u32 fgR = (fgCol      ) & 0x1F;
								u32 fgG = (fgCol >>  5) & 0x1F;
								u32 fgB = (fgCol >> 10) & 0x1F;

								u32 bgR = (bgCol      ) & 0x1F;
								u32 bgG = (bgCol >>  5) & 0x1F;
								u32 bgB = (bgCol >> 10) & 0x1F;

								u32 outR = (fgR * alphaFg + bgR * alphaBg) >> 5;
								u32 outG = (fgG * alphaFg + bgG * alphaBg) >> 5;
								u32 outB = (fgB * alphaFg + bgB * alphaBg) >> 5;

								if(outR > 31) outR = 31;
								if(outG > 31) outG = 31;
								if(outB > 31) outB = 31;

								fgCol = (outB << 10) | (outG << 5) | outR;
							}

							frame[scnY * BMP_WIDTH + scnX] = fgCol;
						}
					}
				}
			}
		}

		// SPRITE
		for(s32 i=0; i<8; i++)
		{
			ST_SPRITE* spr = &Vram.s[i];

			if(spr->isClr == true || spr->pri != pri)
			{
				continue;
			}

			printf("sp:%d scr=(%03d,%03d) size=(%03d,%03d) blend:0x%x xy=(%03d,%03d) pri:%d\n", i, spr->scrX, spr->scrY, spr->tWidth, spr->tHeight, spr->blend, spr->x, spr->y, spr->pri);

			for(s32 tileY=0; tileY < spr->tHeight; tileY++)
			{
				for(s32 tileX=0; tileX < spr->tWidth; tileX++)
				{
					for(s32 pixY=0; pixY<8; pixY++)
					{
						for(s32 pixX=0; pixX<8; pixX++)
						{
							s32 scnX = (spr->scrX * -1) + spr->x + (tileX * 8) + pixX;
							s32 scnY = (spr->scrY * -1) + spr->y + (tileY * 8) + pixY;

							if(scnX < 0 || scnX >= BMP_WIDTH || scnY < 0 || scnY >= BMP_HEIGHT)
							{
								continue;
							}

							u16 tileData = spr->map[tileY * spr->tWidth + tileX];
							u16 tileId   = (tileData & 0x3FFF) + 0x2000;
							u8  flipH    = (tileData >> 14) & 1;
							u8  flipV    = (tileData >> 15) & 1;

							s32 srcX = flipH ? (7 - pixX) : pixX;
							s32 srcY = flipV ? (7 - pixY) : pixY;

							u8 palIdx = Vram.tile[tileId * 64 + srcY * 8 + srcX];

							if(palIdx == 0)
							{
								continue;
							}

							// スプライトはパレット[3]を使用
							u16 fgCol = Vram.p[3].work[palIdx]; 

							if(spr->blend != 0x1F)
							{
								u16 bgCol = frame[scnY * BMP_WIDTH + scnX];
								u32 alphaFg, alphaBg;

								if(spr->blend < 0x20)
								{
									// アルファブレンド
									alphaFg = spr->blend + 1;
									alphaBg = 31 - spr->blend;
								}
								else
								{
									// 加算合成
									alphaBg = 32;

									if(spr->blend == 0x3F)
									{
										alphaFg = 16;
									}
									else
									{
										alphaFg = spr->blend - 31;
									}
								}

								u32 fgR = (fgCol      ) & 0x1F;
								u32 fgG = (fgCol >>  5) & 0x1F;
								u32 fgB = (fgCol >> 10) & 0x1F;

								u32 bgR = (bgCol      ) & 0x1F;
								u32 bgG = (bgCol >>  5) & 0x1F;
								u32 bgB = (bgCol >> 10) & 0x1F;

								u32 outR = (fgR * alphaFg + bgR * alphaBg) >> 5;
								u32 outG = (fgG * alphaFg + bgG * alphaBg) >> 5;
								u32 outB = (fgB * alphaFg + bgB * alphaBg) >> 5;

								if(outR > 31) outR = 31;
								if(outG > 31) outG = 31;
								if(outB > 31) outB = 31;

								fgCol = (outB << 10) | (outG << 5) | outR;
							}

							frame[scnY * BMP_WIDTH + scnX] = fgCol;
						}
					}
				}
			}
		}
	}


	if(Vram.frameCnt >= Vram.recCnt)
	{
		char fname[64];
		sprintf(fname, "f%05d.bmp", Vram.frameCnt);

		BmpSave(fname, frame);

		printf("%s\n", fname);
		printf("------------------------------------------------------------\n");

		Vram.fileCnt += 1;

		while(Vram.recCnt <= Vram.frameCnt)
		{
			Vram.recCnt += 2;
		}
	}

	if(wait == 0)
	{
		wait++;
	}

	Vram.frameCnt += wait;

/*
	s32 st = 0;
	s32 ed = 4000;		// max: 3914

	if(Vram.fileCnt >= st && Vram.fileCnt <= ed)
	{
		char fname[64];
//		sprintf(fname, "Z_%04d_%05d.bmp", Vram.fileCnt, Vram.frameCnt);
		sprintf(fname, "f%05d.bmp", Vram.frameCnt);

		BmpSave(fname, frame);

		printf("%s\n", fname);
		printf("------------------------------------------------------------\n");

		if(Vram.fileCnt >= ed)
		{
			exit(1);
		}
	}

	if(wait == 0)
	{
		wait++;
	}

	Vram.fileCnt  += 1;
	Vram.frameCnt += wait;
*/
}
//---------------------------------------------------------------------------
void CutDecMap(u8* in, u16* out)
{
	// mov esi, [esp+4+_P]
	// mov edi, [esp+8+_P]
	u8* esi = in;
	u8* edi = (u8*)out;

	// mov [esp], dword ptr 0
	// xor eax, eax
	// xor ebx, ebx
	// xor ecx, ecx
	// xor edx, edx
	// xor ebp, ebp
	u8  z[4] = {0};
	u8  al   = 0;
	u8  bl   = 0;
	u8  bh   = 0;
	u8  cl   = 0;
	u8  dl   = 0;
	u32 ebp  = 0;

L_lp:

	// mov al, [esi]
	// inc esi
	al = *esi++;

	// test al, 80h
	// jz short #L0
	if((al & 0x80) == 0) goto L_L0;

	// mov bh, al
	// mov bl, al
	// and bh, 1Fh
	// add bl, bl
	// and bl, 0C0h
	// add bh, bl
	// jmp short #lp
	bh = al;
	bl = al;
	bh &= 0x1F;
	bl += bl;
	bl &= 0xC0;
	bh += bl;
	goto L_lp;

L_L0:

	// mov cl, al
	// shr cl, 4
	// and al, 15
	cl = al;
	cl >>= 4;
	al &= 15;

	// jmp dword ptr cs:#case_base[ecx*4]
	if(cl == 0) goto L_case0;
	if(cl == 1) goto L_case1;
	if(cl == 2) goto L_case2;
	if(cl == 3) goto L_case3;
	goto L_case4_7;

L_case0:
L_L00:

	// mov bl, [esi]
	// inc esi
	// mov [edi], bx
	// add edi, 2
	// dec al
	bl = *esi++;
	*edi++ = bl;
	*edi++ = bh;
	al--;

	// jge short #L00
	// jmp short #lp
	if((s8)al >= 0) goto L_L00;
	goto L_lp;

L_case1:

	// jz short #exit
	if(al == 0) goto L_exit;

	// mov dl, [esi]
	// inc esi
	dl = *esi++;

L_case2:

	// mov bl, dl
	bl = dl;

L_L20:

	// mov [edi], bx
	// add edi, 2
	// inc bl
	// dec al
	*edi++ = bl;
	*edi++ = bh;
	bl++;
	al--;

	// jge short #L20
	if((s8)al >= 0) goto L_L20;

	// mov dl, bl
	// jmp short #lp
	dl = bl;
	goto L_lp;

L_case3:

	// inc al
	// mov bl, [esi]
	// inc esi
	al++;
	bl = *esi++;

L_L30:

	// mov [edi], bx
	// add edi, 2
	// dec al
	*edi++ = bl;
	*edi++ = bh;
	al--;

	// jge short #L30
	if((s8)al >= 0) goto L_L30;

	// mov [esp+ebp], bl
	// inc ebp
	// and ebp, 3
	// jmp #lp
	z[ebp] = bl;
	ebp++;
	ebp &= 3;
	goto L_lp;

L_case4_7:

	// inc al
	// mov bl, [esp+ecx-4]
	al++;
	bl = z[cl - 4];

L_L40:

	// mov [edi], bx
	// add edi, 2
	// dec al
	*edi++ = bl;
	*edi++ = bh;
	al--;

	// jge short #L40
	// jmp #lp
	if((s8)al >= 0) goto L_L40;
	goto L_lp;

L_exit:

	// mov eax, esi
	// ret
	// return esi;

	// 雑アサート
	assert(edi <= (u8*)out + sizeof(Vram.f[0].map));
}
//---------------------------------------------------------------------------
u8* CutDecTile(u8* in, u8* out)
{
	const u8 cycle[16] = {0,2,3,4,5,6,7,1, 0,10,11,12,13,14,15,9};

	// mov esi, [esp+4+_P]
	// mov edi, [esp+8+_P]
	u8* esi = in;
	u8* edi = out;

	// mov edx, 1
	// mov ebp, edx
	// xor eax, eax
	// xor ecx, ecx
	// xor ebx, ebx
	u32 edx = 1;
	u32 ebp = 1;
	u32 eax = 0;
	u32 ebx = 0;
	u32 ecx = 0;

	u8 al = 0;
	u8 ah = 0;
	u8 bl = 0;
	u8 cl = 0;
	u8 dl = 0;

	// y equ esp
	// z equ esp+8
	// mov [esp], eax
	// mov [esp+4], eax
	// mov [esp+8], eax
	// mov [esp+12], eax
	u8 yz[16] = {0};

L_lp:

	// mov cl, [esi]
	// xor ebx, ebx
	// inc esi
	cl = *esi++;
	ecx = (ecx & 0xFFFFFF00) | cl;
	ebx = 0;
	bl = 0;

	// mov bl, cl
	// shr bl, 6
	bl = ecx;
	bl >>= 6;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// jmp dword ptr cs:#case_base1[ebx*4]
	if(bl == 0) goto L_case0;
	if(bl == 1) goto L_case1;
	if(bl == 2) goto L_case2;
	if(bl == 3) goto L_case3;

L_case0:

	// mov bl, cl
	bl = ecx;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// shr cl, 3
	// and cl, 7
	cl = ecx;
	cl >>= 3;
	cl &= 7;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// jz short #F00
	if(cl == 0) goto L_F00;

	// mov cl, [z+ecx]
	// jmp short #F01
	cl = yz[8 + cl];
	ecx = (ecx & 0xFFFFFF00) | cl;
	goto L_F01;

L_F00:

	// mov cl, [esi]
	// inc esi
	cl = *esi++;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// mov [z+edx], cl
	// mov dl, cycle[edx]
	yz[8 + edx] = cl;
	dl = cycle[edx];
	edx = (edx & 0xFFFFFF00) | dl;

L_F01:

	// and bl, 7
	bl &= 7;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// jz short #F02
	if(bl == 0) goto L_F02;

	// mov ah, cl
	ah = cl;
	eax = (eax & 0xFFFF00FF) | (ah << 8);

L_F02:

	// cmp bl, 7
	// jne short #F03
	if(bl != 7) goto L_F03;

	// mov bl, [esi]
	// inc esi
	bl = *esi++;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// test bl, bl
	// jz #exit
	if(bl == 0) goto L_exit;

L_F03:

	// inc ebx
	ebx++;
	bl = ebx;

L_B04:

	// mov [edi], cl
	// inc edi
	// dec ebx
	*edi++ = cl;
	ebx--;
	bl = ebx;

	// jge short #B04
	// jmp short #lp
	if((s32)ebx >= 0) goto L_B04;
	goto L_lp;

L_case1:

	// bswap eax
	eax = ((eax >> 24) & 0xFF) | ((eax >> 8) & 0xFF00) | ((eax << 8) & 0xFF0000) | ((eax << 24) & 0xFF000000);
	al = eax;
	ah = eax >> 8;

	// test cl, 100000b
	// jnz short #F10
	if((cl & 0x20) != 0) goto L_F10;

	// mov ax, [esi]
	// add esi, 2
	// sub al, ah
	al = *esi++;
	ah = *esi++;
	al -= ah;
	eax = (eax & 0xFFFF0000) | (ah << 8) | al;

L_F10:

	// mov bl, 4
	bl = 4;
	ebx = (ebx & 0xFFFFFF00) | bl;

L_B11:

	// mov [edi], ah
	*edi = ah;

	// test cl, 10000b
	// jnz short #F12
	if((cl & 0x10) != 0) goto L_F12;

	// add [edi], al
	*edi += al;

L_F12:

	// inc edi
	// add cl, cl
	edi++;
	cl += cl;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// dec bl
	bl--;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// jge short #B11
	if((s8)bl >= 0) goto L_B11;

	// bswap eax
	eax = ((eax >> 24) & 0xFF) | ((eax >> 8) & 0xFF00) | ((eax << 8) & 0xFF0000) | ((eax << 24) & 0xFF000000);
	al = eax;
	ah = eax >> 8;

	// jmp #lp
	goto L_lp;

L_case2:

	// mov bl, cl
	// and bl, 3
	bl = ecx;
	bl &= 3;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// shr cl, 2
	cl >>= 2;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// and ecx, 15
	// jz #case_c0
	// cmp cl, 8
	// je #case_c8
	ecx &= 15;
	cl = ecx;
	if(ecx == 0) goto L_case_c0;
	if(ecx == 8) goto L_case_c8;

L_B20:

	// mov al, [y+ecx]
	al = yz[ecx];
	eax = (eax & 0xFFFFFF00) | al;

	// mov [edi], al
	// inc edi
	// mov cl, cycle[ecx]
	*edi++ = al;
	cl = cycle[ecx];
	ecx = (ecx & 0xFFFFFF00) | cl;

	// dec ebx
	// jge short #B20
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B20;
	goto L_lp;

L_case_c8:

	// mov ecx, [edi-8]
	// mov [edi], ecx
	// add edi, 4
	// xor ecx, ecx
	ecx = edi[-8] | (edi[-7] << 8) | (edi[-6] << 16) | (edi[-5] << 24);
	*edi++ = (ecx      ) & 0xFF;
	*edi++ = (ecx >>  8) & 0xFF;
	*edi++ = (ecx >> 16) & 0xFF;
	*edi++ = (ecx >> 24) & 0xFF;
	ecx = 0;
	cl = 0;

L_B21:

	// mov al, [edi-8]
	// mov [edi], al
	// inc edi
	al = edi[-8];
	eax = (eax & 0xFFFFFF00) | al;
	*edi++ = al;

	// dec ebx
	// jge short #B21
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B21;
	goto L_lp;

L_case_c0:
L_B22:

	// mov al, [esi]
	// inc esi
	// mov [edi], al
	// inc edi
	al = *esi++;
	eax = (eax & 0xFFFFFF00) | al;
	*edi++ = al;

	// mov [y+ebp], al
	// movzx ebp, cycle[ebp]
	yz[ebp] = al;
	ebp = cycle[ebp];

	// dec ebx
	// jge short #B22
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B22;
	goto L_lp;

L_case3:

	// mov bl, cl
	// and bl, 7
	bl = cl;
	bl &= 7;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// shr cl, 3
	// and cl, 7
	cl >>= 3;
	cl &= 7;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// jz short #F30
	if(cl == 0) goto L_F30;

	// mov al, [y+ecx]
	// mov [edi], al
	// inc edi
	// jmp short #F31
	al = yz[ecx];
	eax = (eax & 0xFFFFFF00) | al;
	*edi++ = al;
	goto L_F31;

L_F30:

	// mov al, [esi]
	// inc esi
	al = *esi++;
	eax = (eax & 0xFFFFFF00) | al;

	// mov [edi], al; inc edi
	// mov [y+ebp], al
	// movzx ebp, cycle[ebp]
	*edi++ = al;
	yz[ebp] = al;
	ebp = cycle[ebp];

L_F31:

	// cmp bl, 7
	// jne short #F32
	if(bl != 7) goto L_F32;

	// mov bl, [esi]
	// inc esi
	bl = *esi++;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// test bl, bl
	// jz short #exit
	if(bl == 0) goto L_exit;

L_F32:
L_B32:

	// mov [edi], ah
	// inc edi
	*edi++ = ah;

	// dec ebx
	// jge short #B32
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B32;
	goto L_lp;

L_exit:

	// mov GI1nextFontBuf, edi
	// mov eax, esi
	// ret

	// 雑アサート
	assert(edi <= (u8*)out + sizeof(Vram.dec));

	return edi;
}
//---------------------------------------------------------------------------
s32 CutPalClip(s32 val)
{
	if(val <  0) return  0;
	if(val > 31) return 31;

	return val;
}
//---------------------------------------------------------------------------
void CutPalBias(s32 msk, s32 b, s32 g, s32 r)
{
	s32 i, j;

	for(i=0; i<4; i++, msk >>= 1)
	{
		if((msk & 1) == 0)
		{
			continue;
		}

		for(j=0; j<256; j++)
		{
			u16 base = Vram.p[i].base[j];

			s32 oB = CutPalClip(((base >> 10) & 0x1F) + b);
			s32 oG = CutPalClip(((base >>  5) & 0x1F) + g);
			s32 oR = CutPalClip(((base      ) & 0x1F) + r);

			Vram.p[i].work[j] = (oB << 10) | (oG << 5) | oR;
		}
	}
}
//---------------------------------------------------------------------------
void CutPalFade(u32 msk, s32 level)
{
	s32 i, j;

	if(level < 0)
	{
		// 黒ブレンド
		s32 l = level + 256;

		for(i=0; i<4; i++, msk >>= 1)
		{
			if((msk & 1) == 0)
			{
				continue;
			}

			for(j=0; j<256; j++)
			{
				u32 base = Vram.p[i].base[j];

				s32 b = (((base >> 10) & 0x1F) * l) >> 8;
				s32 g = (((base >>  5) & 0x1F) * l) >> 8;
				s32 r = (((base      ) & 0x1F) * l) >> 8;

				Vram.p[i].work[j] = (b << 10) | (g << 5) | r;
			}
		}
	}
	else
	{
		// 白ブレンド
		s32 c =  31 * level;
		s32 l = 256 - level;

		for(i=0; i<4; i++, msk >>= 1)
		{
			if((msk & 1) == 0)
			{
				continue;
			}

			for(j=0; j<256; j++)
			{
				u32 base = Vram.p[i].base[j];

				s32 b = (c + (((base >> 10) & 0x1F) * l)) >> 8;
				s32 g = (c + (((base >>  5) & 0x1F) * l)) >> 8;
				s32 r = (c + (((base      ) & 0x1F) * l)) >> 8;

				if(b > 31) b = 31;
				if(g > 31) g = 31;
				if(r > 31) r = 31;

				Vram.p[i].work[j] = (b << 10) | (g << 5) | r;
			}
		}
	}
}
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("dbl2bmp [DBL File]\n");

		exit(0);
	}

	printf("dbl2bmp... %s\n", argv[1]);


	BitCalloc(argv[1]);
	s32 pos = 0x800;
	s32 max = BitGetSize();

	CutInit();

	while(pos + 0x10A < max)
	{
		BitSeek(pos);
		CutExec();

		pos = (BitGetPos() + 0xFF) & ~0xFF;
	}

	BitFree();

	return 0;
}
