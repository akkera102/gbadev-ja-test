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
#include "mem.h"
#include "cpu.h"

jmp_buf EmuJmp;

static int current_opcode;

gameboy_proc_t gbz80;

void gameboy_cpu_hardreset()
{	
//	if (color_gameboy)
//		gbz80.AF.b.h = 0x11;
//	else
		gbz80.AF.b.h = 0x01;
	
	gbz80.AF.b.l = 0xB0;
	gbz80.BC.uw  = 0x0013;
	gbz80.DE.uw  = 0x00D8;
	gbz80.HL.uw  = 0x014D;
	gbz80.SP.uw  = 0xFFFE;
	gbz80.PC.uw  = 0x0100;
	gbz80.IFF    = 0;

	gbz80.machine_cycles = 0;
	
	memory_write_byte(0xFF05, 0);
	memory_write_byte(0xFF06, 0);
	memory_write_byte(0xFF07, 0);
	memory_write_byte(0xFF26, 0x80);
	memory_write_byte(0xFF10, 0x80);
	memory_write_byte(0xFF11, 0xBF);
	memory_write_byte(0xFF12, 0xF3);
	memory_write_byte(0xFF14, 0xBF);
	memory_write_byte(0xFF16, 0x3F);
	memory_write_byte(0xFF17, 0x00);
	memory_write_byte(0xFF19, 0xBF);
	memory_write_byte(0xFF1A, 0x7A);
	memory_write_byte(0xFF1B, 0xFF);
	memory_write_byte(0xFF1C, 0x9F);
	memory_write_byte(0xFF1E, 0xBF);
	memory_write_byte(0xFF20, 0xFF);
	memory_write_byte(0xFF21, 0x00);
	memory_write_byte(0xFF22, 0x00);
	memory_write_byte(0xFF23, 0xBF);
	memory_write_byte(0xFF24, 0x77);
	memory_write_byte(0xFF25, 0xF3);
	
	memory_write_byte(0xFF40, 0x91);
	memory_write_byte(0xFF41, 0x80);
	memory_write_byte(0xFF42, 0x00);
	memory_write_byte(0xFF43, 0x00);
	memory_write_byte(0xFF45, 0x00);
	memory_write_byte(0xFF47, 0xFC);
	memory_write_byte(0xFF48, 0xFF);
	memory_write_byte(0xFF49, 0xFF);
	memory_write_byte(0xFF4A, 0x00);
	memory_write_byte(0xFF4B, 0x00);
	memory_write_byte(0xFFFF, 0x00);
}

void gameboy_cpu_run()
{	
	gbz80.running = 1;
	
	setjmp(EmuJmp);

	if (gbz80.running) {
		gameboy_cpu_execute_opcode();	
	}
}

// static void gameboy_stack_write_word(unsigned short val)
void gameboy_stack_write_word(unsigned short val)
{
	gbz80.SP.uw -= 2;
	memory_write_word(gbz80.SP.uw, val);
}

unsigned short int gameboy_stack_read_word()
{
	unsigned short int ret;
	
	ret = memory_read_word(gbz80.SP.uw);
	
	gbz80.SP.uw += 2;
	
	return ret;
}

//#define memory_read_pc_byte() (gameboy_memory[gbz80.PC.uw >> 12][gbz80.PC.uw & 0x0FFF])
//#define memory_read_pc_word() (gameboy_memory[gbz80.PC.uw >> 12][gbz80.PC.uw & 0x0FFF] | (gameboy_memory[(gbz80.PC.uw+1) >> 12][(gbz80.PC.uw+1) & 0x0FFF] << 8))
#define memory_read_pc_byte() (gameboy_memory[gbz80.PC.uw & 0x0FFF])
#define memory_read_pc_word() (gameboy_memory[gbz80.PC.uw & 0x0FFF] | (gameboy_memory[(gbz80.PC.uw+1) & 0x0FFF] << 8))

	
extern int HaltActive;

void inst_adc_a_a()
{
	int value = gbz80.AF.b.h;
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);

	if(result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(4);
}

void inst_adc_a_b()
{
	int value = gbz80.BC.b.h;
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(4);
}

void inst_adc_a_c()
{
	int value = gbz80.BC.b.l;
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);

	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(4);
}

void inst_adc_a_d()
{
	int value = gbz80.DE.b.h;
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(4);
}

void inst_adc_a_e()
{
	int value = gbz80.DE.b.l;
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);

	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(4);
}

void inst_adc_a_h()
{
	int value = gbz80.HL.b.h;
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(4);
}

void inst_adc_a_hl_indirect()
{
	int value = memory_read_byte(gbz80.HL.uw);
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(8);
}

void inst_adc_a_l()
{
	int value = gbz80.HL.b.l;
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(4);
}

void inst_adc_a_n()
{
	int value = memory_read_pc_byte();
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 1 : 0;
	int result = gbz80.AF.b.h + value + carry;
	
	gbz80.PC.uw++;

	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0xFF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	if (((value & 0x0F) + (gbz80.AF.b.h & 0x0F) + carry) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);

	gbz80.AF.b.h = result & 0xFF;
			
	MORE_CYCLES2(8);
}

void inst_add_a_a()
{
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	if (gbz80.AF.b.h & 0x08)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h += gbz80.AF.b.h;
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(4);
}

void inst_add_a_b()
{
	int value = gbz80.BC.b.h;
	int result = gbz80.AF.b.h + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(4);
}

void inst_add_a_c()
{
	int value = gbz80.BC.b.l;
	int result = gbz80.AF.b.h + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(4);
}

void inst_add_a_d()
{
	int value = gbz80.DE.b.h;
	int result = gbz80.AF.b.h + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(4);
}

void inst_add_a_e()
{
	int value = gbz80.DE.b.l;
	int result = gbz80.AF.b.h + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(4);
}

void inst_add_a_h()
{
	int value = gbz80.HL.b.h;
	int result = gbz80.AF.b.h + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(4);
}

void inst_add_a_hl_indirect()
{
	int value = memory_read_byte(gbz80.HL.uw);
	int result = gbz80.AF.b.h + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(8);
}

void inst_add_a_l()
{
	int value = gbz80.HL.b.l;
	int result = gbz80.AF.b.h + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(4);
}

void inst_add_a_n()
{
	int value = memory_read_pc_byte();
	int result = gbz80.AF.b.h + value;
	
	gbz80.PC.uw++;
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if (result & 0xFF00)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (result & 0x00FF)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	if (((gbz80.AF.b.h & 0x0F) + (value & 0x0F)) > 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h = result & 0xFF;
	
	MORE_CYCLES2(8);
}

void inst_add_hl_bc()
{
	unsigned long result;
	unsigned short value = gbz80.BC.uw;
	
	result = gbz80.HL.uw + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFFFF0000)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (((gbz80.HL.uw & 0xFFF) + (value & 0xFFF)) > 0xFFF)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.HL.uw = (unsigned short)(result & 0xFFFF);
	
	MORE_CYCLES2(8);
}

void inst_add_hl_de()
{
	unsigned long result;
	unsigned short value = gbz80.DE.uw;
	
	result = gbz80.HL.uw + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFFFF0000)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (((gbz80.HL.uw & 0xFFF) + (value & 0xFFF)) > 0xFFF)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.HL.uw = (unsigned short)(result & 0xFFFF);
	
	MORE_CYCLES2(8);
}

void inst_add_hl_hl()
{
	unsigned long result;
	unsigned short value = gbz80.HL.uw;
	
	result = gbz80.HL.uw + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFFFF0000)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (((gbz80.HL.uw & 0xFFF) + (value & 0xFFF)) > 0xFFF)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.HL.uw = (unsigned short)(result & 0xFFFF);
	
	MORE_CYCLES2(8);
}

void inst_add_hl_sp()
{
	unsigned long result;
	unsigned short value = gbz80.SP.uw;
	
	result = gbz80.HL.uw + value;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	if(result & 0xFFFF0000)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if (((gbz80.HL.uw & 0xFFF) + (value & 0xFFF)) > 0xFFF)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.HL.uw = (unsigned short)(result & 0xFFFF);
	
	MORE_CYCLES2(8);
}

void inst_add_sp_n()
{
	signed char value = memory_read_pc_byte();
	int result = gbz80.SP.uw + value;
	
	gbz80.PC.uw++;
	FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO | FLAGS_NEGATIVE);
	
	if (result & 0xFFFF0000)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	gbz80.SP.uw = result & 0xFFFF;
	
	/* TODO: i think */
	if (((gbz80.SP.uw & 0xFFF) + (value & 0xFFF)) > 0xFFF)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(16);
}

void inst_and_a()
{
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(4);
}

void inst_and_b()
{
	gbz80.AF.b.h &= gbz80.BC.b.h;
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(4);
}

void inst_and_c()
{
	gbz80.AF.b.h &= gbz80.BC.b.l;
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(4);
}

void inst_and_d()
{
	gbz80.AF.b.h &= gbz80.DE.b.h;
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(4);
}

void inst_and_e()
{
	gbz80.AF.b.h &= gbz80.DE.b.l;
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(4);
}

void inst_and_h()
{
	gbz80.AF.b.h &= gbz80.HL.b.h;
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(4);
}

void inst_and_hl_indirect()
{
	gbz80.AF.b.h &= memory_read_byte(gbz80.HL.uw);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(8);
}

void inst_and_l()
{
	gbz80.AF.b.h &= gbz80.HL.b.l;
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(4);
}

void inst_and_n()
{
	gbz80.AF.b.h &= memory_read_pc_byte();
	gbz80.PC.uw++;
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	MORE_CYCLES2(8);
}

void inst_call_c_nn()
{
	if (FLAGS_ISCARRY(gameboy_proc)) {
		gameboy_stack_write_word(gbz80.PC.uw + 2);
		gbz80.PC.uw = memory_read_pc_word();
		MORE_CYCLES2(24);
	} else {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	}
}

void inst_call_nc_nn()
{
	if (FLAGS_ISCARRY(gameboy_proc)) {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	} else {
		gameboy_stack_write_word(gbz80.PC.uw + 2);
		gbz80.PC.uw = memory_read_pc_word();;
		MORE_CYCLES2(24);
	}
}

void inst_call_nn()
{
	gameboy_stack_write_word(gbz80.PC.uw + 2);
	gbz80.PC.uw = memory_read_word(gbz80.PC.uw);
	MORE_CYCLES2(24);
}

void inst_call_nz_nn()
{
	if (FLAGS_ISZERO(gameboy_proc)) {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	} else {
		gameboy_stack_write_word(gbz80.PC.uw + 2);
		gbz80.PC.uw = memory_read_pc_word();
		MORE_CYCLES2(24);
	}
}

void inst_call_z_nn()
{
	if (FLAGS_ISZERO(gameboy_proc)) {
		gameboy_stack_write_word(gbz80.PC.uw + 2);
		gbz80.PC.uw = memory_read_pc_word();;
		MORE_CYCLES2(24);
	} else {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	}
}

