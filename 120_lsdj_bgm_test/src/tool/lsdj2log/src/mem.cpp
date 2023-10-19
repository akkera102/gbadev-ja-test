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

#include "system.h"
#include "rom.h"
#include "mem.h"
#include "regs.h"
#include "joypad.h"
#include "cpu.h"
#include "vram.h"
#include "sound.h"
#include "main.h"

unsigned char *gameboy_memory[16];	/* 0-F */
unsigned char *video_ram    = (unsigned char *)NULL;	/* Mapped to 8 & 9 */
unsigned char *internal_ram = (unsigned char *)NULL;	/* Mapped to B and C */
unsigned char *bank_sixteen = (unsigned char *)NULL;	/* Mapped to F */
unsigned char *sprite_oam   = (unsigned char *)NULL;	/* Mapped to FE00 */
unsigned short int bkg_palettes[8][4];	/* 8 Palettes of 4 Colors Each */
unsigned short int obj_palettes[8][4];	/* " */

unsigned char mbc1_ram_bank_enable = 0;		/* Default is disabled */
unsigned char mbc1_address_line    = 0;
unsigned short int mbc5_rom_select = 0;

char vidram[0x4000];
char intram[0x8000];
unsigned char hiram[0x1000];
void reset_colors();
//void set_color(int num, int color);

int HDMADst;
int HDMASrc;
int HDMACnt;

extern int vram_mode;

void install_memory(int bank, void *fromwhere)
{
	gameboy_memory[bank] = (unsigned char *)fromwhere;
}

inline void memory_select_wram_bank(unsigned int bank, unsigned int where)
{
	char *ptr;

	if (!color_gameboy)	/* Useless on regular GB */
		return;	
	
	if (bank == 0)
		bank = 1;
	
	ptr = (char *)internal_ram + (bank * 0x1000);

	install_memory(where, ptr);
}

inline void memory_select_vram_bank(int bank, int where)
{
	char *ptr;
	
	if(!color_gameboy)
		return;
	
	ptr = (char *)video_ram + (bank * 0x2000);

	install_memory(where, ptr);
	install_memory(where + 1, ptr + 0x1000);
}

int initialize_memory()
{
	int i;
	
	for(i = 0; i < 16; i++) 
		gameboy_memory[i] = (unsigned char *)NULL;
	
	memset(vidram, 0, sizeof(vidram));	
	video_ram = (unsigned char *)&vidram[0];
	
	memset(intram, 0, sizeof(intram));
	internal_ram = (unsigned char *)&intram[0];
	
	memset(hiram, 0, sizeof(hiram));
	bank_sixteen = &hiram[0];

	install_memory(8, video_ram + 0x0000);
	install_memory(9, video_ram + 0x1000);

	install_memory(0x0A, NULL);	/* 8 Kilobyte Switchable RAM */
	install_memory(0x0B, NULL);
	
	install_memory(0x0C, internal_ram + 0x0000);	/* This is ok for both GB and GBC */
	install_memory(0x0D, internal_ram + 0x1000);
	install_memory(0x0E, internal_ram + 0x0000);	/* Echo of Internal Ram */

	install_memory(0x0F, bank_sixteen);
	
	sprite_oam    = &gameboy_memory[0xF][0xE00];

	reset_colors();
	
	return 1;
}

void free_memory()
{
	if(video_ram) {
		install_memory(8, NULL);
		install_memory(9, NULL);
		video_ram = (unsigned char *)NULL;
	}
	if(internal_ram) {
		install_memory(0x0C, NULL);
		install_memory(0x0D, NULL);
		install_memory(0x0E, NULL);
		internal_ram = (unsigned char *)NULL;
	}
	if(bank_sixteen) {
		install_memory(0xF, NULL);
		bank_sixteen = (unsigned char *)NULL;
	}
	sprite_oam = (unsigned char *)NULL;	
}

