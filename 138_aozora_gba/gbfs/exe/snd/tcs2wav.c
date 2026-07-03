// gcc tcs2wav.c -s -o tcs2wav

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
u16   BitGet16(void);
u32   BitGet32(void);
s32   BitGetSize(void);

void  WavWrite8(FILE* fp, u8 h);
void  WavWrite16(FILE* fp, u16 h);
void  WavWrite32(FILE* fp, u32 h);

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
u16 BitGet16(void)
{
	u16 b1 = BitGet8();
	u16 b2 = BitGet8() << 8;

	return b2 | b1;
}
//---------------------------------------------------------------------------
u32 BitGet32(void)
{
	u32 b1 = BitGet8();
	u32 b2 = BitGet8() <<  8;
	u32 b3 = BitGet8() << 16;
	u32 b4 = BitGet8() << 24;

	return b4 | b3 | b2 | b1;
}
//---------------------------------------------------------------------------
s32 BitGetSize(void)
{
	return Bit.size;
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
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("tcs2wav [TCS File]\n");

		exit(0);
	}

	if(strlen(argv[1]) > 30)
	{
		printf("too long file name\n");

		exit(1);
	}

	printf("tcs2wav... %s\n", argv[1]);


	char fname[50];

	strncpy(fname, argv[1], 40);
	char* p = strchr(fname, '.');

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

	FILE* fp = fopen(fname, "wb");

	if(fp == NULL)
	{
		fprintf(stderr, "couldn't open file\n");

		exit(1);
	}

	BitCalloc(argv[1]);

	s32 sample = BitGetSize() / 4;
	s32 sampleRate = 22050;
	s32 channel = 2;

	// "RIFF" chunk id
	WavWrite8(fp, 'R');
	WavWrite8(fp, 'I');
	WavWrite8(fp, 'F');
	WavWrite8(fp, 'F');

	// chunk size
	WavWrite32(fp, sample * channel * 16 / 8 + 44 - 8);

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

	// number of channel
	WavWrite16(fp, channel);

	// sample rate
	WavWrite32(fp, sampleRate);

	// bytes per second (SampleRate * channel * BitsPerSample / 8)
	WavWrite32(fp, sampleRate * channel * 16 / 8);

	// block size (channel * BitsPerSample / 8)
	WavWrite16(fp, channel * 16 / 8);

	// bits per sample
	WavWrite16(fp, 0x10);

	// "data" subchunk id
	WavWrite8(fp, 'd');
	WavWrite8(fp, 'a');
	WavWrite8(fp, 't');
	WavWrite8(fp, 'a');

	// write data size (sample * channel * BitsPerSample / 8, or total file size - 44)
	WavWrite32(fp, sample * channel * 16 / 8);

	s32 i;

	for(i=0; i<sample * channel; i++)
	{
		WavWrite16(fp, BitGet16());
	}

	fclose(fp);

	BitFree();

	return 0;
}
