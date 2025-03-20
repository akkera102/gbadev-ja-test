// Sogna PCM2WAV (Windows Viper V16 RISE)
// Copyright (C) 2024 Notequalsoft. Arranged by akkera102. GPL2 License.

// gcc pcm2wav.c -o pcm2wav

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
void BitCalloc(char* fname);
void BitFree(void);
u8   BitGet8(void);

void WavWrite8(FILE* fp, u8 h);
void WavWrite16(FILE* fp, u16 h);
void WavWrite32(FILE* fp, u32 h);
void WavWrite(char* fname);

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

	fclose(fp);
}
//---------------------------------------------------------------------------
void BitFree(void)
{
	free(Bit.p);

	Bit.p = NULL;
}
//---------------------------------------------------------------------------
u8 BitGet8(void)
{
	assert(Bit.pos < Bit.size);

	return Bit.p[Bit.pos++];
}
//---------------------------------------------------------------------------
void WavWrite8(FILE* fp, u8 h)
{
	u8 buf[1];

	buf[0] = h;

	fwrite(buf, 1, 1, fp);
}
//---------------------------------------------------------------------------
void WavWrite16(FILE* fp, u16 h)
{
	u8 buf[2];

	buf[0] = (h >> 0) & 0xFF;
	buf[1] = (h >> 8) & 0xFF;

	fwrite(buf, 2, 1, fp);
}
//---------------------------------------------------------------------------
void WavWrite32(FILE* fp, u32 h)
{
	u8 buf[4];

	buf[0] = (h >>  0) & 0xFF;
	buf[1] = (h >>  8) & 0xFF;
	buf[2] = (h >> 16) & 0xFF;
	buf[3] = (h >> 24) & 0xFF;

	fwrite(buf, 4, 1, fp);
}
//---------------------------------------------------------------------------
void WavWrite(char* fname)
{
	// 保存するファイル名の拡張子を変更
	char rname[30];
	strncpy(rname, fname, 20);

	char* p = strchr(rname, '.');

	if(p == NULL)
	{
		fprintf(stderr, "couldn't find extension\n");

		exit(1);
	}

	p[0] = '.';
	p[1] = 'w';
	p[2] = 'a';
	p[3] = 'v';
	p[4] = '\0';

	FILE* fp = fopen(rname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open WAV file\n");

		exit(1);
	}


	// "RIFF" chunk id
	WavWrite8(fp, 'R');
	WavWrite8(fp, 'I');
	WavWrite8(fp, 'F');
	WavWrite8(fp, 'F');

	// chunk size
	WavWrite32(fp, Bit.size + 44 - 8);

	// "WAVE" format id
	WavWrite8(fp, 'W');
	WavWrite8(fp, 'A');
	WavWrite8(fp, 'V');
	WavWrite8(fp, 'E');

	// "fmt " subchunk id
	WavWrite8(fp, 'f');
	WavWrite8(fp, 'm');
	WavWrite8(fp, 't');
	WavWrite8(fp, ' ');

	// 16 for subchunk size
	WavWrite32(fp, 0x10);

	// audio format (1 = linear quantization)
	WavWrite16(fp, 0x1);

	// number of channels
	WavWrite16(fp, 0x1);

	// sample rate
	WavWrite32(fp, 22050);

	// bytes per second (SampleRate * NumChannels * BitsPerSample / 8)
	WavWrite32(fp, 22050 * 1 * 8 / 8);

	// block size (NumChannels * BitsPerSample / 8)
	WavWrite16(fp, 1 * 8 / 8);

	// bits per sample
	WavWrite16(fp, 8);

	// "data" subchunk id
	WavWrite8(fp, 'd');
	WavWrite8(fp, 'a');
	WavWrite8(fp, 't');
	WavWrite8(fp, 'a');

	// write data size (NumSamples * NumChannels * BitsPerSample / 8, or total file size - 44)
	WavWrite32(fp, Bit.size);

	s32 i;

	for(i=0; i<Bit.size; i++)
	{
		WavWrite8(fp, (BitGet8() + 0x80) & 0xFF);
	}

	fclose(fp);
}
//---------------------------------------------------------------------------
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("pcn2wav [PCM File]\n");

		exit(0);
	}

	printf("pcm2wav... %s\n", argv[1]);


	BitCalloc(argv[1]);
	WavWrite(argv[1]);

	BitFree();

	return 0;
}
