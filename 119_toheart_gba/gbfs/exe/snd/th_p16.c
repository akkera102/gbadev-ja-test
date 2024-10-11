// ToHeart 効果音ファイル（P16）のwav化ツール
// gcc th_p16.c -o th_p16

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

//---------------------------------------------------------------------------
typedef unsigned char  u_char;
typedef unsigned long  u_long;
typedef unsigned short u_short;

//---------------------------------------------------------------------------
u_char wavHeader[] = {
	0x52, 0x49, 0x46, 0x46, 0xff, 0xff, 0xff, 0xff, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6d, 0x74, 0x20,
	0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0xf8, 0x2a, 0x00, 0x00, 0x44, 0xac, 0x00, 0x00,
	0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61, 0xff, 0xff, 0xff, 0xff
};

typedef struct {
	// src
	u_char* p;
	u_long  size;

} ST_P16;

ST_P16 P16;

//---------------------------------------------------------------------------
void    P16Open(const char* fname);
void    P16Save(const char* fname);
void    P16Free();

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	printf("converting %s\n", argv[1]);

	P16Open(argv[1]);
	P16Save(argv[1]);
	P16Free();

	return 0;
}
//---------------------------------------------------------------------------
void P16Open(const char* fname)
{
	// get filesize
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "Open Error fp %s\n", fname);
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	P16.size = ftell(fp);

	// read file
	P16.p = calloc(P16.size, sizeof(u_char));

	if(P16.p == NULL)
	{
		fprintf(stderr, "Open Calloc Error\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(P16.p, 1, P16.size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void P16Save(const char* fname)
{
	char sname[13];
	strncpy(sname, fname, 13);

	char* p = strchr(sname, '.') + 1;
	p[0] = 'W';
	p[1] = 'A';
	p[2] = 'V';

	FILE* fp = fopen(sname, "wb");
	if(fp == NULL)
	{
		printf("Save Error %s\n", sname);
		exit(1);
	}

	// ヘッダ修正
	u_long size1 = P16.size + 44 -  8;		// header size - 8
	u_long size2 = P16.size;				// data size

	wavHeader[0x04] = (size1      ) & 0xff;
	wavHeader[0x05] = (size1 >>  8) & 0xff;
	wavHeader[0x06] = (size1 >> 16) & 0xff;
	wavHeader[0x07] = (size1 >> 24) & 0xff;

	wavHeader[0x28] = (size2      ) & 0xff;
	wavHeader[0x29] = (size2 >>  8) & 0xff;
	wavHeader[0x2a] = (size2 >> 16) & 0xff;
	wavHeader[0x2b] = (size2 >> 24) & 0xff;


	for(int i=0; i<sizeof(wavHeader); i++)
	{
		fputc(wavHeader[i], fp);
	}

	for(int i=0; i<P16.size; i++)
	{
		fputc(P16.p[i], fp);
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
void P16Free()
{
	free(P16.p);
}
