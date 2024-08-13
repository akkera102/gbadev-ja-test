// ジャンプラベルのアドレスをテーブル化。改行を'\0'に変更します
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

// gcc addlbl.c -o addlbl

//---------------------------------------------------------------------------
#define MAX_LBL_TABLE_CNT		100

typedef unsigned char   u8;
typedef char            s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;


typedef struct {
	u8* pS;
	u8* pD;
	u32 sizeS;
	u32 sizeD;

	s32 tblCnt;
	u32 tbl[MAX_LBL_TABLE_CNT];

} ST_LBL;

//---------------------------------------------------------------------------
ST_LBL Lbl;


//---------------------------------------------------------------------------
void open_file(char* fname)
{
	// get filesize
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "error fp\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Lbl.sizeS = ftell(fp);

	// read file & make work area
	Lbl.pS = calloc(Lbl.sizeS, sizeof(u8));
	Lbl.pD = calloc(Lbl.sizeS, sizeof(u8));

	if(Lbl.pS == NULL || Lbl.pD == NULL)
	{
		fprintf(stderr, "calloc error\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Lbl.pS, 1, Lbl.sizeS, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void save_file(char* fname)
{
	char sname[20];
	strncpy(sname, fname, 20);

	char* n = strchr(sname, '.');

	if(n == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");
		exit(1);
	}

	n[1] = 's';
	n[2] = 'c';
	n[3] = 'n';

	FILE* fp = fopen(sname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open savefille\n");
		exit(1);
	}

	fwrite(&Lbl.tblCnt, sizeof(u32), 1, fp);
	fwrite(&Lbl.tbl, sizeof(u32), Lbl.tblCnt, fp);
	fwrite(Lbl.pD, sizeof(u8), Lbl.sizeD, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void make_bin(void)
{
	u8* pS = Lbl.pS;
	u8* pD = Lbl.pD;
	u32 i = 0;
	u32 j = 0;

	while(i < Lbl.sizeS)
	{
		// LF
		if(pS[i] == 0x0A)
		{
			pD[j] = '\0';

			i++;
			j++;
			continue;
		}

		// CRLF or CR
		if(pS[i] == 0x0D)
		{
			pD[j] = '\0';

			i += (i+1 < Lbl.sizeS && pS[i+1] == 0x0A) ? 2 : 1;
			j++;
			continue;
		}

		// 空白
		if(pS[i] == 0x20)
		{
			pD[j] = '\0';

			i++;
			j++;
			continue;
		}

		// SJIS
		if(((pS[i] >= 0x81 && pS[i] <= 0x9f) || (pS[i] >= 0xe0 && pS[i] <= 0xef)) == true)
		{
			pD[j+0] = pS[i+0];
			pD[j+1] = pS[i+1];

			i += 2;
			j += 2;
			continue;
		}

		// 他
		pD[j] = pS[i];

		i++;
		j++;
	}

	Lbl.sizeD = j;
}
//---------------------------------------------------------------------------
void make_tbl(void)
{
	u8* pD = Lbl.pD;
	u32 i;

	for(i=0; i<Lbl.sizeD - sizeof("LBL"); i++)
	{
		if(pD[i+0] != 'L') continue;
		if(pD[i+1] != 'B') continue;
		if(pD[i+2] != 'L') continue;

		Lbl.tbl[Lbl.tblCnt++] = i;
	}

	// テーブルをファイル先頭に追加する為、オフセット値を変更します
	for(i=0; i<Lbl.tblCnt; i++)
	{
		Lbl.tbl[i] += 4 + Lbl.tblCnt * 4;

//		printf("%d %4X\n", i, Lbl.tbl[i]);
	}
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "addlbl [filename.txt]\n");
		exit(1);
	}

	printf("addlbl... %s\n", argv[1]);

	open_file(argv[1]);
	make_bin();
	make_tbl();
	save_file(argv[1]);


	free(Lbl.pS);
	free(Lbl.pD);

	return 0;
}
