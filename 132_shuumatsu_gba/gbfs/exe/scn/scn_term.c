// ãÛîíÇ∆â¸çsÇ'\0'Ç…ïœçX
// gcc scn_term.c -s -o scn_term

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

} ST_SCN;

//---------------------------------------------------------------------------
ST_SCN Scn;


//---------------------------------------------------------------------------
void ScnCalloc(char* fname);
void ScnFree(void);

//---------------------------------------------------------------------------
void ScnCalloc(char* fname)
{
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "error fp\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Scn.size = ftell(fp);

	Scn.p = calloc(Scn.size, sizeof(u8));

	if(Scn.p == NULL)
	{
		fprintf(stderr, "error calloc\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Scn.p, 1, Scn.size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void ScnFree(void)
{
	free(Scn.p);

	Scn.p = NULL;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "scn_term [filename]\n");
		exit(1);
	}

	printf("scn_term... %s\n", argv[1]);

	ScnCalloc(argv[1]);


	char sname[30];
	strncpy(sname, argv[1], 20);

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


	s32 i = 0;

	while(i < Scn.size)
	{
		// CRLF or CR
		if(Scn.p[i] == 0x0D)
		{
			fputc('\0', fp);
			i += (i+1 < Scn.size && Scn.p[i+1] == 0x0A) ? 2 : 1;

			continue;
		}

		// LF
		if(Scn.p[i] == 0x0A)
		{
			fputc('\0', fp);
			i++;

			continue;
		}

		// ãÛîí
		if(Scn.p[i] == ' ')
		{
			fputc('\0', fp);
			i++;

			continue;
		}

		// ëº
		fputc(Scn.p[i], fp);
		i++;
	}

	fclose(fp);
	ScnFree();

	return 0;
}
