// gcc dskpak.c -s -o dskpak

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
	char str[13];

} ST_BIT;

//---------------------------------------------------------------------------
void  BitCalloc(ST_BIT* b, char* fname);
void  BitFree(ST_BIT* b);
void  BitSeek(ST_BIT* b, s32 pos);
u8    BitGet8(ST_BIT* b);
u16   BitGet16(ST_BIT* b);
u32   BitGet32(ST_BIT* b);
char* BitGetStr(ST_BIT* b, s32 cnt, char* ext);

//---------------------------------------------------------------------------
void BitCalloc(ST_BIT* b, char* fname)
{
	memset(b, 0x00, sizeof(ST_BIT));


	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't find file \"%s\"\n", fname);

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	b->size = ftell(fp);

	b->p = (u8*)calloc(b->size, sizeof(u8));

	if(b->p == NULL)
	{
		fprintf(stderr, "calloc datSize error\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(b->p, 1, b->size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void BitFree(ST_BIT* b)
{
	free(b->p);

	b->p = NULL;
}
//---------------------------------------------------------------------------
void BitSeek(ST_BIT* b, s32 pos)
{
	b->pos = pos;
}
//---------------------------------------------------------------------------
void BitAdd(ST_BIT* b, s32 add)
{
	b->pos += add;
}
//---------------------------------------------------------------------------
u8 BitGet8(ST_BIT* b)
{
	assert(b->pos < b->size);

	return b->p[b->pos++];
}
//---------------------------------------------------------------------------
u16 BitGet16(ST_BIT* b)
{
	u16 b1 = BitGet8(b);
	u16 b2 = BitGet8(b) << 8;

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 BitGet32(ST_BIT* b)
{
	u32 b1 = BitGet8(b);
	u32 b2 = BitGet8(b) <<  8;
	u32 b3 = BitGet8(b) << 16;
	u32 b4 = BitGet8(b) << 24;

	return b4 | b3 | b2 | b1;
}
//---------------------------------------------------------------------------
char* BitGetStr(ST_BIT* b, s32 cnt, char* ext)
{
	// ファイル名と拡張子（8+1+3+'\0'）
	assert(cnt+1+3+1 <= sizeof(b->str));

	s32 i;

	for(i=0; i<cnt; i++)
	{
		b->str[i] = (char)BitGet8(b);
	}
	b->str[i] = '\0';

	strcat(b->str, ".");
	strcat(b->str, ext);

	return b->str;
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 4)
	{
		printf("dskpak [DSK File] [PFT File] [extension name]\n");

		exit(0);
	}

	if(strlen(argv[3]) > 3)
	{
		printf("too long extension name\n");

		exit(1);
	}

	printf("dskpak... %s %s %s\n", argv[1], argv[2], argv[3]);


	ST_BIT d;
	ST_BIT p;

	BitCalloc(&d, argv[1]);
	BitCalloc(&p, argv[2]);

	u16 headSize = BitGet16(&p);
	u16 clusterSize = BitGet16(&p);
	u32 fileCnt = BitGet32(&p);

	BitSeek(&p, headSize);


	s32 i;

	for(i=0; i<fileCnt; i++)
	{
		char* fname = BitGetStr(&p, 8, argv[3]);
		u32 offset = BitGet32(&p) * clusterSize;
		u32 size = BitGet32(&p);

//		printf("%03d %08X %08X %s\n", i, offset, size, fname);

		FILE* fp = fopen(fname, "wb");

		if(fp == NULL)
		{
			fprintf(stderr, "couldn't open %s file\n", fname);

			exit(1);
		}

		BitSeek(&d, offset);

		s32 j;

		for(j=0; j<size; j++)
		{
			fputc(BitGet8(&d), fp);
		}

		fclose(fp);
	}

	BitFree(&d);
	BitFree(&p);

	return 0;
}
