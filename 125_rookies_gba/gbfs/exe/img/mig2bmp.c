// PC98 Rookies(海月製作所) MIG2BMP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>

// gcc mig2bmp.c -o mig2bmp

//---------------------------------------------------------------------------
#define MAX_LINE			 10
#define MAX_CX				640

typedef unsigned char		 u8;
typedef char				 s8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		u32;
typedef int					s32;

typedef struct {
	u8 by[2];
} ST_DOT;

typedef struct {
	ST_DOT bx[MAX_CX];
} ST_LINE;

typedef struct {
	s32  cx;
	s32  cy;
	u8   r[16];
	u8   g[16];
	u8   b[16];

	// 画像データの解凍作業用
	s32  x;
	s32  y;
	u8*  pDat;

	// 10ライン分のバッファ
	ST_LINE line[MAX_LINE];	

	// ビット操作用
	u8    chr;
	s32   bitp;

} ST_MIG;


//---------------------------------------------------------------------------
s32 data_b_1004[][2] = {
	{  0,   0}, { -2,   0}, {  0,  -1}, {  2,  -1},
	{ -2,  -1}, {  4,  -1}, {  2,  -2}, { -4,  -1},
	{ -2,  -2}, {  0,  -2}, {  0,  -8}, { -6,  -1},
	{  6,  -1}, {-16,   0}, {  8,  -2}, { -4,   0},
};

s32 data_b_1024[][2] = {
	{  3,   1}, {  4,   2}, {  5,   6}, {  7,   8},
	{  9,  10}, { -9,  11}, { 12,  13}, { -1,  -2},
	{ -3,  -4}, { -5,  -6}, { -7,  -8}, {-10, -11},
	{-12, -13}, {-14, -15},
};

s32 data_b_105C[][2] = {
	{ 26,   1}, {  3,   2}, { -3,   4}, {  8,   6},
	{ -4,   5}, { 10,   7}, { 14,   9}, { 29,  13},
	{ -5,  11}, { -7,  15}, { 16,  12}, { -6,  27},
	{-17,  22}, { 21,  17}, { -8,  28}, { 30,  18},
	{ 19,  20}, { 36,  25}, { 31,  32}, {-19,  33},
	{-20,  34}, {-21,  35}, { 23,  24}, { 37,  38},
	{ 39,  40}, { 41,  42}, { -1,  -2}, { -9, -10},
	{-11, -12}, {-13, -14}, {-15, -16}, {-18, -44},
	{-22, -23}, {-24, -25}, {-26, -27}, {-28, -29},
	{-30, -31}, {-32, -33}, {-34, -35}, {-36, -37},
	{-38, -39}, {-40, -41}, {-42, -43},
};

s32 data_b_1108[][2] = {
	{  0,   1}, { -1,   2}, { -2,   3}, { 11,   4},
	{ -3,   5}, { -6,   6}, {  7,   8}, { -7,   9},
	{ -8,  10}, { -9,  12}, {-10,  13}, { -4,  -5},
	{-11,  14}, {-12, -15}, {-13, -14},
};

