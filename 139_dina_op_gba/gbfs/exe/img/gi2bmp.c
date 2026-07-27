// gcc gi2bmp.c -s -o gi2bmp

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

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
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
u8    BitGet8(void);
u16   BitGet16(void);
u32   BitGet32(void);
s32   BitGetPos(void);
s32   BitGetSize(void);
u8*   BitGetPointer(void);

void  BmpWrite8(FILE* fp, u8 h);
void  BmpWrite16(FILE* fp, u16 h);
void  BmpWrite32(FILE* fp, u32 h);

u8*   DecMap(u8* in, u16* out);
u8*   DecTile(u8* in, u8* out);


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
	u16 b1 = BitGet8() << 8;
	u16 b2 = BitGet8();

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 BitGet32(void)
{
	u32 b1 = BitGet8() << 24;
	u32 b2 = BitGet8() << 16;
	u32 b3 = BitGet8() <<  8;
	u32 b4 = BitGet8();

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
u8* BitGetPointer(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p + Bit.pos;
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
u8* DecMap(u8* in, u16* out)
{
	// mov esi, [esp+4+_P]
	// mov edi, [esp+8+_P]
	u8* esi = in;
	u8* edi = (u8*)out;

	// mov [esp], dword ptr 0
	// xor eax, eax
	// xor ebx, ebx
	// xor ecx, ecx
	// xor edx, edx
	// xor ebp, ebp
	u8  z[4] = {0};
	u8  al   = 0;
	u8  bl   = 0;
	u8  bh   = 0;
	u8  cl   = 0;
	u8  dl   = 0;
	u32 ebp  = 0;

L_lp:

	// mov al, [esi]
	// inc esi
	al = *esi++;

	// test al, 80h
	// jz short #L0
	if((al & 0x80) == 0) goto L_L0;

	// mov bh, al
	// mov bl, al
	// and bh, 1Fh
	// add bl, bl
	// and bl, 0C0h
	// add bh, bl
	// jmp short #lp
	bh = al;
	bl = al;
	bh &= 0x1F;
	bl += bl;
	bl &= 0xC0;
	bh += bl;
	goto L_lp;

L_L0:

	// mov cl, al
	// shr cl, 4
	// and al, 15
	cl = al;
	cl >>= 4;
	al &= 15;

	// jmp dword ptr cs:#case_base[ecx*4]
	if(cl == 0) goto L_case0;
	if(cl == 1) goto L_case1;
	if(cl == 2) goto L_case2;
	if(cl == 3) goto L_case3;
	goto L_case4_7;

L_case0:
L_L00:

	// mov bl, [esi]
	// inc esi
	// mov [edi], bx
	// add edi, 2
	// dec al
	bl = *esi++;
	*edi++ = bl;
	*edi++ = bh;
	al--;

	// jge short #L00
	// jmp short #lp
	if((s8)al >= 0) goto L_L00;
	goto L_lp;

L_case1:

	// jz short #exit
	if(al == 0) goto L_exit;

	// mov dl, [esi]
	// inc esi
	dl = *esi++;

L_case2:

	// mov bl, dl
	bl = dl;

L_L20:

	// mov [edi], bx
	// add edi, 2
	// inc bl
	// dec al
	*edi++ = bl;
	*edi++ = bh;
	bl++;
	al--;

	// jge short #L20
	if((s8)al >= 0) goto L_L20;

	// mov dl, bl
	// jmp short #lp
	dl = bl;
	goto L_lp;

L_case3:

	// inc al
	// mov bl, [esi]
	// inc esi
	al++;
	bl = *esi++;

L_L30:

	// mov [edi], bx
	// add edi, 2
	// dec al
	*edi++ = bl;
	*edi++ = bh;
	al--;

	// jge short #L30
	if((s8)al >= 0) goto L_L30;

	// mov [esp+ebp], bl
	// inc ebp
	// and ebp, 3
	// jmp #lp
	z[ebp] = bl;
	ebp++;
	ebp &= 3;
	goto L_lp;

L_case4_7:

	// inc al
	// mov bl, [esp+ecx-4]
	al++;
	bl = z[cl - 4];

L_L40:

	// mov [edi], bx
	// add edi, 2
	// dec al
	*edi++ = bl;
	*edi++ = bh;
	al--;

	// jge short #L40
	// jmp #lp
	if((s8)al >= 0) goto L_L40;
	goto L_lp;

L_exit:

	// mov eax, esi
	// ret
	return esi;
}
//---------------------------------------------------------------------------
u8* DecTile(u8* in, u8* out)
{
	const u8 cycle[16] = {0,2,3,4,5,6,7,1, 0,10,11,12,13,14,15,9};

	// mov esi, [esp+4+_P]
	// mov edi, [esp+8+_P]
	u8* esi = in;
	u8* edi = out;

	// mov edx, 1
	// mov ebp, edx
	// xor eax, eax
	// xor ecx, ecx
	// xor ebx, ebx
	u32 edx = 1;
	u32 ebp = 1;
	u32 eax = 0;
	u32 ebx = 0;
	u32 ecx = 0;

	u8 al = 0;
	u8 ah = 0;
	u8 bl = 0;
	u8 cl = 0;
	u8 dl = 0;

	// y equ esp
	// z equ esp+8
	// mov [esp], eax
	// mov [esp+4], eax
	// mov [esp+8], eax
	// mov [esp+12], eax
	u8 yz[16] = {0};

L_lp:

	// mov cl, [esi]
	// xor ebx, ebx
	// inc esi
	cl = *esi++;
	ecx = (ecx & 0xFFFFFF00) | cl;
	ebx = 0;
	bl = 0;

	// mov bl, cl
	// shr bl, 6
	bl = ecx;
	bl >>= 6;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// jmp dword ptr cs:#case_base1[ebx*4]
	if(bl == 0) goto L_case0;
	if(bl == 1) goto L_case1;
	if(bl == 2) goto L_case2;
	if(bl == 3) goto L_case3;

L_case0:

	// mov bl, cl
	bl = ecx;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// shr cl, 3
	// and cl, 7
	cl = ecx;
	cl >>= 3;
	cl &= 7;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// jz short #F00
	if(cl == 0) goto L_F00;

	// mov cl, [z+ecx]
	// jmp short #F01
	cl = yz[8 + cl];
	ecx = (ecx & 0xFFFFFF00) | cl;
	goto L_F01;

L_F00:

	// mov cl, [esi]
	// inc esi
	cl = *esi++;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// mov [z+edx], cl
	// mov dl, cycle[edx]
	yz[8 + edx] = cl;
	dl = cycle[edx];
	edx = (edx & 0xFFFFFF00) | dl;

L_F01:

	// and bl, 7
	bl &= 7;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// jz short #F02
	if(bl == 0) goto L_F02;

	// mov ah, cl
	ah = cl;
	eax = (eax & 0xFFFF00FF) | (ah << 8);

L_F02:

	// cmp bl, 7
	// jne short #F03
	if(bl != 7) goto L_F03;

	// mov bl, [esi]
	// inc esi
	bl = *esi++;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// test bl, bl
	// jz #exit
	if(bl == 0) goto L_exit;

L_F03:

	// inc ebx
	ebx++;
	bl = ebx;

L_B04:

	// mov [edi], cl
	// inc edi
	// dec ebx
	*edi++ = cl;
	ebx--;
	bl = ebx;

	// jge short #B04
	// jmp short #lp
	if((s32)ebx >= 0) goto L_B04;
	goto L_lp;

L_case1:

	// bswap eax
	eax = ((eax >> 24) & 0xFF) | ((eax >> 8) & 0xFF00) | ((eax << 8) & 0xFF0000) | ((eax << 24) & 0xFF000000);
	al = eax;
	ah = eax >> 8;

	// test cl, 100000b
	// jnz short #F10
	if((cl & 0x20) != 0) goto L_F10;

	// mov ax, [esi]
	// add esi, 2
	// sub al, ah
	al = *esi++;
	ah = *esi++;
	al -= ah;
	eax = (eax & 0xFFFF0000) | (ah << 8) | al;

L_F10:

	// mov bl, 4
	bl = 4;
	ebx = (ebx & 0xFFFFFF00) | bl;

L_B11:

	// mov [edi], ah
	*edi = ah;

	// test cl, 10000b
	// jnz short #F12
	if((cl & 0x10) != 0) goto L_F12;

	// add [edi], al
	*edi += al;

L_F12:

	// inc edi
	// add cl, cl
	edi++;
	cl += cl;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// dec bl
	bl--;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// jge short #B11
	if((s8)bl >= 0) goto L_B11;

	// bswap eax
	eax = ((eax >> 24) & 0xFF) | ((eax >> 8) & 0xFF00) | ((eax << 8) & 0xFF0000) | ((eax << 24) & 0xFF000000);
	al = eax;
	ah = eax >> 8;

	// jmp #lp
	goto L_lp;

L_case2:

	// mov bl, cl
	// and bl, 3
	bl = ecx;
	bl &= 3;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// shr cl, 2
	cl >>= 2;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// and ecx, 15
	// jz #case_c0
	// cmp cl, 8
	// je #case_c8
	ecx &= 15;
	cl = ecx;
	if(ecx == 0) goto L_case_c0;
	if(ecx == 8) goto L_case_c8;

L_B20:

	// mov al, [y+ecx]
	al = yz[ecx];
	eax = (eax & 0xFFFFFF00) | al;

	// mov [edi], al
	// inc edi
	// mov cl, cycle[ecx]
	*edi++ = al;
	cl = cycle[ecx];
	ecx = (ecx & 0xFFFFFF00) | cl;

	// dec ebx
	// jge short #B20
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B20;
	goto L_lp;

L_case_c8:

	// mov ecx, [edi-8]
	// mov [edi], ecx
	// add edi, 4
	// xor ecx, ecx
	ecx = edi[-8] | (edi[-7] << 8) | (edi[-6] << 16) | (edi[-5] << 24);
	*edi++ = (ecx      ) & 0xFF;
	*edi++ = (ecx >>  8) & 0xFF;
	*edi++ = (ecx >> 16) & 0xFF;
	*edi++ = (ecx >> 24) & 0xFF;
	ecx = 0;
	cl = 0;

L_B21:

	// mov al, [edi-8]
	// mov [edi], al
	// inc edi
	al = edi[-8];
	eax = (eax & 0xFFFFFF00) | al;
	*edi++ = al;

	// dec ebx
	// jge short #B21
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B21;
	goto L_lp;

L_case_c0:
L_B22:

	// mov al, [esi]
	// inc esi
	// mov [edi], al
	// inc edi
	al = *esi++;
	eax = (eax & 0xFFFFFF00) | al;
	*edi++ = al;

	// mov [y+ebp], al
	// movzx ebp, cycle[ebp]
	yz[ebp] = al;
	ebp = cycle[ebp];

	// dec ebx
	// jge short #B22
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B22;
	goto L_lp;

L_case3:

	// mov bl, cl
	// and bl, 7
	bl = cl;
	bl &= 7;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// shr cl, 3
	// and cl, 7
	cl >>= 3;
	cl &= 7;
	ecx = (ecx & 0xFFFFFF00) | cl;

	// jz short #F30
	if(cl == 0) goto L_F30;

	// mov al, [y+ecx]
	// mov [edi], al
	// inc edi
	// jmp short #F31
	al = yz[ecx];
	eax = (eax & 0xFFFFFF00) | al;
	*edi++ = al;
	goto L_F31;

L_F30:

	// mov al, [esi]
	// inc esi
	al = *esi++;
	eax = (eax & 0xFFFFFF00) | al;

	// mov [edi], al; inc edi
	// mov [y+ebp], al
	// movzx ebp, cycle[ebp]
	*edi++ = al;
	yz[ebp] = al;
	ebp = cycle[ebp];

L_F31:

	// cmp bl, 7
	// jne short #F32
	if(bl != 7) goto L_F32;

	// mov bl, [esi]
	// inc esi
	bl = *esi++;
	ebx = (ebx & 0xFFFFFF00) | bl;

	// test bl, bl
	// jz short #exit
	if(bl == 0) goto L_exit;

L_F32:
L_B32:

	// mov [edi], ah
	// inc edi
	*edi++ = ah;

	// dec ebx
	// jge short #B32
	// jmp #lp
	ebx--;
	bl = ebx;
	if((s32)ebx >= 0) goto L_B32;
	goto L_lp;

L_exit:

	// mov GI1nextFontBuf, edi
	// mov eax, esi
	// ret
	return edi;
}
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("gi2bmp [GI File]\n");

		exit(0);
	}

	printf("gi2bmp... %s\n", argv[1]);


	BitCalloc(argv[1]);
	BitSeek(0x8);

	u16 width  = BitGet16();
	u16 height = BitGet16();
	u16 chk    = BitGet16();
	u16 scr    = BitGet16();

//	printf("w:%d h:%d c:%x s:%d\n", width, height, chk, scr);

	bool isPal = (chk == 0) ? false : true;
	s32  bpp   = ((isPal == true) ? 1 : 3);

	if(isPal == false)
	{
		// ヘッダ修正 229 -> 224
		height = 224;
	}

	u8* pDat = (u8*)calloc(width * height * bpp, 1);

	if(pDat == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");

		exit(1);
	}

	assert(width  <= 40*8);
	assert(height <= 40*8);

	u8  pal[256 * 4] = {0};
	u16 map[40 * 40] = {0};
	u8  tile[40 * 40 * 64] = {0};
	s32 i, j;

	if(isPal == true)
	{
		// 8ビットパレット
		u16 nazo   = BitGet16();		// 必ず0
		u16 palCnt = BitGet16();

		for(i=0, j=0; i<palCnt; i++)
		{
			u16 c = BitGet16();

			u8 b5 = (c >> 10) & 0x1F;
			u8 g5 = (c >>  5) & 0x1F;
			u8 r5 = (c >>  0) & 0x1F;

			pal[j++] = (b5 << 3) | (b5 >> 2);
			pal[j++] = (g5 << 3) | (g5 >> 2);
			pal[j++] = (r5 << 3) | (r5 >> 2);
			pal[j++] = 0;
		}

		u8* p1 = BitGetPointer();
		u8* p2 = DecMap(p1, map);
		DecTile(p2 + 2, tile);			// skip +2 max tile

		for(s32 ty=0; ty<height/8; ty++)
		{
			for(s32 tx=0; tx<width/8; tx++)
			{
				s32 n = map[tx + ty * (width / 8)];
				u8* t = &tile[n * 64];

				for(s32 y=0; y<8; y++)
				{
					for(s32 x=0; x<8; x++)
					{
						pDat[(ty * 8 + y) * width + (tx * 8 + x)] = t[y * 8 + x];
					}
				}
			}
		}
	}
	else
	{
		// 15ビットBGR
		for(s32 ty=0; ty<height/8; ty++)
		{
			for(s32 tx=0; tx<width/8; tx++)
			{
				for(s32 y=0; y<8; y++)
				{
					for(s32 x=0; x<8; x++)
					{
						u16 c = BitGet16();

						u8 b5 = (c >> 10) & 0x1F;
						u8 g5 = (c >>  5) & 0x1F;
						u8 r5 = (c >>  0) & 0x1F;

						s32 px  = tx * 8 + x;
						s32 py  = ty * 8 + y;
						s32 idx = (py * width + px) * 3;

						pDat[idx + 0] = (b5 << 3) | (b5 >> 2);
						pDat[idx + 1] = (g5 << 3) | (g5 >> 2);
						pDat[idx + 2] = (r5 << 3) | (r5 >> 2);
					}
				}
			}
		}
	}


	char fname[50] = {0};

	strncpy(fname, argv[1], 40);
	char* p = strchr(fname, '.');

	if(p != NULL)
	{
		strcpy(p, ".bmp");
	}
	else
	{
		strcat(fname, ".bmp");
	}

	FILE* fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open file\n");

		exit(1);
	}

	s32 stride   = (width * bpp + 3) & ~3;
	s32 offset   = 14 + 40 + ((isPal == true) ? 256 * 4 : 0);
	s32 dataSize = stride * height;
	s32 fileSize = offset + dataSize;

	// BITMAPFILEHEADER
	BmpWrite8(fp, 'B');
	BmpWrite8(fp, 'M');
	BmpWrite32(fp, fileSize);
	BmpWrite16(fp, 0);
	BmpWrite16(fp, 0);
	BmpWrite32(fp, offset);

	// BITMAPINFOHEADER
	BmpWrite32(fp, 40);
	BmpWrite32(fp, width);
	BmpWrite32(fp, height);
	BmpWrite16(fp, 1);
	BmpWrite16(fp, ((isPal == true) ? 8 : 24));
	BmpWrite32(fp, 0);
	BmpWrite32(fp, dataSize);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, 0);
	BmpWrite32(fp, ((isPal == true) ? 256 : 0));
	BmpWrite32(fp, ((isPal == true) ? 256 : 0));

	// PALETTE
	if(isPal == true)
	{
		for(i=0; i<256*4; i++)
		{
			BmpWrite8(fp, pal[i]);
		}
	}

	// DATA
	u8 pad[4 * 3] = {0};

	for(s32 y=height-1; y>=0; y--)
	{
		fwrite(pDat + y * (width * bpp), 1, (width * bpp), fp);

		if(stride > width * bpp) 
		{
			fwrite(pad, 1, stride - (width * bpp), fp);
		}
	}

	fclose(fp);
	free(pDat);
	BitFree();

	return 0;
}
