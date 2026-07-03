// gcc tcdpak.c -s -o tcdpak

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
	FILE* fp;
	s32   size;
	s32   pos;

} ST_FILE;

//---------------------------------------------------------------------------
ST_FILE File;

//---------------------------------------------------------------------------
void FileOpen(char* fname);
void FileClose(void);
void FileSeek(s32 pos);
void FileSave(s32 pos, s32 size, char* fname);
u8   FileGet8(void);
u16  FileGet16(void);
u32  FileGet32(void);
s32  FileGetSize(void);

//---------------------------------------------------------------------------
void FileOpen(char* fname)
{
	memset(&File, 0x00, sizeof(ST_FILE));

	File.fp = fopen(fname, "rb");

	if(File.fp == NULL)
	{
		fprintf(stderr, "couldn't find file \"%s\"\n", fname);

		exit(1);
	}

	fseek(File.fp, 0, SEEK_END);
	File.size = ftell(File.fp);

	fseek(File.fp, 0, SEEK_SET);
}
//---------------------------------------------------------------------------
void FileClose(void)
{
	fclose(File.fp);
}
//---------------------------------------------------------------------------
void FileSeek(s32 pos)
{
	fseek(File.fp, pos, SEEK_SET);

	File.pos = pos;
}
//---------------------------------------------------------------------------
u8 FileGet8(void)
{
	assert(File.pos < File.size);

	File.pos++;

	return fgetc(File.fp);
}
//---------------------------------------------------------------------------
u16 FileGet16(void)
{
	u16 b1 = FileGet8();
	u16 b2 = FileGet8() << 8;

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 FileGet32(void)
{
	u32 b1 = FileGet8();
	u32 b2 = FileGet8() <<  8;
	u32 b3 = FileGet8() << 16;
	u32 b4 = FileGet8() << 24;

	return b4 | b3 | b2 | b1;
}
//---------------------------------------------------------------------------
s32 FileGetSize(void)
{
	return File.size;
}
//---------------------------------------------------------------------------
void FileSave(s32 pos, s32 size, char* fname)
{
	FILE* fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open file \"%s\"\n", fname);

		exit(1);
	}

	FileSeek(pos);

	s32 i;

	for(i=0; i<size; i++)
	{
		fputc(FileGet8(), fp);
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("tcdpak [TCD File]\n");

		exit(0);
	}

	printf("tcdpak... %s\n", argv[1]);

	FileOpen(argv[1]);


	u32 sig = FileGet32();

	// "TCD1"
	if(sig != 0x31444354)
	{
		printf("%s is not TCD1 file\n", argv[1]);

		exit(1);
	}

	s32 fileCnt    = FileGet32();
	s32 fileOffset = FileGet32();
	s32 nameOffset = FileGet32();
	s32 i;


	// オフセットを複合化
	u32* pOffset = (u32*)calloc(fileCnt+1, sizeof(u32));

	if(pOffset == NULL)
	{
		fprintf(stderr, "calloc offset error\n");

		exit(1);
	}

	FileSeek(fileOffset);

	for(i=0; i<fileCnt; i++)
	{
		pOffset[i] = FileGet32() - (fileOffset << ((i & 7) + 8));
	}
	pOffset[i] = FileGet32();


	// ファイル名を複合化
	s32 nameSize = FileGetSize() - nameOffset;
	u8* pName = (u8*)calloc(nameSize, sizeof(u8));

	if(pName == NULL)
	{
		fprintf(stderr, "calloc name error\n");

		exit(1);
	}

	FileSeek(nameOffset);

	for(i=0; i<nameSize; i++)
	{
		u8 c = FileGet8();

		if(c != 0)
		{
			c -= 0x57;
		}

		pName[i] = c;
	}


	// データ切り出し
	char* pStr = pName;

	for(i=0; i<fileCnt; i++)
	{
		printf("%03d %08X %08X %s\n", i, pOffset[i], pOffset[i+1] - pOffset[i], pStr);

		FileSave(pOffset[i], pOffset[i+1] - pOffset[i], pStr);

		// next filename
		while(*pStr++ != '\0')
		{
			// EMPTY
		}
	}


	free(pOffset);
	free(pName);

	FileClose();

	return 0;
}
