// gcc eff2bmp.c -s -o eff2bmp
// 160x120 256 col

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>

//---------------------------------------------------------------------------
#define EFF_MAX_FRAME_CNT				200

typedef unsigned char			 u8;
typedef char					 s8;
typedef unsigned short			u16;
typedef short					s16;
typedef unsigned int			u32;
typedef int						s32;


typedef struct {
	u32 pixelSize;
	u32 width;
	u32 height;
	u32 frameCnt;
	u32 stride;
	u32 length;

	u8  r[256];
	u8  g[256];
	u8  b[256];
	u8  a[256];

	u32 frameOffset[EFF_MAX_FRAME_CNT];

	u32 unknown1;
	u32 unknown2[EFF_MAX_FRAME_CNT];

} ST_EFF;

typedef struct {
	u8*  p;
	s32  size;

	s32  pos;
	s32  dig;
	u8   chr;

} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;
ST_EFF Eff;

//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
u8    BitGet1(void);
u8    BitGet4(void);
u8    BitGet8(void);
u16   BitGet16(void);
u32   BitGet32(void);

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
	u8 r = 0;

	r += BitGet1() << 3;
	r += BitGet1() << 2;
	r += BitGet1() << 1;
	r += BitGet1();

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
		printf("eff2bmp [EFF File]\n");

		exit(0);
	}

	if(strlen(argv[1]) > 12)
	{
		fprintf(stderr, "too long file name\n");

		exit(1);
	}

	s32 i, j;
	char fname[32], buf[32];

	strncpy(fname, argv[1], 20);
	char* p = strchr(fname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '\0';

	printf("eff2bmp... %s\n", argv[1]);

	BitCalloc(argv[1]);

	Eff.pixelSize = BitGet16();
	Eff.width     = BitGet16();
	Eff.height    = BitGet16();
	Eff.unknown1  = BitGet16();
	Eff.frameCnt  = BitGet32();
	Eff.stride    = Eff.pixelSize * Eff.width;
	Eff.length    = Eff.stride * Eff.height;

	// frame
	for(i=0; i<Eff.frameCnt; i++)
	{
		Eff.unknown2[i] = BitGet32();
		Eff.frameOffset[i] = BitGet32();
	}

	// palette
	for(i=0; i<256; i++)
	{
		Eff.b[i] = BitGet8();
		Eff.g[i] = BitGet8();
		Eff.r[i] = BitGet8();
		Eff.a[i] = BitGet8() ^ 0xff;
	}

	// ŠeƒtƒŒ[ƒ€‚ðbmp•Û‘¶
	for(i=0; i<Eff.frameCnt; i++)
	{
		sprintf(buf, "%s_%02d.bmp", fname, i);

		FILE* fp = fopen(buf, "wb");

		if(fp == NULL)
		{
			fprintf(stderr, "couldn't open file\n");

			exit(1);
		}


		// BITMAPFILEHEADER
		BmpWrite8(fp, 'B');
		BmpWrite8(fp, 'M');
		BmpWrite32(fp, 14 + 40 + 256 * 4 + Eff.length);
		BmpWrite16(fp, 0);
		BmpWrite16(fp, 0);
		BmpWrite32(fp, 14 + 40 + 256 * 4);

		// BITMAPCOREHEADER
		BmpWrite32(fp, 40);
		BmpWrite32(fp, Eff.width);
		BmpWrite32(fp, Eff.height);
		BmpWrite16(fp, 1);
		BmpWrite16(fp, 8);
		BmpWrite32(fp, 0);
		BmpWrite32(fp, 0);
		BmpWrite32(fp, 0x1274);
		BmpWrite32(fp, 0x1274);
		BmpWrite32(fp, 256);
		BmpWrite32(fp, 256);

		// PALETTE
		for(j=0; j<256; j++)
		{
			BmpWrite8(fp, Eff.b[j]);
			BmpWrite8(fp, Eff.g[j]);
			BmpWrite8(fp, Eff.r[j]);
			BmpWrite8(fp, Eff.a[j]);
		}

		// DATA
		BitSeek(Eff.frameOffset[i]);

		for(j=0; j<Eff.length; j++)
		{
			fputc(BitGet8(), fp);
		}

		fclose(fp);
	}

	BitFree();

	return 0;
}
