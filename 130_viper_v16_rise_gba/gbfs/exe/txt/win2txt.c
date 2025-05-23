// Sogna WIN2TXT (Windows Viper V16 RISE)
// Copyright (C) 2024 Notequalsoft. Arranged by akkera102. GPL2 License.

// gcc win2txt.c -o win2txt


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

//---------------------------------------------------------------------------
typedef unsigned char			 u8;
typedef char					 s8;
typedef unsigned short			u16;
typedef short					s16;
typedef unsigned int			u32;
typedef int						s32;
typedef double					d32;

typedef struct {
	u8* p;
	s32 size;
	s32 pos;

} ST_BIT;

typedef struct {
	FILE* fp;
	char* pAnm;

} ST_DEC;


typedef struct {
	char* p;
	s32   f;			// frame
	d32   w;			// wait

} ST_WAIT_LIST;

//---------------------------------------------------------------------------
// 画像パーツリスト　リストに該当した場合はウェイト値を調整します（dat_info.pyより抽出、一部手修正）
ST_WAIT_LIST waitList[] = {
	{ "A1",      1, 2.7 },
	{ "A1",      2, 2.7 },
	{ "A1",      3, 2.7 },
	{ "A1",      4, 2.7 },
	{ "A1",      5, 2.7 },
	{ "A1",      6, 2.7 },
	{ "A1",      7, 2.7 },
	{ "A1",      8, 2.7 },
	{ "A1",      9, 2.7 },
	{ "A1",     10, 2.7 },
	{ "A1",     11, 2.7 },
	{ "A1",     12, 2.7 },
	{ "A1",     13, 2.7 },
	{ "A1",     14, 2.7 },
	{ "A1",     15, 2.7 },
	{ "A1",     16, 2.7 },
	{ "A1",     17, 2.7 },
	{ "A1",     18, 2.7 },
	{ "A1",     19, 2.7 },
	{ "A1",     20, 2.7 },
	{ "A1",     21, 2.7 },
	{ "A1",     22, 2.7 },
	{ "A1",     23, 2.7 },
	{ "A1",     24, 2.7 },
	{ "A1",     26, 2.7 },
	{ "A1",     27, 2.7 },
	{ "A1",     28, 2.7 },
	{ "A1",     29, 2.7 },
	{ "A1",     30, 2.7 },
	{ "A1",     31, 2.7 },
	{ "A1",     32, 2.7 },
	{ "A1",     33, 2.7 },
	{ "A1",     34, 2.7 },
	{ "A1",     35, 2.7 },
	{ "A1",     36, 2.7 },
	{ "A1",     37, 2.7 },
	{ "A1",     38, 2.7 },
	{ "A1",     39, 2.7 },
	{ "A1",     40, 2.7 },
	{ "A1",     41, 2.7 },
	{ "A1",     42, 2.7 },
	{ "A1",     43, 2.7 },
	{ "A1",     44, 2.7 },
	{ "A1",     45, 2.7 },
	{ "A1",     46, 2.7 },
	{ "A1",     47, 2.7 },
	{ "A1",     48, 2.7 },
	{ "A1",     49, 2.7 },
	{ "A1",     50, 2.7 },
	{ "A1",     51, 2.7 },
	{ "A1",     52, 2.7 },
	{ "A1",     53, 2.7 },
	{ "A1",     54, 2.7 },
	{ "A1",     55, 2.7 },
	{ "A1",     56, 2.7 },
	{ "A1",     57, 2.7 },
	{ "A1",     58, 2.7 },
	{ "A1",     59, 2.7 },
	{ "A1",     60, 2.7 },
	{ "A5",      1, 2.7 },
	{ "A5",      2, 2.7 },
	{ "A5",      3, 2.7 },
	{ "A5",      4, 2.7 },
	{ "B4",      1, 2.7 },
	{ "B4",      2, 2.7 },
	{ "B4",      3, 2.7 },
	{ "B4",      4, 2.7 },
	{ "B4",      5, 2.7 },
	{ "B4",      6, 2.7 },
	{ "C1",      1, 2.7 },
	{ "C1",      2, 2.7 },
	{ "C2",      1, 2.7 },
	{ "C2",      2, 2.7 },
	{ "C2",      3, 2.7 },
	{ "C2B",     1, 2.7 },
	{ "C2B",     2, 2.7 },
	{ "C2B",     3, 2.7 },
	{ "C4",      1, 2.7 },
	{ "C4",      9, 2.7 },
	{ "C4",     10, 2.7 },
	{ "C4",     11, 2.7 },
	{ "C4",     12, 2.7 },
	{ "ED41",    1, 2.7 },
	{ "ED41",    2, 2.7 },
	{ "ED41",    3, 2.7 },
	{ "ED42",    1, 2.7 },
	{ "ED42",    2, 2.7 },
	{ "ED42",    3, 2.7 },
	{ "ED42",    4, 2.7 },
	{ "ED42",    5, 2.7 },
	{ "ED42",    6, 2.7 },
	{ "ED43",    1, 2.7 },
	{ "ED43",    2, 2.7 },
	{ "ED43",    3, 2.7 },
	{ "ED43",    4, 2.7 },
	{ "ED43",    5, 2.7 },
	{ "ED43",    6, 2.7 },
	{ "ED43",    7, 2.7 },
	{ "ED43",    8, 2.7 },
	{ "ED43",    9, 2.7 },
	{ "ED43",   10, 2.7 },
	{ "ED43",   11, 2.7 },
	{ "ED43",   12, 2.7 },
	{ "ED43",   13, 2.7 },
	{ "ED43",   14, 2.7 },
	{ "ED43",   15, 2.7 },
	{ "ED43",   16, 2.7 },
	{ "ED43",   17, 2.7 },
	{ "ED43",   18, 2.7 },
	{ "ED46",    1, 2.7 },
	{ "ED46",    2, 2.7 },
	{ "ED46",    3, 2.7 },
	{ "ED46",    4, 2.7 },
	{ "ED46",    5, 2.7 },
	{ "ED46",    6, 2.7 },
	{ "ED51",    3, 2.7 },
	{ "ED51",    4, 2.7 },
	{ "ED52",   49, 2.7 },
	{ "ED52",   50, 2.7 },
	{ "ED52",   51, 2.7 },
	{ "ED52",   52, 2.7 },
	{ "ED52",   53, 2.7 },
	{ "ED52",   54, 2.7 },
	{ "ED52",   55, 2.7 },
	{ "ED53",    6, 2.7 },
	{ "ED53",    7, 2.7 },
	{ "ED53",    8, 2.7 },
	{ "ED53",    9, 2.7 },
	{ "ED53",   10, 2.7 },
	{ "ED53",   11, 2.7 },
	{ "ED53",   12, 2.7 },
	{ "ED53",   13, 2.7 },
	{ "ED53",   14, 2.7 },
	{ "ED53",   15, 2.7 },
	{ "ED54",    1, 2.7 },
	{ "ED54",    2, 2.7 },
	{ "ED54",    3, 2.7 },
	{ "ED54",    5, 2.7 },
	{ "ED54",    6, 2.7 },
	{ "ED54",    9, 2.7 },
	{ "ED54",   10, 2.7 },
	{ "ED54",   11, 2.7 },
	{ "ED54",   12, 2.7 },
	{ "ED54",   13, 2.7 },
	{ "ED54",   14, 2.7 },
	{ "ED61",    1, 2.7 },
	{ "ED61",    2, 2.7 },
	{ "ED61",    3, 2.7 },
	{ "ED61",    4, 2.7 },
	{ "ED62",    1, 2.7 },
	{ "ED62",    2, 2.7 },
	{ "ED62",    3, 2.7 },
	{ "ED62",    4, 2.7 },
	{ "ED62",    5, 2.7 },
	{ "ED62",    6, 2.7 },
	{ "ED62",    7, 2.7 },
	{ "ED62",   17, 2.7 },
	{ "ED62",   18, 2.7 },
	{ "ED62",   19, 2.7 },
	{ "ED62",   20, 2.7 },
	{ "ED62",   21, 2.7 },
	{ "ED62",   22, 2.7 },
	{ "ED62",   23, 2.7 },
	{ "ED62",   24, 2.7 },
	{ "ED62",   25, 2.7 },
	{ "ED62",   26, 2.7 },
	{ "ED63",   38, 2.7 },
	{ "ED63",   39, 2.7 },
	{ "ED63",   40, 2.7 },
	{ "ED64",   79, 2.7 },
	{ "ED64",   80, 2.7 },
	{ "ED64",   81, 2.7 },
	{ "ED64",   82, 2.7 },
	{ "ED64",   83, 2.7 },
	{ "ED64",   84, 2.7 },
	{ "ED64",   86, 2.7 },
	{ "ED64",   87, 2.7 },
	{ "ED65",    1, 2.7 },
	{ "ED65",    2, 2.7 },
	{ "ED65",    3, 2.7 },
	{ "ED66",   11, 2.7 },
	{ "ED66",   12, 2.7 },
	{ "ED66",   13, 2.7 },
	{ "ED66",   14, 2.7 },
	{ "ED66",   15, 2.7 },
	{ "ED66",   16, 2.7 },
	{ "ED66",   17, 2.7 },
	{ "ED66",   18, 2.7 },
	{ "ED66",   19, 2.7 },
	{ "ED66",   20, 2.7 },
	{ "ED66",   21, 2.7 },
	{ "ED66",   22, 2.7 },
	{ "ED66",   23, 2.7 },
	{ "ED66",   24, 2.7 },
	{ "ED67",    1, 2.7 },
	{ "ED67",    2, 2.7 },
	{ "ED67",    3, 2.7 },
	{ "ED67",    4, 2.7 },
	{ "ED67",    5, 2.7 },
	{ "ED67",    6, 2.7 },
	{ "ED67",    7, 2.7 },
	{ "ED67",    8, 2.7 },
	{ "ED67",    9, 2.7 },
	{ "ED67",   10, 2.7 },
	{ "ED67",   11, 2.7 },
	{ "ED67",   12, 2.7 },
	{ "ED67",   13, 2.7 },
	{ "ED67",   14, 2.7 },
	{ "ED67",   15, 2.7 },
	{ "ED67",   16, 2.7 },
	{ "ED67",   17, 2.7 },
	{ "ED67",   18, 2.7 },
	{ "ED67",   19, 2.7 },
	{ "ED68",   34, 2.7 },
	{ "ED68",   35, 2.7 },
	{ "ED68",   36, 2.7 },
	{ "ED68",   37, 2.7 },
	{ "ED68",   38, 2.7 },
	{ "ED68",   39, 2.7 },
	{ "ED68",   40, 2.7 },
	{ "ED71",   29, 2.7 },
	{ "ED71",   30, 2.7 },
	{ "ED71",   31, 2.7 },
	{ "ED71",   32, 2.7 },
	{ "ED71",   33, 2.7 },
	{ "ED71",   34, 2.7 },
	{ "ED71",   35, 2.7 },
	{ "ED71",   36, 2.7 },
	{ "ED71",   37, 2.7 },
	{ "ED71",   38, 2.7 },
	{ "ED71",   39, 2.7 },
	{ "ED71",   40, 2.7 },
	{ "ED71",   41, 2.7 },
	{ "ED71",   42, 2.7 },
	{ "ED71",   43, 2.7 },
	{ "ED71",   44, 2.7 },
	{ "OP2",     1, 2.7 },
	{ "OP2",     2, 2.7 },
	{ "OP2",     3, 2.7 },
	{ "OP3",     1, 2.7 },
	{ "OP3",     2, 2.7 },
	{ "OP3",     3, 2.7 },
	{ "RI_SEL",  2, 2.7 },
	{ "RI_SEL",  3, 2.7 },
	{ "RI_SEL",  4, 2.7 },
	{ "RI_SEL",  5, 2.7 },

	// 例外

};

