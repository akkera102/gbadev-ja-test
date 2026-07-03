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
	u8*  p;
	s32  size;

	s32  pos;
	s32  dig;
	u8   chr;

} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;

//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
u8    BitGet8(void);
u16   BitGet16(void);
u32   BitGet32(void);
s32   BitGetSize(void);

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
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("bmp2msk [BMP File]\n");

		exit(0);
	}

	if(strlen(argv[1]) > 30)
	{
		printf("too long file name\n");

		exit(1);
	}

	printf("bmp2msk... %s\n", argv[1]);


	BitCalloc(argv[1]);

	// "BM"チェック
	if(BitGet16() != 0x4D42)
	{
		fprintf(stderr, "file isn't BMP\n");

		exit(1);
	}

	char fname[50];

	strncpy(fname, argv[1], 40);
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
			u8 alpha = BitGet32() >> 24;

			if(alpha & 0xff)
			{
				BmpWrite8(fp, alpha);
				BmpWrite8(fp, alpha);
				BmpWrite8(fp, alpha);
				BmpWrite8(fp, alpha);
			}
			else
			{
				BmpWrite8(fp, 0);
				BmpWrite8(fp, 0);
				BmpWrite8(fp, 0);
				BmpWrite8(fp, 0);
			}
		}
	}

	fclose(fp);
	BitFree();

	return 0;
}
