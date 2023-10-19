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

#ifndef __ROM_H__
#define __ROM_H__

typedef enum _cartsize { SIZE_Unknown = 0, SIZE_32k, SIZE_64k, SIZE_128k, SIZE_256k, SIZE_512k, SIZE_1M, SIZE_2M, SIZE_4M, SIZE_8M } cartsize;
typedef enum _carttype { TYPE_Unknown = 0, 
                         TYPE_ROM_Only, 
                         TYPE_ROM_MBC1, 
                         TYPE_ROM_MBC1_RAM,
                         TYPE_ROM_MBC1_RAM_BATTERY,
                         TYPE_ROM_MBC2,
                         TYPE_ROM_MBC2_BATTERY,
                         TYPE_ROM_MBC3,
                         TYPE_ROM_MBC3_RAM,
                         TYPE_ROM_MBC3_RAM_BATTERY,
                         TYPE_ROM_MBC5,
                         TYPE_ROM_MBC5_RAM,
                         TYPE_ROM_MBC5_RAM_BATTERY } carttype;
typedef enum _mbc1type { MBC1_Unused  = 0, MBC1_16M_8K, MBC1_4M_32K } mbc1type;
typedef enum _ramsize  { RAM_SIZE_2KB = 1, RAM_SIZE_8KB, RAM_SIZE_32KB, RAM_SIZE_128KB = 6 } ramsize;

extern int color_gameboy;
extern int super_gameboy;

extern cartsize       cartridge_size;
extern carttype       cartridge_type;
extern unsigned char *cartridge_rom;
extern mbc1type       cartridge_mbc1;
extern unsigned char *cartridge_ram;
extern ramsize        cartridge_ramsize;

int load_rom(char *);
void initialize_rom();
void free_rom();
void install_rom();
void install_ram();
void rom_select_bank(int, int);
void rom_select_ram_bank(int);
void rom_create_sav_path(char *);
void rom_save_ram();
void rom_load_ram();

#endif

