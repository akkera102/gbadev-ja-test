// Sogna SGSPAK (Windows Viper GTS)
// Copyright (C) 2024 Notequalsoft. Arranged by akkera102. GPL2 License.

// gcc sgspak.c -o sgspak

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
	s32 dig;
	u8  chr;
} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;


//---------------------------------------------------------------------------
void BitCalloc(char* fname);
void BitFree(void);
void BitSeek(s32 pos);
u8   BitGet1(void);
u8   BitGet4(void);
u8   BitGet8(void);
u16  BitGet16(void);
u32  BitGet32(void);

void SgsWriteDir(void);
void SgsWriteFile(s32 fcnt);
void SgsDec(u8* pD, s32 cmpSize, s32 orgSize);
void SgsCut(u8* pD, s32 cmpSize, s32 orgSize);

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
		fprintf(stderr, "calloc datSize error\n");

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
	u32 r = 0;
	s32 i;

	for(i=0; i<4; i++)
	{
		r <<= 1;
		r += BitGet1();
	}

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
void SgsWriteDir(void)
{
	char* dir[2] = { "ANM", "PCM" };
	struct stat st;
	s32 i;

	for(i=0; i<2; i++)
	{
		stat(dir[i], &st);

		if(S_ISDIR(st.st_mode))
		{
			continue;
		}

		if(mkdir(dir[i]) == -1)
		{
			fprintf(stderr, "can't make directory %s\n", dir[i]);

			exit(1);
		}
	}
}
//---------------------------------------------------------------------------
void SgsWriteFile(s32 fcnt)
{
	BitSeek(0x10 + 0x20 * fcnt);

	// ファイル名を取得（フォルダパスが含まれる場合あり）
	char fname[16+1];
	s32  i;

	for(i=0; i<16; i++)
	{
		fname[i] = BitGet8();
	}
	fname[i] = '\0';

	// ファイル情報を取得
	bool isLz    = ((BitGet32() >> 24) == 0x01) ? true : false;
	s32  cmpSize = BitGet32();
	s32  orgSize = BitGet32();
	s32  pos     = BitGet32();

	printf("%03d %-16s %01X %08X %08X %08X\n", fcnt, fname, isLz, cmpSize, orgSize, pos);

	// 保存先のメモリ確保
	u8* pD = (u8*)calloc(orgSize, sizeof(u8));

	if(pD == NULL)
	{
		fprintf(stderr, "calloc datSize error\n");

		exit(1);
	}

	// 保存ファイルに書き込む
	FILE* fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open %s file\n", fname);

		exit(1);
	}

	// LZ解凍 or 単純コピー
	BitSeek(pos);

	if(isLz == true)
	{
		SgsDec(pD, cmpSize, orgSize);
	}
	else
	{
		SgsCut(pD, cmpSize, orgSize);
	}

	fwrite(pD, orgSize, 1, fp);

	free(pD);
	fclose(fp);
}
//---------------------------------------------------------------------------
// LZ
void SgsDec(u8* pD, s32 cmpSize, s32 orgSize)
{
	s32 in  = 0;
	s32 out = 0;
	s32 bit = 0;
	s32 msk = 0x00;

	while(in < cmpSize)
	{
		if(bit == 0)
		{
			bit = 8;
			msk = BitGet8();

			in++;
		}

		if((msk & 0x80) == 0x00)
		{
			pD[out++] = BitGet8();

			in++;
		}
		else
		{
			u32 w = BitGet16();
			in += 2;

			s32 b = w & 0x0FFF;
			s32 c = (w >> 12) + 1;
			s32 i;

			// TODO C#コードにある処理
/*
			if(b > out)
			{
				b = out;
			}
*/

			for(i=0; i<c; i++)
			{
				pD[out] = pD[out - b];
				out++;
			}
		}

		msk <<= 1;
		bit--;
	}

	assert(out == orgSize);
}
//---------------------------------------------------------------------------
//	TODO 検証データがないので合っているか不明
void SgsCut(u8* pD, s32 cmpSize, s32 orgSize)
{
	assert(cmpSize == orgSize);

	s32 i;

	for(i=0; i<cmpSize; i++)
	{
		*pD++ = BitGet8();
	}
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("sgspak [DAT File]\n");

		exit(0);
	}

	printf("sgspak... %s\n", argv[1]);

	BitCalloc(argv[1]);


	char buf[12];
	s32 i;

	// シグネチャチェック
	for(i=0; i<12; i++)
	{
		buf[i] = BitGet8();
	}

	if(memcmp(buf, "SGS.DAT 1.00", 12) != 0)
	{
		fprintf(stderr, "this is NOT a DAT file\n");

		exit(1);
	}

	// ANM, PCMディレクトリを作成
	SgsWriteDir();


	// ファイル個数を取得
	s32 fcnt = BitGet32();

	// 各ファイルを展開
	for(i=0; i<fcnt; i++)
	{
		SgsWriteFile(i);
	}


	BitFree();

	return 0;
}