int memory_read_hibyte(int reg)
{
	switch(reg) {
		case 0x00:
			
			Memory_key_gba_patch();
			
			if(!(JOYPAD & 0x20)) { /* Low bits */
				return ((~current_joypad & 0xF0) >> 4) | 0x10;
			} else if(!(JOYPAD & 0x10)) {
				return (~current_joypad & 0x0F) | 0x20;
			} 
			return 0xFF;
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1A:
		case 0x1B:
		case 0x1C:
		case 0x1D:
		case 0x1E:
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x25:
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
		case 0x3A:
		case 0x3B:
		case 0x3C:
		case 0x3D:
		case 0x3E:
		case 0x3F:
			return SoundRead(reg);
		case 0x26:
			if (!SoundEnabled) {
				SNDREG52 ^= 0x0F;
				return SNDREG52;
			}
			return SoundRead(reg);
		case 0x41:
			return (LCDSTAT & 0xF8) | vram_mode | ((CURLINE == CMPLINE) ? 4 : 0);
		case 0x55:
			return HDMACnt - 1; /* TODO: ??? */
		case 0x69: {
			unsigned char pal;
			unsigned char col;
			unsigned char hl;
			unsigned char value;

			pal    = (BCPSREG & 0x38) >> 3;
			col    = (BCPSREG & 0x06) >> 1;
			hl     = (BCPSREG & 0x01);

			if(hl) { /* 0BBBBBGG */
				value = (bkg_palettes[pal][col] >> 8);
			} else { /* GGGRRRRR */
				value = (bkg_palettes[pal][col] & 0x00FF);
			}
			return value;
		}	
		case 0x6B: {
			unsigned char pal;
			unsigned char col;
			unsigned char hl;
			unsigned char value;

			pal    = (OCPSREG & 0x38) >> 3;
			col    = (OCPSREG & 0x06) >> 1;
			hl     = (OCPSREG & 0x01);

			if(hl) { /* 0BBBBBGG */
				value = (obj_palettes[pal][col] >> 8);
			} else { /* GGGRRRRR */
				value = (obj_palettes[pal][col] & 0x00FF);
			}
			return value;
		}
		default:
			return hiram[0x0F00 | reg];
	}
}

