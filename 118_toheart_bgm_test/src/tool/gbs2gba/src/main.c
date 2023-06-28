#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "cpu.h"
#include "mem.h"


//---------------------------------------------------------------------------
#define GB_CLOCK 4194304

typedef struct {
	char     sig[3];			// "GBS"
	uint8_t  ver;				// Version(1)
	uint8_t  numSong;			// Number of songs(1 - 255)
	uint8_t  firstSong;			// First song(usually 1)
	uint16_t adrLoad;			// Load address ($400-$7fff)
	uint16_t adrInit;			// Init address ($400-$7fff)
	uint16_t adrPlay;			// Play address ($400-$7fff)
	uint16_t adrStack;			// Stack pointer
	uint8_t  tma;				// Timer modulo
	uint8_t  tac;				// Timer control
	uint8_t  title[32];			// Title string
	uint8_t  author[32];		// Author string
	char     copyright[32];		// Copyright string

} __attribute__ ((__packed__)) ST_GBS_HEADER;


typedef struct {
	uint16_t adrLoad;
	uint16_t adrInit;
	uint16_t adrPlay;

	uint16_t baseRst;
	uint16_t baseSP;

} ST_GBS;

//---------------------------------------------------------------------------
ST_GBS Gbs;

FILE*    wp;
uint32_t wCnt;
uint32_t chLoop[4];
bool     isFileWrite;
bool     isAdrPlayLoop;


//---------------------------------------------------------------------------
void gbs_open(const char* fname);
void gbs_exec(void);
void gbs_exec_adr_init(void);
void gbs_exec_adr_play(void);
void gbs_save(const char* fname);


//---------------------------------------------------------------------------
void gbs_open(const char* fname)
{
	memset(&Gbs, 0x00, sizeof(ST_GBS));

	// get filesize
	FILE* fp = fopen(fname, "rb");

	if(fp == NULL)
	{
		fprintf(stderr, "Open Error fp %s\n", fname);

		exit(1);
	}

	fseek(fp, 0, SEEK_END);
	uint32_t size = ftell(fp);

	// read file
	uint8_t* p = calloc(size, sizeof(uint8_t));

	if(p == NULL)
	{
		fprintf(stderr, "Open Calloc Error\n");

		exit(1);
	}

	fseek(fp, 0, SEEK_SET);
	fread(p, 1, size, fp);
	fclose(fp);


	// load gbs header
	ST_GBS_HEADER* pG = (ST_GBS_HEADER*)p;

	Gbs.adrLoad = pG->adrLoad;
	Gbs.adrInit = pG->adrInit;
	Gbs.adrPlay = pG->adrPlay;
	Gbs.baseRst = pG->adrLoad;
	Gbs.baseSP  = pG->adrStack;

	printf("adrLoad:%4X\n", pG->adrLoad);
	printf("adrInit:%4X\n", pG->adrInit);
	printf("adrPlay:%4X\n", pG->adrPlay);

	// load gbs data
	uint8_t* pD = p + sizeof(ST_GBS_HEADER);
	int i;

	for(i=0; i<size - sizeof(ST_GBS_HEADER); i++)
	{
		gameboy_memory[Gbs.adrLoad + i] = *pD++;
	}

	free(p);

	// timer or v-blank
	if(pG->tac & 0x04)
	{
		uint32_t rate = 0;

		switch(pG->tac & 0x03)
		{
		case 0x0: rate = GB_CLOCK /  4096; break;	// 基本クロック1024分周    4096 Hz
		case 0x1: rate = GB_CLOCK / 26144; break;	// 基本クロック  16分周  262144 Hz
		case 0x2: rate = GB_CLOCK / 65536; break;	// 基本クロック  64分周   65536 Hz
		case 0x3: rate = GB_CLOCK / 16384; break;	// 基本クロック 256分周   16384 Hz
		}

		// CPU clock rate 2x?
		if(pG->tac & 0x80)
		{
			// GBC mode
			rate /= 2;
		}

		float hz = GB_CLOCK / rate / (float)(256 - pG->tma);
		printf("timing : %2.2fHz\n", hz);
//		printf("tac:0x%x tma:0x%x rate:%d\n", pG->tac, pG->tma, rate);
	}
	else
	{
		// 59.737 Hz
		printf("Timing : 59.737Hz(v-blank)\n");
	}
}
//---------------------------------------------------------------------------
void gbs_exec_adr_init(void)
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw  = Gbs.adrInit;
	gbz80.AF.b.h = 1;

	gameboy_cpu_execute_opcode();
}
//---------------------------------------------------------------------------
void gbs_exec_adr_play(void)
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw  = Gbs.adrPlay;
	gbz80.AF.b.h = 1;

	while(gbz80.SP.uw < Gbs.baseSP)
	{
		gameboy_cpu_execute_opcode();
	}
}
//---------------------------------------------------------------------------
void gbs_save(const char* fname)
{
	// save vgm modoki file
	char savname[0x100];
	int len = strlen(fname) & 0xff;

	strcpy(savname, fname);
	savname[len - 4] = '\0';
	strcat(savname, ".bin");

	wp = fopen(savname, "wb");

	if(wp == NULL)
	{
		printf("Error: savname open\n");

		exit(EXIT_FAILURE);
	}

	//adr_init
	gbs_exec_adr_init();
	fputc(0x61, wp);

	//adr_play
	wCnt = 0;
	memset(&chLoop, 0x00, sizeof(chLoop));

	isFileWrite = true;
	isAdrPlayLoop = true;

//	for(uint32_t i=0; i<0x20000; i++)

	while(isAdrPlayLoop == true)
	{
/*
		// GBS 4096Hzの場合...
		// 4096Hz / vBlank 60Hz = 68.266..

		for(uint32_t i=0; i<68; i++)
		{
			gbs_exec_adr_play();
		}
		fputc(0x61, wp);
*/

		// GBS Vblank
		gbs_exec_adr_play();
		// vblank command
		fputc(0x61, wp);
		wCnt++;
	}

	// patch
/*
	if(strncmp(savname, "th04.bin", len) == 0)
	{
		printf("patched. NR51 0xff\n");

		fputc(0xb3, wp);
		fputc(0x81, wp);
		fputc(0xff, wp);
		wCnt += 3;
	}
*/

	// end of mark
	fputc(0x66, wp);
	wCnt++;

	// loop point ch0 $01
	fputc((uint8_t)(chLoop[0] >>  0), wp);
	fputc((uint8_t)(chLoop[0] >>  8), wp);
	fputc((uint8_t)(chLoop[0] >> 16), wp);
	fputc((uint8_t)(chLoop[0] >> 24), wp);
	wCnt += 4;

	fclose(wp);
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("input filename\n");
		exit(0);
	}

	printf("converting %s\n", argv[1]);

	isFileWrite = false;
	memory_init();
	gameboy_cpu_hardreset();

	gbs_open(argv[1]);
	gbs_save(argv[1]);

	return 0;
}
