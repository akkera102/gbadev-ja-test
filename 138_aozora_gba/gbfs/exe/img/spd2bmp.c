// gcc spd2bmp.c -s -o spd2bmp

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

typedef struct {
	u8* pLz;
	u8* pRgb;

	u32 format;
	u32 width;
	u32 height;
	u32 lzSize;

	u32 bpp;
	u32 comp;

} ST_SPD;

//---------------------------------------------------------------------------
ST_BIT Bit;
ST_SPD Spd;

//---------------------------------------------------------------------------
void BitCalloc(char* fname);
void BitFree(void);
void BitSeek(s32 pos);
u8   BitGet8(void);
u16  BitGet16(void);
u32  BitGet32(void);
s32  BitGetPos(void);
s32  BitGetSize(void);

void SpdUnpackLz(void);
void SpdUnpackAlpha(void);
void SpdUnpackRle(void);
void SpdFree(void);

void BmpWrite8(FILE* fp, u8 h);
void BmpWrite16(FILE* fp, u16 h);
void BmpWrite32(FILE* fp, u32 h);

s32  ToInt32(u8* p, s32 pos);

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
void SpdFree(void)
{
	if(Spd.pLz != NULL)
	{
		free(Spd.pLz);
	}

	if(Spd.pRgb != NULL)
	{
		free(Spd.pRgb);
	}
}
//---------------------------------------------------------------------------
void SpdUnpackLz(void)
{
	Spd.pLz = (u8*)calloc(Spd.lzSize, sizeof(u8));

	if(Spd.pLz == NULL)
	{
		fprintf(stderr, "calloc error\n");

		exit(1);
	}

	u8* pDst    = Spd.pLz;
	s32 dstSize = Spd.lzSize;
	s32 dst     = 0;
	s32 bit     = 2;
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
}
//---------------------------------------------------------------------------
void SpdUnpackAlpha(void)
{
	assert(Spd.pLz != NULL);


	s32 dstSize = Spd.width * Spd.height * 4;

	Spd.pRgb = (u8*)calloc(dstSize, sizeof(u8));

	if(Spd.pRgb == NULL)
	{
		fprintf(stderr, "calloc pRgb error\n");

		exit(1);
	}

	u8* pSrc = Spd.pLz;
	u8* pDst = Spd.pRgb;
	s32 src  = ToInt32(pSrc, 0);
	s32 dst  = 0;
	s32 idx  = 4;

	while(dst < dstSize)
	{
		s32 ctl = pSrc[idx++];

		if(ctl == 0)
		{
			s32 cnt = pSrc[idx++] + 1;

			dst += 4 * cnt;

			continue;
		}

		if(ctl == 1)
		{
			s32 cnt = pSrc[idx++] + 1;
			s32 i;

			for(i=0; i<cnt; i++)
			{
				pDst[dst++] = pSrc[src++];
				pDst[dst++] = pSrc[src++];
				pDst[dst++] = pSrc[src++];
				pDst[dst++] = 0xFF;
			}

			continue;
		}

		pDst[dst++] = pSrc[src++];
		pDst[dst++] = pSrc[src++];
		pDst[dst++] = pSrc[src++];
		pDst[dst++] = (u8)-ctl;
	}
}
//---------------------------------------------------------------------------
void SpdUnpackRle(void)
{
	assert(Spd.pLz != NULL);


	s32 dstSize = Spd.width * Spd.height * 4;

	Spd.pRgb = (u8*)calloc(dstSize, sizeof(u8));

	if(Spd.pRgb == NULL)
	{
		fprintf(stderr, "calloc pRgb error\n");

		exit(1);
	}

	u8*  pSrc   = Spd.pLz;
	u8*  pDst   = Spd.pRgb;
	bool isSkip = (ToInt32(pSrc, 0) == 0) ? true : false;
	s32  src    = ToInt32(pSrc, 4);
	s32  dst    = 0;
	s32  idx    = 8;

	while(dst < dstSize)
	{
		assert(dst+4 < dstSize);

		s32 n = ToInt32(pSrc, idx);
		idx += 4;

		if(isSkip == true)
		{
			dst += n * 4;
		}
		else
		{
			for( ; n!=0; n--)
			{
				pDst[dst++] = pSrc[src++];
				pDst[dst++] = pSrc[src++];
				pDst[dst++] = pSrc[src++];
				pDst[dst++] = 0xFF;
			}
		}

		isSkip = !isSkip;
	}
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
s32 ToInt32(u8* p, s32 pos)
{
	return (p[pos+3] << 24) | (p[pos+2] << 16) | (p[pos+1] <<  8) | p[pos+0];
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("spd2bmp [SPD7 File]\n");

		exit(0);
	}

	if(strlen(argv[1]) > 30)
	{
		printf("too long file name\n");

		exit(1);
	}

	printf("spd2bmp... %s\n", argv[1]);

	BitCalloc(argv[1]);

	// header fix
	BitSeek(0x10);

	u32 fix = BitGet32();
	fix = (u8)((fix >> 16) + fix);

	// header chk
	BitSeek(0);

	u8 b1 = BitGet8() - fix;
	u8 b2 = BitGet8() - fix;
	u8 b3 = BitGet8() - fix;
	u8 b4 = BitGet8() - fix;

	if(b1 != 'S' || b2 != 'P' || b3 != 'D' || b4 != '7')
	{
		printf("%s is not SPD7 file\n", argv[1]);

		exit(1);
	}

	Spd.format = BitGet32();
	Spd.width  = BitGet32();
	Spd.height = BitGet32();
	Spd.lzSize = BitGet32();

	Spd.format -= (Spd.lzSize << 4) & 0xffff;
	Spd.width  -= (Spd.lzSize << 2) & 0x137f;
	Spd.height -= (Spd.lzSize >> 2) & 0xf731;

	Spd.bpp  = Spd.format >> 16;
	Spd.comp = Spd.format & 0xffff;

	switch(Spd.comp)
	{
	// Lz + Rle
	case 0:
		SpdUnpackLz();
		SpdUnpackRle();
		Spd.bpp = 32;
		break;

	// Lz
	case 1:
		SpdUnpackLz();
		break;

	// Lz + Alpha
	case 2:
		SpdUnpackLz();
		SpdUnpackAlpha();
		Spd.bpp = 32;
		break;

	default:
		printf("Unsupport format\n");
		exit(1);
	}

//	printf("w:%d h:%d size:0x%x bpp:%d comp:%d\n", Spd.width, Spd.height, Spd.lzSize, Spd.bpp, Spd.comp);


	char fname[50];
	s32 i;

	strncpy(fname, argv[1], 40);
	char* p = strchr(fname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '.';
	p[1] = 'b';
	p[2] = 'm';
	p[3] = 'p';
	p[4] = '\0';

	FILE* fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open file\n");

		exit(1);
	}

	// BITMAPFILEHEADER
	s32 stride = Spd.width * Spd.bpp / 8;

	BmpWrite8(fp, 'B');
	BmpWrite8(fp, 'M');
	BmpWrite32(fp, 14 + 40 + stride * Spd.height);
	BmpWrite16(fp, 0);
	BmpWrite16(fp, 0);
	BmpWrite32(fp, 14 + 40);

	// BITMAPCOREHEADER
	BmpWrite32(fp, 40);
	BmpWrite32(fp, Spd.width);
	BmpWrite32(fp, Spd.height);
	BmpWrite16(fp, 1);
	BmpWrite16(fp, Spd.bpp);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);

	// DATA
	u8* pDat;

	if(Spd.pRgb == NULL)
	{
		pDat = Spd.pLz;
	}
	else
	{
		pDat = Spd.pRgb;
	}

	for(i=0; i<Spd.height; i++)
	{
		fwrite(pDat + stride * Spd.height - stride * (i+1), stride, 1, fp);
	}

	fclose(fp);

	SpdFree();
	BitFree();

	return 0;
}
