/*
 *  InfoGB - A portable GameBoy emulator
 *  Copyright (C) 2003  Jay's Factory <jays_factory@excite.co.jp>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 *  based on gbe - gameboy emulator
 *  Copyright (C) 1999  Chuck Mason, Steven Fuller, Jeff Miller
 */

#include <stdbool.h>
#include "system.h"
#include "mem.h"
#include "cpu.h"

//---------------------------------------------------------------------------
// main.c
extern FILE*    wp;
extern uint32_t wCnt;
extern uint32_t chLoop[8];
extern bool     isFileWrite;
extern bool     isAdrPlayLoop;


//---------------------------------------------------------------------------
unsigned char gameboy_memory[0x10000];


//---------------------------------------------------------------------------
void memory_init(void)
{
	memset(&gameboy_memory, 0x00, sizeof(gameboy_memory));
}
//---------------------------------------------------------------------------
int memory_read_hibyte(int reg)
{
	return gameboy_memory[0xFF00 + (reg & 0xFF)];
}
//---------------------------------------------------------------------------
void memory_write_hibyte(int reg, int value)
{
	memory_write_byte(0xFF00 + (reg & 0xFF), value & 0xff);
}
//---------------------------------------------------------------------------
unsigned char memory_read_byte(unsigned short int address)
{
	return gameboy_memory[address & 0xFFFF];
}
//---------------------------------------------------------------------------
unsigned short int memory_read_word(unsigned short int address)
{
	return (memory_read_byte(address) | (memory_read_byte(address+1) << 8));
}
//---------------------------------------------------------------------------
void memory_write_byte(unsigned short int address, unsigned char value)
{
	gameboy_memory[address & 0xFFFF] = value;

	if(address >= 0xff00)
	{
		memory_file_gba_patch(address & 0xff, value);
	}
}
//---------------------------------------------------------------------------
void memory_write_word(unsigned short int address, unsigned short int value)
{
	memory_write_byte(address, value & 0xFF);
	memory_write_byte(address + 1, value >> 8);
}
//---------------------------------------------------------------------------
void memory_file_gba_patch(unsigned char address, unsigned char value)
{
	if(isFileWrite == false)
	{
		return;
	}

	uint8_t reg = address;
	uint8_t adr;
	uint8_t dat;

	switch(reg)
	{
	case 0x10: adr = 0x60; break;	// NR 10
	case 0x11: adr = 0x62; break;	// NR 11
	case 0x12: adr = 0x63; break;	// NR 12
	case 0x13: adr = 0x64; break;	// NR 13
	case 0x14: adr = 0x65; break;	// NR 14
	case 0x16: adr = 0x68; break;	// NR 21
	case 0x17: adr = 0x69; break;	// NR 22
	case 0x18: adr = 0x6c; break;	// NR 23
	case 0x19: adr = 0x6d; break;	// NR 24
	case 0x1a: adr = 0x70; break;	// NR 30
	case 0x1b: adr = 0x72; break;	// NR 31
	case 0x1c: adr = 0x73; break;	// NR 32
	case 0x1d: adr = 0x74; break;	// NR 33
	case 0x1e: adr = 0x75; break;	// NR 34

	case 0x1f:
		// loop point
		switch(value)
		{
		// loop start point ch0-3
		case 0x01: chLoop[0] = wCnt; break;
		case 0x02: chLoop[1] = wCnt; break;
		case 0x04: chLoop[2] = wCnt; break;
		case 0x08: chLoop[3] = wCnt; break;

		// loop end point ch0-3
		case 0x81: chLoop[4] = wCnt;
			isFileWrite = false;
			isAdrPlayLoop = false;
			break;

		case 0x82: chLoop[5] = wCnt; break;
		case 0x84: chLoop[6] = wCnt; break;
		case 0x88: chLoop[7] = wCnt; break;
		default:
			printf("FF1F Error %x\n", value);
			exit(1);
		}

		printf("FF1F=%02X counter=%X\n", value, wCnt);
		return;

	case 0x20: adr = 0x78; break;	// NR 41
	case 0x21: adr = 0x79; break;	// NR 42
	case 0x22: adr = 0x7c; break;	// NR 43
	case 0x23: adr = 0x7d; break;	// NR 44
	case 0x24: adr = 0x80; break;	// NR 50
	case 0x25: adr = 0x81; break;	// NR 51
	case 0x26: adr = 0x84; break;	// NR 52

	// RAM
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x3d:
	case 0x3e:
	case 0x3f:
		adr = 0x90 + reg - 0x30;
		break;

	default:
		return;
	}

	dat = value;

	// NR 30
	if(adr == 0x70)
	{
		dat &= 0x80;
	}

	// NR 32
	if(adr == 0x73)
	{
		dat &= 0x60;
	}

	// NR 50
	if(adr == 0x80 && dat & 0x08)
	{
		printf("Warning: no use GBA bit. NR 50(FF24) Right Flag.\n");
	}

	// NR 50
	if(adr == 0x80 && dat & 0x80)
	{
		printf("Warning: no use GBA bit. NR 50(FF24) Left Flag.\n");
	}


	fputc(0xb3, wp);
	fputc(adr & 0xff, wp);
	fputc(dat & 0xff, wp);
	wCnt += 3;

	// add REG_SOUND3CNT_L = 0x40;
	if(adr >= 0x90 && adr <= 0x9f)
	{
		fputc(0xb3, wp);
		fputc(0x70, wp);
		fputc(0x40, wp);
		wCnt += 3;
	}
}
