// CRLFÅASPACEÇ'\0'Ç…ïœä∑
// gcc txt_crlf.c -s -o txt_crlf

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

//---------------------------------------------------------------------------
typedef unsigned char   u8;
typedef char            s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;


typedef struct {
	u8*   p;
	u32   size;

} ST_BIT;

//---------------------------------------------------------------------------
ST_BIT Bit;


//---------------------------------------------------------------------------
void BitCalloc(char* fname);
void BitFree(void);

//---------------------------------------------------------------------------
void BitCalloc(char* fname)
{
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "error fp\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Bit.size = ftell(fp);

	Bit.p = calloc(Bit.size, sizeof(u8));

	if(Bit.p == NULL)
	{
		fprintf(stderr, "error calloc\n");

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
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "txt_crlf [filename]\n");
		exit(1);
	}

	if(strlen(argv[1]) > 30)
	{
		printf("too long file name\n");

		exit(1);
	}

	printf("txt_crlf... %s\n", argv[1]);

	BitCalloc(argv[1]);


	char sname[50];
	strncpy(sname, argv[1], 40);

	char* n = strchr(sname, '.');

	if(n == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	n[1] = 's';
	n[2] = '0';
	n[3] = '1';

	FILE* fp = fopen(sname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open savefille\n");

		exit(1);
	}


	u8 c;
	s32 i;

	for(i=0; i<Bit.size; i++)
	{
		u8 c = Bit.p[i];

		// CR
		if(c == 0x0D)
		{
			continue;
		}

		// LF or SPACE
		if(c == 0x0A || c == 0x20)
		{
			c = 0x00;
		}

		fputc(c, fp);
	}

	fclose(fp);
	BitFree();

	return 0;
}
