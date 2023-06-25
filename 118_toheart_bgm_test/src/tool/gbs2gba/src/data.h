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

#ifndef __DATA_H__
#define __DATA_H__

typedef enum _force_type { REGULAR, COLOR, SUPER, NONE } force_type;

typedef union _wordun {
     unsigned short uw;
       signed short sw;
     struct {
#ifdef MSB_FIRST
          unsigned char h;
          unsigned char l;
#else
          unsigned char l;
          unsigned char h;
#endif
     } b;
} wordun;

extern unsigned char use_joystick;
extern force_type force_system;

#endif