void inst_cb_bit_0_a()
{
	if (gbz80.AF.b.h & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_0_b()
{
	if (gbz80.BC.b.h & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_0_c()
{
	if (gbz80.BC.b.l & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_0_d()
{
	if (gbz80.DE.b.h & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_0_e()
{
	if (gbz80.DE.b.l & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_0_h()
{
	if (gbz80.HL.b.h & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_0_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_0_l()
{
	if (gbz80.HL.b.l & 0x01)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_1_a()
{
	if (gbz80.AF.b.h & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_1_b()
{
	if (gbz80.BC.b.h & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_1_c()
{
	if (gbz80.BC.b.l & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_1_d()
{
	if (gbz80.DE.b.h & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_1_e()
{
	if (gbz80.DE.b.l & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_1_h()
{
	if (gbz80.HL.b.h & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_1_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_1_l()
{
	if (gbz80.HL.b.l & 0x02)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_2_a()
{
	if (gbz80.AF.b.h & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_2_b()
{
	if (gbz80.BC.b.h & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_2_c()
{
	if (gbz80.BC.b.l & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_2_d()
{
	if (gbz80.DE.b.h & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_2_e()
{
	if (gbz80.DE.b.l & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_2_h()
{
	if (gbz80.HL.b.h & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_2_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_2_l()
{
	if (gbz80.HL.b.l & 0x04)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_3_a()
{
	if (gbz80.AF.b.h & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_3_b()
{
	if (gbz80.BC.b.h & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_3_c()
{
	if (gbz80.BC.b.l & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_3_d()
{
	if (gbz80.DE.b.h & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_3_e()
{
	if (gbz80.DE.b.l & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_3_h()
{
	if (gbz80.HL.b.h & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_3_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_3_l()
{
	if (gbz80.HL.b.l & 0x08)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_4_a()
{
	if (gbz80.AF.b.h & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_4_b()
{
	if (gbz80.BC.b.h & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_4_c()
{
	if (gbz80.BC.b.l & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_4_d()
{
	if (gbz80.DE.b.h & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_4_e()
{
	if (gbz80.DE.b.l & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_4_h()
{
	if (gbz80.HL.b.h & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_4_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_4_l()
{
	if (gbz80.HL.b.l & 0x10)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_5_a()
{
	if (gbz80.AF.b.h & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_5_b()
{
	if (gbz80.BC.b.h & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_5_c()
{
	if (gbz80.BC.b.l & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_5_d()
{
	if (gbz80.DE.b.h & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_5_e()
{
	if (gbz80.DE.b.l & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_5_h()
{
	if (gbz80.HL.b.h & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_5_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_5_l()
{
	if (gbz80.HL.b.l & 0x20)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_6_a()
{
	if (gbz80.AF.b.h & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_6_b()
{
	if (gbz80.BC.b.h & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_6_c()
{
	if (gbz80.BC.b.l & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_6_d()
{
	if (gbz80.DE.b.h & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_6_e()
{
	if (gbz80.DE.b.l & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_6_h()
{
	if (gbz80.HL.b.h & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_6_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_6_l()
{
	if (gbz80.HL.b.l & 0x40)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_7_a()
{
	if (gbz80.AF.b.h & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_7_b()
{
	if (gbz80.BC.b.h & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_7_c()
{
	if (gbz80.BC.b.l & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_7_d()
{
	if (gbz80.DE.b.h & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_7_e()
{
	if (gbz80.DE.b.l & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_7_h()
{
	if (gbz80.HL.b.h & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_bit_7_hl_indirect()
{
	if (memory_read_byte(gbz80.HL.uw) & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(12);
}

void inst_cb_bit_7_l()
{
	if (gbz80.HL.b.l & 0x80)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_res_0_a()
{
	gbz80.AF.b.h &= ~0x01;
	MORE_CYCLES2(8);
}

void inst_cb_res_0_b()
{
	gbz80.BC.b.h &= ~0x01;
	MORE_CYCLES2(8);
}

void inst_cb_res_0_c()
{
	gbz80.BC.b.l &= ~0x01;
	MORE_CYCLES2(8);
}

void inst_cb_res_0_d()
{
	gbz80.DE.b.h &= ~0x01;
	MORE_CYCLES2(8);
}

void inst_cb_res_0_e()
{
	gbz80.DE.b.l &= ~0x01;
	MORE_CYCLES2(8);
}

void inst_cb_res_0_h()
{
	gbz80.HL.b.h &= ~0x01;
	MORE_CYCLES2(8);
}

void inst_cb_res_0_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x01);
	MORE_CYCLES2(12);
}

void inst_cb_res_0_l()
{
	gbz80.HL.b.l &= ~0x01;
	MORE_CYCLES2(8);
}

void inst_cb_res_1_a()
{
	gbz80.AF.b.h &= ~0x02;
	MORE_CYCLES2(8);
}

void inst_cb_res_1_b()
{
	gbz80.BC.b.h &= ~0x02;
	MORE_CYCLES2(8);
}

void inst_cb_res_1_c()
{
	gbz80.BC.b.l &= ~0x02;
	MORE_CYCLES2(8);
}

void inst_cb_res_1_d()
{
	gbz80.DE.b.h &= ~0x02;
	MORE_CYCLES2(8);
}

void inst_cb_res_1_e()
{
	gbz80.DE.b.l &= ~0x02;
	MORE_CYCLES2(8);
}

void inst_cb_res_1_h()
{
	gbz80.HL.b.h &= ~0x02;
	MORE_CYCLES2(8);
}

void inst_cb_res_1_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x02);
	MORE_CYCLES2(12);
}

void inst_cb_res_1_l()
{
	gbz80.HL.b.l &= ~0x02;
	MORE_CYCLES2(8);
}

void inst_cb_res_2_a()
{
	gbz80.AF.b.h &= ~0x04;
	MORE_CYCLES2(8);
}

void inst_cb_res_2_b()
{
	gbz80.BC.b.h &= ~0x04;
	MORE_CYCLES2(8);
}

void inst_cb_res_2_c()
{
	gbz80.BC.b.l &= ~0x04;
	MORE_CYCLES2(8);
}

void inst_cb_res_2_d()
{
	gbz80.DE.b.h &= ~0x04;
	MORE_CYCLES2(8);
}

void inst_cb_res_2_e()
{
	gbz80.DE.b.l &= ~0x04;
	MORE_CYCLES2(8);
}

void inst_cb_res_2_h()
{
	gbz80.HL.b.h &= ~0x04;
	MORE_CYCLES2(8);
}

void inst_cb_res_2_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x04);
	MORE_CYCLES2(12);
}

void inst_cb_res_2_l()
{
	gbz80.HL.b.l &= ~0x04;
	MORE_CYCLES2(8);
}

void inst_cb_res_3_a()
{
	gbz80.AF.b.h &= ~0x08;
	MORE_CYCLES2(8);
}

void inst_cb_res_3_b()
{
	gbz80.BC.b.h &= ~0x08;
	MORE_CYCLES2(8);
}

void inst_cb_res_3_c()
{
	gbz80.BC.b.l &= ~0x08;
	MORE_CYCLES2(8);
}

void inst_cb_res_3_d()
{
	gbz80.DE.b.h &= ~0x08;
	MORE_CYCLES2(8);
}

void inst_cb_res_3_e()
{
	gbz80.DE.b.l &= ~0x08;
	MORE_CYCLES2(8);
}

void inst_cb_res_3_h()
{
	gbz80.HL.b.h &= ~0x08;
	MORE_CYCLES2(8);
}

void inst_cb_res_3_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x08);
	MORE_CYCLES2(12);
}

void inst_cb_res_3_l()
{
	gbz80.HL.b.l &= ~0x08;
	MORE_CYCLES2(8);
}

void inst_cb_res_4_a()
{
	gbz80.AF.b.h &= ~0x10;
	MORE_CYCLES2(8);
}

void inst_cb_res_4_b()
{
	gbz80.BC.b.h &= ~0x10;
	MORE_CYCLES2(8);
}

void inst_cb_res_4_c()
{
	gbz80.BC.b.l &= ~0x10;
	MORE_CYCLES2(8);
}

void inst_cb_res_4_d()
{
	gbz80.DE.b.h &= ~0x10;
	MORE_CYCLES2(8);
}

void inst_cb_res_4_e()
{
	gbz80.DE.b.l &= ~0x10;
	MORE_CYCLES2(8);
}

void inst_cb_res_4_h()
{
	gbz80.HL.b.h &= ~0x10;
	MORE_CYCLES2(8);
}

void inst_cb_res_4_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x10);
	MORE_CYCLES2(12);
}

void inst_cb_res_4_l()
{
	gbz80.HL.b.l &= ~0x10;
	MORE_CYCLES2(8);
}

void inst_cb_res_5_a()
{
	gbz80.AF.b.h &= ~0x20;
	MORE_CYCLES2(8);
}

void inst_cb_res_5_b()
{
	gbz80.BC.b.h &= ~0x20;
	MORE_CYCLES2(8);
}

void inst_cb_res_5_c()
{
	gbz80.BC.b.l &= ~0x20;
	MORE_CYCLES2(8);
}

void inst_cb_res_5_d()
{
	gbz80.DE.b.h &= ~0x20;
	MORE_CYCLES2(8);
}

void inst_cb_res_5_e()
{
	gbz80.DE.b.l &= ~0x20;
	MORE_CYCLES2(8);
}

void inst_cb_res_5_h()
{
	gbz80.HL.b.h &= ~0x20;
	MORE_CYCLES2(8);
}

void inst_cb_res_5_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x20);
	MORE_CYCLES2(12);
}

void inst_cb_res_5_l()
{
	gbz80.HL.b.l &= ~0x20;
	MORE_CYCLES2(8);
}

void inst_cb_res_6_a()
{
	gbz80.AF.b.h &= ~0x40;
	MORE_CYCLES2(8);
}

void inst_cb_res_6_b()
{
	gbz80.BC.b.h &= ~0x40;
	MORE_CYCLES2(8);
}

void inst_cb_res_6_c()
{
	gbz80.BC.b.l &= ~0x40;
	MORE_CYCLES2(8);
}

void inst_cb_res_6_d()
{
	gbz80.DE.b.h &= ~0x40;
	MORE_CYCLES2(8);
}

void inst_cb_res_6_e()
{
	gbz80.DE.b.l &= ~0x40;
	MORE_CYCLES2(8);
}

void inst_cb_res_6_h()
{
	gbz80.HL.b.h &= ~0x40;
	MORE_CYCLES2(8);
}

void inst_cb_res_6_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x40);
	MORE_CYCLES2(12);
}

void inst_cb_res_6_l()
{
	gbz80.HL.b.l &= ~0x40;
	MORE_CYCLES2(8);
}

void inst_cb_res_7_a()
{
	gbz80.AF.b.h &= ~0x80;
	MORE_CYCLES2(8);
}

void inst_cb_res_7_b()
{
	gbz80.BC.b.h &= ~0x80;
	MORE_CYCLES2(8);
}

void inst_cb_res_7_c()
{
	gbz80.BC.b.l &= ~0x80;
	MORE_CYCLES2(8);
}

void inst_cb_res_7_d()
{
	gbz80.DE.b.h &= ~0x80;
	MORE_CYCLES2(8);
}

void inst_cb_res_7_e()
{
	gbz80.DE.b.l &= ~0x80;
	MORE_CYCLES2(8);
}

void inst_cb_res_7_h()
{
	gbz80.HL.b.h &= ~0x80;
	MORE_CYCLES2(8);
}

void inst_cb_res_7_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what & ~0x80);
	MORE_CYCLES2(12);
}

void inst_cb_res_7_l()
{
	gbz80.HL.b.l &= ~0x80;
	MORE_CYCLES2(8);
}

void inst_cb_rl_a()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;

	if (gbz80.AF.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.AF.b.h <<= 1;
	gbz80.AF.b.h += carry;

	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_cb_rl_b()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;

	if (gbz80.BC.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.h <<= 1;
	gbz80.BC.b.h += carry;
	
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_cb_rl_c()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;

	if (gbz80.BC.b.l & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.l <<= 1;
	gbz80.BC.b.l += carry;
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_cb_rl_d()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;

	if (gbz80.DE.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);

	gbz80.DE.b.h <<= 1;
	gbz80.DE.b.h += carry;
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_cb_rl_e()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;

	if (gbz80.DE.b.l & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);

	gbz80.DE.b.l <<= 1;
	gbz80.DE.b.l += carry;
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_cb_rl_h()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;
	
	if (gbz80.HL.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.h <<= 1;
	gbz80.HL.b.h += carry;
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_cb_rl_hl_indirect()
{
	unsigned char value = memory_read_byte(gbz80.HL.uw);
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;
	
	if (value & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	value <<= 1;
	value += carry;
	
	if (value)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	memory_write_byte(gbz80.HL.uw, value);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(16);
}

void inst_cb_rl_l()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;
	
	if (gbz80.HL.b.l & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.l <<= 1;
	gbz80.HL.b.l += carry;
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_cb_rlc_a()
{
	int carry = (gbz80.AF.b.h & 0x80) >> 7;
	
	if (gbz80.AF.b.h & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.AF.b.h <<= 1;
	gbz80.AF.b.h += carry;
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8); 
}

void inst_cb_rlc_b()
{
	int carry = (gbz80.BC.b.h & 0x80) >> 7;
	
	if (gbz80.BC.b.h & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.h <<= 1;
	gbz80.BC.b.h += carry;
	
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_rlc_c()
{
	int carry = (gbz80.BC.b.l & 0x80) >> 7;
	
	if (gbz80.BC.b.l & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.l <<= 1;
	gbz80.BC.b.l += carry;
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_rlc_d()
{
	int carry = (gbz80.DE.b.h & 0x80) >> 7;
	
	if (gbz80.DE.b.h & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.h <<= 1;
	gbz80.DE.b.h += carry;
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_rlc_e()
{
	int carry = (gbz80.DE.b.l & 0x80) >> 7;
	
	if (gbz80.DE.b.l & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.l <<= 1;
	gbz80.DE.b.l += carry;
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_rlc_h()
{
	int carry = (gbz80.HL.b.h & 0x80) >> 7;
	
	if (gbz80.HL.b.h & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.h <<= 1;
	gbz80.HL.b.h += carry;
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_rlc_hl_indirect()
{
	unsigned char value = memory_read_byte(gbz80.HL.uw);
	int carry = (value & 0x80) >> 7;
	
	if (value & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	value <<= 1;
	value += carry;
	
	if (value)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	memory_write_byte(gbz80.HL.uw, value);
	
	MORE_CYCLES2(16);
}

void inst_cb_rlc_l()
{
	int carry = (gbz80.HL.b.l & 0x80) >> 7;
	
	if (gbz80.HL.b.l & 0x80) 
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.l <<= 1;
	gbz80.HL.b.l += carry;
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_rr_a()
{
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;
	
	if (gbz80.AF.b.h & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);	
	
	gbz80.AF.b.h >>= 1;	
	gbz80.AF.b.h |= carry;
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
			
	MORE_CYCLES2(8);
}

void inst_cb_rr_b()
{
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;
	
	if (gbz80.BC.b.h & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);	
	
	gbz80.BC.b.h >>= 1;
	gbz80.BC.b.h |= carry;
	
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
			
	MORE_CYCLES2(8);
}

void inst_cb_rr_c()
{
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;

	if (gbz80.BC.b.l & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);	
	
	gbz80.BC.b.l >>= 1;
	gbz80.BC.b.l |= carry;
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
			
	MORE_CYCLES2(8);
}

void inst_cb_rr_d()
{
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;
	
	
	if (gbz80.DE.b.h & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);	
	
	gbz80.DE.b.h >>= 1;
	gbz80.DE.b.h |= carry;
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
			
	MORE_CYCLES2(8);
}

void inst_cb_rr_e()
{
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;
	
	if (gbz80.DE.b.l & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);	
	
	gbz80.DE.b.l >>= 1;
	gbz80.DE.b.l |= carry;
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
			
	MORE_CYCLES2(8);
}

void inst_cb_rr_h()
{
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;
	
	if (gbz80.HL.b.h & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);	
	
	gbz80.HL.b.h >>= 1;
	gbz80.HL.b.h |= carry;
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
			
	MORE_CYCLES2(8);
}

void inst_cb_rr_hl_indirect()
{
	unsigned char value = memory_read_byte(gbz80.HL.uw);
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;
	
	if (value & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	value >>= 1;	
	value |= carry;
		
	if (value) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);	
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	memory_write_byte(gbz80.HL.uw, value);
	
	MORE_CYCLES2(16);
}

void inst_cb_rr_l()
{
	int carry = FLAGS_ISCARRY(gameboy_proc) ? 0x80 : 0;
	
	
	if (gbz80.HL.b.l & 1)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);	
	
	gbz80.HL.b.l >>= 1;
	gbz80.HL.b.l |= carry;
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
			
	MORE_CYCLES2(8);
}

void inst_cb_rrc_a()
{
	int carry = gbz80.AF.b.h & 0x01;
	
	gbz80.AF.b.h >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		gbz80.AF.b.h |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(8);
}

void inst_cb_rrc_b()
{
	int carry = gbz80.BC.b.h & 0x01;
	
	gbz80.BC.b.h >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		gbz80.BC.b.h |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(8);
}

void inst_cb_rrc_c()
{
	int carry = gbz80.BC.b.l & 0x01;
	
	gbz80.BC.b.l >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		gbz80.BC.b.l |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(8);
}

void inst_cb_rrc_d()
{
	int carry = gbz80.DE.b.h & 0x01;
	
	gbz80.DE.b.h >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		gbz80.DE.b.h |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(8);
}

void inst_cb_rrc_e()
{
	int carry = gbz80.DE.b.l & 0x01;
	
	gbz80.DE.b.l >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		gbz80.DE.b.l |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(8);
}

void inst_cb_rrc_h()
{
	int carry = gbz80.HL.b.h & 0x01;
	
	gbz80.HL.b.h >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		gbz80.HL.b.h |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(8);
}

void inst_cb_rrc_hl_indirect()
{
	unsigned char value = memory_read_byte(gbz80.HL.uw);
	int carry = value & 0x01;
	
	value >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		value |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (value)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	memory_write_byte(gbz80.HL.uw, value);
	
	MORE_CYCLES2(16);
}

void inst_cb_rrc_l()
{
	int carry = gbz80.HL.b.l & 0x01;
	
	gbz80.HL.b.l >>= 1;
	
	if (carry) {
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		gbz80.HL.b.l |= 0x80;
	} else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	MORE_CYCLES2(8);
}

void inst_cb_set_0_a()
{
	gbz80.AF.b.h |= 0x01;
	MORE_CYCLES2(8);
}

void inst_cb_set_0_b()
{
	gbz80.BC.b.h |= 0x01;
	MORE_CYCLES2(8);
}

void inst_cb_set_0_c()
{
	gbz80.BC.b.l |= 0x01;
	MORE_CYCLES2(8);
}

void inst_cb_set_0_d()
{
	gbz80.DE.b.h |= 0x01;
	MORE_CYCLES2(8);
}

void inst_cb_set_0_e()
{
	gbz80.DE.b.l |= 0x01;
	MORE_CYCLES2(8);
}

void inst_cb_set_0_h()
{
	gbz80.HL.b.h |= 0x01;
	MORE_CYCLES2(8);
}

void inst_cb_set_0_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x01);
	MORE_CYCLES2(12);
}

void inst_cb_set_0_l()
{
	gbz80.HL.b.l |= 0x01;
	MORE_CYCLES2(8);
}

void inst_cb_set_1_a()
{
	gbz80.AF.b.h |= 0x02;
	MORE_CYCLES2(8);
}

void inst_cb_set_1_b()
{
	gbz80.BC.b.h |= 0x02;
	MORE_CYCLES2(8);
}

void inst_cb_set_1_c()
{
	gbz80.BC.b.l |= 0x02;
	MORE_CYCLES2(8);
}

void inst_cb_set_1_d()
{
	gbz80.DE.b.h |= 0x02;
	MORE_CYCLES2(8);
}

void inst_cb_set_1_e()
{
	gbz80.DE.b.l |= 0x02;
	MORE_CYCLES2(8);
}

void inst_cb_set_1_h()
{
	gbz80.HL.b.h |= 0x02;
	MORE_CYCLES2(8);
}

void inst_cb_set_1_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x02);
	MORE_CYCLES2(12);
}

void inst_cb_set_1_l()
{
	gbz80.HL.b.l |= 0x02;
	MORE_CYCLES2(8);
}

void inst_cb_set_2_a()
{
	gbz80.AF.b.h |= 0x04;
	MORE_CYCLES2(8);
}

void inst_cb_set_2_b()
{
	gbz80.BC.b.h |= 0x04;
	MORE_CYCLES2(8);
}

void inst_cb_set_2_c()
{
	gbz80.BC.b.l |= 0x04;
	MORE_CYCLES2(8);
}

void inst_cb_set_2_d()
{
	gbz80.DE.b.h |= 0x04;
	MORE_CYCLES2(8);
}

void inst_cb_set_2_e()
{
	gbz80.DE.b.l |= 0x04;
	MORE_CYCLES2(8);
}

void inst_cb_set_2_h()
{
	gbz80.HL.b.h |= 0x04;
	MORE_CYCLES2(8);
}

void inst_cb_set_2_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x04);
	MORE_CYCLES2(12);
}

void inst_cb_set_2_l()
{
	gbz80.HL.b.l |= 0x04;
	MORE_CYCLES2(8);
}

void inst_cb_set_3_a()
{
	gbz80.AF.b.h |= 0x08;
	MORE_CYCLES2(8);
}

void inst_cb_set_3_b()
{
	gbz80.BC.b.h |= 0x08;
	MORE_CYCLES2(8);
}

void inst_cb_set_3_c()
{
	gbz80.BC.b.l |= 0x08;
	MORE_CYCLES2(8);
}

void inst_cb_set_3_d()
{
	gbz80.DE.b.h |= 0x08;
	MORE_CYCLES2(8);
}

void inst_cb_set_3_e()
{
	gbz80.DE.b.l |= 0x08;
	MORE_CYCLES2(8);
}

void inst_cb_set_3_h()
{
	gbz80.HL.b.h |= 0x08;
	MORE_CYCLES2(8);
}

void inst_cb_set_3_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x08);
	MORE_CYCLES2(12);
}

void inst_cb_set_3_l()
{
	gbz80.HL.b.l |= 0x08;
	MORE_CYCLES2(8);
}

void inst_cb_set_4_a()
{
	gbz80.AF.b.h |= 0x10;
	MORE_CYCLES2(8);
}

void inst_cb_set_4_b()
{
	gbz80.BC.b.h |= 0x10;
	MORE_CYCLES2(8);
}

void inst_cb_set_4_c()
{
	gbz80.BC.b.l |= 0x10;
	MORE_CYCLES2(8);
}

void inst_cb_set_4_d()
{
	gbz80.DE.b.h |= 0x10;
	MORE_CYCLES2(8);
}

void inst_cb_set_4_e()
{
	gbz80.DE.b.l |= 0x10;
	MORE_CYCLES2(8);
}

void inst_cb_set_4_h()
{
	gbz80.HL.b.h |= 0x10;
	MORE_CYCLES2(8);
}

void inst_cb_set_4_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x10);
	MORE_CYCLES2(12);
}

void inst_cb_set_4_l()
{
	gbz80.HL.b.l |= 0x10;
	MORE_CYCLES2(8);
}

void inst_cb_set_5_a()
{
	gbz80.AF.b.h |= 0x20;
	MORE_CYCLES2(8);
}

void inst_cb_set_5_b()
{
	gbz80.BC.b.h |= 0x20;
	MORE_CYCLES2(8);
}

void inst_cb_set_5_c()
{
	gbz80.BC.b.l |= 0x20;
	MORE_CYCLES2(8);
}

void inst_cb_set_5_d()
{
	gbz80.DE.b.h |= 0x20;
	MORE_CYCLES2(8);
}

void inst_cb_set_5_e()
{
	gbz80.DE.b.l |= 0x20;
	MORE_CYCLES2(8);
}

void inst_cb_set_5_h()
{
	gbz80.HL.b.h |= 0x20;
	MORE_CYCLES2(8);
}

void inst_cb_set_5_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x20);
	MORE_CYCLES2(12);
}

void inst_cb_set_5_l()
{
	gbz80.HL.b.l |= 0x20;
	MORE_CYCLES2(8);
}

void inst_cb_set_6_a()
{
	gbz80.AF.b.h |= 0x40;
	MORE_CYCLES2(8);
}

void inst_cb_set_6_b()
{
	gbz80.BC.b.h |= 0x40;
	MORE_CYCLES2(8);
}

void inst_cb_set_6_c()
{
	gbz80.BC.b.l |= 0x40;
	MORE_CYCLES2(8);
}

void inst_cb_set_6_d()
{
	gbz80.DE.b.h |= 0x40;
	MORE_CYCLES2(8);
}

void inst_cb_set_6_e()
{
	gbz80.DE.b.l |= 0x40;
	MORE_CYCLES2(8);
}

void inst_cb_set_6_h()
{
	gbz80.HL.b.h |= 0x40;
	MORE_CYCLES2(8);
}

void inst_cb_set_6_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x40);
	MORE_CYCLES2(12);
}

void inst_cb_set_6_l()
{
	gbz80.HL.b.l |= 0x40;
	MORE_CYCLES2(8);
}

void inst_cb_set_7_a()
{
	gbz80.AF.b.h |= 0x80;
	MORE_CYCLES2(8);
}

void inst_cb_set_7_b()
{
	gbz80.BC.b.h |= 0x80;
	MORE_CYCLES2(8);
}

void inst_cb_set_7_c()
{
	gbz80.BC.b.l |= 0x80;
	MORE_CYCLES2(8);
}

void inst_cb_set_7_d()
{
	gbz80.DE.b.h |= 0x80;
	MORE_CYCLES2(8);
}

void inst_cb_set_7_e()
{
	gbz80.DE.b.l |= 0x80;
	MORE_CYCLES2(8);
}

void inst_cb_set_7_h()
{
	gbz80.HL.b.h |= 0x80;
	MORE_CYCLES2(8);
}

void inst_cb_set_7_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, what | 0x80);
	MORE_CYCLES2(12);
}

void inst_cb_set_7_l()
{
	gbz80.HL.b.l |= 0x80;
	MORE_CYCLES2(8);
}

void inst_cb_sla_a()
{
	if (gbz80.AF.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.AF.b.h <<= 1;
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sla_b()
{
	if (gbz80.BC.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.h <<= 1;
	
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sla_c()
{
	if (gbz80.BC.b.l & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.l <<= 1;
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sla_d()
{
	if (gbz80.DE.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.h <<= 1;
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sla_e()
{
	if (gbz80.DE.b.l & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.l <<= 1;
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sla_h()
{
	if (gbz80.HL.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.h <<= 1;
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sla_hl_indirect()
{
	unsigned char data = memory_read_byte(gbz80.HL.uw);
	
	if (data & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	data <<= 1;

	memory_write_byte(gbz80.HL.uw, data);	/* fix */
		
	if (data)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(16);
}

void inst_cb_sla_l()
{
	if (gbz80.HL.b.l & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.l <<= 1;
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sra_a()
{
	if (gbz80.AF.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.AF.b.h = (gbz80.AF.b.h & 0x80) | (gbz80.AF.b.h >> 1);
	
	if (gbz80.AF.b.h) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sra_b()
{
	if (gbz80.BC.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.h = (gbz80.BC.b.h & 0x80) | (gbz80.BC.b.h >> 1);
	
	if (gbz80.BC.b.h) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sra_c()
{
	if (gbz80.BC.b.l & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.l = (gbz80.BC.b.l & 0x80) | (gbz80.BC.b.l >> 1);
	
	if (gbz80.BC.b.l) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sra_d()
{
	if (gbz80.DE.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.h = (gbz80.DE.b.h & 0x80) | (gbz80.DE.b.h >> 1);
	
	if (gbz80.DE.b.h) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sra_e()
{
	if (gbz80.DE.b.l & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.l = (gbz80.DE.b.l & 0x80) | (gbz80.DE.b.l >> 1);
	
	if (gbz80.DE.b.l) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sra_h()
{
	if (gbz80.HL.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.h = (gbz80.HL.b.h & 0x80) | (gbz80.HL.b.h >> 1);
	
	if (gbz80.HL.b.h) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_sra_hl_indirect()
{
	unsigned char value = memory_read_byte(gbz80.HL.uw);
	
	if (value & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	value = (value & 0x80) | (value >> 1);
	
	if (value) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	memory_write_byte(gbz80.HL.uw, value);
	
	MORE_CYCLES2(16);
}

void inst_cb_sra_l()
{
	if (gbz80.HL.b.l & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.l = (gbz80.HL.b.l & 0x80) | (gbz80.HL.b.l >> 1);
	
	if (gbz80.HL.b.l) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_srl_a()
{
	if (gbz80.AF.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.AF.b.h >>= 1;
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_srl_b()
{
	if (gbz80.BC.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.h >>= 1;
	
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_srl_c()
{
	if (gbz80.BC.b.l & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.BC.b.l >>= 1;
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_srl_d()
{
	if (gbz80.DE.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.h >>= 1;
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_srl_e()
{
	if (gbz80.DE.b.l & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.DE.b.l >>= 1;
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_srl_h()
{
	if (gbz80.HL.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.h >>= 1;
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_srl_hl_indirect()
{
	unsigned char value = memory_read_byte(gbz80.HL.uw);
	
	if (value & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	value >>= 1;
	
	if (value)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	memory_write_byte(gbz80.HL.uw, value);
	
	MORE_CYCLES2(16);
}

void inst_cb_srl_l()
{
	if (gbz80.HL.b.l & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	gbz80.HL.b.l >>= 1;
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_swap_a()
{
	unsigned char what = gbz80.AF.b.h;
	gbz80.AF.b.h = ((what & 0xF) << 4) | ((what & 0xF0) >> 4);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_swap_b()
{
	unsigned char what = gbz80.BC.b.h;
	gbz80.BC.b.h = ((what & 0xF) << 4) | ((what & 0xF0) >> 4);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_swap_c()
{
	unsigned char what = gbz80.BC.b.l;
	gbz80.BC.b.l = ((what & 0xF) << 4) | ((what & 0xF0) >> 4);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_swap_d()
{
	unsigned char what = gbz80.DE.b.h;
	gbz80.DE.b.h = ((what & 0xF) << 4) | ((what & 0xF0) >> 4);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_swap_e()
{
	unsigned char what = gbz80.DE.b.l;
	gbz80.DE.b.l = ((what & 0xF) << 4) | ((what & 0xF0) >> 4);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_swap_h()
{
	unsigned char what = gbz80.HL.b.h;
	gbz80.HL.b.h = ((what & 0xF) << 4) | ((what & 0xF0) >> 4);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(8);
}

void inst_cb_swap_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	memory_write_byte(gbz80.HL.uw, ((what & 0xF) << 4) | ((what & 0xF0) >> 4));
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(16);
}

void inst_cb_swap_l()
{
	unsigned char what = gbz80.HL.b.l;
	gbz80.HL.b.l = ((what & 0xF) << 4) | ((what & 0xF0) >> 4);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY | FLAGS_CARRY);
	
	MORE_CYCLES2(8);
}

void inst_ccf()
{
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	if (FLAGS_ISCARRY(gameboy_proc))
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	MORE_CYCLES2(4);
}

void inst_cp_a()
{
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE | FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_cp_b()
{
	unsigned char value = gbz80.BC.b.h;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(4);
}

void inst_cp_c()
{
	unsigned char value = gbz80.BC.b.l;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(4);
}

void inst_cp_d()
{
	unsigned char value = gbz80.DE.b.h;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(4);
}

void inst_cp_e()
{
	unsigned char value = gbz80.DE.b.l;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(4);
}

void inst_cp_h()
{
	unsigned char value = gbz80.HL.b.h;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(4);
}

void inst_cp_hl_indirect()
{
	unsigned char value = memory_read_byte(gbz80.HL.uw);
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(8);
}

void inst_cp_l()
{
	unsigned char value = gbz80.HL.b.l;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(4);
}

void inst_cp_n()
{
	unsigned char value = memory_read_pc_byte();
	gbz80.PC.uw++;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if (gbz80.AF.b.h == value)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if (value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	MORE_CYCLES2(8);
}

void inst_cpl()
{
	gbz80.AF.b.h = ~gbz80.AF.b.h;
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

#include "daa.h"

void inst_daa()
{
	int x = daa_table[((((gbz80.AF.b.l & 0xF0) << 4) | gbz80.AF.b.h) << 1) + 0];
	int y = daa_table[((((gbz80.AF.b.l & 0xF0) << 4) | gbz80.AF.b.h) << 1) + 1];
	gbz80.AF.b.h = x;
	gbz80.AF.b.l = y;
	MORE_CYCLES2(4);	
}

void inst_dec_a()
{
	if (gbz80.AF.b.h & 0x0F) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.AF.b.h--;
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_dec_b()
{
	if (gbz80.BC.b.h & 0x0F) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.BC.b.h--;
	
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_dec_bc()
{
	gbz80.BC.uw--;
	MORE_CYCLES2(8);
}

void inst_dec_c()
{
	if (gbz80.BC.b.l & 0x0F) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.BC.b.l--;
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_dec_d()
{
	if (gbz80.DE.b.h & 0x0F) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.DE.b.h--;
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_dec_de()
{
	gbz80.DE.uw--;
	MORE_CYCLES2(8);
}

void inst_dec_e()
{
	if (gbz80.DE.b.l & 0x0F) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.DE.b.l--;
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_dec_h()
{
	if (gbz80.HL.b.h & 0x0F) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.HL.b.h--;
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_dec_hl()
{
	gbz80.HL.uw--;
	MORE_CYCLES2(8);
}

void inst_dec_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	if (what & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	what--;
	memory_write_byte(gbz80.HL.uw, what);
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	MORE_CYCLES2(12);
}

void inst_dec_l()
{
	if (gbz80.HL.b.l & 0x0F) 
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	gbz80.HL.b.l--;
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_dec_sp()
{
	gbz80.SP.uw--;
	MORE_CYCLES2(8);
}

void inst_di()
{
	gbz80.IFF = 0;
	MORE_CYCLES2(4);
}

void inst_ei()
{
	gbz80.IFF = 1;
	MORE_CYCLES2(4);
}

void inst_halt()
{
	MORE_CYCLES2(4);
	
	if (gbz80.IFF) {
		HaltActive = 1;
	}
}

void inst_inc_a()
{
/*	
	if ((gbz80.AF.b.h & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/		
	gbz80.AF.b.h++;
	
	if (gbz80.AF.b.h & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
		
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_inc_b()
{
/*
	if ((gbz80.BC.b.h & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/		
	gbz80.BC.b.h++;
	
	if (gbz80.BC.b.h & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
		
	if (gbz80.BC.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_inc_bc()
{
	gbz80.BC.uw++;
	MORE_CYCLES2(8);
}

void inst_inc_c()
{
/*
	if ((gbz80.BC.b.l & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/
		
	gbz80.BC.b.l++;
	
	if (gbz80.BC.b.l & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	if (gbz80.BC.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_inc_d()
{
/*
	if ((gbz80.DE.b.h & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/
		
	gbz80.DE.b.h++;
	
	if (gbz80.DE.b.h & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	if (gbz80.DE.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_inc_de()
{
	gbz80.DE.uw++;
	MORE_CYCLES2(8);
}

void inst_inc_e()
{
/*
	if ((gbz80.DE.b.l & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/
		
	gbz80.DE.b.l++;
	
	if (gbz80.DE.b.l & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	if (gbz80.DE.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_inc_h()
{
/*
	if ((gbz80.HL.b.h & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/		
	gbz80.HL.b.h++;
	
	if (gbz80.HL.b.h & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	if (gbz80.HL.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_inc_hl()
{
	gbz80.HL.uw++;
	MORE_CYCLES2(8);
}

void inst_inc_hl_indirect()
{
	unsigned char what = memory_read_byte(gbz80.HL.uw);
	
/*
	if ((what & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/
		
	what++;
	memory_write_byte(gbz80.HL.uw, what);
	
	if (what & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	if (what)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(12);
}

void inst_inc_l()
{
/*
	if ((gbz80.HL.b.l & 0x0F) == 0x0F)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
*/
		
	gbz80.HL.b.l++;
	
	if (gbz80.HL.b.l & 0x0F)
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	
	if (gbz80.HL.b.l)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE);
	
	MORE_CYCLES2(4);
}

void inst_inc_sp()
{
	gbz80.SP.uw++;
	MORE_CYCLES2(8);
}

void inst_jp_c_nn()
{
	if(FLAGS_ISCARRY(gameboy_proc)) {
		gbz80.PC.uw = memory_read_pc_word();
		MORE_CYCLES2(16);
	} else {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	}
}

void inst_jp_hl()
{
	gbz80.PC.uw = gbz80.HL.uw;
	MORE_CYCLES2(4);
}

void inst_jp_nc_nn()
{
	if (FLAGS_ISCARRY(gameboy_proc)) {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	} else {
		gbz80.PC.uw = memory_read_pc_word();
		MORE_CYCLES2(16);
	}
}

void inst_jp_nn() /* C3 */
{
	gbz80.PC.uw = memory_read_pc_word();
	MORE_CYCLES2(16);
}

void inst_jp_nz_nn()
{
	if (FLAGS_ISZERO(gameboy_proc)) {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	} else {
		gbz80.PC.uw = memory_read_pc_word();
		MORE_CYCLES2(16);
	}
}

void inst_jp_z_nn()
{
	if (FLAGS_ISZERO(gameboy_proc)) {
		gbz80.PC.uw = memory_read_pc_word();
		MORE_CYCLES2(16);
	} else {
		gbz80.PC.uw += 2;
		MORE_CYCLES2(12);
	}
}

void inst_jr_c_n()
{
	signed char offset = memory_read_pc_byte();
	gbz80.PC.uw++;
	
	if (FLAGS_ISCARRY(gameboy_proc)) {
		gbz80.PC.uw += offset;
		MORE_CYCLES2(12);
	} else {
		MORE_CYCLES2(8);
	}
}

void inst_jr_n()
{
	signed char offset = memory_read_pc_byte();
	gbz80.PC.uw++;
	
	gbz80.PC.uw += offset;
	MORE_CYCLES2(12);
}

void inst_jr_nc_n()
{
	signed char offset = memory_read_pc_byte();
	gbz80.PC.uw++;
	
	if(FLAGS_ISCARRY(gameboy_proc)) {
		MORE_CYCLES2(8);
	} else {
		gbz80.PC.uw += offset;
		MORE_CYCLES2(12);
	}
}

void inst_jr_nz_n()
{
	signed char offset = memory_read_pc_byte();
	gbz80.PC.uw++;
	
	if (FLAGS_ISZERO(gameboy_proc)) {
		MORE_CYCLES2(8);
	} else {
		gbz80.PC.uw += offset;
		MORE_CYCLES2(12);
	}
}

void inst_jr_z_n()
{
	signed char offset = memory_read_pc_byte();
	gbz80.PC.uw++;
	
	if (FLAGS_ISZERO(gameboy_proc)) {
		gbz80.PC.uw += offset;
		MORE_CYCLES2(12);
	} else {
		MORE_CYCLES2(8);
	}
}

#define INST_LD(x, y) \
{ \
	x = y; \
}

void inst_ld_a_bc_indirect()
{
	gbz80.AF.b.h = memory_read_byte(gbz80.BC.uw);
	MORE_CYCLES2(8);
}

void inst_ld_a_c_indirect()
{
	gbz80.AF.b.h = memory_read_hibyte(gbz80.BC.b.l);
	MORE_CYCLES2(8);
}

void inst_ld_a_de_indirect()
{
	gbz80.AF.b.h = memory_read_byte(gbz80.DE.uw);
	MORE_CYCLES2(8);
}

void inst_ld_a_ff_n_indirect()
{
	gbz80.AF.b.h = memory_read_hibyte(memory_read_pc_byte());
	gbz80.PC.uw++;
	MORE_CYCLES2(12);
}

void inst_ld_a_hld_indirect()
{
	gbz80.AF.b.h = memory_read_byte(gbz80.HL.uw);
	gbz80.HL.uw--;
	MORE_CYCLES2(8);
}

void inst_ld_a_hli_indirect()
{
	gbz80.AF.b.h = memory_read_byte(gbz80.HL.uw);
	gbz80.HL.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_a_n()
{
	gbz80.AF.b.h = memory_read_pc_byte();
	gbz80.PC.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_a_nn_indirect()
{
	gbz80.AF.b.h = memory_read_byte(memory_read_pc_word());
	gbz80.PC.uw += 2;
	MORE_CYCLES2(16);
}

void inst_ld_b_a()
{
	gbz80.BC.b.h = gbz80.AF.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_b_c()
{
	gbz80.BC.b.h = gbz80.BC.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_b_d()
{
	gbz80.BC.b.h = gbz80.DE.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_b_e()
{
	gbz80.BC.b.h = gbz80.DE.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_b_h()
{
	gbz80.BC.b.h = gbz80.HL.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_b_hl_indirect()
{
	gbz80.BC.b.h = memory_read_byte(gbz80.HL.uw);
	MORE_CYCLES2(8);
}

void inst_ld_b_l()
{
	gbz80.BC.b.h = gbz80.HL.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_b_n()
{
	gbz80.BC.b.h = memory_read_pc_byte();
	gbz80.PC.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_bc_indirect_a()
{
	memory_write_byte(gbz80.BC.uw, gbz80.AF.b.h);
	MORE_CYCLES2(8);
}

void inst_ld_bc_nn()
{
	gbz80.BC.uw = memory_read_pc_word();
	gbz80.PC.uw += 2;
	
	MORE_CYCLES2(12);
}

void inst_ld_c_a()
{
	gbz80.BC.b.l = gbz80.AF.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_c_b()
{
	gbz80.BC.b.l = gbz80.BC.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_c_d()
{
	gbz80.BC.b.l = gbz80.DE.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_c_e()
{
	gbz80.BC.b.l = gbz80.DE.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_c_h()
{
	gbz80.BC.b.l = gbz80.HL.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_c_hl_indirect()
{
	gbz80.BC.b.l = memory_read_byte(gbz80.HL.uw);
	MORE_CYCLES2(8);
}

void inst_ld_c_indirect_a()
{
	memory_write_hibyte(gbz80.BC.b.l, gbz80.AF.b.h);
	MORE_CYCLES2(8);
}

void inst_ld_c_l()
{
	gbz80.BC.b.l = gbz80.HL.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_c_n()
{
	gbz80.BC.b.l = memory_read_pc_byte();
	gbz80.PC.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_d_a()
{
	gbz80.DE.b.h = gbz80.AF.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_d_b()
{
	gbz80.DE.b.h = gbz80.BC.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_d_c()
{
	gbz80.DE.b.h = gbz80.BC.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_d_e()
{
	gbz80.DE.b.h = gbz80.DE.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_d_h()
{
	gbz80.DE.b.h = gbz80.HL.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_d_hl_indirect()
{
	gbz80.DE.b.h = memory_read_byte(gbz80.HL.uw);
	MORE_CYCLES2(8);
}

void inst_ld_d_l()
{
	gbz80.DE.b.h = gbz80.HL.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_d_n()
{
	gbz80.DE.b.h = memory_read_pc_byte();
	gbz80.PC.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_de_indirect_a()
{
	memory_write_byte(gbz80.DE.uw, gbz80.AF.b.h);
	MORE_CYCLES2(8);
}

void inst_ld_de_nn()
{
	gbz80.DE.uw = memory_read_pc_word();
	gbz80.PC.uw += 2;
	
	MORE_CYCLES2(12);
}

void inst_ld_e_a()
{
	gbz80.DE.b.l = gbz80.AF.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_e_b()
{
	gbz80.DE.b.l = gbz80.BC.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_e_c()
{
	gbz80.DE.b.l = gbz80.BC.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_e_d()
{
	gbz80.DE.b.l = gbz80.DE.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_e_h()
{
	gbz80.DE.b.l = gbz80.HL.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_e_hl_indirect()
{
	gbz80.DE.b.l = memory_read_byte(gbz80.HL.uw);
	MORE_CYCLES2(8);
}

void inst_ld_e_l()
{
	gbz80.DE.b.l = gbz80.HL.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_e_n()
{
	gbz80.DE.b.l = memory_read_pc_byte();
	gbz80.PC.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_ff_n_indirect_a()
{
	memory_write_hibyte(memory_read_pc_byte(), gbz80.AF.b.h);
	gbz80.PC.uw++;
	MORE_CYCLES2(12);
}

void inst_ld_h_a()
{
	gbz80.HL.b.h = gbz80.AF.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_h_b()
{
	gbz80.HL.b.h = gbz80.BC.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_h_c()
{
	gbz80.HL.b.h = gbz80.BC.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_h_d()
{
	gbz80.HL.b.h = gbz80.DE.b.h;
	MORE_CYCLES2(4);
}

void inst_ld_h_e()
{
	gbz80.HL.b.h = gbz80.DE.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_h_hl_indirect()
{
	gbz80.HL.b.h = memory_read_byte(gbz80.HL.uw);
	MORE_CYCLES2(8);
}

void inst_ld_h_l()
{
	gbz80.HL.b.h = gbz80.HL.b.l;
	MORE_CYCLES2(4);
}

void inst_ld_h_n()
{
	gbz80.HL.b.h = memory_read_pc_byte();
	gbz80.PC.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_a()
{
	memory_write_byte(gbz80.HL.uw, gbz80.AF.b.h);
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_b()
{
	memory_write_byte(gbz80.HL.uw, gbz80.BC.b.h);
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_c()
{
	memory_write_byte(gbz80.HL.uw, gbz80.BC.b.l);
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_d()
{
	memory_write_byte(gbz80.HL.uw, gbz80.DE.b.h);
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_e()
{
	memory_write_byte(gbz80.HL.uw, gbz80.DE.b.l);
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_h()
{
	memory_write_byte(gbz80.HL.uw, gbz80.HL.b.h);
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_l()
{
	memory_write_byte(gbz80.HL.uw, gbz80.HL.b.l);
	MORE_CYCLES2(8);
}

void inst_ld_hl_indirect_n()
{
	memory_write_byte(gbz80.HL.uw, memory_read_pc_byte());
	gbz80.PC.uw++;
	MORE_CYCLES2(12);
}

void inst_ld_hl_nn()
{
	gbz80.HL.uw = memory_read_pc_word();
	gbz80.PC.uw += 2;
	
	MORE_CYCLES2(12);
}

void inst_ld_hl_sp_n()
{
	signed char offset = memory_read_pc_byte();
	int result = gbz80.SP.uw + offset;
	gbz80.PC.uw++;
	
	if(result & 0xFFFF0000)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	
	/* TODO, I think so.. */
	if (((gbz80.SP.uw & 0xFFF) + (offset & 0xFFF)) > 0xFFF)
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO | FLAGS_NEGATIVE);
	
	gbz80.HL.uw  = result & 0xFFFF;
	
	MORE_CYCLES2(12);
}

void inst_ld_hld_indirect_a()
{
	memory_write_byte(gbz80.HL.uw, gbz80.AF.b.h);
	gbz80.HL.uw--;
	MORE_CYCLES2(8);
}

void inst_ld_hli_indirect_a()
{
	memory_write_byte(gbz80.HL.uw, gbz80.AF.b.h);
	gbz80.HL.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_l_a()
{
	gbz80.HL.b.l = gbz80.AF.b.h;
	MORE_CYCLES2(8);
}

void inst_ld_l_b()
{
	gbz80.HL.b.l = gbz80.BC.b.h;
	MORE_CYCLES2(8);
}

void inst_ld_l_c()
{
	gbz80.HL.b.l = gbz80.BC.b.l;
	MORE_CYCLES2(8);
}

void inst_ld_l_d()
{
	gbz80.HL.b.l = gbz80.DE.b.h;
	MORE_CYCLES2(8);
}

void inst_ld_l_e()
{
	gbz80.HL.b.l = gbz80.DE.b.l;
	MORE_CYCLES2(8);
}

void inst_ld_l_h()
{
	gbz80.HL.b.l = gbz80.HL.b.h;
	MORE_CYCLES2(8);
}

void inst_ld_l_hl_indirect()
{
	gbz80.HL.b.l = memory_read_byte(gbz80.HL.uw);
	MORE_CYCLES2(8);
}

void inst_ld_l_n()
{
	gbz80.HL.b.l = memory_read_pc_byte();
	gbz80.PC.uw++;
	MORE_CYCLES2(8);
}

void inst_ld_nn_indirect_a()
{
	memory_write_byte(memory_read_pc_word(), gbz80.AF.b.h);
	gbz80.PC.uw += 2;
	MORE_CYCLES2(16);
}

void inst_ld_nn_indirect_sp()
{
	memory_write_word(memory_read_pc_word(), gbz80.SP.uw);
	gbz80.PC.uw += 2;
	MORE_CYCLES2(20);
}

void inst_ld_sp_hl()
{
	gbz80.SP.uw = gbz80.HL.uw;
	MORE_CYCLES2(8);
}

void inst_ld_sp_nn()
{
	gbz80.SP.uw = memory_read_pc_word();
	gbz80.PC.uw += 2;
	MORE_CYCLES2(12);
}

void inst_or_a()
{
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_or_b()
{
	gbz80.AF.b.h |= gbz80.BC.b.h;
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_or_c()
{
	gbz80.AF.b.h |= gbz80.BC.b.l;
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_or_d()
{
	gbz80.AF.b.h |= gbz80.DE.b.h;
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_or_e()
{
	gbz80.AF.b.h |= gbz80.DE.b.l;
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_or_h()
{
	gbz80.AF.b.h |= gbz80.HL.b.h;
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_or_hl_indirect()
{
	gbz80.AF.b.h |= memory_read_byte(gbz80.HL.uw);
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_or_l()
{
	gbz80.AF.b.h |= gbz80.HL.b.l;
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_or_n()
{
	gbz80.AF.b.h |= memory_read_pc_byte();
	gbz80.PC.uw++;
	
	if (gbz80.AF.b.h)
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(8);
}

void inst_pop_af()
{
	gbz80.AF.uw = gameboy_stack_read_word();
	MORE_CYCLES2(12);
}

void inst_pop_bc()
{
	gbz80.BC.uw = gameboy_stack_read_word();
	MORE_CYCLES2(12);
}

void inst_pop_de()
{
	gbz80.DE.uw = gameboy_stack_read_word();
	MORE_CYCLES2(12);
}

void inst_pop_hl()
{
	gbz80.HL.uw = gameboy_stack_read_word();
	MORE_CYCLES2(12);
}

void inst_push_af()
{
	gameboy_stack_write_word(gbz80.AF.uw);
	MORE_CYCLES2(16);
}

void inst_push_bc()
{
	gameboy_stack_write_word(gbz80.BC.uw);
	MORE_CYCLES2(16);
}

void inst_push_de()
{
	gameboy_stack_write_word(gbz80.DE.uw);
	MORE_CYCLES2(16);
}

void inst_push_hl()
{
	gameboy_stack_write_word(gbz80.HL.uw);
	MORE_CYCLES2(16);
}

void inst_ret()
{
	gbz80.PC.uw = gameboy_stack_read_word();
	MORE_CYCLES2(16);
}

void inst_ret_c()
{
	if (FLAGS_ISCARRY(gameboy_proc)) {
		gbz80.PC.uw = gameboy_stack_read_word();
		MORE_CYCLES2(20);
	} else {
		MORE_CYCLES2(8);
	}
}

void inst_ret_nc()
{
	if (FLAGS_ISCARRY(gameboy_proc)) {
		MORE_CYCLES2(8);
	} else {
		gbz80.PC.uw = gameboy_stack_read_word();
		MORE_CYCLES2(20);
	}
}

void inst_ret_nz()
{
	if (FLAGS_ISZERO(gameboy_proc)) {
		MORE_CYCLES2(8);
	} else {
		gbz80.PC.uw = gameboy_stack_read_word();
		MORE_CYCLES2(20);
	}
}

void inst_ret_z()
{
	if (FLAGS_ISZERO(gameboy_proc)) {
		gbz80.PC.uw = gameboy_stack_read_word();
		MORE_CYCLES2(20);
	} else {
		MORE_CYCLES2(8);
	}
}

void inst_reti()
{
	gbz80.PC.uw = gameboy_stack_read_word();
	gbz80.IFF = 1;
	MORE_CYCLES2(16);
}

void inst_rla()
{
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;
	if (gbz80.AF.b.h & 0x80)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	gbz80.AF.b.h <<= 1;
	gbz80.AF.b.h += carry;
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_ZERO | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_rlca()
{
	int carry = (gbz80.AF.b.h & 0x80) >> 7;
	if (carry)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	gbz80.AF.b.h <<= 1;
	gbz80.AF.b.h += carry;
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_ZERO | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_rra()
{
	int carry = (FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0) << 7;
	if (gbz80.AF.b.h & 0x01)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	gbz80.AF.b.h >>= 1;
	gbz80.AF.b.h += carry;
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_ZERO | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_rrca()
{
	int carry = gbz80.AF.b.h & 0x01;
	if (carry)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	gbz80.AF.b.h >>= 1;
	if (carry)
		gbz80.AF.b.h |= 0x80;
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_ZERO | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

void inst_rst_00h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x00;
	MORE_CYCLES2(16);
}

void inst_rst_08h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x08;
	MORE_CYCLES2(16);
}

void inst_rst_10h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x10;
	MORE_CYCLES2(16);
}

void inst_rst_18h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x18;
	MORE_CYCLES2(16);
}

void inst_rst_20h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x20;
	MORE_CYCLES2(16);
}

void inst_rst_28h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x28;
	MORE_CYCLES2(16);
}

void inst_rst_30h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x30;
	MORE_CYCLES2(16);
}

void inst_rst_38h()
{
	gameboy_stack_write_word(gbz80.PC.uw);
	gbz80.PC.uw = 0x38;
	MORE_CYCLES2(16);
}

void inst_sbc_a()
{
	if (FLAGS_ISCARRY(gameboy_proc)) {
		gbz80.AF.b.h = 0xFF;
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	} else {
		gbz80.AF.b.h = 0;
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	}
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
}

#define INST_SBC(x) { \
	int num = x;					\
	int carry = FLAGS_ISSET(gameboy_proc, FLAGS_CARRY) ? 1 : 0;	\
	int value = num + carry;					\
									\
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);			\
									\
	if(value > gbz80.AF.b.h)				\
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);			\
	else								\
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);			\
									\
	if((value & 0xFF) == gbz80.AF.b.h)			\
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);			\
	else								\
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);			\
									\
	if (((num & 0x0F) + carry) > (gbz80.AF.b.h & 0x0F))	\
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);		\
	else								\
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);		\
									\
	gbz80.AF.b.h -= value;					\
}

void inst_scf()
{
	FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	FLAGS_CLEAR(gameboy_proc, FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	
	MORE_CYCLES2(4);
}

void inst_stop()
{
/*
	if (KEY1REG & 0x01) {
		KEY1REG ^= 0x81;
	} else {
		unsigned long oc = current_joypad;
		while(oc != current_joypad)
			vram_sysupdate();
	}
	
	if (KEY1REG & 0x80)
		CPUSpeed = 2;
	else
		CPUSpeed = 1;
		
*/
	gbz80.PC.uw++; 
	MORE_CYCLES2(4);
}

void inst_sub_a()
{
	gbz80.AF.b.h = 0;
	FLAGS_SET(gameboy_proc, FLAGS_ZERO | FLAGS_NEGATIVE);
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
	FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
	
	MORE_CYCLES2(8);
}

void inst_sub_b()
{
	int value = gbz80.BC.b.h;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(4);
}

void inst_sub_c()
{
	int value = gbz80.BC.b.l;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(4);
}

void inst_sub_d()
{
	int value = gbz80.DE.b.h;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(4);
}

void inst_sub_e()
{
	int value = gbz80.DE.b.l;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(4);
}

void inst_sub_h()
{
	int value = gbz80.HL.b.h;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(4);
}

void inst_sub_hl_indirect()
{
	int value = memory_read_byte(gbz80.HL.uw);
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(8);
}

void inst_sub_l()
{
	int value = gbz80.HL.b.l;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(4);
}

void inst_sub_n()
{
	int value = memory_read_pc_byte();
	gbz80.PC.uw++;
	
	FLAGS_SET(gameboy_proc, FLAGS_NEGATIVE);
	
	if(value > gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_CARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY);
		
	if(value == gbz80.AF.b.h)
		FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO);
	
	if ((value & 0x0F) > (gbz80.AF.b.h & 0x0F))
		FLAGS_SET(gameboy_proc, FLAGS_HALFCARRY);
	else
		FLAGS_CLEAR(gameboy_proc, FLAGS_HALFCARRY);
		
	gbz80.AF.b.h -= value;
	
	MORE_CYCLES2(8);
}

void inst_unknown()
{
	gbz80.running = 0;
	gbz80.PC.uw  -= 1;
	printf("Unknown opcode:\n");
	printf("[%04X]: AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X (%02X/%02X) %02X %02X)\n", 
	gbz80.PC.uw, gbz80.AF.uw, gbz80.BC.uw,
	gbz80.DE.uw, gbz80.HL.uw, gbz80.SP.uw,
	memory_read_pc_byte(), memory_read_byte(gbz80.PC.uw), memory_read_byte(gbz80.PC.uw+1), memory_read_byte(gbz80.PC.uw+2));
}

void inst_xor_a() /* AF */
{
	gbz80.AF.b.h = 0;
	FLAGS_SET(gameboy_proc, FLAGS_ZERO);
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY);
	MORE_CYCLES2(4);
}

#define INST_XOR(x) \
{ \
	gbz80.AF.b.h ^= x; \
	\
	if (gbz80.AF.b.h) \
		FLAGS_CLEAR(gameboy_proc, FLAGS_ZERO); \
	else \
		FLAGS_SET(gameboy_proc, FLAGS_ZERO); \
	\
	FLAGS_CLEAR(gameboy_proc, FLAGS_CARRY | FLAGS_NEGATIVE | FLAGS_HALFCARRY); \
}

void inst_cb()
{
	int cbinst;
	
	cbinst = memory_read_pc_byte();
	
	gbz80.PC.uw++;
	
	switch((unsigned char )cbinst) {
		case 0x00: /* RLC B */
			inst_cb_rlc_b();
			break;
		case 0x01: /* RLC C */
			inst_cb_rlc_c();
			break;
		case 0x02:
			inst_cb_rlc_d();
			break;
		case 0x03:
			inst_cb_rlc_e();
			break;
		case 0x04:
			inst_cb_rlc_h();
			break;
		case 0x05:
			inst_cb_rlc_l();
			break;
		case 0x06:
			inst_cb_rlc_hl_indirect();
			break;
		case 0x07:
			inst_cb_rlc_a();
			break;
		
		case 0x08: /* RRC B */
			inst_cb_rrc_b();
			break;
		case 0x09: /* RRC C */
			inst_cb_rrc_c();
			break;
		case 0x0A: /* RRC D */
			inst_cb_rrc_d();
			break;
		case 0x0B: /* RRC E */
			inst_cb_rrc_e();
			break;
		case 0x0C:
			inst_cb_rrc_h();
			break;
		case 0x0D:
			inst_cb_rrc_l();
			break;
		case 0x0E:
			inst_cb_rrc_hl_indirect();
			break;
		case 0x0F:
			inst_cb_rrc_a();
			break;
		
		case 0x10: /* RL B */
			inst_cb_rl_b();
			break;
		case 0x11: /* RL C */
			inst_cb_rl_c();
			break;
		case 0x12:
			inst_cb_rl_d();
			break;
		case 0x13:
			inst_cb_rl_e();
			break;
		case 0x14:
			inst_cb_rl_h();
			break;
		case 0x15:
			inst_cb_rl_l();
			break;
		case 0x16:
			inst_cb_rl_hl_indirect();
			break;
		case 0x17:
			inst_cb_rl_a();
			break;
		
		case 0x18: /* RR B */
			inst_cb_rr_b();
			break;
		case 0x19: /* RR C */
			inst_cb_rr_c();
			break;
		case 0x1A: /* RR D */
			inst_cb_rr_d();
			break;
		case 0x1B:
			inst_cb_rr_e();
			break;
		case 0x1C:
			inst_cb_rr_h();
			break;
		case 0x1D:
			inst_cb_rr_l();
			break;
		case 0x1E:
			inst_cb_rr_hl_indirect();
			break;
		case 0x1F:
			inst_cb_rr_a();
			break;
		
		case 0x20: /* SLA B */
			inst_cb_sla_b();
			break;
		case 0x21: /* SLA C */
			inst_cb_sla_c();
			break;
		case 0x22:
			inst_cb_sla_d();
			break;
		case 0x23:
			inst_cb_sla_e();
			break;
		case 0x24:
			inst_cb_sla_h();
			break;
		case 0x25:
			inst_cb_sla_l();
			break;
		case 0x26:
			inst_cb_sla_hl_indirect();
			break;
		case 0x27:
			inst_cb_sla_a();
			break;
		
		case 0x28: /* SRA B */
			inst_cb_sra_b();
			break;
		case 0x29:
			inst_cb_sra_c();
			break;
		case 0x2A:
			inst_cb_sra_d();
			break;
		case 0x2B:
			inst_cb_sra_e();
			break;
		case 0x2C:
			inst_cb_sra_h();
			break;
		case 0x2D:
			inst_cb_sra_l();
			break;
		case 0x2E:
			inst_cb_sra_hl_indirect();
			break;
		case 0x2F:
			inst_cb_sra_a();
			break;
		
		case 0x30: /* SWAP B */
			inst_cb_swap_b();
			break;
		case 0x31:
			inst_cb_swap_c();
			break;
		case 0x32:
			inst_cb_swap_d();
			break;
		case 0x33:
			inst_cb_swap_e();
			break;
		case 0x34:
			inst_cb_swap_h();
			break;
		case 0x35:
			inst_cb_swap_l();
			break;
		case 0x36:
			inst_cb_swap_hl_indirect();
			break;
		case 0x37:
			inst_cb_swap_a();
			break;
		
		case 0x38: /* SRL B */
			inst_cb_srl_b();
			break;
		case 0x39:
			inst_cb_srl_c();
			break;
		case 0x3A:
			inst_cb_srl_d();
			break;
		case 0x3B:
			inst_cb_srl_e();
			break;
		case 0x3C:
			inst_cb_srl_h();
			break;
		case 0x3D:
			inst_cb_srl_l();
			break;
		case 0x3E:
			inst_cb_srl_hl_indirect();
			break;
		case 0x3F:
			inst_cb_srl_a();
			break;
		
		case 0x40: /* BIT 0, B */
			inst_cb_bit_0_b();
			break;
		case 0x41:
			inst_cb_bit_0_c();
			break;
		case 0x42:
			inst_cb_bit_0_d();
			break;
		case 0x43:
			inst_cb_bit_0_e();
			break;
		case 0x44:
			inst_cb_bit_0_h();
			break;
		case 0x45:
			inst_cb_bit_0_l();
			break;
		case 0x46:
			inst_cb_bit_0_hl_indirect();
			break;
		case 0x47:
			inst_cb_bit_0_a();
			break;
		
		case 0x48: /* BIT 1, B */
			inst_cb_bit_1_b();
			break;
		case 0x49: /* BIT 1, C */
			inst_cb_bit_1_c();
			break;
		case 0x4A: /* BIT 1, D */
			inst_cb_bit_1_d();
			break;
		case 0x4B: /* BIT 1, E */
			inst_cb_bit_1_e();
			break;
		case 0x4C:
			inst_cb_bit_1_h();
			break;
		case 0x4D:
			inst_cb_bit_1_l();
			break;
		case 0x4E:
			inst_cb_bit_1_hl_indirect();
			break;
		case 0x4F:
			inst_cb_bit_1_a();
			break;
		
		case 0x50: /* BIT 2, B */
			inst_cb_bit_2_b();
			break;
		case 0x51: /* BIT 2, C */
			inst_cb_bit_2_c();
			break;
		case 0x52:
			inst_cb_bit_2_d();
			break;
		case 0x53:
			inst_cb_bit_2_e();
			break;
		case 0x54:
			inst_cb_bit_2_h();
			break;
		case 0x55:
			inst_cb_bit_2_l();
			break;
		case 0x56:
			inst_cb_bit_2_hl_indirect();
			break;
		case 0x57:
			inst_cb_bit_2_a();
			break;
		
		case 0x58: /* BIT 3, B */
			inst_cb_bit_3_b();
			break;
		case 0x59:
			inst_cb_bit_3_c();
			break;
		case 0x5A:
			inst_cb_bit_3_d();
			break;
		case 0x5B:
			inst_cb_bit_3_e();
			break;
		case 0x5C:
			inst_cb_bit_3_h();
			break;
		case 0x5D:
			inst_cb_bit_3_l();
			break;
		case 0x5E:
			inst_cb_bit_3_hl_indirect();
			break;
		case 0x5F:
			inst_cb_bit_3_a();
			break;
		
		case 0x60: /* BIT 4, B */
			inst_cb_bit_4_b();
			break;
		case 0x61: /* BIT 4, C */
			inst_cb_bit_4_c();
			break;
		case 0x62:
			inst_cb_bit_4_d();
			break;
		case 0x63:
			inst_cb_bit_4_e();
			break;
		case 0x64:
			inst_cb_bit_4_h();
			break;
		case 0x65:
			inst_cb_bit_4_l();
			break;
		case 0x66:
			inst_cb_bit_4_hl_indirect();
			break;
		case 0x67:
			inst_cb_bit_4_a();
			break;
		
		case 0x68: /* BIT 5, B */
			inst_cb_bit_5_b();
			break;
		case 0x69:
			inst_cb_bit_5_c();
			break;
		case 0x6A:
			inst_cb_bit_5_d();
			break;
		case 0x6B:
			inst_cb_bit_5_e();
			break;
		case 0x6C:
			inst_cb_bit_5_h();
			break;
		case 0x6D:
			inst_cb_bit_5_l();
			break;
		case 0x6E:
			inst_cb_bit_5_hl_indirect();
			break;
		case 0x6F:
			inst_cb_bit_5_a();
			break;			
		
		case 0x70: /* BIT 6, B */
			inst_cb_bit_6_b();
			break;
		case 0x71: /* BIT 6, C */
			inst_cb_bit_6_c();
			break;
		case 0x72:
			inst_cb_bit_6_d();
			break;
		case 0x73:
			inst_cb_bit_6_e();
			break;
		case 0x74:
			inst_cb_bit_6_h();
			break;
		case 0x75:
			inst_cb_bit_6_l();
			break;
		case 0x76:
			inst_cb_bit_6_hl_indirect();
			break;
		case 0x77:
			inst_cb_bit_6_a();
			break;
		
		case 0x78: /* BIT 7, B */
			inst_cb_bit_7_b();
			break;
		case 0x79:
			inst_cb_bit_7_c();
			break;
		case 0x7A:
			inst_cb_bit_7_d();
			break;
		case 0x7B:
			inst_cb_bit_7_e();
			break;
		case 0x7C:
			inst_cb_bit_7_h();
			break;
		case 0x7D:
			inst_cb_bit_7_l();
			break;
		case 0x7E:
			inst_cb_bit_7_hl_indirect();
			break;
		case 0x7F:
			inst_cb_bit_7_a();
			break;
		 
		case 0x80: /* RES 0, B */
			inst_cb_res_0_b();
			break;
		case 0x81:
			inst_cb_res_0_c();
			break;
		case 0x82:
			inst_cb_res_0_d();
			break;
		case 0x83:
			inst_cb_res_0_e();
			break;
		case 0x84:
			inst_cb_res_0_h();
			break;
		case 0x85:
			inst_cb_res_0_l();
			break;
		case 0x86:
			inst_cb_res_0_hl_indirect();
			break;
		case 0x87:
			inst_cb_res_0_a();
			break;
		
		case 0x88: /* RES 1, B */
			inst_cb_res_1_b();
			break;
		case 0x89:
			inst_cb_res_1_c();
			break;
		case 0x8A:
			inst_cb_res_1_d();
			break;
		case 0x8B:
			inst_cb_res_1_e();
			break;
		case 0x8C:
			inst_cb_res_1_h();
			break;
		case 0x8D:
			inst_cb_res_1_l();
			break;
		case 0x8E:
			inst_cb_res_1_hl_indirect();
			break;
		case 0x8F:
			inst_cb_res_1_a();
			break;
		
		case 0x90: /* RES 2, B */
			inst_cb_res_2_b();
			break;
		case 0x91:
			inst_cb_res_2_c();
			break;
		case 0x92:
			inst_cb_res_2_d();
			break;
		case 0x93:
			inst_cb_res_2_e();
			break;
		case 0x94:
			inst_cb_res_2_h();
			break;
		case 0x95:
			inst_cb_res_2_l();
			break;
		case 0x96:
			inst_cb_res_2_hl_indirect();
			break;
		case 0x97:
			inst_cb_res_2_a();
			break;
		
		case 0x98: /* RES 3, B */
			inst_cb_res_3_b();
			break;
		case 0x99:
			inst_cb_res_3_c();
			break;
		case 0x9A:
			inst_cb_res_3_d();
			break;
		case 0x9B:
			inst_cb_res_3_e();
			break;
		case 0x9C:
			inst_cb_res_3_h();
			break;
		case 0x9D:
			inst_cb_res_3_l();
			break;
		case 0x9E:
			inst_cb_res_3_hl_indirect();
			break;
		case 0x9F:
			inst_cb_res_3_a();
			break;	
		
		case 0xA0: /* RES 4, B */
			inst_cb_res_4_b();
			break;
		case 0xA1:
			inst_cb_res_4_c();
			break;
		case 0xA2:
			inst_cb_res_4_d();
			break;
		case 0xA3:
			inst_cb_res_4_e();
			break;
		case 0xA4:
			inst_cb_res_4_h();
			break;
		case 0xA5:
			inst_cb_res_4_l();
			break;
		case 0xA6:
			inst_cb_res_4_hl_indirect();
			break;
		case 0xA7:
			inst_cb_res_4_a();
			break;
		
		case 0xA8: /* RES 5, B */
			inst_cb_res_5_b();
			break;
		case 0xA9:
			inst_cb_res_5_c();
			break;
		case 0xAA:
			inst_cb_res_5_d();
			break;
		case 0xAB:
			inst_cb_res_5_e();
			break;
		case 0xAC:
			inst_cb_res_5_h();
			break;
		case 0xAD:
			inst_cb_res_5_l();
			break;
		case 0xAE:
			inst_cb_res_5_hl_indirect();
			break;
		case 0xAF:
			inst_cb_res_5_a();
			break;
		
		case 0xB0: /* RES 6, B */
			inst_cb_res_6_b();
			break;
		case 0xB1:
			inst_cb_res_6_c();
			break;
		case 0xB2:
			inst_cb_res_6_d();
			break;
		case 0xB3:
			inst_cb_res_6_e();
			break;
		case 0xB4:
			inst_cb_res_6_h();
			break;
		case 0xB5:
			inst_cb_res_6_l();
			break;
		case 0xB6:
			inst_cb_res_6_hl_indirect();
			break;
		case 0xB7:
			inst_cb_res_6_a();
			break;
		
		case 0xB8: /* RES 7, B */
			inst_cb_res_7_b();
			break;
		case 0xB9:
			inst_cb_res_7_c();
			break;
		case 0xBA:
			inst_cb_res_7_d();
			break;
		case 0xBB:
			inst_cb_res_7_e();
			break;
		case 0xBC:
			inst_cb_res_7_h();
			break;
		case 0xBD:
			inst_cb_res_7_l();
			break;
		case 0xBE:
			inst_cb_res_7_hl_indirect();
			break;
		case 0xBF:
			inst_cb_res_7_a();
			break;
		
		case 0xC0: /* SET 0, B */
			inst_cb_set_0_b();
			break;
		case 0xC1:
			inst_cb_set_0_c();
			break;
		case 0xC2:
			inst_cb_set_0_d();
			break;
		case 0xC3:
			inst_cb_set_0_e();
			break;
		case 0xC4:
			inst_cb_set_0_h();
			break;
		case 0xC5:
			inst_cb_set_0_l();
			break;
		case 0xC6:
			inst_cb_set_0_hl_indirect();
			break;
		case 0xC7:
			inst_cb_set_0_a();
			break;
		
		case 0xC8: /* SET 1, B */
			inst_cb_set_1_b();
			break;
		case 0xC9:
			inst_cb_set_1_c();
			break;
		case 0xCA:
			inst_cb_set_1_d();
			break;
		case 0xCB:
			inst_cb_set_1_e();
			break;
		case 0xCC:
			inst_cb_set_1_h();
			break;
		case 0xCD:
			inst_cb_set_1_l();
			break;
		case 0xCE:
			inst_cb_set_1_hl_indirect();
			break;
		case 0xCF:
			inst_cb_set_1_a();
			break;
		
		case 0xD0: /* SET 2, B */
			inst_cb_set_2_b();
			break;
		case 0xD1:
			inst_cb_set_2_c();
			break;
		case 0xD2:
			inst_cb_set_2_d();
			break;
		case 0xD3:
			inst_cb_set_2_e();
			break;
		case 0xD4:
			inst_cb_set_2_h();
			break;
		case 0xD5:
			inst_cb_set_2_l();
			break;
		case 0xD6:
			inst_cb_set_2_hl_indirect();
			break;
		case 0xD7:
			inst_cb_set_2_a();
			break;
		
		case 0xD8: /* SET 3, B */
			inst_cb_set_3_b();
			break;
		case 0xD9:
			inst_cb_set_3_c();
			break;
		case 0xDA:
			inst_cb_set_3_d();
			break;
		case 0xDB:
			inst_cb_set_3_e();
			break;
		case 0xDC:
			inst_cb_set_3_h();
			break;
		case 0xDD:
			inst_cb_set_3_l();
			break;
		case 0xDE:
			inst_cb_set_3_hl_indirect();
			break;
		case 0xDF:
			inst_cb_set_3_a();
			break;
		
		case 0xE0: /* SET 4, B */
			inst_cb_set_4_b();
			break;
		case 0xE1:
			inst_cb_set_4_c();
			break;
		case 0xE2:
			inst_cb_set_4_d();
			break;
		case 0xE3:
			inst_cb_set_4_e();
			break;
		case 0xE4:
			inst_cb_set_4_h();
			break;
		case 0xE5:
			inst_cb_set_4_l();
			break;
		case 0xE6:
			inst_cb_set_4_hl_indirect();
			break;
		case 0xE7:
			inst_cb_set_4_a();
			break;
		
		case 0xE8: /* SET 5, B */
			inst_cb_set_5_b();
			break;
		case 0xE9:
			inst_cb_set_5_c();
			break;
		case 0xEA:
			inst_cb_set_5_d();
			break;
		case 0xEB:
			inst_cb_set_5_e();
			break;
		case 0xEC:
			inst_cb_set_5_h();
			break;
		case 0xED:
			inst_cb_set_5_l();
			break;
		case 0xEE:
			inst_cb_set_5_hl_indirect();
			break;
		case 0xEF:
			inst_cb_set_5_a();
			break;
		
		case 0xF0: /* SET 6, B */
			inst_cb_set_6_b();
			break;
		case 0xF1:
			inst_cb_set_6_c();
			break;
		case 0xF2:
			inst_cb_set_6_d();
			break;
		case 0xF3:
			inst_cb_set_6_e();
			break;
		case 0xF4:
			inst_cb_set_6_h();
			break;
		case 0xF5:
			inst_cb_set_6_l();
			break;
		case 0xF6:
			inst_cb_set_6_hl_indirect();
			break;
		case 0xF7:
			inst_cb_set_6_a();
			break;
		
		case 0xF8: /* SET 7, B */
			inst_cb_set_7_b();
			break;
		case 0xF9:
			inst_cb_set_7_c();
			break;
		case 0xFA:
			inst_cb_set_7_d();
			break;
		case 0xFB:
			inst_cb_set_7_e();
			break;
		case 0xFC:
			inst_cb_set_7_h();
			break;
		case 0xFD:
			inst_cb_set_7_l();
			break;
		case 0xFE:
			inst_cb_set_7_hl_indirect();
			break;
		case 0xFF:
			inst_cb_set_7_a();
			break;
	}
}

int HaltActive;

int ScrCycle;
int SioCycle;
int DivCycle;
int TimCycle;
int JoyProbe;
int TimLoad;

int VblIntDelay;
int LcdIntDelay;

int DrawDelay;

int vram_mode;

int OldJoy;

int CPUSpeed = 1;

/* Interrupt type stuff */
#define VBL	0x01
#define LCD	0x02
#define TIM	0x04
#define SIO	0x08
#define JOY	0x10 

extern int HDMADst;
extern int HDMASrc;
extern int HDMACnt;

/* A spare variable for debugging */
int tempy;

void gameboy_cpu_execute_opcode()
{	
#define diff gbz80.machine_cycles

//CPUThing:
/*
	if (tempy != hiram[0xF07]) {
			printf("CHANGED! (%02X != %02X)\n", tempy, hiram[0xF07]);
			tempy = hiram[0xF07];
	}
*/

	gbz80.machine_cycles = 0;
	
//	if (!HaltActive) {
		current_opcode = memory_read_pc_byte();

//if ( (gbz80.PC.uw > 0x6600) && (gbz80.PC.uw < 0x8000) ) 
/*
printf("[%04X]: AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X (%02X/%02X) %02X %02X)\n", 
	gbz80.PC.uw, gbz80.AF.uw, gbz80.BC.uw,
	gbz80.DE.uw, gbz80.HL.uw, gbz80.SP.uw,
	current_opcode, memory_read_byte(gbz80.PC.uw), memory_read_byte(gbz80.PC.uw+1), memory_read_byte(gbz80.PC.uw+2));
*/
		gbz80.PC.uw++;	

switch((unsigned char)current_opcode) {
	case 0x00: /* NOP */
		MORE_CYCLES2(4);
		break;
	
	case 0x01: /* LD BC, $XXXX */
		inst_ld_bc_nn();
		break;
	
	case 0x02: /* LD [BC], A */
		inst_ld_bc_indirect_a();
		break;
	
	case 0x03: /* INC BC */
		inst_inc_bc();
		break;
	
	case 0x04: /* INC B */
		inst_inc_b();
		break;
	
	case 0x05: /* DEC B */
		inst_dec_b();
		break;
	
	case 0x06: /* LD B, $XX */
		inst_ld_b_n();
		break;
		
	case 0x07: /* RLCA */
		inst_rlca();
		break;
	
	case 0x08: /* LD [$XXXX], SP */
		inst_ld_nn_indirect_sp();
		break;
	
	case 0x09: /* ADD HL, BC */
		inst_add_hl_bc();
		break;
	
	case 0x0A: /* LD A, [BC] */
		inst_ld_a_bc_indirect();
		break;
	
	case 0x0B: /* DEC BC */
		inst_dec_bc();
		break;
	
	case 0x0C: /* INC C */
		inst_inc_c();
		break;
	
	case 0x0D: /* DEC C */
		inst_dec_c();
		break;
	
	case 0x0E: /* LD C, $XX */
		inst_ld_c_n();
		break;
				
	case 0x0F: /* RRCA */
		inst_rrca();
		break;
			
	case 0x10: /* STOP */
		inst_stop();
		break;
	
	case 0x11: /* LD DE, $XXXX */
		inst_ld_de_nn();
		break;
	
	case 0x12: /* LD [DE], A */
		inst_ld_de_indirect_a();
		break;
	
	case 0x13: /* INC DE */
		inst_inc_de();
		break;
	
	case 0x14: /* INC D */
		inst_inc_d();
		break;
		
	case 0x15: /* DEC D */
		inst_dec_d();
		break;
	
	case 0x16: /* LD D, $XX */
		inst_ld_d_n();
		break;
				
	case 0x17: /* RLA */
		inst_rla();
		break;
	
	case 0x18: /* JR $XX */
		inst_jr_n();
		break;
		
	case 0x19: /* ADD HL, DE */
		inst_add_hl_de();
		break;
	
	case 0x1A: /* LD A, [DE] */
		inst_ld_a_de_indirect();
		break;
	
	case 0x1B: /* DEC DE */
		inst_dec_de();
		break;
	
	case 0x1C: /* INC E */
		inst_inc_e();
		break;
	
	case 0x1D: /* DEC E */
		inst_dec_e();
		break;
	
	case 0x1E: /* LD E, $XX */
		inst_ld_e_n();
		break;
		
	case 0x1F: /* RRA */
		inst_rra();
		break;
	
	case 0x20: /* JR NZ, $XX */
		inst_jr_nz_n();
		break;
	
	case 0x21: /* LD HL, $XXXX */
		inst_ld_hl_nn();
		break;
	
	case 0x22: /* LD [HL+], A */
		inst_ld_hli_indirect_a();
		break;
	
	case 0x23: /* INC HL */
		inst_inc_hl();
		break;
	
	case 0x24: /* INC H */
		inst_inc_h();
		break;
	
	case 0x25: /* DEC H */
		inst_dec_h();
		break;
	
	case 0x26: /* LD H, $XX */
		inst_ld_h_n();
		break;
						
	case 0x27: /* DAA */
		inst_daa();
		break;
	
	case 0x28: /* JR Z, $XX */
		inst_jr_z_n();
		break;
	
	case 0x29: /* ADD HL, HL */
		inst_add_hl_hl();
		break;
	
	case 0x2A: /* LD A, [HL+] */
		inst_ld_a_hli_indirect();
		break;
	
	case 0x2B: /* DEC HL */
		inst_dec_hl();
		break;
	
	case 0x2C: /* INC L */
		inst_inc_l();
		break;
	
	case 0x2D: /* DEC L */
		inst_dec_l();
		break;
	
	case 0x2E: /* LD L, $XX */
		inst_ld_l_n();
		break;
			
	case 0x2F: /* CPL */
		inst_cpl();
		break;
	
	case 0x30: /* JR NC, $XX */
		inst_jr_nc_n();
		break;
	
	case 0x31: /* LD SP, $XXXX */
		inst_ld_sp_nn();
		break;
	
	case 0x32: /* LD [HL-], A */
		inst_ld_hld_indirect_a();
		break;
	
	case 0x33: /* INC SP */
		inst_inc_sp();
		break;
	
	case 0x34: /* INC [HL] */
		inst_inc_hl_indirect();
		break;
	
	case 0x35: /* DEC [HL] */
		inst_dec_hl_indirect();
		break;
	
	case 0x36: /* LD [HL], $XX */
		inst_ld_hl_indirect_n();
		break;
			
	case 0x37: /* SCF */
		inst_scf();
		break;
	
	case 0x38: /* JR C, $XX */
		inst_jr_c_n();
		break;
	
	case 0x39: /* ADD HL, SP */
		inst_add_hl_sp();
		break;
	
	case 0x3A: /* LD A, [HL-] */
		inst_ld_a_hld_indirect();
		break;
	
	case 0x3B: /* DEC SP */
		inst_dec_sp();
		break;
	
	case 0x3C: /* INC A */
		inst_inc_a();
		break;
	
	case 0x3D: /* DEC A */
		inst_dec_a();
		break;
	
	case 0x3E: /* LD A, $XX */
		inst_ld_a_n();
		break;
			
	case 0x3F: /* CCF */
		inst_ccf();
		break;
		
	case 0x40: /* LD B, B */
		MORE_CYCLES2(4);
		break;
	case 0x41: /* LD B, C */
		inst_ld_b_c();
		break;
	case 0x42: /* LD B, D */
		inst_ld_b_d();
		break;
	case 0x43:
		inst_ld_b_e();
		break;
	case 0x44:
		inst_ld_b_h();
		break;
	case 0x45:
		inst_ld_b_l();
		break;
	case 0x46:
		inst_ld_b_hl_indirect();
		break;
	case 0x47:
		inst_ld_b_a();
		break;
	
	case 0x48:
		inst_ld_c_b();	
		break;
	case 0x49: /* LD C, C */
		MORE_CYCLES2(4);
		break;
	case 0x4A:
		inst_ld_c_d();
		break;
	case 0x4B:
		inst_ld_c_e();
		break;
	case 0x4C:
		inst_ld_c_h();
		break;
	case 0x4D:
		inst_ld_c_l();
		break;
	case 0x4E:
		inst_ld_c_hl_indirect();
		break;
	case 0x4F:
		inst_ld_c_a();
		break;
	
	case 0x50: /* LD D, B */
		inst_ld_d_b();
		break;
	case 0x51: /* LD D, C */
		inst_ld_d_c();
		break;			
	case 0x52: /* LD D, D */
		MORE_CYCLES2(4);
		break;
	case 0x53:
		inst_ld_d_e();
		break;
	case 0x54:
		inst_ld_d_h();
		break;
	case 0x55:
		inst_ld_d_l();
		break;
	case 0x56:
		inst_ld_d_hl_indirect();
		break;
	case 0x57:
		inst_ld_d_a();
		break;
	
	case 0x58: /* LD E, B */
		inst_ld_e_b();
		break;
	case 0x59:
		inst_ld_e_c();
		break;
	case 0x5A:
		inst_ld_e_d();
		break;		
	case 0x5B: /* LD E, E */
		MORE_CYCLES2(4);
		break;
	case 0x5C:
		inst_ld_e_h();
		break;
	case 0x5D:
		inst_ld_e_l();
		break;
	case 0x5E:
		inst_ld_e_hl_indirect();
		break;
	case 0x5F:
		inst_ld_e_a();
		break;
	
	case 0x60: /* LD H, B */
		inst_ld_h_b();
		break;
	case 0x61: /* LD H, C */
		inst_ld_h_c();
		break;
	case 0x62: /* LD H, D */
		inst_ld_h_d();
		break;
	case 0x63: 
		inst_ld_h_e();
		break;		
	case 0x64: /* LD H, H */
		MORE_CYCLES2(4);
		break;
	case 0x65:
		inst_ld_h_l();
		break;
	case 0x66:
		inst_ld_h_hl_indirect();
		break;
	case 0x67:
		inst_ld_h_a();
		break;
	
	case 0x68: /* LD L, B */
		inst_ld_l_b();
		break;
	case 0x69: /* LD L, C */
		inst_ld_l_c();
		break;
	case 0x6A:
		inst_ld_l_d();
		break;
	case 0x6B:
		inst_ld_l_e();
		break;
	case 0x6C:
		inst_ld_l_h();
		break;		
	case 0x6D: /* LD L, L */
		MORE_CYCLES2(4);
		break;
	case 0x6E:
		inst_ld_l_hl_indirect();
		break;
	case 0x6F:
		inst_ld_l_a();
		break;
	
	case 0x70: /* LD [HL], B */
		inst_ld_hl_indirect_b();
		break;
	case 0x71: /* LD [HL], C */
		inst_ld_hl_indirect_c();
		break;
	case 0x72: /* LD [HL], D */
		inst_ld_hl_indirect_d();
		break;
	case 0x73: /* LD [HL], E */
		inst_ld_hl_indirect_e();
		break;
	case 0x74: /* LD [HL], H */
		inst_ld_hl_indirect_h();
		break;
	case 0x75: /* LD [HL], L */
		inst_ld_hl_indirect_l();
		break;
		
	case 0x76: /* HALT */
		inst_halt();
		break;
	
	case 0x77: /* LD [HL], A */
		inst_ld_hl_indirect_a();
		break;
				
	case 0x78: /* LD A, B */
		INST_LD(gbz80.AF.b.h, gbz80.BC.b.h);
		MORE_CYCLES2(4);
		break;
	case 0x79: /* LD A, C */
		INST_LD(gbz80.AF.b.h, gbz80.BC.b.l);
		MORE_CYCLES2(4);
		break;
	case 0x7A: /* LD A, D */
		INST_LD(gbz80.AF.b.h, gbz80.DE.b.h);
		MORE_CYCLES2(4);
		break;
	case 0x7B: /* LD A, E */
		INST_LD(gbz80.AF.b.h, gbz80.DE.b.l);
		MORE_CYCLES2(4);
		break;
	case 0x7C: /* LD A, H */
		INST_LD(gbz80.AF.b.h, gbz80.HL.b.h);
		MORE_CYCLES2(4);
		break;
	case 0x7D: /* LD A, L */
		INST_LD(gbz80.AF.b.h, gbz80.HL.b.l);
		MORE_CYCLES2(4);
		break;
	case 0x7E: /* LD A, [HL] */
		INST_LD(gbz80.AF.b.h, memory_read_byte(gbz80.HL.uw));
		MORE_CYCLES2(8);
		break;
	case 0x7F: /* LD A, A */
		MORE_CYCLES2(4);
		break;
	
	case 0x80: /* ADD A, B */
		inst_add_a_b();
		break;
	case 0x81: /* ADD A, C */
		inst_add_a_c();
		break;
	case 0x82: /* ADD A, D */
		inst_add_a_d();
		break;
	case 0x83: /* ADD A, E */
		inst_add_a_e();
		break;
	case 0x84: /* ADD A, H */
		inst_add_a_h();
		break;
	case 0x85: /* ADD A, L */
		inst_add_a_l();
		break;
	case 0x86: /* ADD A, [HL] */
		inst_add_a_hl_indirect();
		break;
	case 0x87: /* ADD A, A */
		inst_add_a_a();
		break;
	
	case 0x88: /* ADC A, B */
		inst_adc_a_b();
		break;
	case 0x89: /* ADC A, C */
		inst_adc_a_c();
		break;
	case 0x8A: /* ADC A, D */
		inst_adc_a_d();
		break;
	case 0x8B: /* ADC A, E */
		inst_adc_a_e();
		break;
	case 0x8C: /* ADC A, H */
		inst_adc_a_h();
		break;
	case 0x8D: /* ADC A, L */
		inst_adc_a_l();
		break;
	case 0x8E: /* ADC A, [HL] */
		inst_adc_a_hl_indirect();
		break;
	case 0x8F: /* ADC A, A */
		inst_adc_a_a();
		break;
	
	case 0x90: /* SUB A, B */
		inst_sub_b();
		break;
	case 0x91:
		inst_sub_c();
		break;
	case 0x92:
		inst_sub_d();
		break;
	case 0x93:
		inst_sub_e();
		break;
	case 0x94:
		inst_sub_h();
		break;
	case 0x95:
		inst_sub_l();
		break;
	case 0x96:
		inst_sub_hl_indirect();
		break;
	case 0x97: /* SUB A, A */
		inst_sub_a();
		break;
			
	case 0x98: /* SBC A, B */
		INST_SBC(gbz80.BC.b.h);
		MORE_CYCLES2(4);
		break;
	case 0x99: /* SBC A, C */
		INST_SBC(gbz80.BC.b.l);
		MORE_CYCLES2(4);
		break;
	case 0x9A: /* SBC A, D */
		INST_SBC(gbz80.DE.b.h);
		MORE_CYCLES2(4);
		break;
	case 0x9B: /* SBC A, E */
		INST_SBC(gbz80.DE.b.l);
		MORE_CYCLES2(4);
		break;
	case 0x9C: /* SBC A, H */
		INST_SBC(gbz80.HL.b.h);
		MORE_CYCLES2(4);
		break;
	case 0x9D: /* SBC A, L */
		INST_SBC(gbz80.HL.b.l);
		MORE_CYCLES2(4);
		break;
	case 0x9E: /* SBC A, [HL] */
		INST_SBC(memory_read_byte(gbz80.HL.uw));
		MORE_CYCLES2(8);
		break;
	case 0x9F: /* SBC A, A */
		inst_sbc_a();
		break;
	
	case 0xA0: /* AND B */
		inst_and_b();
		break;
	case 0xA1: /* AND C */
		inst_and_c();
		break;
	case 0xA2:
		inst_and_d();
		break;
	case 0xA3:
		inst_and_e();
		break;
	case 0xA4:
		inst_and_h();
		break;
	case 0xA5:
		inst_and_l();
		break;
	case 0xA6:
		inst_and_hl_indirect();
		break;
	case 0xA7:
		inst_and_a();
		break;
			
	case 0xA8: /* XOR B */
		INST_XOR(gbz80.BC.b.h);
		MORE_CYCLES2(4);
		break;
	case 0xA9: /* XOR C */
		INST_XOR(gbz80.BC.b.l);
		MORE_CYCLES2(4);
		break;
	case 0xAA: /* XOR D */
		INST_XOR(gbz80.DE.b.h);
		MORE_CYCLES2(4);
		break;
	case 0xAB: /* XOR E */
		INST_XOR(gbz80.DE.b.l);
		MORE_CYCLES2(4);
		break;
	case 0xAC: /* XOR H */
		INST_XOR(gbz80.HL.b.h);
		MORE_CYCLES2(4);
		break;
	case 0xAD: /* XOR L */
		INST_XOR(gbz80.HL.b.l);
		MORE_CYCLES2(4);
		break;
	case 0xAE: /* XOR [HL] */
		INST_XOR(memory_read_byte(gbz80.HL.uw));
		MORE_CYCLES2(8);
		break;
	case 0xAF: /* XOR A */
		inst_xor_a();
		break;
	
	case 0xB0: /* OR B */
		inst_or_b();
		break;
	case 0xB1: /* OR C */
		inst_or_c();
		break;
	case 0xB2: /* OR D */
		inst_or_d();
		break;
	case 0xB3: /* OR E */
		inst_or_e();
		break;
	case 0xB4: /* OR H */
		inst_or_h();
		break;
	case 0xB5: /* OR L */
		inst_or_l();
		break;
	case 0xB6:
		inst_or_hl_indirect();
		break;
	case 0xB7:
		inst_or_a();
		break;
		
	case 0xB8: /* CP B */
		inst_cp_b();
		break;
	case 0xB9: /* CP C */
		inst_cp_c();
		break;
	case 0xBA: /* CP D */
		inst_cp_d();
		break;
	case 0xBB: /* CP E */
		inst_cp_e();
		break;
	case 0xBC: /* CP H */
		inst_cp_h();
		break;
	case 0xBD: /* CP L */
		inst_cp_l();
		break;
	case 0xBE: /* CP [HL] */
		inst_cp_hl_indirect();
		break;
	case 0xBF: /* CP A */
		inst_cp_a();
		break;
	
	case 0xC0: /* RET NZ */
		inst_ret_nz();
		break;
	
	case 0xC1: /* POP BC */
		inst_pop_bc();
		break;
	
	case 0xC2: /* JP NZ, $XXXX */
		inst_jp_nz_nn();
		break;
	case 0xC3: /* JP $XXXX */
		inst_jp_nn();
		break;
	
	case 0xC4: /* CALL NZ, $XXXX */
		inst_call_nz_nn();
		break;
	
	case 0xC5: /* PUSH BC */
		inst_push_bc();
		break;
	
	case 0xC6: /* ADD A, $XX */
		inst_add_a_n();
		break;
			
	case 0xC7: /* RST $00 */	
		inst_rst_00h();
		break;
	
	case 0xC8: /* RET Z */
		inst_ret_z();
		break;
	case 0xC9: /* RET */
		inst_ret();
		break;
	
	case 0xCA: /* JP Z, $XXXX */
		inst_jp_z_nn();
		break;
		
	case 0xCB: /* CB .. */
		inst_cb();
		break;
	
	case 0xCC: /* CALL Z, $XXXX */
		inst_call_z_nn();
		break;
	case 0xCD: /* CALL $XXXX */
		inst_call_nn();
		break;
		
	case 0xCE: /* ADC A, $XX */
		inst_adc_a_n();
		break;
		
	case 0xCF: /* RST $08 */
		inst_rst_08h();
		break;
	
	case 0xD0: /* RET NC */
		inst_ret_nc();
		break;
	
	case 0xD1: /* POP DE */
		inst_pop_de();
		break;
	
	case 0xD2: /* JP NC, $XXXX */
		inst_jp_nc_nn();
		break;
	
	//case 0xD3: /* UNKNOWN */
	
	case 0xD4: /* CALL NC, $XXXX */
		inst_call_nc_nn();
		break;
	
	case 0xD5: /* PUSH DE */
		inst_push_de();
		break;
	
	case 0xD6: /* SUB $XX */
		inst_sub_n();
		break;
	
	case 0xD7: /* RST $10 */
		inst_rst_10h();
		break;
	
	case 0xD8: /* RET C */
		inst_ret_c();
		break;
	
	case 0xD9: /* RETI */
		inst_reti();
		break;
	
	case 0xDA: /* JP C, $XXXX */
		inst_jp_c_nn();
		break;
	
	//case 0xDB: /* UNKNOWN */
	
	case 0xDC: /* CALL C, $XXXX */
		inst_call_c_nn();
		break;
	
	//case 0xDD: /* UNKNOWN */
	
	case 0xDE: /* SBC A, $XX */
		INST_SBC(memory_read_pc_byte());
		MORE_CYCLES2(8);
		gbz80.PC.uw++;
		break;
	
	case 0xDF: /* RST $18 */
		inst_rst_18h();
		break;
	
	case 0xE0: /* LD [$FFXX], A */
		inst_ld_ff_n_indirect_a();
		break;
	
	case 0xE1: /* POP HL */
		inst_pop_hl();
		break;
	
	case 0xE2: /* LD [C], A */
		inst_ld_c_indirect_a();
		break;
	
	//case 0xE3: /* UNKNOWN */
	
	//case 0xE4: /* UNKNOWN */
	
	case 0xE5: /* PUSH HL */
		inst_push_hl();
		break;
	
	case 0xE6: /* AND $XX */
		inst_and_n();
		break;
		
	case 0xE7: /* RST $20 */
		inst_rst_20h();
		break;
	
	case 0xE8: /* ADD SP, $XX */
		inst_add_sp_n();
		break;
	
	case 0xE9: /* JP HL */
		inst_jp_hl();
		break;
		
	case 0xEA: /* LD [$XXXX], A */
		inst_ld_nn_indirect_a();
		break;
	
	//case 0xEB: /* UNKNOWN */
	//case 0xEC:
	//case 0xED:	
		
	case 0xEE: /* XOR $XX */
		INST_XOR(memory_read_pc_byte());
		MORE_CYCLES2(8);
		gbz80.PC.uw++;
		break;

	case 0xEF: /* RST $28 */
		inst_rst_28h();
		break;
		
	case 0xF0: /* LD A, [$FFXX] */
		inst_ld_a_ff_n_indirect();
		break;
	
	case 0xF1: /* POP AF */
		inst_pop_af();
		break;
		
	case 0xF2: /* LD A, [C] */
		inst_ld_a_c_indirect();
		break;
			
	case 0xF3: /*  DI */
		inst_di();
		break;
	
	//case 0xF4: /* UNKNOWN */
	
	case 0xF5: /* PUSH AF */
		inst_push_af();
		break;
	
	case 0xF6: /* OR $XX */
		inst_or_n();
		break;
			
	case 0xF7: /* RST $30 */
		inst_rst_30h();
		break;
	
	case 0xF8: /* LD HL, SP+$XX */
		inst_ld_hl_sp_n();
		break;
		
	case 0xF9: /* LD SP, HL */
		inst_ld_sp_hl();
		break;
		
	case 0xFA: /* LD A, [$XXXX] */
		inst_ld_a_nn_indirect();
		break;
			
	case 0xFB: /* EI */
		inst_ei();
		break;
	
	//case 0xFC: /* UNKNOWN */
	//case 0xFD: 
	
	case 0xFE: /* CP $XX */
		inst_cp_n();
		break;
		
	case 0xFF: /* RST $38 */
		inst_rst_38h();
		break;

	default:
		inst_unknown();
		//exit(EXIT_FAILURE); //
		return;
}	
	
//	} else {
//		MORE_CYCLES2(8);
//	}

/*
	if (tempy != hiram[0xF07]) {
		printf("CHANGED [2]! (%02X != %02X)\n", tempy, hiram[0xF07]);
		printf("Opcode Was: %02X\n", current_opcode);
		printf("[%04X]: AF:%04X BC:%04X DE:%04X HL:%04X SP:%04X\n", 
			gbz80.PC.uw, gbz80.AF.uw, gbz80.BC.uw,
			gbz80.DE.uw, gbz80.HL.uw, gbz80.SP.uw);
		tempy = hiram[0xF07];
	}
*/
/*
	if (SIOCONT & 0x80) {
		if (SIOCONT & 0x01) {
			int NewSet = 0;
			SioCycle += diff;
		
			if (color_gameboy) {
				if (SIOCONT & 0x02) {
					if (KEY1REG & 0x80) {
						if (SioCycle > 15)
							NewSet |= SIO;
					} else {
						if (SioCycle > 127)
							NewSet |= SIO;
					}
				} else {
					if (KEY1REG & 0x80) {
						if (SioCycle > 511)
							NewSet |= SIO;
					} else {
						if (SioCycle > 4095)
							NewSet |= SIO;
					}	
				}
			} else {
				if (SioCycle > 4095) {
					NewSet |= SIO;
				}
			}
	
			if (NewSet & SIO) {
				if (SIOCONT & 0x01)
					IFLAGS |= 0x08;
				 
				SioCycle = 0;
				SIOCONT &= 0x7F;
			}	
		} else {
		}
	}
*/	
//	DivCycle -= diff;	
/*
	while (DivCycle <= 0) {
		DIVIDER++;
		DivCycle += 256*CPUSpeed;
	}
		
	if (TIMCONT & 0x04) {		
		TimCycle -= diff;
	
		while (TimCycle <= 0) {
			TIMECNT++;
			if (TIMECNT == 0) {
				TIMECNT = TIMEMOD;
				IFLAGS |= 0x04;
			}
			TimCycle += TimLoad;
		}
	}	
*/
/*
if (SoundEnabled) {
	int c = 0;
	SoundCycle -= diff;
	while (SoundCycle <= 0) {
		SoundCycle += SoundLoader*CPUSpeed;
		c += SoundLoader;
	}
	if (c)
		ProcessSound(c);
}
*/
/*
if (tempy != hiram[0xF07]) {
	printf("CHANGED [3]! (%02X != %02X)\n", tempy, hiram[0xF07]);
	tempy = hiram[0xF07];
}
*/
/*
if (LCDCONT & 0x80) {	
extern int window_current_line;	
*/
/*
if (DrawDelay) {
	DrawDelay -= diff;
	if (DrawDelay <= 0) {
		vram_plot_screen();
		DrawDelay = 0;
	}
}
*/

//	ScrCycle -= diff;
/*
while (ScrCycle <= 0) {
	switch(vram_mode) {
		case 0:
			CURLINE++;
			
			if (LCDSTAT & 0x40) { 
				if (CURLINE == CMPLINE) {
					if (!(IFLAGS & 0x02)) {
						IFLAGS |= 0x02;
						LcdIntDelay = 32*CPUSpeed+ScrCycle;
					}
				}
			}	
			
			if (CURLINE == 0x90) {
				if (LCDSTAT & 0x10) {
					if (!(IFLAGS & 0x02)) {
						//printf("lcd 0x10\n");
						IFLAGS |= 0x02;
						LcdIntDelay = 32*CPUSpeed+ScrCycle;
					}
 				}
				vram_mode = 1;
				infogb_vram_blit();
				window_current_line = 0;
				vram_sysupdate();
		
				if (OldJoy != current_joypad) {
					OldJoy = current_joypad;
 					IFLAGS |= 0x10;
				}

				if (!(IFLAGS & 0x01)) {
					IFLAGS |= 0x01;
					VblIntDelay = 16*CPUSpeed+ScrCycle;
				}
				ScrCycle += 451*CPUSpeed;
			} else {
				if (LCDSTAT & 0x20) {
					if (!(IFLAGS & 0x02)) {
						//printf("lcd 0x20\n");
						IFLAGS |= 0x02;
						LcdIntDelay = 0*CPUSpeed+ScrCycle;
					}
				}
				vram_mode = 2;
				ScrCycle += 80*CPUSpeed;
			}
			break;
		case 1:
			CURLINE++;	
			if (CURLINE > 153) {
				CURLINE -= 154;
				vram_mode = 2;
				if (LCDSTAT & 0x20) {
					if (!(IFLAGS & 0x02)) {
						//printf("lcd 0x20\n");
						IFLAGS |= 0x02;
						LcdIntDelay = 0*CPUSpeed+ScrCycle;
					}
				}
				if (LCDSTAT & 0x40) { 
					if (CURLINE == CMPLINE) {
						if (!(IFLAGS & 0x02)) {
							IFLAGS |= 0x02;
							LcdIntDelay = 32*CPUSpeed+ScrCycle;
						}
 					}
				}
				ScrCycle += 80*CPUSpeed;
			} else {
				vram_mode = 1;
				if (LCDSTAT & 0x40) { 
					if (CURLINE == CMPLINE) {
						if (!(IFLAGS & 0x02)) {
							IFLAGS |= 0x02;
							LcdIntDelay = 32*CPUSpeed+ScrCycle;
						}
					}
				}
				ScrCycle += 451*CPUSpeed;
			}
			break;
  		case 2:
			vram_mode = 3;
			//DrawDelay = 152*CPUSpeed;
			vram_plot_screen();
			ScrCycle += 172*CPUSpeed;
			break;
		case 3:
			vram_mode = 0;
			if (LCDSTAT & 0x08) {
				if (!(IFLAGS & 0x02)) {
					//printf("lcd 0x08\n");
					IFLAGS |= 0x02;
					LcdIntDelay = 32*CPUSpeed+ScrCycle;
				}
			}
			if (HDMADst) {
				if (HDMACnt) {
					int i, a, b;
					
					a = HDMASrc >> 12;
					b = HDMADst >> 12;
					for (i = 0; i < 16; i++) {
						gameboy_memory[b][HDMADst & 0x0FFF] = gameboy_memory[a][HDMASrc & 0x0FFF];
						HDMASrc++;
						HDMADst++;
					}
					HDMACnt--;	
					if (HDMACnt == 0)
						HDMADst = 0;
					MORE_CYCLES((204*CPUSpeed));
				}
			} else {	
				//ScrCycle += 204*CPUSpeed;
			}
			ScrCycle += 204*CPUSpeed;
			break;
	}

}

} else {
	vram_mode = 0;
	CURLINE = 0;
	ScrCycle = 0;
	LCDSTAT &= ~0x04;

	JoyProbe += diff;
	if (JoyProbe > (70221*CPUSpeed)) {
		JoyProbe -= 70221*CPUSpeed;
   		vram_sysupdate();
   		
   		if (OldJoy != current_joypad) {
			OldJoy = current_joypad;
 			IFLAGS |= 0x10;
		}

	}
}
*/
/*
	if (gbz80.IFF) {
		int Int = IFLAGS & IENABLE;
		if (Int & 0x01) {
			VblIntDelay -= diff;
			if (VblIntDelay <= 0) {
				VblIntDelay = 0;
				IFLAGS &= ~0x01;
				gbz80.IFF = 0;
				gameboy_stack_write_word(gbz80.PC.uw);
				gbz80.PC.uw = 0x40;
			}
		} else if (Int & 0x02) {
			//LcdIntDelay -= diff;
			//if (LcdIntDelay <= 0) {
			//	LcdIntDelay = 0;
				IFLAGS &= ~0x02;
				gbz80.IFF = 0;
				gameboy_stack_write_word(gbz80.PC.uw);
				gbz80.PC.uw = 0x48;
			//}
		} else if (Int & 0x04) {
			IFLAGS &= ~0x04;
			gbz80.IFF = 0;
			gameboy_stack_write_word(gbz80.PC.uw);
			gbz80.PC.uw = 0x50;
		} else if (Int & 0x08) {
			IFLAGS &= ~0x08;
			gbz80.IFF = 0;
			gameboy_stack_write_word(gbz80.PC.uw);
			gbz80.PC.uw = 0x58;
		} else if (Int & 0x10) {
			IFLAGS &= ~0x10;
			gbz80.IFF = 0;
			gameboy_stack_write_word(gbz80.PC.uw);
			gbz80.PC.uw = 0x60;
		} 
	} else if (HaltActive) {
		HaltActive = 0;
	}
*/
/*
	if (tempy != hiram[0xF07]) {
		printf("CHANGED [6]! (%02X != %02X)\n", tempy, hiram[0xF07]);
		tempy = hiram[0xF07];
	}
*/
  
//	goto CPUThing;
	
}
