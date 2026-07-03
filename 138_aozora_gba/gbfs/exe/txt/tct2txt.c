// gcc tct2txt.c -s -o tct2txt

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
	u8* p;
	s32 size;
	s32 pos;

} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;

//---------------------------------------------------------------------------
void BitCalloc(char* fname);
void BitFree(void);
void BitSeek(s32 pos);
u8   BitGet8(void);
u16  BitGet16(void);
u32  BitGet32(void);
s32  BitGetPos(void);
s32  BitGetSize(void);

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
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("tct2txt [TCT File]\n");

		exit(0);
	}

	if(strlen(argv[1]) > 30)
	{
		printf("too long file name\n");

		exit(1);
	}

	printf("tct2txt... %s\n", argv[1]);


	BitCalloc(argv[1]);

	s32 dstSize = BitGet32();

	u8* pDst = (u8*)calloc(dstSize, sizeof(u8));

	if(pDst == NULL)
	{
		printf("calloc error\n");

		exit(1);
	}


	// LZ
	s32 dst = 0;
	s32 bit = 2;
	s32 i;

	while(dst < dstSize)
	{
		bit >>= 1;

		if(bit == 1)
		{
			bit = BitGet8() | 0x100;
		}

		if(bit & 1)
		{
			pDst[dst++] = BitGet8();

			continue;
		}

		assert(dst < dstSize);

		s32 b1  = BitGet8();
		s32 b2  = BitGet8();
		s32 pos = (b2 << 4) | (b1 >> 4);
		s32 cnt = __min((b1 & 0xF) + 3, dstSize - dst);

		for(i=0; i<cnt; i++)
		{
			assert(dst >= pos);

			pDst[dst] = pDst[dst - pos];
			dst++;
		}
	}


	char fname[50];

	strncpy(fname, argv[1], 40);
	char* p = strchr(fname, '.');

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

	FILE* fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open file\n");

		exit(1);
	}

	for(i=0; i<dstSize; i++)
	{
		// rotate right
		fputc((pDst[i] >> 1) | (pDst[i] << 7), fp);
	}

	fclose(fp);
	free(pDst);


	BitFree();

	return 0;
}
