// PC98 Rookies(海月製作所) ANIM2BMP
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <ctype.h>

// gcc anim2bmp.c -o anim2bmp

//---------------------------------------------------------------------------
typedef unsigned char		 u8;
typedef char				 s8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		u32;
typedef int					s32;

typedef struct {
	s32   cx;
	s32   cy;
	u16   r[16];
	u16   g[16];
	u16   b[16];
	u8*   pDat;					// 解凍データ

	// ビット操作用
	u8    chr;
	s32   bitp;
} ST_ANIM;

u32 hoge[16] = {
	0x00000000, 0x00000001, 0x00000100, 0x00000101,
	0x00010000, 0x00010001, 0x00010100, 0x00010101,
	0x01000000, 0x01000001, 0x01000100, 0x01000101,
	0x01010000, 0x01010001, 0x01010100, 0x01010101,
};


ST_ANIM Anim;

//---------------------------------------------------------------------------
s32 msb(u32 val)
{
	s32 m;

	for(m=-1; val!=0; m++)
	{
		val >>= 1;
	}

	return m;
}
//---------------------------------------------------------------------------
s32 getbit(FILE *fp)
{
	if(Anim.bitp <= 0)
	{
		Anim.bitp = 8;
		fread(&Anim.chr, 1, 1, fp);
	}

	Anim.bitp--;
	return (Anim.chr & (1 << Anim.bitp)) ? 1 : 0;
}
//---------------------------------------------------------------------------
u32 getbits(FILE* fp, s32 a1)
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
u8* expand_file(char* fname)
{
	FILE* fp = fopen(fname, "rb");

	if((fp = fopen(fname, "rb")) == NULL)
	{
		fprintf(stderr, "couldn't find file \"%s\"\n", fname);
		exit(1);
	}


	u8 buf[4];

	// ファイルチェック
	fread(buf, 4, 1, fp);

	if(memcmp(buf, "LZ96", 4) != 0)
	{
		fprintf(stderr, "this is NOT a file: \"%s\"\n", fname);
		exit(1);
	}

	// 解凍サイズ取得
	fread(buf, 4, 1, fp);

	s32 size = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
	u8* pRet = calloc(size, sizeof(u8));

	if(pRet == NULL)
	{
		fprintf(stderr, "calloc error\n");
		exit(1);
	}

	// 解凍
	u32 l3, l5;
	s32 l4;
	u8  l7;
	u32 l1 = 0;

	Anim.chr = 0;
	Anim.bitp = 0;

	while(l1 < size)
	{
		if(getbits(fp, 1) == 0)
		{
			pRet[l1++] = getbits(fp, 8);

			continue;
		}

		if((l1 & 0xffff) >= 0 && (l1 & 0xffff) < 0x4000)
		{
			l4 = msb(l1 & 0xffff) + 1;
		}
		else
		{
			l4 = 0xe;
		}

		l3 = getbits(fp, l4); 

		for(l7=2; l7!=8; l7++)
		{
			if(getbits(fp, 1) != 0)
			{
				 break;
			}
		}

		if(l7 == 8)
		{
			l7 = getbits(fp, 8);
		}

		for(l5=0; l5<l7; l5++)
		{
			pRet[l1] = pRet[l1 - l3];

			l1++;
		}
	}

	fclose(fp);

	return pRet;
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
	assert((Anim.cx & 0x3) == 0);

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
	fwrite32(fp, 14 + 12 + 256 * 3 + Anim.cx * Anim.cy);
	fwrite16(fp, 0);
	fwrite16(fp, 0);
	fwrite32(fp, 14 + 12 + 256 * 3);

	// BITMAPCOREHEADER
	fwrite32(fp, 12);
	fwrite16(fp, Anim.cx);
	fwrite16(fp, Anim.cy);
	fwrite16(fp, 1);
	fwrite16(fp, 8);

	// COLOR
	s32 i;

	for(i=0; i<256; i++)
	{
		if(i < 16)
		{
			fputc(Anim.b[i], fp);
			fputc(Anim.g[i], fp);
			fputc(Anim.r[i], fp);
		}
		else
		{
			fputc(0x00, fp);
			fputc(0x00, fp);
			fputc(0x00, fp);
		}
	}

	// DATA
	for(i=0; i<Anim.cy; i++)
	{
		fwrite(Anim.pDat + Anim.cx * (Anim.cy - 1 - i), Anim.cx, 1, fp);
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 3)
	{
		fprintf(stderr, "anim2bmp [filename.idx] [filename.pix]\n");
		exit(1);
	}

	printf("anim2bmp... %s %s\n", argv[1], argv[2]);


	u8* pIdx = expand_file(argv[1]);
	u8* pPix = expand_file(argv[2]);

	s32 i;
	s32 idx_pos = 4;

	// palette parameters
	for(i=0; i<16; i++)
	{
		Anim.g[i] = pIdx[idx_pos + 0] * 0x1111;
		Anim.r[i] = pIdx[idx_pos + 1] * 0x1111;
		Anim.b[i] = pIdx[idx_pos + 2] * 0x1111;

		idx_pos += 3;
	}

	// misc parameters
	s32 c = pIdx[idx_pos + 0] + (pIdx[idx_pos + 1] << 8);
	s32 d = pIdx[idx_pos + 2] + (pIdx[idx_pos + 3] << 8);
	s32 e = pIdx[idx_pos + 4] + (pIdx[idx_pos + 5] << 8);
	s32 f = pIdx[idx_pos + 6] + (pIdx[idx_pos + 7] << 8);
	idx_pos += 8;


	s32 cx   = (e - c) * 8;
	s32 cy   = (f - d) / 0x50;
	s32 size = cx * cy;
	u8* pDat = (u8*)calloc(size, sizeof(u8));
	u8* p    = pDat;

	s32 x, y;

	for(x=0; x<cx; x+=8, p+=8)
	{
		u8* q = p;
		s32 len;

		for(y=0; y<cy; y+=len)
		{
			len = 1;

			u8  ppp = pIdx[idx_pos++];
			s32 pix_pos = (u8)(ppp << 2);

			if((ppp & 0x80) == 0)
			{
				pix_pos += (pIdx[idx_pos++] << 8);
			}

			if((ppp & 0x40) != 0)
			{
				u8 qqq = pIdx[idx_pos++];
				len = (qqq == 0) ? (pIdx[idx_pos++] + 0x100) : qqq;
			}

			u32 hrp = hoge[pPix[pix_pos + 0] >> 4];
			u32 lrp = hoge[pPix[pix_pos + 0] & 0xf];
			u32 hbp = hoge[pPix[pix_pos + 1] >> 4];
			u32 lbp = hoge[pPix[pix_pos + 1] & 0xf];
			u32 hgp = hoge[pPix[pix_pos + 2] >> 4];
			u32 lgp = hoge[pPix[pix_pos + 2] & 0xf];
			u32 hip = hoge[pPix[pix_pos + 3] >> 4];
			u32 lip = hoge[pPix[pix_pos + 3] & 0xf];
			u32  hz = (hip << 3) | (hgp << 2) | (hbp << 1) | hrp;
			u32  lz = (lip << 3) | (lgp << 2) | (lbp << 1) | lrp;

			for(i=0; i<len; i++)
			{
				if(y + i < cy)
				{
					q[0] = (u8)(hz >> 24);
					q[1] = (u8)(hz >> 16);
					q[2] = (u8)(hz >>  8);
					q[3] = (u8)(hz      );
					q[4] = (u8)(lz >> 24);
					q[5] = (u8)(lz >> 16);
					q[6] = (u8)(lz >>  8);
					q[7] = (u8)(lz      );
				}

				 q += cx;
			}
		}
	}

	Anim.cx = cx;
	Anim.cy = cy;
	Anim.pDat = pDat;
	save_file(argv[1]);

	free(pIdx);
	free(pPix);
	free(Anim.pDat);

	return 0;
}
