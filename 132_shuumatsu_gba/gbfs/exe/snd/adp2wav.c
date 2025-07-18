// gcc adp2wav.c -s -o adp2wav

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

typedef struct {
	s32 prevSample;
	s32 quantIdx;

} ST_ADP;

//---------------------------------------------------------------------------
ST_BIT Bit;
ST_ADP Adp[2];


u16 QuantizeTable[] = {
	0x0007, 0x0008, 0x0009, 0x000A, 0x000B, 0x000C, 0x000D, 0x000E,
	0x0010, 0x0011, 0x0013, 0x0015, 0x0017, 0x0019, 0x001C, 0x001F,
	0x0022, 0x0025, 0x0029, 0x002D, 0x0032, 0x0037, 0x003C, 0x0042,
	0x0049, 0x0050, 0x0058, 0x0061, 0x006B, 0x0076, 0x0082, 0x008F,
	0x009D, 0x00AD, 0x00BE, 0x00D1, 0x00E6, 0x00FD, 0x0117, 0x0133,
	0x0151, 0x0173, 0x0198, 0x01C1, 0x01EE, 0x0220, 0x0256, 0x0292,
	0x02D4, 0x031C, 0x036C, 0x03C3, 0x0424, 0x048E, 0x0502, 0x0583,
	0x0610, 0x06AB, 0x0756, 0x0812, 0x08E0, 0x09C3, 0x0ABD, 0x0BD0,
	0x0CFF, 0x0E4C, 0x0FBA, 0x114C, 0x1307, 0x14EE, 0x1706, 0x1954,
	0x1BDC, 0x1EA5, 0x21B6, 0x2515, 0x28CA, 0x2CDF, 0x315B, 0x364B,
	0x3BB9, 0x41B2, 0x4844, 0x4F7E, 0x5771, 0x602F, 0x69CE, 0x7462, 0x7FFF,
};

s32 IncrementTable[] = {
	-1, -1, -1, -1, 2, 4, 6, 8, -1, -1, -1, -1, 2, 4, 6, 8
};

//---------------------------------------------------------------------------
void  BitCalloc(char* fname);
void  BitFree(void);
void  BitSeek(s32 pos);
u8    BitGet8(void);
u16   BitGet16(void);
u32   BitGet32(void);
s32   BitGetSize(void);

s16   AdpDecode(s32 no, s32 sample);

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
s16 AdpDecode(s32 no, s32 sample)
{
	ST_ADP* p = &Adp[no];

	sample &= 0xF;

	u16 quant = QuantizeTable[p->quantIdx];
	p->quantIdx += IncrementTable[sample];

	if(p->quantIdx < 0)
	{
		p->quantIdx = 0;
	}
	else if(p->quantIdx > 0x58)
	{
		p->quantIdx = 0x58;
	}

	s32 step = (2 * (sample & 7) + 1) * quant >> 3;

	if(sample < 8)
	{
		s32 max = p->prevSample + step;

		if(max > 32767)
		{
			max = 32767;
		}

		sample = max;
	}
	else
	{
		s32 min = p->prevSample - step;

		if(min < -32768)
		{
			min = -32768;
		}

		sample = min;
	}

	p->prevSample = sample;

	return (s16)sample;
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
		printf("adp2wav [ADP File]\n");

		exit(0);
	}

	printf("adp2wav... %s\n", argv[1]);


	BitCalloc(argv[1]);

	u32 sampleRate = BitGet32();

	if(sampleRate < 8000 || sampleRate > 96000)
	{
		fprintf(stderr, "error sampleRate %d\n", sampleRate);

		exit(1);
	}

	assert(sampleRate == 0x5622 || sampleRate == 0xAC44);

	u16 channels = BitGet16();

	if(channels != 1 && channels != 2)
	{
		fprintf(stderr, "error channels %d\n", channels);

		exit(1);
	}

	BitSeek(0xBC);
	s32 samples = BitGet32();
	s32 startPos = BitGet32();

	if(samples <= 0 || startPos >= BitGetSize())
	{
		fprintf(stderr, "error samples or startPos %d %d\n", samples, startPos);

		exit(1);
	}


	char fname[30];

	strncpy(fname, argv[1], 20);
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

	// "RIFF" chunk id
	WavWrite8(fp, 'R');
	WavWrite8(fp, 'I');
	WavWrite8(fp, 'F');
	WavWrite8(fp, 'F');

	// chunk size
	WavWrite32(fp, samples * channels * 16 / 8 + 44 - 8);

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
	WavWrite16(fp, channels);

	// sample rate
	WavWrite32(fp, sampleRate);

	// bytes per second (SampleRate * channels * BitsPerSample / 8)
	WavWrite32(fp, sampleRate * channels * 16 / 8);

	// block size (channels * BitsPerSample / 8)
	WavWrite16(fp, channels * 16 / 8);

	// bits per sample
	WavWrite16(fp, 0x10);

	// "data" subchunk id
	WavWrite8(fp, 'd');
	WavWrite8(fp, 'a');
	WavWrite8(fp, 't');
	WavWrite8(fp, 'a');

	// write data size (samples * channels * BitsPerSample / 8, or total file size - 44)
	WavWrite32(fp, samples * channels * 16 / 8);

	// decode ADPCM
	BitSeek(startPos);

	s32 dsize = samples * channels;

	while(dsize > 0)
	{
		u8 v = BitGet8();

		s16 s0 = AdpDecode(0, v >> 4);
		WavWrite16(fp, s0);
		dsize--;

		if(dsize == 0)
		{
			break;
		}

		s16 s1 = AdpDecode(1, v & 0xf);
		WavWrite16(fp, s1);
		dsize--;
	}

	fclose(fp);

	BitFree();

	return 0;
}
