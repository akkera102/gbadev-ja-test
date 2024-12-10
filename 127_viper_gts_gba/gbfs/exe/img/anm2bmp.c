// Sogna ANM2BMP (Windows Viper GTS)
// Copyright (C) 2024 Notequalsoft. Arranged by akkera102. GPL2 License.

// gcc anm2bmp.c -o anm2bmp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

//---------------------------------------------------------------------------
#define ANM_MAX_FRAME_CNT						100

typedef unsigned char			 u8;
typedef char					 s8;
typedef unsigned short			u16;
typedef short					s16;
typedef unsigned int			u32;
typedef int						s32;

// フレーム1つ分
typedef struct {
	u8* pDat;			// RLE or 無圧縮
	s32 pos;			// ANM上での開始位置
	s32 size;

	s32 x;
	s32 y;
	s32 cx;
	s32 cy;
} ST_ANM_FRAME;

// フレームまとめ
typedef struct {
	s32  frameMax;
	s32  cx;
	s32  cy;

	u8   r[256];
	u8   g[256];
	u8   b[256];

	bool isRle;

	ST_ANM_FRAME frame[ANM_MAX_FRAME_CNT];
} ST_ANM;

typedef struct {
	u8* p;
	s32 size;

	s32 pos;
	s32 dig;
	u8  chr;
} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;
ST_ANM Anm;


//---------------------------------------------------------------------------
void BitCalloc(char* fname);
void BitFree(void);
void BitSeek(s32 pos);
s32  BitGetPos(void);
s32  BitGetSize(void);
u8   BitGet1(void);
u8   BitGet4(void);
u8   BitGet8(void);
u16  BitGet16(void);
u32  BitGet32(void);

