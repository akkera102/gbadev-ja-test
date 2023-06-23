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

extern unsigned char gameboy_memory[0x10000];

void memory_init(void);
int  memory_read_hibyte(int reg);
void memory_write_hibyte(int reg, int value);
unsigned char memory_read_byte(unsigned short int address);
unsigned short int memory_read_word(unsigned short int address);
void memory_write_byte(unsigned short int address, unsigned char value);
void memory_write_word(unsigned short int address, unsigned short int value);

void memory_write_gba_patch(unsigned char address, unsigned char value);


#endif

