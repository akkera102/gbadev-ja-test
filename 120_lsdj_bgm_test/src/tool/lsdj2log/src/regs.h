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

#ifndef __REGS_H__
#define __REGS_H__

#define VBLANK_INT 0x0040

#define JOYPAD  (hiram[0xF00])
#define SIODATA (hiram[0xF01])
#define SIOCONT (hiram[0xF02])
#define DIVIDER (hiram[0xF04])
#define TIMECNT (hiram[0xF05])
#define TIMEMOD (hiram[0xF06])
#define TIMCONT (hiram[0xF07])
#define IFLAGS  (hiram[0xF0F])
#define SNDREG10 (hiram[0xF10])
#define SNDREG11 (hiram[0xF11])
#define SNDREG12 (hiram[0xF12])
#define SNDREG13 (hiram[0xF13])
#define SNDREG21 (hiram[0xF16])
#define SNDREG22 (hiram[0xF17])
#define SNDREG23 (hiram[0xF18])
#define SNDREG24 (hiram[0xF19])
#define SNDREG30 (hiram[0xF1A])
#define SNDREG31 (hiram[0xF1B])
#define SNDREG32 (hiram[0xF1C])
#define SNDREG33 (hiram[0xF1D])
#define SNDREG34 (hiram[0xF1E])
#define SNDREG41 (hiram[0xF20])
#define SNDREG42 (hiram[0xF21])
#define SNDREG43 (hiram[0xF22])
#define SNDREG44 (hiram[0xF23])
#define SNDREG50 (hiram[0xF24])
#define SNDREG51 (hiram[0xF25])
#define SNDREG52 (hiram[0xF26])
#define LCDCONT (hiram[0xF40])
#define LCDSTAT (hiram[0xF41])
#define SCROLLY (hiram[0xF42])
#define SCROLLX (hiram[0xF43])
#define CURLINE (hiram[0xF44])
#define CMPLINE (hiram[0xF45])
#define DMACONT (hiram[0xF46])
#define BGRDPAL (hiram[0xF47])
#define OBJ0PAL (hiram[0xF48])
#define OBJ1PAL (hiram[0xF49])
#define WNDPOSY (hiram[0xF4A])
#define WNDPOSX (hiram[0xF4B])
#define IENABLE (hiram[0xFFF])

/* Gameboy Color Registers */
#define KEY1REG (hiram[0xF4D])
#define RPREG   (hiram[0xF56])
#define SVBKREG (hiram[0xF70])
#define VBKREG  (hiram[0xF4F])
#define HDMA1REG (hiram[0xF51])
#define HDMA2REG (hiram[0xF52])
#define HDMA3REG (hiram[0xF53])
#define HDMA4REG (hiram[0xF54])
#define HDMA5REG (hiram[0xF55])
#define BCPSREG  (hiram[0xF68])
#define BCPDREG  (hiram[0xF69])
#define OCPSREG  (hiram[0xF6A])
#define OCPDREG  (hiram[0xF6B])

#endif
