// gcc bmp2msk.c -s -o bmp2msk

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

typedef struct {
	char* fname;
	s32   x;
	s32   y;
	u8    alpha;

} ST_FIX_LIST;

typedef struct {
	u8*  p;
	s32  size;

	s32  pos;
	s32  dig;
	u8   chr;

} ST_BIT;

//---------------------------------------------------------------------------
// 立ち絵周辺のドットを修正
ST_FIX_LIST FixList[] = {
	{"CHIEKO",  203,  47, 0x00},		// 白→黒
	{"CHIEKO",  211, 124, 0x00},
//	{"CHIEKO",  158, 152, 0xff},		// 黒→白
//	{"CHIEKO",   96, 255, 0xff},
	{"CHIEKO",   74, 312, 0x00},

	{"CHIHIR0", 392,  86, 0x00},
	{"CHIHIR0", 406, 123, 0x00},
	{"CHIHIR0", 407, 123, 0x00},
	{"CHIHIR0", 401, 127, 0x00},
	{"CHIHIR0", 402, 127, 0x00},
	{"CHIHIR0", 402, 128, 0x00},
	{"CHIHIR0", 432, 313, 0x00},
	{"CHIHIR0", 432, 314, 0x00},
	{"CHIHIR0", 400, 407, 0x00},
	{"CHIHIR0", 421, 460, 0x00},
	{"CHIHIR0", 421, 461, 0x00},

	{"IROHA",   536,  62, 0x00},
	{"IROHA",   438, 175, 0x00},
	{"IROHA",   438, 176, 0x00},

	{"KANA",    277,  91, 0x00},
	{"KANA",    278,  91, 0x00},
	{"KANA",    225, 104, 0x00},
	{"KANA",    286, 129, 0x00},
	{"KANA",    286, 130, 0x00},
	{"KANA",    287, 129, 0x00},
	{"KANA",    287, 130, 0x00},
	{"KANA",    181, 106, 0x00},
	{"KANA",    182, 106, 0x00},
	{"KANA",    227, 214, 0x00},
	{"KANA",     38, 186, 0x00},
	{"KANA",    210, 223, 0x00},
	{"KANA",    211, 223, 0x00},
	{"KANA",     54, 245, 0x00},
	{"KANA",    231, 357, 0x00},
	{"KANA",    246, 360, 0x00},
	{"KANA",    246, 361, 0x00},
	{"KANA",    248, 361, 0x00},
	{"KANA",    255, 400, 0x00},
	{"KANA",    279, 415, 0x00},
	{"KANA",     64, 478, 0x00},

	{"KAORI",   540,  61, 0x00},
	{"KAORI",   416, 127, 0x00},
	{"KAORI",   414, 210, 0x00},
	{"KAORI",   414, 211, 0x00},
	{"KAORI",   552, 293, 0x00},

	{"MIDORI",  100,   0, 0x00},
	{"MIDORI",  101,   0, 0x00},
	{"MIDORI",   74,  21, 0x00},
	{"MIDORI",  190,  34, 0x00},
	{"MIDORI",  192,  35, 0x00},
	{"MIDORI",  166, 124, 0x00},
	{"MIDORI",  216, 154, 0x00},
	{"MIDORI",  216, 155, 0x00},
	{"MIDORI",  218, 168, 0x00},
	{"MIDORI",  214, 218, 0x00},
	{"MIDORI",  212, 222, 0x00},
	{"MIDORI",  207, 353, 0x00},
	{"MIDORI",  219, 382, 0x00},
	{"MIDORI",   63, 426, 0x00},
	{"MIDORI",   66, 444, 0x00},
	{"MIDORI",  199, 439, 0x00},
	{"MIDORI",  199, 440, 0x00},
	{"MIDORI",  200, 440, 0x00},
	{"MIDORI",  220, 442, 0x00},
	{"MIDORI",   30, 465, 0x00},
	{"MIDORI",   32, 464, 0x00},
	{"MIDORI",   34, 466, 0x00},
	{"MIDORI",   31, 474, 0x00},
	{"MIDORI",   31, 475, 0x00},
	{"MIDORI",   16, 478, 0x00},
	{"MIDORI",  192, 469, 0x00},
	{"MIDORI",  192, 470, 0x00},

	{"RUKI",    550,  49, 0x00},
	{"RUKI",    583, 123, 0x00},
	{"RUKI",    580, 174, 0x00},
	{"RUKI",    540, 277, 0x00},

	{"SHIGE",   558,  35, 0x00},
	{"SHIGE",   558,  36, 0x00},
	{"SHIGE",   557,  36, 0x00},
	{"SHIGE",   345,  60, 0x00},
	{"SHIGE",   346,  60, 0x00},
	{"SHIGE",   574, 338, 0x00},
	{"SHIGE",   574, 339, 0x00},
	{"SHIGE",   559, 367, 0x00},
	{"SHIGE",   343, 440, 0x00},
	{"SHIGE",   335, 466, 0x00},
	{"SHIGE",   336, 466, 0x00},
	{"SHIGE",   335, 467, 0x00},
	{"SHIGE",   336, 467, 0x00},

	{"TAHIRO",   71, 145, 0x00},
	{"TAHIRO",  103, 386, 0x00},
	{"TAHIRO",  104, 386, 0x00},
	{"TAHIRO",  104, 387, 0x00},
	{"TAHIRO",  193, 162, 0x00},
	{"TAHIRO",  206, 186, 0x00},
	{"TAHIRO",  219, 200, 0x00},
	{"TAHIRO",  220, 200, 0x00},
	{"TAHIRO",  232, 290, 0x00},
	{"TAHIRO",  233, 290, 0x00},
	{"TAHIRO",  232, 291, 0x00},
};

