// ToHeart アーカイブ展開ツール（LVNS3DAT.PAK, LVNS3SCN.PAK）
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

//---------------------------------------------------------------------------
#define PAK_KEY_LEN 11

typedef struct {
	// pak data
	unsigned char* p;
	long size;
	int  file_num;
	int  key[PAK_KEY_LEN];

	// file list
	char** name;
	int*   pos;
	int*   len;
} ST_PAK;

ST_PAK Pak;

//---------------------------------------------------------------------------
void PakOpen(const char* fname);
void PakChkMagic();
void PakGetNum();
void PakGetKey();
void PakCalloc();
void PakExtTable();
void PakExtAll();
void PakFree();
int  Swap(int b[]);


//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	PakOpen(argv[1]);

	PakChkMagic();
	PakGetNum();
	PakGetKey();
	PakCalloc();
	PakExtTable();
	PakExtAll();
	PakFree();

	return 0;
}
//---------------------------------------------------------------------------
void PakOpen(const char* fname)
{
	// get filesize
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "Open Error fp %s\n", fname);
		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	Pak.size = ftell(fp);

	// read file
	Pak.p = calloc(Pak.size, sizeof(char));

	if(Pak.p == NULL)
	{
		fprintf(stderr, "Open Calloc Error\n");
		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(Pak.p, 1, Pak.size, fp);

	fclose(fp);
}
//---------------------------------------------------------------------------
void PakChkMagic()
{
	char buf[9];

	for(int i=0; i<8; i++)
	{
		buf[i] = Pak.p[i];
	}
	buf[8] = '\0';

	if(strcmp(buf, "LEAFPACK"))
	{
		fprintf(stderr, "This file isn't a Leaf archive file.\n");
		exit(1);
	}
}
//---------------------------------------------------------------------------
void PakGetNum()
{
	Pak.file_num = (Pak.p[9] << 8) | Pak.p[8];

	if(Pak.file_num != 0x0248 && Pak.file_num != 0x03e1)
	{
		fprintf(stderr, "This file isn't a To Heart archive file.\n");
		exit(1);
	}
}
//---------------------------------------------------------------------------
void PakGetKey()
{
	// find the top of table
	unsigned char* p = Pak.p + Pak.size - 24 * Pak.file_num;

	// zero
	Pak.key[0] = p[11];

	// 1st position, (maybe :-)) constant
	Pak.key[1]  = (p[12] - 0x0a) & 0xff;
	Pak.key[2]  =  p[13];
	Pak.key[3]  =  p[14];
	Pak.key[4]  =  p[15];

	// 2nd position, from 1st next position
	Pak.key[5]  = (p[38] -  p[22] + Pak.key[0]) & 0xff;
	Pak.key[6]  = (p[39] -  p[23] + Pak.key[1]) & 0xff;

	// 3rd position, from 2nd next position
	Pak.key[7]  = (p[62] - p[46] + Pak.key[2]) & 0xff;
	Pak.key[8]  = (p[63] - p[47] + Pak.key[3]) & 0xff;

	// 1st next position, from 2nd position
	Pak.key[9]  = (p[20] - p[36] + Pak.key[3]) & 0xff;
	Pak.key[10] = (p[21] - p[37] + Pak.key[4]) & 0xff;
}
//---------------------------------------------------------------------------
void PakCalloc()
{
	// TODO calloc check

	Pak.name = (char**)calloc(Pak.file_num, sizeof(char*));

	for(int i=0; i<Pak.file_num; i++)
	{
		Pak.name[i] = (char*)calloc(13, sizeof(char));
	}

	Pak.pos = (int*)calloc(Pak.file_num, sizeof(int));
	Pak.len = (int*)calloc(Pak.file_num, sizeof(int));
}
//---------------------------------------------------------------------------
void PakExtTable()
{
	char buf[12];
	int  tmp[4];

	int k = 0;
	int l;

	// set a position to the head of the header part
	unsigned char* p = Pak.p + Pak.size - 24 * Pak.file_num;

	for(int i=0; i<Pak.file_num; i++)
	{
		// get filename
		for(int j=0; j<12; j++)
		{
			buf[j] = (*p++ - Pak.key[k++]) & 0xff;
			k %= PAK_KEY_LEN;
		}

		for(l=0; l<8 && buf[l] != 0x20; l++)
		{
			Pak.name[i][l] = buf[l];
		}

		Pak.name[i][l++] = '.';
		Pak.name[i][l++] = buf[8];
		Pak.name[i][l++] = buf[9];
		Pak.name[i][l++] = buf[10];
		Pak.name[i][l]   = '\0';

		// a position in the archive file
		for(int j=0; j<4; j++)
		{
			tmp[j] = (*p++ - Pak.key[k++]) & 0xff;
			k %= PAK_KEY_LEN;
		}
		Pak.pos[i] = Swap(tmp);

		// file length
		for(int j=0; j<4; j++)
		{
			tmp[j] = (*p++ - Pak.key[k++]) & 0xff;
			k %= PAK_KEY_LEN;
		}
		Pak.len[i] = Swap(tmp);

		// next file
		for(int j=0; j<4; j++)
		{
			tmp[j] = (*p++ - Pak.key[k++]) & 0xff;
			k %= PAK_KEY_LEN;
		}
		// no use next pos

	}
}
//---------------------------------------------------------------------------
void PakExtAll()
{
	unsigned char* p;
	int k;

	for(int i=0; i<Pak.file_num; i++)
	{
		FILE* fp = fopen(Pak.name[i], "wb");

		if(fp == NULL)
		{
			printf("Can't write %s.\n", Pak.name[i]);
			exit(1);
		}

		printf("extracting %s\n", Pak.name[i]);

		p = Pak.p + Pak.pos[i];
		k = 0;

		for(int j=0; j<Pak.len[i]; j++)
		{
			fputc((*p++ - Pak.key[k++]) & 0xff, fp);
			k %= PAK_KEY_LEN;
		}
		fclose(fp);

	}

	printf("All files are extracted.\n");
}
//---------------------------------------------------------------------------
void PakFree()
{
	free(Pak.p);

	for(int i=0; i<Pak.file_num; i++)
	{
		free(Pak.name[i]);
	}

	free(Pak.name);
	free(Pak.pos);
	free(Pak.len);
}
//---------------------------------------------------------------------------
int Swap(int b[])
{
	return (b[3] << 24) | (b[2] << 16) | (b[1] << 8) | b[0];
}
