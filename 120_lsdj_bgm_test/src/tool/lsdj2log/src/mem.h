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

#ifndef __MEM_H__
#define __MEM_H__

extern unsigned char *gameboy_memory[16];
extern unsigned char hiram[0x1000];
extern unsigned char *video_ram;
extern unsigned char *sprite_oam;
extern unsigned short int bkg_palettes[8][4];
extern unsigned short int obj_palettes[8][4];

void install_memory(int, void *);
int  initialize_memory();
void free_memory();

unsigned char memory_read_byte(unsigned short int);
unsigned short int memory_read_word(unsigned short int);

void memory_write_byte(unsigned short int, unsigned char);
void memory_write_word(unsigned short int, unsigned short int);

extern int memory_read_hibyte(int reg);
extern void memory_write_hibyte(int reg, int val);

void memory_file_gba_patch(unsigned char reg, unsigned char value);
void Memory_key_gba_patch(void);

#endif

