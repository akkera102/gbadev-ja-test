// SCNDAT.TBLÇÃèÓïÒíäèo
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
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
u8    BitGet8(void);

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
int main(int argc, char** argv)
{
	printf("scntbl... \n");

	BitCalloc("SCNDAT.TBL");
	BitSeek(0x47);

	char s[9];
	s[8] = '\0';

	s32 i, j;

	// âÊëú
	for(i=0; i<0x93; i++)
	{
		for(j=0; j<8; j++)
		{
			s[j] = BitGet8();
		}

		printf("%02d %s\n", i, s);
	}

	// âπäy
	for(i=0; i<0x15; i++)
	{
		for(j=0; j<8; j++)
		{
			s[j] = BitGet8();
		}

		printf("%02d %s\n", i, s);
	}

	// å¯â âπ
	for(i=0; i<0x0C; i++)
	{
		for(j=0; j<8; j++)
		{
			s[j] = BitGet8();
		}

		printf("%02d %s\n", i, s);
	}


	BitFree();

	return 0;
}
