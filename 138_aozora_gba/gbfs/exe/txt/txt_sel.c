// 選択肢コマンドにCASEオフセットを付与
// gcc txt_sel.c -s -o txt_sel

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <assert.h>

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


typedef struct {
	s32 max;
	s32 grp[200];
	s32 pos[200];

} ST_TBL;

//---------------------------------------------------------------------------
ST_BIT Bit;
ST_TBL Tbl;

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

	printf("txt_sel... %s\n", argv[1]);

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
	n[3] = '2';

	FILE* fp = fopen(sname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open savefille\n");

		exit(1);
	}


	// SEL, CAS, SEE位置を求めます
	// ネストしていないので順次格納（調査済）
	s32 idx = 0;
	s32 grp = -1;
	s32 pos, sta;

	for(pos=0; pos<Bit.size-3; pos++)
	{
		if(strncmp(&Bit.p[pos], "SEL", 3) == 0)
		{
			grp++;

			Tbl.grp[idx] = grp;
			Tbl.pos[idx] = pos;
			idx++;
		}

		if(strncmp(&Bit.p[pos], "CAS", 3) == 0)
		{
			Tbl.grp[idx] = grp;
			Tbl.pos[idx] = pos;
			idx++;
		}

		if(strncmp(&Bit.p[pos], "SEE", 3) == 0)
		{
			Tbl.grp[idx] = grp;
			Tbl.pos[idx] = pos;
			idx++;
		}
	}
	Tbl.max = idx;

/*
	s32 i;

	for(i=0; i<Tbl.max; i++)
	{
		printf("i:%02d grp:%02d pos:%04d\n", i, Tbl.grp[i], Tbl.pos[i]);
	}
*/

	idx = 0;
	s32 pad = 0;

	for(pos=0; pos<Bit.size; pos++)
	{
		fputc(Bit.p[pos], fp);

		if(idx >= Tbl.max)
		{
			continue;
		}

		// SELまでposを進める
		if(Tbl.pos[idx]+3 != pos)
		{
			continue;
		}

		// SELのグループ番号
		grp = Tbl.grp[idx];
		idx++;

		// CASとSEEの個数を記述
		s32 cnt = 0;

		do {
			cnt++;

		} while(idx+cnt < Tbl.max && grp == Tbl.grp[idx+cnt]);

		fprintf(fp, "%d%c", cnt, '\0');

		// 記入分のアドレスを調整
		pad += 2 + (4+1) * cnt;

		// CASとSEEのアドレスを記述
		s32 j;

		for(j=0; j<cnt; j++)
		{
			fprintf(fp, "%04X%c", Tbl.pos[idx+j] + pad, '\0');
		}

		idx += cnt;
	}


	fclose(fp);
	BitFree();

	return 0;
}