s32 col_tab[16][16] = {
	{ 0, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1},
	{ 1,  0, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2},
	{ 2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3},
	{ 3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4},
	{ 4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5},
	{ 5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6},
	{ 6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8,  7},
	{ 7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9,  8},
	{ 8,  7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10,  9},
	{ 9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11, 10},
	{10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12, 11},
	{11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13, 12},
	{12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 15, 14, 13},
	{13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 15, 14},
	{14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0, 15},
	{15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
};


ST_MIG Mig;

//---------------------------------------------------------------------------
s32 getbit(FILE* fp)
{
	if(Mig.bitp <= 0)
	{
		Mig.bitp = 8;
		fread(&Mig.chr, 1, 1, fp);
	}

	s32 p = --Mig.bitp;
	return (Mig.chr & (1 << p)) ? 1 : 0;
}
//---------------------------------------------------------------------------
s32 getbits(FILE* fp, s32 a1)
{
	s32 r = 0;
	s32 i;

	for(i=0; i<a1; i++)
	{
		r <<= 1;
		r += getbit(fp);
	}

	return r;
}
//---------------------------------------------------------------------------
s32 poi(FILE* fp, s32 (*p)[2])
{
	s32 c;
	s32 cur  = 0;
	s32 next = 0;

	while(1)
	{
		c = getbit(fp);
		next = p[cur][c];

		if(next <= 0)
		{
			return -next;
		}

		cur = next;
	}
}
//---------------------------------------------------------------------------
void rotate_row(s32 p, s32 q)
{
	s32 c = col_tab[p][q];
	s32 i;

	for(i=q; i>1; i--)
	{
		col_tab[p][i] = col_tab[p][i-1];
	}

	col_tab[p][1] = c;
}
//---------------------------------------------------------------------------
s32 one_token(FILE* fp, s32 s)
{
	s32 c = poi(fp, data_b_1108);
	s32 r;

	if(c == 0)
	{
		r = s;
	}
	else
	{
		rotate_row(s, c);
		r = col_tab[s][1];
	}

	return r;
}
//---------------------------------------------------------------------------
void expand_2x2(FILE* fp)
{
	s32 p;
	ST_DOT left, upper_l, upper_r, cur_l, cur_r;

	if(Mig.x == 0)
	{
		left = Mig.line[1].bx[Mig.cx - 1];
	}
	else
	{
		left = Mig.line[0].bx[Mig.x - 1];
	}

	upper_l = Mig.line[1].bx[Mig.x + 0];
	upper_r = Mig.line[1].bx[Mig.x + 1];

	if(upper_l.by[0] == upper_l.by[1])
	{
		p = upper_l.by[0];
	}
	else
	{
		p = left.by[0];
	}

	cur_l.by[0] = one_token(fp, p);

	if(upper_r.by[0] == upper_r.by[1])
	{
		p = upper_r.by[0];
	}
	else
	{
		p = cur_l.by[0];
	}

	cur_r.by[0] = one_token(fp, p);

	if(upper_l.by[1] == cur_l.by[0])
	{
		p = upper_l.by[1];
	}
	else
	{
		p = left.by[1];
	}

	cur_l.by[1] = one_token(fp, p);

	if(upper_r.by[1] == cur_r.by[0])
	{
		p = upper_r.by[1];
	}
	else
	{
		p = cur_l.by[1];
	}

	cur_r.by[1] = one_token(fp, p);

	Mig.line[0].bx[Mig.x + 0] = cur_l;
	Mig.line[0].bx[Mig.x + 1] = cur_r;
	Mig.x += 2;
}
//---------------------------------------------------------------------------
void expand_chunk(FILE* fp)
{
	s32 p = poi(fp, data_b_1024);
	s32 q = poi(fp, data_b_105C);

	if(q == 0x2c)
	{
		s32 d;

		while(1)
		{
			d = getbits(fp, 4);

			if(d != 0xf)
			{
				break;
			}

			q += 0xf;
		}

		q += d;
	}

	s32 dx =  data_b_1004[p][0];
	s32 dy = -data_b_1004[p][1];
	s32 x0 = Mig.x;
	s32 x1 = Mig.x;
	s32 i;

	x0 += dx;

	for(i=0; i<q; i++)
	{
		if(x0 < 0)
		{
			Mig.line[0].bx[x1] = Mig.line[dy+1].bx[Mig.cx+x0];
		}
		else if(x0 >= Mig.cx)
		{
			Mig.line[0].bx[x1] = Mig.line[dy-1].bx[x0-Mig.cx];
		}
		else
		{
			Mig.line[0].bx[x1] = Mig.line[dy].bx[x0];
		}

		if(x0 + 1 < 0)
		{
			Mig.line[0].bx[x1+1] = Mig.line[dy+1].bx[Mig.cx+x0+1];
		}
		else if(x0 + 1 >= Mig.cx)
		{
			Mig.line[0].bx[x1+1] = Mig.line[dy-1].bx[x0+1-Mig.cx];
		}
		else
		{
			Mig.line[0].bx[x1+1] = Mig.line[dy].bx[x0+1];
		}

		x0 += 2;
		x1 += 2;
	}

	Mig.x += q * 2;
}
//---------------------------------------------------------------------------
void output_line(void)
{
	s32 i;

	for(i=0; i<Mig.cx; i++)
	{
		Mig.pDat[(Mig.y * 2 + 0) * Mig.cx + i] = Mig.line[0].bx[i].by[0];
		Mig.pDat[(Mig.y * 2 + 1) * Mig.cx + i] = Mig.line[0].bx[i].by[1];
	}
}
//---------------------------------------------------------------------------
void movedown_line_buf(void)
{
	s32 i, j;

	for(i=MAX_LINE-1; i>0; i--)
	{
		for(j=0; j<MAX_CX; j++)
		{
			Mig.line[i].bx[j] = Mig.line[i-1].bx[j];
		}
	}

	for(j=0; j<MAX_CX; j++)
	{
		Mig.line[0].bx[j].by[0] = 0;
		Mig.line[0].bx[j].by[1] = 0;
	}
}
//---------------------------------------------------------------------------
void fwrite16(FILE* fp, u16 n)
{
	u8 buf[2];

	buf[0] = (n >> 0) & 0xFF;
	buf[1] = (n >> 8) & 0xFF;

	fwrite(buf, 2, 1, fp);
}
//---------------------------------------------------------------------------
void fwrite32(FILE* fp, u32 n)
{
	u8 buf[4];

	buf[0] = (n >>  0) & 0xFF;
	buf[1] = (n >>  8) & 0xFF;
	buf[2] = (n >> 16) & 0xFF;
	buf[3] = (n >> 24) & 0xFF;

	fwrite(buf, 4, 1, fp);
}
//---------------------------------------------------------------------------
void save_file(char* fname)
{
	// bmpのpaddingは未処理です。rookiesの画像は全て通るのでこのままにしています
	assert((Mig.cx & 0x3) == 0);

	char sname[20];
	strncpy(sname, fname, 20);

	char* p = strchr(sname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");
		exit(1);
	}

	p[1] = 'b';
	p[2] = 'm';
	p[3] = 'p';

	FILE* fp = fopen(sname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open savefille\n");
		exit(1);
	}

	// BITMAPFILEHEADER
	fwrite("BM", 2, 1, fp);
	fwrite32(fp, 14 + 12 + 256 * 3 + Mig.cx * Mig.cy);
	fwrite16(fp, 0);
	fwrite16(fp, 0);
	fwrite32(fp, 14 + 12 + 256 * 3);

	// BITMAPCOREHEADER
	fwrite32(fp, 12);
	fwrite16(fp, Mig.cx);
	fwrite16(fp, Mig.cy);
	fwrite16(fp, 1);
	fwrite16(fp, 8);

	// PALETTE
	s32 i;

	for(i=0; i<256; i++)
	{
		if(i < 16)
		{
			fputc(Mig.b[i], fp);
			fputc(Mig.g[i], fp);
			fputc(Mig.r[i], fp);
		}
		else
		{
			fputc(0x00, fp);
			fputc(0x00, fp);
			fputc(0x00, fp);
		}
	}

	// DATA
	for(i=0; i<Mig.cy; i++)
	{
		fwrite(Mig.pDat + Mig.cx * (Mig.cy - 1 - i), Mig.cx, 1, fp);
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "mig2bmp [filename]\n");
		exit(1);
	}

	printf("mig2bmp... %s\n", argv[1]);


	FILE* fp = fopen(argv[1], "rb");

	if((fp = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr, "couldn't find MIG file \"%s\"\n", argv[1]);
		exit(1);
	}


	u8 buf[50];

	// ファイルチェック
	fread(buf, 3, 1, fp);

	if(memcmp(buf, "MIG", 3) != 0)
	{
		fprintf(stderr, "this is NOT a mig file: \"%s\"\n", argv[1]);
		exit(1);
	}

	// 縦、横サイズ取得
	fread(buf, 4, 1, fp);
	Mig.cx = ((buf[1] << 8) + buf[0]);
	Mig.cy = ((buf[3] << 8) + buf[2]) * 2;

	// 4bit GRB（24バイト）を8bit RGB（48バイト）に変更
	fread(buf, (4*3*16) / 8, 1, fp);

	s32 j = 0;
	s32 i;

	for(i=0; i<16; i++)
	{
		if((i & 0x01) == 0)
		{
			Mig.g[i] = ((buf[i+j+0] >> 4) & 0xf) * 17;
			Mig.r[i] = ((buf[i+j+0]     ) & 0xf) * 17;
			Mig.b[i] = ((buf[i+j+1] >> 4) & 0xf) * 17;
		}
		else
		{
			Mig.g[i] = ((buf[i+j+0]     ) & 0xf) * 17;
			Mig.r[i] = ((buf[i+j+1] >> 4) & 0xf) * 17;
			Mig.b[i] = ((buf[i+j+1]     ) & 0xf) * 17;
			j++;
		}
	}

	// 画像データの領域確保
	Mig.pDat = (u8*)calloc(Mig.cx * Mig.cy, sizeof(u8));

	if(Mig.pDat == NULL)
	{
		fprintf(stderr, "calloc error\n");
		exit(1);
	}

	// 画像データ解凍
	Mig.x = 0;
	Mig.y = 0;

	while(Mig.y < Mig.cy / 2)
	{
		if(getbit(fp) == 0)
		{
			expand_2x2(fp);
		}
		else
		{
			expand_chunk(fp);
		}

		if(Mig.x >= Mig.cx)
		{
			output_line();
			movedown_line_buf();

			Mig.x = 0;
			Mig.y++;
		}
	}

	fclose(fp);
	save_file(argv[1]);

	return 0;
}
