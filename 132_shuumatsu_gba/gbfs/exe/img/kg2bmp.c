// gcc kg2bmp.c -s -o kg2bmp

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
	u32 alpha;
	s32 bppType;
	s32 bpp;
	u32 width;
	u32 height;

	u32 palOffset;
	u32 datOffset;
	u32 alphaOffset;

	s32 pixelSize;
	s32 stride;
	s32 length;

	u8  r[256];
	u8  g[256];
	u8  b[256];
	u8  a[256];

	u8  dict[0x800];
	u8* out;

} ST_KG;

typedef struct {
	u8*  p;
	s32  size;

	s32  pos;
	s32  dig;
	u8   chr;
	bool isMsb;

} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;
ST_KG Kg;

//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
void  BitSetMsb(bool is);
s32   BitGetSize(void);
u8    BitGet1(void);
u8    BitGet2(void);
u8    BitGet3(void);
u8    BitGet4(void);
u8    BitGet8(void);
u16   BitGet16(void);
u32   BitGet32(void);

void  KgUnpack(void);
void  KgUnpack256a(void);
void  KgUnpackCh(s32 dst);
u8    KgGetPixel(s32 dst);
s32   KgGetCnt(void);
void  KgInitDict(void);
void  KgExecDict(u8 b, u8 prev);

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
void BitSetMsb(bool is)
{
	Bit.isMsb = is;
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
u8 BitGet2(void)
{
	u8 r = 0;

	r += BitGet1() << 1;
	r += BitGet1();

	return r;
}
//---------------------------------------------------------------------------
u8 BitGet3(void)
{
	u8 r = 0;

	r += BitGet1() << 2;
	r += BitGet1() << 1;
	r += BitGet1();

	return r;
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
	u16 b1, b2;

	if(Bit.isMsb == true)
	{
		b1 = BitGet8() << 8;
		b2 = BitGet8();
	}
	else
	{
		b1 = BitGet8();
		b2 = BitGet8() << 8;
	}

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 BitGet32(void)
{
	u32 b1, b2, b3, b4;

	if(Bit.isMsb == true)
	{
		b1 = BitGet8() << 24;
		b2 = BitGet8() << 16;
		b3 = BitGet8() <<  8;
		b4 = BitGet8();
	}
	else
	{
		b1 = BitGet8();
		b2 = BitGet8() <<  8;
		b3 = BitGet8() << 16;
		b4 = BitGet8() << 24;
	}

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
void KgUnpack(void)
{
	if(Kg.bpp == 8)
	{
		BitSeek(Kg.palOffset);

		s32 i;

		for(i=0; i<256; i++)
		{
			Kg.b[i] = BitGet8();
			Kg.g[i] = BitGet8();
			Kg.r[i] = BitGet8();
			Kg.a[i] = BitGet8() ^ 0xff;
		}
	}

	BitSeek(Kg.datOffset);

	KgInitDict();
	KgUnpackCh(0);

	if(Kg.pixelSize > 1)
	{
		KgUnpackCh(1);
		KgUnpackCh(2);
	}

	if(Kg.alphaOffset != 0)
	{
		BitSeek(Kg.alphaOffset);

		KgInitDict();
		KgUnpackCh(3);
	}
}
//---------------------------------------------------------------------------
// 256色＋アルファブレンド画像はRGBAに変換
void KgUnpack256a(void)
{
	BitSeek(Kg.palOffset);

	s32 i;

	for(i=0; i<256; i++)
	{
		Kg.b[i] = BitGet8();
		Kg.g[i] = BitGet8();
		Kg.r[i] = BitGet8();
		Kg.a[i] = BitGet8() ^ 0xff;
	}

	BitSeek(Kg.datOffset);

	KgInitDict();
	KgUnpackCh(0);


	Kg.bpp       = 32;
	Kg.pixelSize = Kg.bpp / 8;
	Kg.stride    = Kg.pixelSize * Kg.width;
	Kg.length    = Kg.stride * Kg.height;

	u8* tmp = (u8*)calloc(Kg.length, sizeof(u8));

	if(tmp == NULL)
	{
		fprintf(stderr, "calloc tmp error\n");

		exit(1);
	}

	for(i=0; i<Kg.width * Kg.height; i++)
	{
		tmp[i*4+0] = Kg.b[Kg.out[i]];
		tmp[i*4+1] = Kg.g[Kg.out[i]];
		tmp[i*4+2] = Kg.r[Kg.out[i]];
	}

	free(Kg.out);
	Kg.out = tmp;


	BitSeek(Kg.alphaOffset);

	KgInitDict();
	KgUnpackCh(3);
}
//---------------------------------------------------------------------------
void KgUnpackCh(s32 dst)
{
	Kg.out[dst] = BitGet8();
	dst += Kg.pixelSize;

	Kg.out[dst] = BitGet8();
	dst += Kg.pixelSize;

	while(dst < Kg.length)
	{
		s32 ctl = BitGet1();

		if(ctl == 0)
		{
			u8 b = KgGetPixel(dst);
			Kg.out[dst] = b;

			KgExecDict(b, Kg.out[dst - Kg.pixelSize]);
			dst += Kg.pixelSize;

			continue;
		}

		if(BitGet1() != 0)
		{
			ctl = BitGet2();
		}
		else
		{
			ctl = 4;
		}

		s32 offset;

		switch(ctl)
		{
		case 0:
			offset = Kg.stride;
			break;

		case 1:
			offset = Kg.stride - Kg.pixelSize;
			break;

		case 2:
			offset = Kg.stride + Kg.pixelSize;
			break;

		case 3:
			offset = 2 * Kg.pixelSize;
			break;

		default:
			offset = Kg.pixelSize;
			break;
		}

		s32 cnt = KgGetCnt();
		s32 src = dst - offset;
		s32 i;

		for(i=0; i<cnt; i++)
		{
			assert(src < Kg.length);
			assert(dst < Kg.length);

			Kg.out[dst] = Kg.out[src];

			dst += Kg.pixelSize;
			src += Kg.pixelSize;
		}
	}
}
//---------------------------------------------------------------------------
u8 KgGetPixel(s32 dst)
{
	if(BitGet1() == 1)
	{
		return BitGet8();
	}

	s32 n = 8 * Kg.out[dst - Kg.pixelSize];

	return Kg.dict[n + BitGet3()];
}
//---------------------------------------------------------------------------
s32 KgGetCnt(void)
{
	s32 cnt = BitGet2();

	if(cnt == 0)
	{
		cnt = BitGet4();

		if(cnt != 0)
		{
			cnt += 3;
		}
		else
		{
			cnt = BitGet8();

			if(cnt == 0)
			{
				cnt = BitGet16();

				if(cnt == 0)
				{
					cnt  = BitGet16() << 16;
					cnt |= BitGet16();
				}
			}
		}
	}

	return cnt;
}
//---------------------------------------------------------------------------
void KgInitDict(void)
{
	s32 i;

	for(i=0; i<0x800; i++)
	{
		Kg.dict[i] = (u8)(i & 7);
	}
}
//---------------------------------------------------------------------------
void KgExecDict(u8 b, u8 prev)
{
	s32 s = 8 * prev;
	s32 i, j;

	for(i=0; i<8; i++)
	{
		if(Kg.dict[s + i] == b)
		{
			break;
		}
	}

	if(i != 0)
	{
		if(i == 8)
		{
			i = 7;
		}

		u8 tmp[0x800];
		assert(i < 0x800);

		for(j=0; j<i; j++)
		{
			tmp[j] = Kg.dict[s+j];
		}

		for(j=0; j<i; j++)
		{
			Kg.dict[s+1+j] = tmp[j];
		}

		Kg.dict[s] = b;
	}
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("kg2bmp [KG File]\n");

		exit(0);
	}

	printf("kg2bmp... %s\n", argv[1]);


	BitCalloc(argv[1]);

	if(BitGet16() != 0x474B)
	{
		fprintf(stderr, "signatures error\n");

		exit(1);
	}

	Kg.alpha   = BitGet8();
	Kg.bppType = BitGet8();
	Kg.width   = BitGet16();
	Kg.height  = BitGet16();

	BitSeek(0x0c);
	Kg.palOffset = BitGet32();
	Kg.datOffset = BitGet32();

	if(Kg.alpha == 2)
	{
		BitSeek(0x2c);
		Kg.alphaOffset = BitGet32();
	}
	else
	{
		Kg.alphaOffset = 0;
	}

	if(Kg.alphaOffset != 0 && Kg.palOffset == 0)
	{
		Kg.bpp = 32;
	}
	else if(Kg.bppType == 2)
	{
		Kg.bpp = 24;
	}
	else
	{
		Kg.bpp = 8;
	}

	Kg.pixelSize = Kg.bpp / 8;
	Kg.stride    = Kg.pixelSize * Kg.width;
	Kg.length    = Kg.stride * Kg.height;

	Kg.out = (u8*)calloc(Kg.length, sizeof(u8));

	if(Kg.out == NULL)
	{
		fprintf(stderr, "calloc Kg.out error\n");

		exit(1);
	}

/*
	printf("alpha     %d\n", Kg.alpha);
	printf("bppType   %d\n", Kg.bppType);
	printf("bpp       %d\n", Kg.bpp);
	printf("width     %d\n", Kg.width);
	printf("height    %d\n", Kg.height);
	printf("pixelSize %d\n", Kg.pixelSize);
	printf("stride    %d\n", Kg.stride);
	printf("length    %d\n", Kg.length);
	printf("palOffset   0x%08X\n", Kg.palOffset);
	printf("datOffset   0x%08X\n", Kg.datOffset);
	printf("alphaOffset 0x%08X\n", Kg.alphaOffset);
*/

	BitSetMsb(true);

	if(Kg.bpp == 8 && Kg.alphaOffset != 0 && Kg.palOffset != 0)
	{
		// 256色＋アルファブレンドは別処理
		KgUnpack256a();
	}
	else
	{
		KgUnpack();
	}

	BitSetMsb(false);


	char fname[30];
	s32 i;

	strncpy(fname, argv[1], 20);
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
	BmpWrite8(fp, 'B');
	BmpWrite8(fp, 'M');
	BmpWrite32(fp, 14 + 40 + ((Kg.bpp == 8) ? 256 * 4 : 0) + Kg.length);
	BmpWrite16(fp, 0);
	BmpWrite16(fp, 0);
	BmpWrite32(fp, 14 + 40 + ((Kg.bpp == 8) ? 256 * 4 : 0));

	// BITMAPCOREHEADER
	BmpWrite32(fp, 40);
	BmpWrite32(fp, Kg.width);
	BmpWrite32(fp, Kg.height);
	BmpWrite16(fp, 1);
	BmpWrite16(fp, Kg.bpp);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0x1274);
	BmpWrite32(fp, 0x1274);
	BmpWrite32(fp, ((Kg.bpp == 8) ? 256 : 0));
	BmpWrite32(fp, ((Kg.bpp == 8) ? 256 : 0));

	// PALETTE
	if(Kg.bpp == 8)
	{
		for(i=0; i<256; i++)
		{
			BmpWrite8(fp, Kg.b[i]);
			BmpWrite8(fp, Kg.g[i]);
			BmpWrite8(fp, Kg.r[i]);
			BmpWrite8(fp, Kg.a[i]);
		}
	}

	// DATA
	for(i=0; i<Kg.height; i++)
	{
		fwrite(Kg.out + Kg.stride * i, Kg.stride, 1, fp);
	}

	fclose(fp);


	free(Kg.out);
	BitFree();

//	printf("done\n");

	return 0;
}
