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

#ifndef __CPU_H__
#define __CPU_H__

#include "data.h"

#define FLAGS_ZERO 0x80
#define FLAGS_NEGATIVE 0x40
#define FLAGS_HALFCARRY 0x20
#define FLAGS_CARRY 0x10

#define FLAGS_ISZERO(proc)     (gbz80.AF.b.l & FLAGS_ZERO)
#define FLAGS_ISNEGATIVE(proc) (gbz80.AF.b.l & FLAGS_NEGATIVE)
#define FLAGS_ISCARRY(proc)    (gbz80.AF.b.l & FLAGS_CARRY)
#define FLAGS_ISHALFCARRY(proc) (gbz80.AF.b.l& FLAGS_HALFCARRY)

#define FLAGS_ISSET(proc,x)    (gbz80.AF.b.l & x)
#define FLAGS_SET(proc,x)      (gbz80.AF.b.l |= x)
#define FLAGS_CLEAR(proc,x)    (gbz80.AF.b.l &= ~(x))

#define MORE_CYCLES(m) { gbz80.machine_cycles += m; }

#define MORE_CYCLES2(m) { gbz80.machine_cycles += m; }

typedef struct _gameboy_proc_t {
	wordun   AF;	
	wordun 	 BC;
	wordun   DE;
	wordun   HL;
	wordun   SP;
	wordun   PC;
	int IFF;
	int running;
	int machine_cycles;
} gameboy_proc_t;

extern gameboy_proc_t gbz80;
extern int CPUSpeed;

void gameboy_cpu_hardreset();
void gameboy_cpu_run();
void gameboy_cpu_execute_opcode();

#endif