//---------------------------------------------------------------------------
ST_BIT Bit;
ST_DEC Dec;


//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
u8    BitCur8(void);
u8    BitGet8(void);
u16   BitGet16(void);
char* BitGetStr(void);

u32   Div(u32 a, u32 b);
void  Dec00(void);
void  Dec01(void);
void  Dec02(void);
void  Dec03(void);
void  Dec04(void);
void  Dec05(void);
void  Dec06(void);
void  Dec07(void);
void  Dec08(void);
void  Dec09(void);
void  Dec0A(void);
void  Dec0B(void);
void  Dec0C(void);
void  Dec0D(void);
void  Dec0E(void);
void  Dec0F(void);
void  Dec10(void);
void  Dec11(void);
void  Dec12(void);
void  Dec13(void);
void  Dec14(void);
void  Dec15(void);
void  Dec16(void);
void  Dec17(void);
void  Dec18(void);
void  Dec19(void);
void  Dec1A(void);
void  Dec1B(void);
void  Dec1C(void);
void  Dec1D(void);
void  Dec1E(void);
void  Dec1F(void);
void  Dec20(void);
void  Dec21(void);
void  Dec22(void);
void  Dec23(void);
void  Dec24(void);
void  Dec25(void);
void  Dec26(void);
void  Dec27(void);
void  Dec28(void);
void  Dec29(void);
void  Dec2A(void);
void  Dec2B(void);
void  Dec2C(void);
void  Dec2D(void);
void  Dec2E(void);
void  Dec2F(void);
void  Dec30(void);
void  Dec31(void);
void  Dec32(void);
void  Dec33(void);
void  Dec34(void);
void  Dec35(void);
void  Dec36(void);
void  Dec37(void);
void  Dec38(void);
void  Dec39(void);
void  Dec3A(void);
void  Dec3B(void);
void  Dec3C(void);
void  Dec3D(void);
void  Dec3E(void);
void  Dec3F(void);
void  Dec40(void);
void  Dec41(void);
void  Dec42(void);
void  Dec43(void);
void  Dec44(void);
void  Dec45(void);
void  Dec46(void);
void  Dec47(void);
void  Dec48(void);
void  Dec49(void);
void  Dec4A(void);
void  Dec4B(void);
void  Dec4C(void);
void  Dec4D(void);
void  Dec4E(void);
void  Dec4F(void);
void  Dec50(void);
void  Dec51(void);
void  Dec52(void);
void  Dec53(void);
void  Dec54(void);
void  Dec55(void);
void  Dec56(void);
void  Dec57(void);
void  Dec58(void);
void  Dec59(void);
void  Dec5A(void);
void  Dec5B(void);
void  Dec5C(void);
void  Dec5D(void);
void  Dec5E(void);
void  Dec5F(void);
void  Dec60(void);
void  Dec61(void);
void  Dec62(void);
void  Dec63(void);
void  Dec64(void);
void  Dec65(void);
void  Dec66(void);
void  Dec67(void);
void  Dec68(void);
void  Dec69(void);
void  Dec6A(void);
void  Dec6B(void);
void  Dec6C(void);
void  Dec6D(void);
void  Dec6E(void);
void  Dec6F(void);
void  Dec70(void);
void  Dec71(void);
void  Dec72(void);
void  Dec73(void);
void  Dec74(void);
void  Dec75(void);
void  Dec76(void);
void  Dec77(void);
void  Dec78(void);
void  Dec79(void);
void  Dec7A(void);
void  Dec7B(void);

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

	fclose(fp);
}
//---------------------------------------------------------------------------
void BitFree(void)
{
	free(Bit.p);

	Bit.p = NULL;
}
//---------------------------------------------------------------------------
u8 BitCur8(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p[Bit.pos];
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
	u16 b1 = BitGet8();
	u16 b2 = BitGet8() << 8;

	return b2 | b1;
}
//---------------------------------------------------------------------------
char* BitGetStr(void)
{
	char* pRet = Bit.p + Bit.pos;

	while(Bit.p[Bit.pos++] != '\0')
	{
		// EMPTY
	}

	return pRet;
}
//---------------------------------------------------------------------------
u32 Div(u32 a, u32 b)
{
	if(a == 0)
	{
		assert(0 && "Div a");
	}

	if(b == 0)
	{
		assert(0 && "Div b");
	}

	return a / b;
}
//---------------------------------------------------------------------------
void Dec00(void)
{
	// NONE

//	fprintf(Dec.fp, "STOP\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec01(void)
{
	u16 a = BitGet16();		// LEFT
	u16 b = BitGet16();		// TOP

//	fprintf(Dec.fp, "SET_VIEWPORT_POS %d %d\n", a, b);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec02(void)
{
	u16 a = BitGet16();		// WIDTH
	u16 b = BitGet16();		// HEIGHT

//	fprintf(Dec.fp, "SET_VIEWPORT_SIZE %d %d\n", a, b);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec03(void)
{
	u8    a = BitGet8();		// IMAGE
	char* s = BitGetStr();		// FILE

//	fprintf(Dec.fp, "LOAD_ANM %d %s\n", a, s);
	fprintf(Dec.fp, "ANM %s\n", s + 4);
	Dec.pAnm = s + 4;
}
//---------------------------------------------------------------------------
void Dec04(void)
{
	u8 a = BitGet8();		// IMAGE

//	fprintf(Dec.fp, "UNLOAD_ANM %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec05(void)
{
	u8  a = BitGet8();		// COLOR
	u16 b = BitGet16();		// CYCLES

//	fprintf(Dec.fp, "FADE_IN_GRAYSCALE %d %d\n", a, b);

	b = Div(b, 12);

	if(a == 0)
	{
		fprintf(Dec.fp, "EFF 2 %d\n", b);
	}
	else if(a == 255)
	{
		fprintf(Dec.fp, "EFF 4 %d\n", b);
	}
	else
	{
		assert(0);
	}
}
//---------------------------------------------------------------------------
void Dec06(void)
{
	u8  a = BitGet8();		// COLOR
	u16 b = BitGet16();		// CYCLES

//	fprintf(Dec.fp, "FADE_OUT_GRAYSCALE %d %d\n", a, b);

	b = Div(b, 12);

	if(a == 0)
	{
		fprintf(Dec.fp, "EFF 1 %d\n", b);
	}
	else if(a == 255)
	{
		fprintf(Dec.fp, "EFF 3 %d\n", b);
	}
	else
	{
		assert(0);
	}
}
//---------------------------------------------------------------------------
void Dec07(void)
{
	u8 a = BitGet8();		// IMAGE

//	fprintf(Dec.fp, "SET_PALETTE_FROM_ANM %d\n", a);
	fprintf(Dec.fp, "PAL\n");
}
//---------------------------------------------------------------------------
void Dec08(void)
{
	// NONE

//	fprintf(Dec.fp, "FORCE_FINISH_FADE_IN\n");
	fprintf(Dec.fp, "EFF 2 255\n");
}
//---------------------------------------------------------------------------
void Dec09(void)
{
	// NONE

//	fprintf(Dec.fp, "FORCE_FINISH_FADE_OUT\n");
	fprintf(Dec.fp, "EFF 1 255\n");
}
//---------------------------------------------------------------------------
void Dec0A(void)
{
	u8  a = BitGet8();		// BUFFER
	u16 b = BitGet16();		// LEFT
	u16 c = BitGet16();		// TOP
	u8  d = BitGet8();		// FLAGS1			X2
	u8  e = BitGet8();		// FLAGS2			X2
	u8  f = BitGet8();		// IMAGE
	u8  g = BitGet8();		// MASK_COLOR		X2

//	fprintf(Dec.fp, "SET_BUFFER_PROPERTIES %d %d %d 0x%02X 0x%02X %d 0x%02X", a, b, c, d, e, f, g);

/*
	FLAGS1 xxxx xxxx
              A B CD

	A: スクロール画像有無？
	B: フレーム描画完了後、バッファ0（スクロール画像）で上書き有無？
	C: スクロール処理終了後、フレーム描画の続行有無？
	D: ループ有無
*/

	fprintf(Dec.fp, "BUF %d %d ", a, d);


	u16 s_fr[300], d_fr[300];
	u16 s_wa[300], d_wa[300];
	u16 s_cnt = 0, d_cnt = 0;

	while(BitCur8() != 0x00)
	{
		assert(s_cnt < 300);

		s_fr[s_cnt] = BitGet8();
		s_wa[s_cnt] = BitGet8();
		s_cnt++;
	}

	// 重複フレームのウェイト値を統合します
	s32 i = 0;
	s32 j = 1;
	s32 k;
	bool isHit;

	do {

		while(s_fr[i] == s_fr[j] && j < s_cnt)
		{
			s_wa[i] += s_wa[j];

			j++;
		}

		// ウェイト0 ED62の一か所のみ typo?
		if(s_wa[i] == 0)
		{
			s_wa[i] = 2;

//			printf("typo!\n");
//			assert(0);
		}

		// パーツ画像 or 圧縮画像
		u8 t_wa = (u8)(s_wa[i] * 2.0);

		// 画像パーツリストにあるかチェックをします
		if(Dec.pAnm != NULL)
		{
			for(k=0; k<sizeof waitList / sizeof waitList[0]; k++)
			{
				if(strcmp(waitList[k].p, Dec.pAnm) == 0 && waitList[k].f == s_fr[i])
				{
					t_wa = (u8)(s_wa[i] * waitList[k].w);
					break;
				}
			}
		}

		d_fr[d_cnt] = s_fr[i];
		d_wa[d_cnt] = t_wa;
		d_cnt++;

		i = j;
		j++;

	} while(i < s_cnt);

	fprintf(Dec.fp, "%d", d_cnt);
//	printf("%d\n", d_cnt);

	for(i=0; i<d_cnt; i++)
	{
		fprintf(Dec.fp, " %d %d", d_fr[i], d_wa[i]);
	}
	fprintf(Dec.fp, "\n");

	// skip 0x00
	BitGet8();


/*
	bool isHit;
	s32 cnt = 0;
	s32 i;

	u8 frB[300];
	u8 waB[300];

	while(BitCur8() != 0x00)
	{
		u8 fr = BitGet8();
		u8 wa = BitGet8();

		// パーツ画像の場合、ウェイトを変更します
		isHit = false;

		if(Dec.pAnm != NULL)
		{
			for(i=0; i<sizeof waitList / sizeof waitList[0]; i++)
			{
				if(strcmp(waitList[i].p, Dec.pAnm) == 0 && waitList[i].f == fr)
				{
					isHit = true;

					break;
				}
			}
		}

		frB[cnt] = fr;
		waB[cnt] = (isHit == true) ? (u8)(wa * 2.5) : (u8)(wa * 2.2);
		cnt++;
	}

	// 最大値を登録
	fprintf(Dec.fp, "%d", cnt);
//	printf("%d\n", cnt);

	for(i=0; i<cnt; i++)
	{
		fprintf(Dec.fp, " %d %d", frB[i], waB[i]);
	}
	fprintf(Dec.fp, "\n");

	// skip 0x00
	BitGet8();
*/
}
//---------------------------------------------------------------------------
void Dec0B(void)
{
	u8 a = BitGet8();		// BUFFER

//	fprintf(Dec.fp, "RESET_BUFFER_FLAGS %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec0C(void)
{
	u8 a = BitGet8();		// BUFFER

//	fprintf(Dec.fp, "WAIT_FOR_BUFFER %d\n", a);
	fprintf(Dec.fp, "WAB %d\n", a);
}
//---------------------------------------------------------------------------
void Dec0D(void)
{
	// NONE

//	fprintf(Dec.fp, "RESET_ALL_BUFFER_FLAGS\n");
	fprintf(Dec.fp, "BUA\n");
}
//---------------------------------------------------------------------------
void Dec0E(void)
{
	// NONE

//	fprintf(Dec.fp, "WAIT_FOR_INPUT\n");
	fprintf(Dec.fp, "WAI\n");
}
//---------------------------------------------------------------------------
void Dec0F(void)
{
	// NONE

	fprintf(Dec.fp, "WAIT_FOR_INPUT2\n");
}
//---------------------------------------------------------------------------
void Dec10(void)
{
	u8 a = BitGet8();		// BUFFER

//	fprintf(Dec.fp, "CLEAR_IMAGE_PROPERTIES %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec11(void)
{
	// NONE

	fprintf(Dec.fp, "UNKNOWN_11\n");
}
//---------------------------------------------------------------------------
void Dec12(void)
{
	u8  a = BitGet8();		// BUFFER
	u8  b = BitGet8();		// OFFSET
	u8  c = BitGet8();		// IMAGE
	u16 d = BitGet16();		// LEFT
	u16 e = BitGet16();		// TOP

//	fprintf(Dec.fp, "SET_IMAGE_PROPERTIES %d %d %d %d %d\n", a, b, c, d, e);
//	fprintf(Dec.fp, "BUI %d %d\n", a, b);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec13(void)
{
	u16 a = BitGet16();		// HUNDREDTH_SECONDS

//	fprintf(Dec.fp, "SLEEP %d\n", a);
	fprintf(Dec.fp, "SLP %d\n", a/2);
}
//---------------------------------------------------------------------------
void Dec14(void)
{
	u16 a = BitGet16();		// ADR

//	fprintf(Dec.fp, "JUMP loc_%04X:\n", a);
	fprintf(Dec.fp, "JMP loc_%04X:\n", a);
}
//---------------------------------------------------------------------------
void Dec15(void)
{
	u16 a = BitGet16();		// ADR

//	fprintf(Dec.fp, "ON_INPUT_JUMP loc_%04X:\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec16(void)
{
	u16 a = BitGet16();		// ADR

//	fprintf(Dec.fp, "ON_ESCAPE_JUMP loc_%04X:\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec17(void)
{
	u8  a = BitGet8();		// BUFFER
	u16 b = BitGet16();		// START_X
	u16 c = BitGet16();		// END_X
	u16 d = BitGet16();		// VISIBLE_WIDTH
	u16 e = BitGet16();		// START_Y
	u16 f = BitGet16();		// END_Y
	u16 g = BitGet16();		// VISIBLE_HEIGHT
	u16 h = BitGet16();		// CYCLES

	// fprintf(Dec.fp, "SCROLL_VIEWPORT %d %d %d %d %d %d %d %d\n", a, b, c, d, e, f, g, h);
	// printf("SCROLL_VIEWPORT a:%d b:%d c:%d d:%d e:%d f:%d g:%d h:%d\n", a, b, c, d, e, f, g, h);

	u16 c1 = (b != 0) ? Div(b, 2) : 0;
	u16 c2 = (c != 0) ? Div(c, 2) : 0;
	u16 c3 = (e != 0) ? Div(e, 2) : 0;
	u16 c4 = (f != 0) ? Div(f, 2) : 0;

	if(h == 0)
	{
		if(b > 0)
		{
			// 視点移動（BUF、1:エフェクト番号、x座標、x移動完了値、x移動量）
			fprintf(Dec.fp, "SCR %d 1 %d %d 0\n", a, c1, c2);
		}
		else
		{
			// 視点移動（BUF、2:エフェクト番号、y座標、y移動完了値、y移動量）
			fprintf(Dec.fp, "SCR %d 2 %d %d 0\n", a, c3, c4);
		}
	}
	else if(b != c)
	{
		// 横移動方向
		u16 c5 = (b != 0) ? 1 : 0;
		// 横移動量
		u16 c6 = Div(c1+c2, h/2);

		if(c6 == 0) c6 = 1;

		// スクロール（BUF、5:左右、6:右左のエフェクト番号、x座標、x移動完了値、x移動量
		fprintf(Dec.fp, "SCR %d %d %d %d %d\n", a, 5 + c5, c1, c2, c6);
	}
	else
	{
		// 縦移動方向
		u16 c5 = (e != 0) ? 1 : 0;
		// 縦移動量
		u16 c6 = Div(c3+c4, h/2);

		if(c6 == 0) c6 = 1;

		// スクロール（BUF、3:上下、4:下上のエフェクト番号、y座標、y移動完了値、y移動量
		fprintf(Dec.fp, "SCR %d %d %d %d %d\n", a, 3 + c5, c3, c4, c6);
	}
}
//---------------------------------------------------------------------------
void Dec18(void)
{
	u8 a = BitGet8();		// BUFFER

//	fprintf(Dec.fp, "WAIT_FOR_SCROLL %d\n", a);
	fprintf(Dec.fp, "WAS %d\n", a);
}
//---------------------------------------------------------------------------
void Dec19(void)
{
	u8 a = BitGet8();		// LOOP
	u8 b = BitGet8();		// STEAM

//	fprintf(Dec.fp, "PLAY_MIDI %d %d\n", a, b);
	fprintf(Dec.fp, "BGM %d %d\n", b, a);
}
//---------------------------------------------------------------------------
void Dec1A(void)
{
	// NONE

//	fprintf(Dec.fp, "STOP_MIDI\n");
	fprintf(Dec.fp, "BGS\n");
}
//---------------------------------------------------------------------------
void Dec1B(void)
{
	u8    a = BitGet8();		// STREAM
	char* s = BitGetStr();		// FILE

//	fprintf(Dec.fp, "LOAD_MIDI %d %s\n", a, s);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec1C(void)
{
	// NONE

	fprintf(Dec.fp, "UNKNOWN_1C\n");
}
//---------------------------------------------------------------------------
void Dec1D(void)
{
	u8    a = BitGet8();		// STREAM
	char* s = BitGetStr();		// FILE

	// PCM or PCMSE
	if(s[3] == '\\')
	{
		s += 4;
	}
	else
	{
		s += 6;
	}


//	fprintf(Dec.fp, "PLAY_PCM %d %s\n", a, s);
	fprintf(Dec.fp, "PCM %s 2 %d\n", s , a);		// 2はadjustパラメータ（一部、正規表現で修正）
}
//---------------------------------------------------------------------------
void Dec1E(void)
{
	// NONE

//	fprintf(Dec.fp, "STOP_PCM\n");
	fprintf(Dec.fp, "PCS\n");
}
//---------------------------------------------------------------------------
void Dec1F(void)
{
	// NONE

//	fprintf(Dec.fp, "STOP_PCM_ON_NEXT_REFRESH\n");
	fprintf(Dec.fp, "PCN\n");
}
//---------------------------------------------------------------------------
void Dec20(void)
{
	u16 a = BitGet16();		// LEFT
	u16 b = BitGet16();		// TOP
	u8  c = BitGet8();		// CHARS
	u8  d = BitGet8();		// LINES

//	fprintf(Dec.fp, "SET_TEXT_AREA %d %d %d %d\n", a, b, c, d);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec21(void)
{
	char* s = BitGetStr();	// TEXT

//	fprintf(Dec.fp, "DISPLAY_TEXT %s\n", s);

	if((u8)(s[0]) == 0x81 && (u8)(s[1]) == 0x4F)
	{
		fprintf(Dec.fp, "TXC\n");

		return;
	}

//	printf("pos:%X\n", );

	// 特殊メッセージ（ＨＰ表示）はテキスト化させない
	if(Bit.pos == 0xAF25 || Bit.pos == 0xAF37 || Bit.pos == 0xAF49)
	{
		return;
	}


	s32 x = 0;
	s32 y = 0;
	s32 t = 0;
	s32 i;

	fprintf(Dec.fp, "TXT ");

	while(s[t] != '\0')
	{
		assert(y < 3);

		u16 code;
		code  = (u8)(s[t++]) << 8;
		code |= (u8)(s[t++]);

		if(code == 0x0101)
		{
			fprintf(Dec.fp, "あきら：");
			x += 4;
		}
		else if(code == 0x0102)
		{
			fprintf(Dec.fp, "かりん：");
			x += 4;
		}
		else if(code == 0x0103)
		{
			fprintf(Dec.fp, "サキ　：");
			x += 4;
		}
		else if(code == 0x0104)
		{
			fprintf(Dec.fp, "ボス　：");
			x += 4;
		}
		else if(code == 0x0105)
		{
			fprintf(Dec.fp, "手下Ａ：");
			x += 4;
		}
		else if(code == 0x0106)
		{
			fprintf(Dec.fp, "手下Ｂ：");
			x += 4;
		}
		else if(code == 0x0107)
		{
			fprintf(Dec.fp, "手下達：");
			x += 4;
		}
		else if(code == 0x0108)
		{
			assert(0);
		}
		else if(code == 0x818F)
		{
			// 改行「￥」
			for(i=x; i<30; i++)
			{
				fprintf(Dec.fp, "　");
			}
			x = 0;
			y++;
		}
		else
		{
			// 文字
			fprintf(Dec.fp, "%c%c", (code >> 8) & 0xff, code & 0xff);
			x++;
		}

		if(x >= 30)
		{
			x = 0;
			y++;
		}
	}
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec22(void)
{
	u8 a = BitGet8();		// PIXELS

//	fprintf(Dec.fp, "SET_TEXT_INDENT %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec23(void)
{
	u8 a = BitGet8();		// HEIGHT

//	fprintf(Dec.fp, "SET_FONT_SIZE %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec24(void)
{
	u8    a = BitGet8();		// TOKEN
	char* s = BitGetStr();		// TEXT

//	fprintf(Dec.fp, "SET_TEXT_TOKEN %d %s\n", a, s);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec25(void)
{
	u16 a = BitGet16();		// ADR

//	fprintf(Dec.fp, "CALL loc_%04X:\n", a);
	fprintf(Dec.fp, "CAL loc_%04X:\n", a);
}
//---------------------------------------------------------------------------
void Dec26(void)
{
	// NONE

//	fprintf(Dec.fp, "RETURN\n");
	fprintf(Dec.fp, "RET\n");
}
//---------------------------------------------------------------------------
void Dec27(void)
{
	u8 a = BitGet8();		// VALUE

	fprintf(Dec.fp, "SET_FULL_SCREEN_MODE %d\n", a);
}
//---------------------------------------------------------------------------
void Dec28(void)
{
	u8  a = BitGet8();		// EFFECT
	u16 b = BitGet16();		// CYCLES
	u8  c = BitGet8();		// COLORS
	s32 i;

	if(b != 0) b = Div(b, 24);

//	fprintf(Dec.fp, "MODIFY_PALETTE_WITH_EFFECT %d %d %d", a, b, c);
	fprintf(Dec.fp, "PAF %d %d", b, c);
//	printf("%d\n", c);

	// PALETTE
	for(i=0; i<c; i++)
	{
		u8 d = BitGet8();	// INDEX
		u8 e = BitGet8();	// BLUE
		u8 f = BitGet8();	// GREEN
		u8 g = BitGet8();	// RED

		fprintf(Dec.fp, " %d %d %d %d", d, e/8, f/8, g/8);
	}

	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec29(void)
{
	u16 a = BitGet16();		// ADR

//	fprintf(Dec.fp, "ENABLE_EXIT_MENU loc_%04X:\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec2A(void)
{
	// NONE

//	fprintf(Dec.fp, "DISABLE_EXIT_MENU\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec2B(void)
{
	u16 a = BitGet16();		// ADR

//	fprintf(Dec.fp, "ENABLE_LOAD_MENU loc_%04X:\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec2C(void)
{
	// NONE

//	fprintf(Dec.fp, "DISABLE_LOAD_MENU\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec2D(void)
{
	// NONE

//	fprintf(Dec.fp, "CLEAR_ON_JUMPS\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec2E(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL
	u16 c = BitGet16();		// ADR

//	fprintf(Dec.fp, "JUMP_IF_REGISTER_EQUAL %d %d loc_%04X:\n", a, b, c);
	fprintf(Dec.fp, "IFR %d %d loc_%04X:\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec2F(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL
	u16 c = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_REGISTER_NOT_EQUAL %d %d loc_%04X:\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec30(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL
	u16 c = BitGet16();		// ADR

//	fprintf(Dec.fp, "JUMP_IF_REGISTER_LESS_THAN_OR_EQUAL %d %d loc_%04X:\n", a, b, c);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec31(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL
	u16 c = BitGet16();		// ADR

//	fprintf(Dec.fp, "JUMP_IF_REGISTER_GREATER_THAN_OR_EQUAL %d %d loc_%04X:\n", a, b, c);
	fprintf(Dec.fp, "IFG %d %d loc_%04X:\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec32(void)
{
	u8 a = BitGet8();		// REG

//	fprintf(Dec.fp, "READ %d\n", a);
	fprintf(Dec.fp, "VRR %d\n", a);
}
//---------------------------------------------------------------------------
void Dec33(void)
{
	u16 a = BitGet16();		// VAL
	u16 b = BitGet16();		// ADR

//	fprintf(Dec.fp, "JUMP_IF_LAST_READ_NOT_EQUAL %d loc_%04X:\n", a, b);
	fprintf(Dec.fp, "IFL %d loc_%04X:\n", a, b);
}
//---------------------------------------------------------------------------
void Dec34(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL

//	fprintf(Dec.fp, "WRITE %d %d\n", a, b);
	fprintf(Dec.fp, "VRW %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec35(void)
{
	u8 a = BitGet8();		// REG

	fprintf(Dec.fp, "INC %d\n", a);
}
//---------------------------------------------------------------------------
void Dec36(void)
{
	u8 a = BitGet8();		// REG

	fprintf(Dec.fp, "DEC %d\n", a);
}
//---------------------------------------------------------------------------
void Dec37(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL

	fprintf(Dec.fp, "ADD %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec38(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL

//	fprintf(Dec.fp, "OR %d %d\n", a, b);
	fprintf(Dec.fp, "OR0 %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec39(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// VAL

	fprintf(Dec.fp, "AND %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec3A(void)
{
	u16 a = BitGet16();		// CYCLES

	fprintf(Dec.fp, "FADE_OUT_PALETTE %d\n", a);
}
//---------------------------------------------------------------------------
void Dec3B(void)
{
	// NONE

//	fprintf(Dec.fp, "LOAD_STATE\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec3C(void)
{
	// NONE
//	fprintf(Dec.fp, "SAVE_STATE\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec3D(void)
{
	u16 a = BitGet16();		// LEFT
	u16 b = BitGet16();		// TOP
	u16 c = BitGet16();		// WIDTH
	u16 d = BitGet16();		// HEIGHT

//	fprintf(Dec.fp, "PAINT_BLACK_RECT %d %d %d %d\n", a, b, c, d);
	fprintf(Dec.fp, "EFF 5 0\n");
}
//---------------------------------------------------------------------------
void Dec3E(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// LEFT
	u16 c = BitGet16();		// TOP
	u8  d = BitGet8();		// CHARS
	u8  e = BitGet8();		// CHOICES
	s32 i;

//	fprintf(Dec.fp, "DISPLAY_HOT_ZONE_TEXT %d %d %d %d %d", a, b, c, d, e);
	fprintf(Dec.fp, "SEL %d %d", a, e);

	// TEXT
	for(i=0; i<e; i++)
	{
		char* s = BitGetStr();

		fprintf(Dec.fp, " %s", s);
	}

	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec3F(void)
{
	u8 a = BitGet8();		// TYPE

//	fprintf(Dec.fp, "SET_HOT_ZONE_SEPERATOR %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec40(void)
{
	u8 a = BitGet8();		// ENABLE

//	fprintf(Dec.fp, "SET_SAVE_MENU_ENABLED %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec41(void)
{
	u8  a = BitGet8();		// COLORS
	s32 i;

//	fprintf(Dec.fp, "MODIFY_PALETTE %d", a);
	fprintf(Dec.fp, "PAE %d", a);
//	printf("%d\n");

	// PALETTE
	for(i=0; i<a; i++)
	{
		u8 b = BitGet8();	// INDEX
		u8 c = BitGet8();	// BLUE
		u8 d = BitGet8();	// GREEN
		u8 e = BitGet8();	// RED

		fprintf(Dec.fp, " %d %d %d %d", b, c/8, d/8, e/8);
	}

	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec42(void)
{
	// NONE

//	fprintf(Dec.fp, "WAIT_FOR_INPUT_OR_PCM\n");
	fprintf(Dec.fp, "WAP\n");
}
//---------------------------------------------------------------------------
void Dec43(void)
{
	u16 a = BitGet16();		// REG

//	fprintf(Dec.fp, "SET_THREAD_SYNC_FREQ %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec44(void)
{
	// NONE

	fprintf(Dec.fp, "WAIT_FOR_DPAD_INPUT\n");
}
//---------------------------------------------------------------------------
void Dec45(void)
{
	u8 a = BitGet8();		// REG

	fprintf(Dec.fp, "WRITE_DPAD_DIR %d\n", a);
}
//---------------------------------------------------------------------------
void Dec46(void)
{
	// NONE

	fprintf(Dec.fp, "WAIT_FOR_DPAD_RELEASE\n");
}
//---------------------------------------------------------------------------
void Dec47(void)
{
	u8 a = BitGet8();		// BYTE

	fprintf(Dec.fp, "RESET_SYSTEM_STATE %d\n", a);
}
//---------------------------------------------------------------------------
void Dec48(void)
{
	u16 a = BitGet16();		// VAL
	u16 b = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_LAST_READ_AND_VALUE_EQUALS_ZERO %d loc_%04X:\n", a, b);
}
//---------------------------------------------------------------------------
void Dec49(void)
{
	u8 a = BitGet8();		// BUF
	u8 b = BitGet8();		// OFFSET
	u8 c = BitGet8();		// REG

	fprintf(Dec.fp, "WRITE_BUFFER_PROP_VALUE %d %d %d\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec4A(void)
{
	char* s = BitGetStr();	// FILE

//	fprintf(Dec.fp, "LOAD_WIN %s\n", s);
	fprintf(Dec.fp, "WIN %s\n", s);
}
//---------------------------------------------------------------------------
void Dec4B(void)
{
	u16 a = BitGet16();		// LEFT
	u16 b = BitGet16();		// TOP

//	fprintf(Dec.fp, "SET_CARET_POS %d %d\n", a, b);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec4C(void)
{
	u16 a = BitGet16();		// START_X
	u16 b = BitGet16();		// END_X
	u16 c = BitGet16();		// START_Y
	u16 d = BitGet16();		// END_Y

//	fprintf(Dec.fp, "MODIFY_SCROLL_PROPERTIES %d %d %d %d\n", a, b, c, d);
	fprintf(Dec.fp, "SCM %d %d\n", c/2, d/2);
}
//---------------------------------------------------------------------------
void Dec4D(void)
{
	// NONE

//	fprintf(Dec.fp, "DISABLE_ANIM_PAUSE\n");
	fprintf(Dec.fp, "ANI\n");
}
//---------------------------------------------------------------------------
void Dec4E(void)
{
	// NONE

//	fprintf(Dec.fp, "ENABLE_ANIM_PAUSE\n");
	fprintf(Dec.fp, "ANE\n");
}
//---------------------------------------------------------------------------
void Dec4F(void)
{
	u8 a = BitGet8();		// IMAGE

//	fprintf(Dec.fp, "WAIT_FOR_BUFFER_WITH_SYNC %d\n", a);
	fprintf(Dec.fp, "WAY %d\n", a);
}
//---------------------------------------------------------------------------
void Dec50(void)
{
	u8  a = BitGet8();		// RED
	u8  b = BitGet8();		// GREEN
	u8  c = BitGet8();		// BLUE
	u16 d = BitGet16();		// CYCLES

//	fprintf(Dec.fp, "FADE_IN_RGB %d %d %d %d\n", a, b, c, d);

	// 戦闘復帰のフェードインのみ対応
	if(d == 6)
	{
		fprintf(Dec.fp, "EFF 4 0\n");
	}
	else
	{
		fprintf(Dec.fp, "\n");
	}
}
//---------------------------------------------------------------------------
void Dec51(void)
{
	u8  a = BitGet8();		// RED
	u8  b = BitGet8();		// GREEN
	u8  c = BitGet8();		// BLUE
	u16 d = BitGet16();		// CYCLES

//	fprintf(Dec.fp, "FADE_OUT_RGB %d %d %d %d\n", a, b, c, d);

	// FADE_OUT_RGB 255 255 255 12　エフェクトで代用
	fprintf(Dec.fp, "EFF 3 %d\n", Div(d, 12));
}
//---------------------------------------------------------------------------
void Dec52(void)
{
	u8 a = BitGet8();		// VAL

//	fprintf(Dec.fp, "SET_SHIMMER %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec53(void)
{
	u16 a = BitGet16();		// ADR

//	fprintf(Dec.fp, "ENABLE_REPEAT_MENU loc_%04X:\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec54(void)
{
	// NONE

//	fprintf(Dec.fp, "DISABLE_REPEAT_MENU\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec55(void)
{
	u8 a = BitGet8();		// TO
	u8 b = BitGet8();		// FROM

//	fprintf(Dec.fp, "SET_VISIBLE_PALETTE_RANGE %d %d\n", a, b);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec56(void)
{
	char* s = BitGetStr();	// REGKEY

//	fprintf(Dec.fp, "LOAD_ADVANCED_STATE %s\n", s);
}
//---------------------------------------------------------------------------
void Dec57(void)
{
	char* s = BitGetStr();	// REGKEY

//	fprintf(Dec.fp, "SAVE_ADVANCED_STATE %s\n", s);
}
//---------------------------------------------------------------------------
void Dec58(void)
{
	u8 a = BitGet8();		// TO
	u8 b = BitGet8();		// FROM

//	fprintf(Dec.fp, "COPY %d %d\n", a, b);
	fprintf(Dec.fp, "CPY %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec59(void)
{
	u16 a = BitGet16();		// BUFFER
	u16 b = BitGet16();		// START
	u16 c = BitGet16();		// END
	u16 d = BitGet16();		// DELTA_X
	u16 e = BitGet16();		// DELTA_Y
	u16 f = BitGet16();		// DIVISOR

	fprintf(Dec.fp, "SCROLL_MAP %d %d %d %d %d %d\n", a, b, c, d, e, f);
}
//---------------------------------------------------------------------------
void Dec5A(void)
{
	u8 a = BitGet8();		// BUFFER

	fprintf(Dec.fp, "WAIT_FOR_MAP %d\n", a);
}
//---------------------------------------------------------------------------
void Dec5B(void)
{
	u8  a = BitGet8();		// INDEX
	u8  b = BitGet8();		// COUNT
	s32 i;

	fprintf(Dec.fp, "DEFINE_MAP_PATH %d %d", a, b);

	// ARRAY
	for(i=0; i<b; i++)
	{
		u8 c = BitGet8();
		u8 d = BitGet8();

		fprintf(Dec.fp, " %d.%d", c, d);
	}

	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec5C(void)
{
	u8 a = BitGet8();		// BUF

	fprintf(Dec.fp, "FORCE_FINISH_SCROLL %d\n", a);
}
//---------------------------------------------------------------------------
void Dec5D(void)
{
	u8 a = BitGet8();		// VOL

//	fprintf(Dec.fp, "SET_MIDI_VOLUME %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec5E(void)
{
	u16 a = BitGet16();		// CYCLES

//	fprintf(Dec.fp, "FADE_OUT_MIDI %d\n", a);
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec5F(void)
{
	// NONE

//	fprintf(Dec.fp, "NOP\n");
	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec60(void)
{
	u8  a = BitGet8();		// VOL
	u16 b = BitGet16();		// CYCLES

	fprintf(Dec.fp, "FADE_MIDI %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec61(void)
{
	u8  a = BitGet8();		// BUF
	u16 b = BitGet16();		// LEFT
	u16 c = BitGet16();		// TOP
	u16 d = BitGet16();		// WIDTH
	u16 e = BitGet16();		// HEIGHT

	fprintf(Dec.fp, "SET_ADVANCED_IMAGE_PROPS %d %d %d %d %d\n", a, b, c, d, e);
}
//---------------------------------------------------------------------------
void Dec62(void)
{
	u8 a = BitGet8();		// VAL

	fprintf(Dec.fp, "SET_DIALOG_MODE %d\n", a);

}
//---------------------------------------------------------------------------
void Dec63(void)
{
	u8 a = BitGet8();		// STREAM

	fprintf(Dec.fp, "SET_MAX_ENABLED_PCM_STREAM %d\n", a);
}
//---------------------------------------------------------------------------
void Dec64(void)
{
	u8  a = BitGet8();		// COLORS
	s32 i;

	fprintf(Dec.fp, "PALETTE_SHIFT %d", a);

	// ARRAY
	for(i=0; i<a; i++)
	{
		u8 b = BitGet8();	// INDEX
		u8 c = BitGet8();	// BLUE
		u8 d = BitGet8();	// GREEN
		u8 e = BitGet8();	// RED

		fprintf(Dec.fp, " %d %d %d %d", b, c, d, e);
	}

	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec65(void)
{
	u8 a = BitGet8();		// STREAM

	fprintf(Dec.fp, "ENABLE_MAX_CD_AUDIO_STREAM %d\n", a);
}
//---------------------------------------------------------------------------
void Dec66(void)
{
	u8 a = BitGet8();		// BUF

	fprintf(Dec.fp, "SET_BUFFER_MOUSE_MOVED_VALUE %d\n", a);
}
//---------------------------------------------------------------------------
void Dec67(void)
{
	// NONE

	fprintf(Dec.fp, "ENABLE_LANGUAGE_MENU\n");
}
//---------------------------------------------------------------------------
void Dec68(void)
{
	u16 a = BitGet16();		// LINE

	fprintf(Dec.fp, "DISPLAY_TEXT_FROM_FILE %d\n", a);
}
//---------------------------------------------------------------------------
void Dec69(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// LEFT
	u16 c = BitGet16();		// TOP
	u8  d = BitGet8();		// CHOICE
	s32 i;

	fprintf(Dec.fp, "DISPLAY_HOT_ZONE_TEXT_FROM_FILE %d %d %d %d", a, b, c, d);

	// LINES
	for(i=0; i<d; i++)
	{
		char* s = BitGetStr();

		fprintf(Dec.fp, " %s", s);
	}

	fprintf(Dec.fp, "\n");
}
//---------------------------------------------------------------------------
void Dec6A(void)
{
	u8  a = BitGet8();		// REG
	u16 b = BitGet16();		// MOD

	fprintf(Dec.fp, "WRITE_RANDOM %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec6B(void)
{
	u8    a = BitGet8();		// STREAM
	u16   b = BitGet16();		// TENTH_SECONDS
	char* s = BitGetStr();		// FILE

	fprintf(Dec.fp, "LOAD_PCM_WITH_DELAY %d %d %s\n", a, b, s);
}
//---------------------------------------------------------------------------
void Dec6C(void)
{
	u8 a = BitGet8();		// INFINITE

	fprintf(Dec.fp, "REPEAT_PCM %d\n", a);
}
//---------------------------------------------------------------------------
void Dec6D(void)
{
	u8  a = BitGet8();		// BUF
	u16 b = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_BUFFER_FLAGS_NOT_ZERO %d loc_%04X:\n", a, b);
}
//---------------------------------------------------------------------------
void Dec6E(void)
{
	u8 a = BitGet8();		// REG
	u8 b = BitGet8();		// BUF

	fprintf(Dec.fp, "READ_BUFFER_FLAGS %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec6F(void)
{
	u8  a = BitGet8();		// REG
	u8  b = BitGet8();		// BUF
	u16 c = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_REGISTER1_EQUALS_REGISTER2 %d %d loc_%04X:\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec70(void)
{
	u8  a = BitGet8();		// REG1
	u8  b = BitGet8();		// REG2
	u16 c = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_REGISTER1_NOT_EQUAL_REGISTER2 %d %d loc_%04X:\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec71(void)
{
	u8  a = BitGet8();		// REG1
	u8  b = BitGet8();		// REG2
	u16 c = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_REGISTER1_LESS_THAN_OR_EQUAL_REGISTER2 %d %d loc_%04X:\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec72(void)
{
	u8  a = BitGet8();		// REG1
	u8  b = BitGet8();		// REG2
	u16 c = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_REGISTER1_GREATER_THAN_OR_EQUAL_REGISTER2 %d %d loc_%04X:\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec73(void)
{
	char* s = BitGetStr();	// TEXT

	fprintf(Dec.fp, "DISPLAY_FREE_FLOATING_TEXT %s\n", s);
}
//---------------------------------------------------------------------------
void Dec74(void)
{
	u8 a = BitGet8();		// RED
	u8 b = BitGet8();		// GREEN
	u8 c = BitGet8();		// BLUE

	fprintf(Dec.fp, "SET_FREE_FLOATING_TEXT_COLOR %d %d %d\n", a, b, c);
}
//---------------------------------------------------------------------------
void Dec75(void)
{
	u16 a = BitGet16();		// LEFT
	u16 b = BitGet16();		// TOP

	fprintf(Dec.fp, "SET_FREE_FLOATING_TEXT_POSITION %d %d\n", a, b);
}
//---------------------------------------------------------------------------
void Dec76(void)
{
	// NONE

	fprintf(Dec.fp, "SHOW_NAME_ENTRY_DIALOG\n");
}
//---------------------------------------------------------------------------
void Dec77(void)
{
	// NONE

	fprintf(Dec.fp, "UNKNOWN_77\n");
}
//---------------------------------------------------------------------------
void Dec78(void)
{
	u8 a = BitGet8();		// DISABLE

	fprintf(Dec.fp, "SET_PCM_SKIPPING_MODE %d\n", a);
}
//---------------------------------------------------------------------------
void Dec79(void)
{
	u8 a = BitGet8();		// REG

	fprintf(Dec.fp, "SET_CHARACTER_FACING_FROM_REGISTER %d\n", a);
}
//---------------------------------------------------------------------------
void Dec7A(void)
{
	u16 a = BitGet16();		// VAL
	u16 b = BitGet16();		// ADR

	fprintf(Dec.fp, "JUMP_IF_LAST_READ_AND_VALUE_NOT_EQUAL_ZERO %d loc_%04X:\n", a, b);
}
//---------------------------------------------------------------------------
void Dec7B(void)
{
	u16   a = BitGet16();		// LEFT
	u16   b = BitGet16();		// TOP
	char* s = BitGetStr();		// FILE

	fprintf(Dec.fp, "DRAW_BMP %d %d %s\n", a, b, s);
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("win2txt [WIN File]\n");

		exit(0);
	}

	printf("win2txt... %s\n", argv[1]);

	BitCalloc(argv[1]);


	char rname[30];
	strncpy(rname, argv[1], 20);

	char* p = strchr(rname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '.';
	p[1] = 't';
	p[2] = 'x';
	p[3] = 't';
	p[4] = '\0';

	Dec.fp = fopen(rname, "wb");

	if(Dec.fp == NULL)
	{
		fprintf(stderr, "couldn't open txt file\n");

		exit(1);
	}


	u8 op;

  	while(Bit.pos < Bit.size)
	{
		fprintf(Dec.fp, "%04X: ", Bit.pos);
//		printf("%04X:\n", Bit.pos);
		op = BitGet8();

		switch(op)
		{
		case 0x00: Dec00(); break;
		case 0x01: Dec01(); break;
		case 0x02: Dec02(); break;
		case 0x03: Dec03(); break;
		case 0x04: Dec04(); break;
		case 0x05: Dec05(); break;
		case 0x06: Dec06(); break;
		case 0x07: Dec07(); break;
		case 0x08: Dec08(); break;
		case 0x09: Dec09(); break;
		case 0x0A: Dec0A(); break;
		case 0x0B: Dec0B(); break;
		case 0x0C: Dec0C(); break;
		case 0x0D: Dec0D(); break;
		case 0x0E: Dec0E(); break;
		case 0x0F: Dec0F(); break;
		case 0x10: Dec10(); break;
		case 0x11: Dec11(); break;
		case 0x12: Dec12(); break;
		case 0x13: Dec13(); break;
		case 0x14: Dec14(); break;
		case 0x15: Dec15(); break;
		case 0x16: Dec16(); break;
		case 0x17: Dec17(); break;
		case 0x18: Dec18(); break;
		case 0x19: Dec19(); break;
		case 0x1A: Dec1A(); break;
		case 0x1B: Dec1B(); break;
		case 0x1C: Dec1C(); break;
		case 0x1D: Dec1D(); break;
		case 0x1E: Dec1E(); break;
		case 0x1F: Dec1F(); break;
		case 0x20: Dec20(); break;
		case 0x21: Dec21(); break;
		case 0x22: Dec22(); break;
		case 0x23: Dec23(); break;
		case 0x24: Dec24(); break;
		case 0x25: Dec25(); break;
		case 0x26: Dec26(); break;
		case 0x27: Dec27(); break;
		case 0x28: Dec28(); break;
		case 0x29: Dec29(); break;
		case 0x2A: Dec2A(); break;
		case 0x2B: Dec2B(); break;
		case 0x2C: Dec2C(); break;
		case 0x2D: Dec2D(); break;
		case 0x2E: Dec2E(); break;
		case 0x2F: Dec2F(); break;
		case 0x30: Dec30(); break;
		case 0x31: Dec31(); break;
		case 0x32: Dec32(); break;
		case 0x33: Dec33(); break;
		case 0x34: Dec34(); break;
		case 0x35: Dec35(); break;
		case 0x36: Dec36(); break;
		case 0x37: Dec37(); break;
		case 0x38: Dec38(); break;
		case 0x39: Dec39(); break;
		case 0x3A: Dec3A(); break;
		case 0x3B: Dec3B(); break;
		case 0x3C: Dec3C(); break;
		case 0x3D: Dec3D(); break;
		case 0x3E: Dec3E(); break;
		case 0x3F: Dec3F(); break;
		case 0x40: Dec40(); break;
		case 0x41: Dec41(); break;
		case 0x42: Dec42(); break;
		case 0x43: Dec43(); break;
		case 0x44: Dec44(); break;
		case 0x45: Dec45(); break;
		case 0x46: Dec46(); break;
		case 0x47: Dec47(); break;
		case 0x48: Dec48(); break;
		case 0x49: Dec49(); break;
		case 0x4A: Dec4A(); break;
		case 0x4B: Dec4B(); break;
		case 0x4C: Dec4C(); break;
		case 0x4D: Dec4D(); break;
		case 0x4E: Dec4E(); break;
		case 0x4F: Dec4F(); break;
		case 0x50: Dec50(); break;
		case 0x51: Dec51(); break;
		case 0x52: Dec52(); break;
		case 0x53: Dec53(); break;
		case 0x54: Dec54(); break;
		case 0x55: Dec55(); break;
		case 0x56: Dec56(); break;
		case 0x57: Dec57(); break;
		case 0x58: Dec58(); break;
		case 0x59: Dec59(); break;
		case 0x5A: Dec5A(); break;
		case 0x5B: Dec5B(); break;
		case 0x5C: Dec5C(); break;
		case 0x5D: Dec5D(); break;
		case 0x5E: Dec5E(); break;
		case 0x5F: Dec5F(); break;
		case 0x60: Dec60(); break;
		case 0x61: Dec61(); break;
		case 0x62: Dec62(); break;
		case 0x63: Dec63(); break;
		case 0x64: Dec64(); break;
		case 0x65: Dec65(); break;
		case 0x66: Dec66(); break;
		case 0x67: Dec67(); break;
		case 0x68: Dec68(); break;
		case 0x69: Dec69(); break;
		case 0x6A: Dec6A(); break;
		case 0x6B: Dec6B(); break;
		case 0x6C: Dec6C(); break;
		case 0x6D: Dec6D(); break;
		case 0x6E: Dec6E(); break;
		case 0x6F: Dec6F(); break;
		case 0x70: Dec70(); break;
		case 0x71: Dec71(); break;
		case 0x72: Dec72(); break;
		case 0x73: Dec73(); break;
		case 0x74: Dec74(); break;
		case 0x75: Dec75(); break;
		case 0x76: Dec76(); break;
		case 0x77: Dec77(); break;
		case 0x78: Dec78(); break;
		case 0x79: Dec79(); break;
		case 0x7A: Dec7A(); break;
		case 0x7B: Dec7B(); break;
		default:
			printf("error op=%02X pos=%X \n", op, Bit.pos);
			assert(0);
			break;
		}
	}

	fclose(Dec.fp);

	BitFree();

	return 0;
}