inline void memory_write_hibyte(int reg, int value)
{
	switch(reg) {
		case 0x02: {
			//printf("SIOCONT -> %02X\n", value);
			if(value & 0x80) {
				SIODATA = 0xFF;
				SIOCONT = value & 0x83;
			} else {
				SIOCONT = value & 3;
			}
			return;
		}
		case 0x04:
			DIVIDER = 0x00;
			return;
		case 0x07:  {
			extern int TimCycle, TimLoad;
			TimCycle = 0;
			TIMCONT = value;
			switch(value & 0x03) {
				case 0:
					TimLoad = 1024;
					break;
				case 1:
					TimLoad = 16;
					break;
				case 2:
					TimLoad = 64;
					break;
				case 3:
					TimLoad = 256;
					break;
			}
			//printf("TIM hit -> %02X\n", value);
			return;
		}
		
		case 0x10:
		case 0x11:
		case 0x12:
		case 0x13:
		case 0x14:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1A:
		case 0x1B:
		case 0x1C:
		case 0x1D:
		case 0x1E:
		case 0x20:
		case 0x21:
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x25:
		case 0x26:
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
		case 0x3A:
		case 0x3B:
		case 0x3C:
		case 0x3D:
		case 0x3E:
		case 0x3F:
		
			memory_file_gba_patch((unsigned char)reg, (unsigned char)value);
		
			if (SoundEnabled)
				SoundWrite((unsigned char)reg, (unsigned char)value);
			else
				hiram[reg | 0xF00] = value;
			return;	
		case 0x40: {
			extern int TileSign;
			extern unsigned char *BkgTiles;
			extern unsigned char *BkgTable;
			extern unsigned char *WindowTable;

			if (value & 0x08) {
				BkgTable = &video_ram[0x1C00];
			} else {
				BkgTable = &video_ram[0x1800];
			}
			if (value & 0x10) {
				TileSign = 0;
				BkgTiles = &video_ram[0];
			} else {
				TileSign = 1;
				BkgTiles = &video_ram[0x1000];
			}
			if (value & 0x40) {
				WindowTable = &video_ram[0x1C00];
			} else {
				WindowTable = &video_ram[0x1800];
			}

			if ((LCDCONT & 0x80) && !(value & 0x80)) {
				/* warning */
				LCDCONT = value;
			} else if (!(LCDCONT & 0x80) && (value & 0x80)) {
				extern int vram_mode;
				extern int ScrCycle;
				CURLINE = 154;
				vram_mode = 1;
				ScrCycle = 0;
				LCDCONT = value;
			} else {
				LCDCONT = value;
			}
			return;
		}
		case 0x41:
			LCDSTAT = (0x80 | (value & 0x78) | (LCDSTAT & 0x07));
			return;
		case 0x44: {
			extern int ScrCycle;
			printf("wrote %d to LY?\n", value);
			ScrCycle = 0;
			vram_mode = 1;
			CURLINE = 154;
			return;
		}
		case 0x46:  {
			int a, b;
			DMACONT = value;
			a = (DMACONT << 8) & 0xFFF;
			b = DMACONT >> 4;
                
			if(gameboy_memory[b])
				memcpy(sprite_oam, &gameboy_memory[b][a], 0xA0);
			return;
		}
		case 0x4D:
			KEY1REG = (KEY1REG & 0x80) | (value & 0x01);
			return;
		case 0x4F:
			VBKREG = value & 0x01;
			memory_select_vram_bank(VBKREG, 0x08);
			return;
		case 0x55:  {
			int src, dest, cntr;

			src = (HDMA1REG << 8) | (HDMA2REG & 0xF0);
			dest = 0x8000 | ((HDMA3REG & 0x1F) << 8) | ((HDMA4REG & 0xF0));
			if (value & 0x80) {				
				if (HDMADst) 
					break;
				HDMASrc = src;
				HDMADst = dest;	
				HDMACnt = (value & 0x7F) + 1;
				
				//printf("HDMA5: %X (%d lines) Bytes From %X to %X\n", ((value & 0x7F) + 1) << 4, (value & 0x7F) + 1, src, dest);
			} else {
				//printf("GDMA5: %X Bytes From %X to %X\n", ((value & 0x7F) + 1) << 4, src, dest);
				cntr = ((value & 0x7F) + 1) << 4;
				MORE_CYCLES( ((1845 + (cntr << 3)) >> 4) );
				memcpy(&gameboy_memory[dest >> 12][dest & 0x0FFF], &gameboy_memory[(src & 0xF000) >> 12][src & 0x0FFF], cntr);
			}
			return;
		}
		case 0x68:
			BCPSREG = value & 0xBF;
			return;
		case 0x69:  {
			int incpal;
			int pal;
			int col;
			int hl;

			incpal = (BCPSREG & 0x80) ? 1 : 0;
			pal    = (BCPSREG & 0x38) >> 3;
			col    = (BCPSREG & 0x06) >> 1;
			hl     = (BCPSREG & 0x01);

			if(hl) { /* 0BBBBBGG */
				bkg_palettes[pal][col] = (bkg_palettes[pal][col] & 0x00FF) | (value << 8);
			} else { /* GGGRRRRR */
				bkg_palettes[pal][col] = (bkg_palettes[pal][col] & 0xFF00) | value;
			}
			infogb_set_color(pal * 4 + col, bkg_palettes[pal][col]);
			if(incpal) {
				incpal = BCPSREG;
				incpal++;
				BCPSREG = 0x80 | (incpal & 0x3F);
			}
			return;
		}
		case 0x6A:
			OCPSREG = value & 0xBF;
			return;
		case 0x6B:  {
			int incpal;
			int pal;
			int col;
			int hl;

			incpal = (OCPSREG & 0x80) ? 1 : 0;
			pal    = (OCPSREG & 0x38) >> 3;
			col    = (OCPSREG & 0x06) >> 1;
			hl     = (OCPSREG & 0x01);

			if(hl) { /* 0BBBBBGG */
				obj_palettes[pal][col] = (obj_palettes[pal][col] & 0x00FF) | (value << 8);
			} else { /* GGGRRRRR */
				obj_palettes[pal][col] = (obj_palettes[pal][col] & 0xFF00) | value;
			}
			infogb_set_color(32 + pal * 4 + col, obj_palettes[pal][col]);
			if(incpal) {
				incpal = OCPSREG;
				incpal++;
				OCPSREG = 0x80 | (incpal & 0x3F);
			}
			return;
		}
		case 0x70:
			SVBKREG = value & 0x07;
			memory_select_wram_bank(SVBKREG, 0x0D);	
			return;
		default:
			hiram[reg | 0xF00] = value;
			return;
	}		
}
			
