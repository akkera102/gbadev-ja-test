// ToHeart LFG, LF2ファイルのBMP化ツール
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

//---------------------------------------------------------------------------
#define IMG_TYPE_LFG 1
#define IMG_TYPE_LF2 2


//---------------------------------------------------------------------------
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned int   u_int;
typedef int            LONG;

typedef unsigned int   DWORD;
typedef unsigned short WORD;
typedef unsigned char  BYTE;

//---------------------------------------------------------------------------
// BMP
#pragma pack(1)

typedef struct {
	WORD  bfType; 
	DWORD bfSize; 
	WORD  bfReserved1; 
	WORD  bfReserved2; 
	DWORD bfOffBits; 
} BITMAPFILEHEADER;

typedef struct {
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct {
   BYTE   rgbBlue;
   BYTE   rgbGreen;
   BYTE   rgbRed;
   BYTE   rgbReserve;
} RGBQUAD;

//#pragma pack(4)


// IMG
typedef struct {
	// src
	u_char* p;
	int  type;

	// dst
	u_char* d;
	long size;

	int w;
	int h;
	int rw;
	int rh;
	int xoff;
	int yoff;

	int pal_num;
	u_char pal[256][3];

	// LFG tmp
	u_char* t;

} ST_IMG;

//---------------------------------------------------------------------------
ST_IMG Img;


//---------------------------------------------------------------------------
void ImgOpen(const char* fname);
void ImgType();
void ImgSave(const char* fname);
void ImgFree();

void ImgLFG();
void ImgLFGCalloc();
void ImgLFGPal();
void ImgLFGLzs();
void ImgLFGCnv();

void ImgLF2();
void ImgLF2Calloc();
void ImgLF2Pal();
void ImgLF2Lzs();

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	ImgOpen(argv[1]);
	ImgType();


	printf("converting %s\n", argv[1]);

	if(Img.type == IMG_TYPE_LFG)
	{
		ImgLFG();
	}
	else
	{
		ImgLF2();
	}

	ImgSave(argv[1]);
	ImgFree();

	return 0;
}
//---------------------------------------------------------------------------
void ImgOpen(const char* fname)
{
	// get filesize
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "Open Error fp %s\n", fname);
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	// read file
	Img.p = calloc(size, sizeof(u_char));

	if(Img.p == NULL)
	{
		fprintf(stderr, "Open Calloc Error\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Img.p, 1, size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void ImgType()
{
	char buf[9];

	for(int i=0; i<8; i++)
	{
		buf[i] = Img.p[i];
	}
	buf[8] = '\0';

	if(strncmp(buf, "LEAFCODE", 8) == 0)
	{
		Img.type = IMG_TYPE_LFG;
		return;
    }

	if(strncmp(buf, "LEAF256\0", 8) == 0)
	{
		Img.type = IMG_TYPE_LF2;
		return;
	}

	fprintf(stderr, "This file isn't LFG or LF2 format.\n");
	exit(1);
}
//---------------------------------------------------------------------------
void ImgLFG()
{
	ImgLFGCalloc();

	ImgLFGPal();
	ImgLFGLzs();
	ImgLFGCnv();
}
//---------------------------------------------------------------------------
void ImgLFGCalloc()
{
	int w, h, xoff, yoff;

	xoff = ( Img.p[33] << 8 | Img.p[32]) * 8;
	yoff = ( Img.p[35] << 8 | Img.p[34]);
	w    = ((Img.p[37] << 8 | Img.p[36]) + 1) * 8;
	h    = ((Img.p[39] << 8 | Img.p[38]) + 1);

	Img.w    = w;
	Img.h    = h;
	Img.rw   = w - xoff;
	Img.rh   = h - yoff;
	Img.xoff = xoff;
	Img.yoff = yoff;
	Img.d    = calloc(w * h, sizeof(u_char));

	if(Img.d == NULL)
	{
		perror("ImgLFGCalloc d Error");
		exit(1);
    }

	Img.size = Img.p[44] | (Img.p[45] << 8) | (Img.p[46] << 16) | (Img.p[47] << 24);
	Img.t = calloc(Img.size, sizeof(u_char));

	if(Img.t == NULL)
	{
		perror("ImgLFGCalloc t Error");
		exit(1);
    }
}
//---------------------------------------------------------------------------
void ImgLFGPal()
{
	Img.pal_num = 16;

	// 4bit 単位 *   RG BR GB RG BR ... 
	u_char* p = Img.p + 8;
	u_char* q = (u_char*)&Img.pal;		// R G B R G B R G B ...
	int up, lo;

	for(int i=0; i<24; i++)
	{
		up  = *p & 0xf0;
		up |= up >> 4;

		lo  = *p & 0x0f;
		lo |= lo << 4;

		*q++ = up;
		*q++ = lo;

		p++;
	}
}
//---------------------------------------------------------------------------
void ImgLFGLzs()
{
	u_char* loadBuf = Img.p + 48;
	u_char* saveBuf = Img.t;
	size_t  size    = Img.size;

	u_char ring[0x1000];
	int i, j;
	int c, m;
	int flag;
	int pos, len;

	// initialize ring buffer 
	memset(ring, 0, sizeof ring);

	// extract data 
	for(i=0, c=0, m=0xfee; i<size; )
	{
		// flag bits, which indicates data or location
		if(--c < 0)
		{
			flag = *loadBuf++;
			c = 7;
		}

		if(flag & 0x80)
		{
			// data
			saveBuf[i++] = ring[m++] = *loadBuf++;
			m &= 0xfff;
		}
		else
		{
			// copy from ring buffer 
			int data = loadBuf[0] + (loadBuf[1] << 8);
			loadBuf += 2;

			len = (data & 0x0f) + 3;
			pos = data >> 4;

			for(j=0; j<len; j++)
			{
				saveBuf[i++] = ring[m++] = ring[pos++];
				m &= 0xfff;
				pos &= 0xfff;
		    }
		}

		flag = flag << 1;
	}
}
//---------------------------------------------------------------------------
void ImgLFGCnv()
{
	// convert to indexed image
	u_char* p = Img.t;
	u_char* q = Img.d;

	// direction flag
	if(!Img.p[40])
	{
		// VERTICAL
		int x = 0, y = 0;

		for(int i=0; i<Img.size; i++, p++)
		{
			q[Img.rw * y + x    ] = (*p & 0x80) >> 4 | (*p & 0x20) >> 3 | (*p & 0x08) >> 2 | (*p & 0x02) >> 1;
			q[Img.rw * y + x + 1] = (*p & 0x40) >> 3 | (*p & 0x10) >> 2 | (*p & 0x04) >> 1 | (*p & 0x01);

			if(++y >= Img.rh)
			{
				y  = 0;
				x += 2;
			}
		}
	}
	else
	{
		// HORIZONTAL 
		for(int i=0; i<Img.size; i++, p++)
		{
			*q++ = (*p & 0x80) >> 4 | (*p & 0x20) >> 3 | (*p & 0x08) >> 2 | (*p & 0x02) >> 1;
			*q++ = (*p & 0x40) >> 3 | (*p & 0x10) >> 2 | (*p & 0x04) >> 1 | (*p & 0x01);
	    }
	}
}
//---------------------------------------------------------------------------
void ImgLF2()
{
	ImgLF2Calloc();

	ImgLF2Pal();
	ImgLF2Lzs();
}
//---------------------------------------------------------------------------
void ImgLF2Calloc()
{
	int w, h, xoff, yoff;

    xoff = ( Img.p[9]  << 8) | Img.p[8];
    yoff = ( Img.p[11] << 8) | Img.p[10];
    w    = ((Img.p[13] << 8) | Img.p[12]) + xoff;
    h    = ((Img.p[15] << 8) | Img.p[14]) + yoff;

	Img.w    = w;
	Img.h    = h;
	Img.rw   = w - xoff;
	Img.rh   = h - yoff;
	Img.xoff = xoff;
	Img.yoff = yoff;
    Img.size = Img.rw * Img.rh;
	Img.d    = calloc(w * h, sizeof(u_char));

	if(Img.d == NULL)
	{
		perror("ImgLF2Calloc Error");
		exit(1);
    }
}
//---------------------------------------------------------------------------
void ImgLF2Pal()
{
	Img.pal_num = Img.p[0x16];

	// read palette
	const u_char *p = Img.p + 0x18;

	for(int i=0; i<Img.pal_num; i++)
	{
		Img.pal[i][2] = *p++;
		Img.pal[i][1] = *p++;
		Img.pal[i][0] = *p++;
	}
}
//---------------------------------------------------------------------------
void ImgLF2Lzs()
{
	int ring[0x1000];
	int i, j;
	int c, m;
	int flag;
	int upper, lower;
	int pos, len;
	int d;
	int idx;
	int p;

	// initialize ring buffer
	for(i=0; i<0xfff; i++)
	{
		ring[i] = 0;
	}

	// extract data
	p = 0x18 + Img.pal_num * 3;

	for(i=0, c=0, m=0xfee; i<Img.size; )
	{
		// flag bits, which indicates data or location
		if(--c < 0)
		{
			flag = Img.p[p++];
			flag ^= 0xff;
			c = 7;
		}

		if(flag & 0x80)
		{
			// data
			d = Img.p[p++];
			d ^= 0xff;

			ring[m++] = d;
			idx = (i % Img.rw) + Img.rw * (Img.rh - i / Img.rw - 1);
			Img.d[idx] = d;

			i++;
			m &= 0xfff;
		}
		else
		{
			// copy from ring buffer
			upper = Img.p[p++];
			upper ^= 0xff;
			lower = Img.p[p++];
			lower ^= 0xff;

			len = (upper & 0x0f) + 3;
			pos = (upper >> 4) + (lower << 4);

			for(j=0; j<len && i<Img.size; j++)
			{
				idx = (i % Img.rw) + Img.rw * (Img.rh - i / Img.rw - 1);
				ring[m++] = Img.d[idx] = ring[pos++];

				i++;
				m &= 0xfff;
				pos &= 0xfff;
			}
		}
		flag = flag << 1;
	}
}
//---------------------------------------------------------------------------
void ImgSave(const char* fname)
{
	// rw サイズ調整（grit用）
	int pad;

	if((Img.rw % 4) == 0)
	{
		pad = 0;
	}
	else
	{
		pad = 4 - (Img.rw % 4);
	}

	BITMAPFILEHEADER bh;
	BITMAPINFOHEADER bi;
	RGBQUAD pal[256];

	int hsize = sizeof(bh) + sizeof(bi) + sizeof(pal);

	bh.bfType      = 0x4d42;		// 'BM'
	bh.bfSize      = hsize + (Img.rw + pad) * Img.rh;
	bh.bfReserved1 = 0;
	bh.bfReserved2 = 0;
	bh.bfOffBits   = hsize;

	bi.biSize          = sizeof(bi);
	bi.biWidth         = Img.rw;
	bi.biHeight        = Img.rh;
	bi.biPlanes        = 0x01;
	bi.biBitCount      = 0x08;
	bi.biCompression   = 0x00;
	bi.biSizeImage     = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed       = 0;
	bi.biClrImportant  = 0;


	for(int i=0; i<256; i++)
	{
		//  RGB -> BGR
		pal[i].rgbBlue    = Img.pal[i][2];
		pal[i].rgbGreen   = Img.pal[i][1];
		pal[i].rgbRed     = Img.pal[i][0];
		pal[i].rgbReserve = 0;
	}

	char sname[13];
	strncpy(sname, fname, 13);

	char* p = strchr(sname, '.') + 1;
	p[0] = 'B';
	p[1] = 'M';
	p[2] = 'P';

	FILE* fp = fopen(sname, "wb");
	if(fp == NULL)
	{
		printf("Save Error %s\n", sname);
		exit(1);
	}

	fwrite(&bh,  sizeof(u_char), sizeof(bh),  fp);
	fwrite(&bi,  sizeof(u_char), sizeof(bi),  fp);
	fwrite(&pal, sizeof(u_char), sizeof(pal), fp);

	for(int y=Img.rh-1; y>=0; y--)
	{
		for(int x=0; x<Img.rw; x++)
		{
			fputc(Img.d[(y * Img.rw) + x], fp);
		}

		for(int i=0; i<pad; i++)
		{
			fputc(0x00, fp);
		}
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
void ImgFree()
{
	free(Img.p);
	free(Img.d);

	if(Img.t != NULL)
	{
		free(Img.t);
	}
}
