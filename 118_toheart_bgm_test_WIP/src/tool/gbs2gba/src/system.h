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

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/* System Specific Compiliation Issue Resolver */
#if defined(WIN32)

	/* Win32 */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <setjmp.h>

	#define inline __inline

#else

/* Linux */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <setjmp.h>

#endif /* End of SSCIR */

/* System-depended functions */
/* To porters, these funcions must be implemented! */

int infogb_init(char *display);
int infogb_close();
int infogb_create_window(char *, int, int);
int infogb_poll_events();
void infogb_wait();
void infogb_vram_blit();
void infogb_set_color(int, unsigned short);
void infogb_plot_line(int, int *);
void infogb_write_sample(short int, short int);

extern int infogb_ready;

#endif