/*
TODO:
 memory_read_byte undefined when inline on win32
*/

unsigned char memory_read_byte(unsigned short int address)
{
	int where, bank;
	
	bank = address >> 12;
	
	switch(bank) {
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
			return cartridge_rom[address];
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
			return gameboy_memory[bank][address & 0x0FFF];
		case 0x08:
		case 0x09:
			return gameboy_memory[bank][address & 0x0FFF];
		case 0x0A:
		case 0x0B:
			if (mbc1_ram_bank_enable == 0) {
				//printf("Ignoring read..\n");
				return 0;
			}
			return gameboy_memory[bank][address & 0x0FFF];
		case 0x0C:
		case 0x0D:
			return gameboy_memory[bank][address & 0x0FFF];
		case 0x0E:
			printf("Echo RAM: %04X\n", address);
			return gameboy_memory[bank][address & 0x0FFF];
		case 0x0F:
			where = address & 0x0FFF;

			if (where >= 0xF00) {
				return memory_read_hibyte(where & 0xFF);	
			} else if (where >= 0xEA0) {
				return hiram[where];
			} else if (where >= 0xE00) {
				return hiram[where];
			} /* Where < 0xE00 */
			return gameboy_memory[0x0D][where];
	}
	return 0;
}

unsigned short int memory_read_word(unsigned short int address)
{
	return (memory_read_byte(address) | (memory_read_byte(address+1) << 8));
}

void memory_write_byte(unsigned short int address, unsigned char value)
{
	int bank, where;

	bank = address >> 12;
	
	switch(bank) {
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
			/* TODO: don't allow ram to be enabled on carts with no ram */
			if( cartridge_type >= TYPE_ROM_MBC1 && cartridge_type <= TYPE_ROM_MBC1_RAM_BATTERY) {
				//printf("MBC1 write: %04X -> %02X\n", address, value);
				if(address < 0x2000) {
					int res = value & 0x0F;
					if(res == 0x0A) {
						mbc1_ram_bank_enable = 1;
					} else {
						mbc1_ram_bank_enable = 0;
					}
				} else if(address < 0x4000) {
					//printf("MBC1 rom bank %d\n", value);
					mbc5_rom_select = (mbc5_rom_select & 0x60) | (value & 0x1F);
					rom_select_bank(mbc5_rom_select, 4);
				} else if(address < 0x6000) {
					//printf("MBC1 ram/rom bank %d\n", value);
					switch(cartridge_mbc1) {
						case MBC1_16M_8K:
							mbc5_rom_select = ((value & 0x03) << 5) | (mbc5_rom_select & 0x1F);
							rom_select_bank(mbc5_rom_select, 4);
							break;
						case MBC1_4M_32K:
							rom_select_ram_bank(value & 0x03);
							break;
						default:
							break;
					}
				} else { /* < 0x8000 */
					//printf("MBC1 mode %d\n", value & 0x01);
					if(value & 0x01) {
						cartridge_mbc1 = MBC1_4M_32K;
						//mbc1_address_line = 0;
					} else {
						cartridge_mbc1 = MBC1_16M_8K;
					}
				} 
			} else if(cartridge_type == TYPE_ROM_MBC2 || cartridge_type == TYPE_ROM_MBC2_BATTERY) {
				int ual = address >> 8;	/* Upper Address Line */
				if(address < 0x2000) {
					if(ual & 0x01) {
						printf("ram bank %s\n", mbc1_ram_bank_enable ? "disabled" : "enabled");
						mbc1_ram_bank_enable = !mbc1_ram_bank_enable;
					}
				} else if(address < 0x3000) {
					if(ual & 0x01) 
						rom_select_bank(value & 0x0F, 4);
				} 
			} else if(cartridge_type >= TYPE_ROM_MBC3 && cartridge_type <= TYPE_ROM_MBC3_RAM_BATTERY) {
				if(address >= 0x2000 && address <= 0x3FFF) {
					rom_select_bank(value & 0x7F, 4);
				} else if(address >= 0x4000 && address <= 0x5FFF) {
					rom_select_ram_bank(value & 0x3);
				}
			} else if(cartridge_type >= TYPE_ROM_MBC5 && cartridge_type <= TYPE_ROM_MBC5_RAM_BATTERY) {
				if(address < 0x2000) {
					#if 0
					if((value & 0x0F) == 0)
						mbc1_ram_bank_enable = 0;
					else if((value & 0x0A) == 0x0A)
						mbc1_ram_bank_enable = 1;
					else printf("??? %02X\n", value);
					#endif
					if (value == 0x0A)
						mbc1_ram_bank_enable = 1;
					else
						mbc1_ram_bank_enable = 0;
				} else if(address < 0x3000) {	/* lower 8 bits of rom select */
					mbc5_rom_select = (mbc5_rom_select & 0xFF00) | value;
					rom_select_bank(mbc5_rom_select, 4);
				} else if(address < 0x4000) {
					mbc5_rom_select = ((value & 0x01) << 8) | (mbc5_rom_select & 0x00FF);
					rom_select_bank(mbc5_rom_select, 4);
				} else if(address < 0x6000) {
					rom_select_ram_bank(value & 0x0F);	/* gets a total of 15 banks */
				}
			}
			return;
		case 0x08:
		case 0x09:
			gameboy_memory[bank][address & 0x0FFF] = value;
			return;
		case 0x0A:
		case 0x0B:
			if ( (mbc1_ram_bank_enable == 0) || !gameboy_memory[bank] ) {
				//printf("Ignoring write..\n");
				return;
			}
			gameboy_memory[bank][address & 0x0FFF] = value;
			return;
		case 0x0C:
		case 0x0D:
			gameboy_memory[bank][address & 0xFFF] = value;
			return;
		case 0x0E:
			printf("Echo RAM: %04X <- %02X\n", address, value);
			gameboy_memory[bank][address & 0x0FFF] = value;
			return;
		case 0x0F:
			where = address & 0x0FFF;
			
			if(where >= 0xF00) {
				memory_write_hibyte(where & 0x0FF, value);
			} else if(where >= 0xEA0) {		
				/* TODO: Is this correct? */
				if (((where & 0x0FF7)+24) >= 0x0F00) {
					if (((where & 0x0FE7)+24) >= 0x0F00) 
						printf("OVERWRITING REGISTERS!!! (%04X)\n", 0xF000 | where);
				}
				hiram[(where & 0x0FE7)] = 
				hiram[(where & 0x0FE7)+8] = 
				hiram[(where & 0x0FE7)+16] =
				hiram[(where & 0x0FE7)+24] = value;
			} else if(where >= 0xE00) {
				hiram[where] = value;
			} else {
				printf("Where = %04X\n", where);
				hiram[where] = value;
			}
			return;
	}	
			
}