void AnmWrite8(FILE* fp, u8 h);
void AnmWrite16(FILE* fp, u16 h);
void AnmWrite32(FILE* fp, u32 h);
void AnmWriteDat(char* fname);
void AnmWriteBmp(char* fname, s32 no);
void AnmDec(u8* p, s32 no);
void AnmCut(u8* p, s32 no);

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
		fprintf(stderr, "calloc datSize error\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Bit.p, 1, Bit.size, fp);

	BitSeek(0);
	fclose(fp);
}
//---------------------------------------------------------------------------
void BitFree(void)
{
	free(Bit.p);

	Bit.p = NULL;
}
//---------------------------------------------------------------------------
void BitSeek(s32 pos)
{
	Bit.pos = pos;
	Bit.dig = 0;
	Bit.chr = 0;
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
u8 BitGet1(void)
{
	if(Bit.dig <= 0)
	{
		Bit.dig = 8;
		Bit.chr = Bit.p[Bit.pos++];

		assert(Bit.pos <= Bit.size);
	}

	s32 p = --Bit.dig;

	return (Bit.chr & (1 << p)) ? 1 : 0;
}
//---------------------------------------------------------------------------
u8 BitGet4(void)
{
	u32 r = 0;
	s32 i;

	for(i=0; i<4; i++)
	{
		r <<= 1;
		r += BitGet1();
	}

	return r;
}
//---------------------------------------------------------------------------
u8 BitGet8(void)
{
	u8 h = BitGet4() << 4;
	u8 l = BitGet4();

	return h | l;
}
//---------------------------------------------------------------------------
u16 BitGet16(void)
{
	u16 b1 = BitGet8();
	u16 b2 = BitGet8() << 8;

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 BitGet32(void)
{
	u32 b1 = BitGet8();
	u32 b2 = BitGet8() <<  8;
	u32 b3 = BitGet8() << 16;
	u32 b4 = BitGet8() << 24;

	return b4 | b3 | b2 | b1;
}
//---------------------------------------------------------------------------
void AnmWrite8(FILE* fp, u8 h)
{
	u8 buf[1];

	buf[0] = h;

	fwrite(buf, 1, 1, fp);
}
//---------------------------------------------------------------------------
void AnmWrite16(FILE* fp, u16 h)
{
	u8 buf[2];

	buf[0] = (h >> 0) & 0xFF;
	buf[1] = (h >> 8) & 0xFF;

	fwrite(buf, 2, 1, fp);
}
//---------------------------------------------------------------------------
void AnmWrite32(FILE* fp, u32 h)
{
	u8 buf[4];

	buf[0] = (h >>  0) & 0xFF;
	buf[1] = (h >>  8) & 0xFF;
	buf[2] = (h >> 16) & 0xFF;
	buf[3] = (h >> 24) & 0xFF;

	fwrite(buf, 4, 1, fp);
}
//---------------------------------------------------------------------------
void AnmWriteDat(char* fname)
{
	char rname[30];
	strncpy(rname, fname, 20);

	char* s = strchr(rname, '.');

	if(s == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	s[0] = '.';
	s[1] = 'd';
	s[2] = 'a';
	s[3] = 't';
	s[4] = '\0';

	FILE* fp = fopen(rname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open dat file\n");

		exit(1);
	}

	AnmWrite32(fp, Anm.frameMax);
	AnmWrite32(fp, 0);
	AnmWrite32(fp, 0);
	AnmWrite32(fp, 0);

	s32 i;

	for(i=0; i<256; i++)
	{
		int r = Anm.r[i] / 8;
		int g = Anm.g[i] / 8;
		int b = Anm.b[i] / 8;
		int c = ((b) | ((g) << 5) | ((r) << 10));

		AnmWrite16(fp, c);
	}

	for(i=0; i<Anm.frameMax; i++)
	{
		AnmWrite16(fp, Anm.frame[i].x);
		AnmWrite16(fp, Anm.frame[i].y);
		AnmWrite16(fp, Anm.frame[i].cx);
		AnmWrite16(fp, Anm.frame[i].cy);
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
void AnmWriteBmp(char* fname, s32 no)
{
	assert((Anm.cx & 0x3) == 0);


	// 保存するファイル名に連番を付与
	char rname[30];
	strncpy(rname, fname, 20);

	char* s = strchr(rname, '.');

	if(s == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	char buf[3];
	sprintf(buf, "%02d", no + 1);

	s[0] = '_';
	s[1] = buf[0];
	s[2] = buf[1];
	s[3] = '.';
	s[4] = 'b';
	s[5] = 'm';
	s[6] = 'p';
	s[7] = '\0';

	FILE* fp = fopen(rname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open BMP file\n");

		exit(1);
	}


	// BITMAPFILEHEADER
	AnmWrite8(fp, 'B');
	AnmWrite8(fp, 'M');
	AnmWrite32(fp, 14 + 12 + 256 * 3 + Anm.frame[no].cx * Anm.frame[no].cy);
	AnmWrite16(fp, 0);
	AnmWrite16(fp, 0);
	AnmWrite32(fp, 14 + 12 + 256 * 3);

	// BITMAPCOREHEADER
	AnmWrite32(fp, 12);
	AnmWrite16(fp, Anm.frame[no].cx);
	AnmWrite16(fp, Anm.frame[no].cy);
	AnmWrite16(fp, 1);
	AnmWrite16(fp, 8);

	// PALETTE
	s32 i;

	for(i=0; i<256; i++)
	{
		AnmWrite8(fp, Anm.r[i]);
		AnmWrite8(fp, Anm.g[i]);
		AnmWrite8(fp, Anm.b[i]);
	}

	// DATA
	u8* p = (u8*)calloc(Anm.frame[no].cx * Anm.frame[no].cy, sizeof(u8));

	if(p == NULL)
	{
		fprintf(stderr, "calloc bmp error\n");

		exit(1);
	}

	if(Anm.isRle == true)
	{
		AnmDec(p, no);
	}
	else
	{
		AnmCut(p, no);
	}

	for(i=0; i<Anm.frame[no].cy; i++)
	{
		fwrite(p + Anm.frame[no].cx * (Anm.frame[no].cy - 1 - i), Anm.frame[no].cx, 1, fp);
	}

	free(p);
	fclose(fp);
}
//---------------------------------------------------------------------------
void AnmDec(u8* p, s32 no)
{
	ST_ANM* pA = (ST_ANM*)&Anm;
	ST_ANM_FRAME* pF = (ST_ANM_FRAME*)&Anm.frame[no];

	u8 curQuad[4] = { 0x00, 0x00, 0x00, 0x00 };
	u8 prvQuad[4] = { 0x00, 0x00, 0x00, 0x00 };
	bool isAllowRle = false;

	s32 wCnt = 0;
	s32 rCnt = 0;
	s32 x    = 0;
	s32 y    = 0;
	s32 i;

	while(rCnt < pF->size)
	{
		// read current quad and check for repeated sequence
		bool isRepeat = isAllowRle;

		for(i=0; i<4; i++)
		{
			curQuad[i] = pF->pDat[rCnt++];
			isRepeat = isRepeat && (curQuad[i] == prvQuad[i]);
		}

		// repeated sequence or new sequence
		if(isRepeat == true)
		{
			// get number of repetitions
			s32 repetitions = pF->pDat[rCnt++];

			if(repetitions == 0)
			{
				repetitions = 256 + pF->pDat[rCnt++];
			}

			// write repetitions of pixels
			for(i=0; i<repetitions; i++)
			{
				s32 j;

				for(j=0; j<4; j++)
				{
					p[wCnt++] = curQuad[j];
				}

				y++;
				wCnt += (pF->cx - 4);
			}

			// disable RLE for next quad
			isAllowRle = false;
		}
		else
		{
			// write pixels and copy current quad as previous quad
			for(i=0; i<4; i++)
			{
				p[wCnt++] = curQuad[i];
				prvQuad[i] = curQuad[i];
			}

			// advance to next line
			y++;
			wCnt += (pF->cx - 4);

			// enable RLE for next quad
			isAllowRle = true;
		}

		// check for end of column
		if(y == pF->cy)
		{
			// go to next column
			x += 4;
			wCnt = x;

			if(x < pF->cx)
			{
				y = 0;
			}

			// disable RLE for next quad
			isAllowRle = false;
		}
	}
}
//---------------------------------------------------------------------------
void AnmCut(u8* p, s32 no)
{
	s32 i;

	for(i=0; i<Anm.cx * Anm.cy; i++)
	{
		p[i] = Anm.frame[no].pDat[i];
	}
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("anm2bmp [ANM File]\n");

		exit(0);
	}

	printf("anm2bmp... %s\n", argv[1]);
	BitCalloc(argv[1]);


	s32 i;

	// パレットを取得
	for(i=0; i<256; i++)
	{
		Anm.r[i] = BitGet8();
		Anm.g[i] = BitGet8();
		Anm.b[i] = BitGet8();
	}

	// フレーム数と圧縮有無を取得
	Anm.frameMax = BitGet16();
	Anm.isRle    = (((BitGet16() >> 24) & 0x80) == 0x00) ? true : false;

	assert(Anm.frameMax < ANM_MAX_FRAME_CNT);

	// 各フレーム開始位置とサイズを取得
	for(i=0; i<Anm.frameMax; i++)
	{
		Anm.frame[i].pos = BitGet32() + 0x30C;

		if(i > 0)
		{
			Anm.frame[i-1].size = Anm.frame[i].pos - Anm.frame[i-1].pos - 8;
		}
	}
	Anm.frame[i-1].size = BitGetSize() - Anm.frame[i-1].pos;

	// 各フレームの大きさ、及びデータを取得
	for(i=0; i<Anm.frameMax; i++)
	{
		Anm.frame[i].x  = BitGet16();
		Anm.frame[i].y  = BitGet16();
		Anm.frame[i].cx = BitGet16();
		Anm.frame[i].cy = BitGet16();

		assert(BitGetPos() == Anm.frame[i].pos);

		// フレーム全体の大きさを計算
		if(Anm.cx < Anm.frame[i].x + Anm.frame[i].cx) Anm.cx = Anm.frame[i].x + Anm.frame[i].cx;
		if(Anm.cy < Anm.frame[i].y + Anm.frame[i].cy) Anm.cy = Anm.frame[i].y + Anm.frame[i].cy;

		// データ分をメモリ確保
		Anm.frame[i].pDat = (u8*)calloc(Anm.frame[i].size, sizeof(u8));

		if(Anm.frame[i].pDat == NULL)
		{
			fprintf(stderr, "calloc Anm.frame[%d].p error\n", i);

			exit(1);
		}

		s32 j;

		for(j=0; j<Anm.frame[i].size; j++)
		{
			Anm.frame[i].pDat[j] = BitGet8();
		}
	}

	// フレーム情報をDAT保存
	AnmWriteDat(argv[1]);

	// 各フレームをBMP保存
	for(i=0; i<Anm.frameMax; i++)
	{
		AnmWriteBmp(argv[1], i);

		free(Anm.frame[i].pDat);
	}

/*
	printf("FRAMEMAX:%02d RLE:%01d CX:%03d CY:%03d\n", Anm.frameMax, Anm.isRle, Anm.cx, Anm.cy);

	for(i=0; i<Anm.frameMax; i++)
	{
		printf("FRAME:%02d %08X %08X %03d %03d %03d %03d\n", i, Anm.frame[i].pos, Anm.frame[i].size, Anm.frame[i].x, Anm.frame[i].y, Anm.frame[i].cx, Anm.frame[i].cy);
	}
*/


	BitFree();

	return 0;
}