ST_BIT Bit;

//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
u8    BitGet8(void);
u16   BitGet16(void);
u32   BitGet32(void);
s32   BitGetSize(void);

u32   FixGetPixel(char* fname, s32 x, s32 y, u8 alpha);

void  BmpWrite8(FILE* fp, u8 h);
void  BmpWrite16(FILE* fp, u16 h);
void  BmpWrite32(FILE* fp, u32 h);

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

	Bit.p = NULL;
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
u32 FixGetPixel(char* fname, s32 x, s32 y, u8 alpha)
{
	s32 i;

	// アルファ値を修正
	for(i=0; i<sizeof FixList / sizeof FixList[0]; i++)
	{
		if(strncmp(fname, FixList[i].fname, strlen(FixList[i].fname)) == 0 && FixList[i].x == x && FixList[i].y == y)
		{
			alpha = FixList[i].alpha;
		}
	}

	// アルファ値がある場合は白
	if(alpha & 0xff)
	{
		return 0xffffffff;
	}

	return 0xff000000;
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("bmp2msk [BMP File]\n");

		exit(0);
	}

	printf("bmp2msk... %s\n", argv[1]);


	BitCalloc(argv[1]);

	// "BM"チェック
	if(BitGet16() != 0x4D42)
	{
		fprintf(stderr, "file isn't BMP\n");

		exit(1);
	}

	char fname[30];

	strncpy(fname, argv[1], 20);
	char* p = strchr(fname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '_';
	p[1] = 'm';
	p[2] = '.';
	p[3] = 'b';
	p[4] = 'm';
	p[5] = 'p';
	p[6] = '\0';

	FILE* fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open file\n");

		exit(1);
	}

	// BITMAPFILEHEADER
	BmpWrite8(fp, 'B');
	BmpWrite8(fp, 'M');
	BmpWrite32(fp, BitGet32());
	BmpWrite16(fp, BitGet16());
	BmpWrite16(fp, BitGet16());
	BmpWrite32(fp, BitGet32());

	// BITMAPCOREHEADER
	BmpWrite32(fp, BitGet32());

	u32 width = BitGet32();
	BmpWrite32(fp, width);

	u32 height = BitGet32();
	BmpWrite32(fp, height);

	BmpWrite16(fp, BitGet16());
	BmpWrite16(fp, BitGet16());
	BmpWrite32(fp, BitGet32());
	BmpWrite32(fp, BitGet32());
	BmpWrite32(fp, BitGet32());
	BmpWrite32(fp, BitGet32());
	BmpWrite32(fp, BitGet32());
	BmpWrite32(fp, BitGet32());

	// DATA
	s32 x, y;

	for(y=height-1; y>=0; y--)
	{
		for(x=0; x<width; x++)
		{
			BmpWrite32(fp, FixGetPixel(argv[1], x, y, BitGet32() >> 24));
		}
	}

	fclose(fp);
	BitFree();

	return 0;
}