void memory_write_word(unsigned short int address, unsigned short int value)
{
	memory_write_byte(address, value & 0xFF);
	memory_write_byte(address + 1, value >> 8);
}
//---------------------------------------------------------------------------
static int wait = 0;
static int step = 0;
static int step2 = 0;
static unsigned char endmark;

void memory_file_gba_patch(unsigned char reg, unsigned char value)
{
	unsigned char adr;
	unsigned char dat;

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

//	printf("%02X = %02X\n", adr, dat);

	Infogb_gba_savelog(0xb3);
	Infogb_gba_savelog(adr);
	Infogb_gba_savelog(dat);

	// add REG_SOUND3CNT_L = 0x40;
	if(adr >= 0x90 && adr <= 0x9f)
	{
		Infogb_gba_savelog(0xb3);
		Infogb_gba_savelog(0x70);
		Infogb_gba_savelog(0x40);
	}

	// endmark
	if(reg == 0x26 && endmark != value)
	{
		step2++;
		endmark = value;
//		printf("%d reg:%x value:%x\n", step2, reg, value);

		if(step2 >= 4)
		{
			printf("end\n");

			gbz80.running = 0;
		}
	}
}
//---------------------------------------------------------------------------
void Memory_key_gba_patch(void)
{
	if(wait < 10)
	{
		wait++;
		return;
	}
	wait = 0;

	switch(step)
	{
	// wait
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		step++;
		break;

	case 6:
		step++;
		joypad_press(GB_START);
		endmark = memory_read_hibyte(0x26);
		break;

	case 7:
		step++;
		break;

	case 8:
		step++;
		joypad_release(GB_START);
		break;

	case 9:
		break;
	}
}
