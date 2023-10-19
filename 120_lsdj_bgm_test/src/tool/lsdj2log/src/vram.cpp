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
#include "vram.h"
#include "mem.h"
#include "regs.h"
#include "cpu.h"
#include "data.h"
#include "joypad.h"

#define GAMEBOY_PIXWIDTH 160
#define GAMEBOY_PIXHEIGHT 144

static unsigned short int colors16[4] = { 0x7FFF, 0x6B5A, 0x4E73, 0x0000 };

//void set_color(int x, unsigned short int c);

int TileSign;
unsigned char *BkgTiles;
unsigned char *BkgTable;
unsigned char *WindowTable;

void vram_set_color(int x, int c)
{
	infogb_set_color(x, (unsigned short)c);
	colors16[x] = c;
}

void reset_colors()
{
	int i;
	
	//if (color_gameboy) 
	//	for (i = 0; i < 64; i++)
	//		set_color(i, 0x7FFF);
	//else
		for (i = 0; i < 4; i++)
			infogb_set_color(i, colors16[i]); 
	infogb_set_color(64, 0x7FFF);
}

int window_current_line = 0;

/* the sprite 'z buffer' -- extra padding just in case */
int test[8];
int strip[168];
int test2[8];
int strip2[168];

static inline void vram_plot_line_sprites()
{
	int current_line = CURLINE;
	char *tiles; 
	unsigned char *sprptr;
	int sprcnt;
	int sprsize;	
	int cntperline = 0;
	tiles = (char *)video_ram;
	sprptr = &sprite_oam[0xA0];
	
	sprsize = (LCDCONT & 0x04) ? 16 : 8;	
	
	for(sprcnt = 40; sprcnt > 0; sprcnt--) {
		int x, xoff;
		int y;
		unsigned char tile, attr;
		unsigned char sprcolors;
		int yflip, xflip;
		
		attr = *--sprptr;
		tile = *--sprptr;
		   x = *--sprptr;
		   y = *--sprptr;
		
		if (x == 0)
			continue;
			 
		x -= 8;
	
		if(y == 0)
			continue;	
			
		y -= 16;
		
		if(x >= GAMEBOY_PIXWIDTH)
			continue;

		y = current_line - y;

		if( (y >= 0) && (sprsize > y) ) {
			int nx;
			char *tileptr;
			
			sprcolors = (attr & 0x10) ? OBJ1PAL : OBJ0PAL;
			yflip = (attr & 0x40);
			xflip = (attr & 0x20);

			if(sprsize == 16)
				tile = tile & 0xFE;	/* 8x16 ignores LS bit */
				
			tileptr = &tiles[tile << 4];
			
			if(!yflip)
				tileptr += y << 1;
			else
				tileptr += ((sprsize - 1) - y) << 1;

			cntperline++;
			
			if (x < 0) {
				xoff = -x;
				x = 0;
			} else {
				xoff = 0;
			}
			
			for(nx = 0; nx < (8 - xoff); nx++) {
				int bit1, bit2, color;
				int wbit = 0;

				if ((attr & 0x80) && strip[x+nx])
					continue;
					
				if(!xflip)
					wbit = nx+xoff;
				else
					wbit = (7 - (nx+xoff));
					
				bit1  = (*tileptr       & (0x80 >> wbit)) ? 1 : 0;
				bit2  = (*(tileptr + 1) & (0x80 >> wbit)) ? 2 : 0;
				color = bit2 | bit1;
				
				if (color)
					strip2[x+nx] = (sprcolors >> (color << 1)) & 0x03;
			}			
		}
	}
}

static inline void vram_plot_line_sprites_color()
{
	int current_line = CURLINE;
	char *tiles; 
	unsigned char *sprptr;
	int sprcnt;
	int sprsize;	
	int cntperline = 0;
		
	tiles = (char *)video_ram;
	sprptr = &sprite_oam[0xA0];
	sprsize = (LCDCONT & 0x04) ? 16 : 8;	
	
	for(sprcnt = 40; sprcnt > 0; sprcnt--) {
		int x, xoff;
		int y;
		unsigned char tile, attr;
		int yflip, xflip;
		unsigned char pal, bank;
		
		attr = *--sprptr;
		tile = *--sprptr;
		   x = *--sprptr;
		   y = *--sprptr;		
		
		if (x == 0)
			continue;
			 
		if(y == 0)
			continue;	
		
		x -= 8;	
		y -= 16;
		
		if(x >= GAMEBOY_PIXWIDTH)
			continue;

		y = current_line - y;
		if( (y >= 0) && (sprsize > y) ) {	
			int nx;
			char *tileptr;
			
			
			yflip = (attr & 0x40);
			xflip = (attr & 0x20);
			pal = (attr & 0x07);
			bank = (attr & 0x08) ? 1 : 0;
			
			if(sprsize == 16)
				tile = tile & 0xFE;	/* 8x16 ignores LS bit */
		
			tileptr = &tiles[(tile << 4) + (bank * 0x2000)];
			
			if(!yflip)
				tileptr += y << 1;
			else
				tileptr += ((sprsize - 1) - y) << 1;

			cntperline++;
			
			if (x < 0) {
				xoff = -x;
				x = 0;
			} else {
				xoff = 0;
			}
			
			for(nx = 0; nx < (8 - xoff); nx++) {
				int bit1, bit2, color;
				int wbit = 0;

				if ((attr & 0x80) && strip[x+nx])
					continue;
				if (strip[x+nx] > 0x80)
					continue;
						
				if(!xflip)
					wbit = nx+xoff;
				else
					wbit = (7 - (nx+xoff));
					
				bit1  = (*tileptr       & (0x80 >> wbit)) ? 1 : 0;
				bit2  = (*(tileptr + 1) & (0x80 >> wbit)) ? 2 : 0;
				color = bit2 | bit1;
				
				if (color) 
					strip2[x+nx] = 32 + (pal << 2) + color;					
			}			
		}
	}
}

static inline void vram_plot_line()
{
	char *table, *tiles, *tileptr;
	int bit1, bit2;
	int color;
	signed char tile;
	int x;
	int scrolled_y = (SCROLLY + CURLINE) & 0xFF;
	int ofn = SCROLLX & 7;
	int t = SCROLLX >> 3;
	int bit;
	
	tiles = (char *)BkgTiles;
	table = (char *)BkgTable + ((scrolled_y >> 3) << 5);
	
	tile = table[t & 0x1F];
	t++;
		
	if (TileSign) {
		tileptr    = &tiles[tile << 4];
	} else {
		unsigned char tl = tile;
		tileptr    = &tiles[tl << 4];
	}
	
	scrolled_y = (scrolled_y & 7) << 1;
		
	tileptr += scrolled_y;
	
	for(x = 0, bit = 0x80 >> ofn; bit; bit >>= 1, x++) {
		bit1  = (*tileptr       & bit) ? 1 : 0;
		bit2  = (*(tileptr + 1) & bit) ? 2 : 0;
		color = bit2 | bit1;

		strip[x] = color;		
		strip2[x] = (BGRDPAL >> (color << 1)) & 0x03;
	}	
	
	for(; x < GAMEBOY_PIXWIDTH;) {
			
		tile = table[t & 0x1F];
		t++;
		
		if (TileSign) {
			tileptr    = &tiles[tile << 4];
		} else {
			unsigned char tl = tile;
			tileptr    = &tiles[tl << 4];
		}
		
		tileptr += scrolled_y;
		
		for (bit = 0x80; bit; bit >>= 1, x++) {
			bit1	= (*tileptr       & bit) ? 1 : 0;
			bit2	= (*(tileptr + 1) & bit) ? 2 : 0;
			color = bit2 | bit1;

			strip[x] = color;
			strip2[x] = (BGRDPAL >> (color << 1)) & 0x03;
		}
		
	}
}

static inline void vram_plot_line_color()
{
	char *table, *tiles, *tileptr, *attrtab;
	int bit1, bit2;
	int color;
	signed char tile;
	unsigned char attr, pal;
	int x;
	int scrolled_y = (SCROLLY + CURLINE) & 0xFF;
	int ofn = SCROLLX & 7;
	int t = SCROLLX >> 3;
	unsigned char pix;
	
	tiles = (char *)BkgTiles;
	table = (char *)BkgTable + ((scrolled_y >> 3) << 5);
	
	attrtab = table + 0x2000;
	
	/* Left-most tile */
	tile = table[t];
	attr = attrtab[t];
	t++;
	t &= 0x1F;
		
	pal  = attr & 0x07;
	
	if(attr & 0x08) { /* Using bank 1 */
		if(TileSign) {
			tileptr = &tiles[0x2000 + (tile << 4)];
		} else {
			unsigned char tl = tile;
			tileptr = &tiles[0x2000 + (tl << 4)];
		}
	} else {
		if(TileSign) {
			tileptr  = &tiles[tile << 4];
		} else {
			unsigned char tl = tile;
			tileptr  = &tiles[tl << 4];		/* File Tile Data from # */
		}
	}
	
	scrolled_y &= 7;
		
	if (attr & 0x40) 
		tileptr += (7 - scrolled_y) << 1;
	else
		tileptr += scrolled_y << 1; 
		
	if (attr & 0x20) {
		for (x = 0, pix = 0x01 << ofn; pix; pix <<= 1, x++) {
			bit1  = (*tileptr       & pix) ? 1 : 0;
			bit2  = (*(tileptr + 1) & pix) ? 2 : 0;
			color = bit2 | bit1;
			
			strip2[x] = (pal << 2) + color;	
			if (attr & 0x80)
				color |= 0x80;
			strip[x] = color;
		}
	} else {
		for (x = 0, pix = 0x80 >> ofn; pix; pix >>= 1, x++) {
			bit1  = (*tileptr       & pix) ? 1 : 0;
			bit2  = (*(tileptr + 1) & pix) ? 2 : 0;
			color = bit2 | bit1;
			
			strip2[x] = (pal << 2) + color;	
			if (attr & 0x80)
				color |= 0x80;
			strip[x] = color;
		}
	}	

	for(; x < GAMEBOY_PIXWIDTH;) {
		tile = table[t];
		attr = attrtab[t];
		t++;
		t &= 0x1F;
		
		pal  = attr & 0x07;
		
		if(attr & 0x08) { /* Using bank 1 */
			if(TileSign) {
				tileptr = &tiles[0x2000 + (tile << 4)];
			} else {
				unsigned char tl = tile;
				tileptr = &tiles[0x2000 + (tl << 4)];
			}
		} else {
			if(TileSign) {
				tileptr  = &tiles[tile << 4];
			} else {
				unsigned char tl = tile;
				tileptr  = &tiles[tl << 4];		/* File Tile Data from # */
			}
		}
			
		if (attr & 0x40) 
			tileptr += (7 - scrolled_y) << 1;
		else
			tileptr += scrolled_y << 1; 
		
		if (attr & 0x20) {
			for (pix = 0x01; pix; pix <<= 1, x++) {
				bit1  = (*tileptr       & pix) ? 1 : 0;
				bit2  = (*(tileptr + 1) & pix) ? 2 : 0;
				color = bit2 | bit1;
				
				strip2[x] = (pal << 2) + color;	
				if (attr & 0x80)
					color |= 0x80;
				strip[x] = color;
			}
		} else {
			for (pix = 0x80; pix; pix >>= 1, x++) {
				bit1  = (*tileptr       & pix) ? 1 : 0;
				bit2  = (*(tileptr + 1) & pix) ? 2 : 0;
				color = bit2 | bit1;
				
				strip2[x] = (pal << 2) + color;	
				if (attr & 0x80)
					color |= 0x80;
				strip[x] = color;
			}
		}
	}
}

static inline void vram_plot_line_window()
{	
	unsigned char *tableptr, *tiles, *tileptr;
	unsigned char tile;
	int bit;
 	int nx, bit1, bit2, color;
	int x;
	
	tiles = BkgTiles;
	tableptr = WindowTable + ((window_current_line >> 3) << 5);	

	tile = *tableptr;
	tableptr++;
		
	if(TileSign) {
		signed char tl = tile;
		tileptr = &tiles[tl << 4];
	} else
		tileptr = &tiles[tile << 4];
		
	tileptr += (window_current_line & 7) << 1;
	
	for(x = WNDPOSX - 7, bit = 0x80; bit; x++, bit >>= 1) {
			
		if (x < 0)
			continue;
			
		bit1  = (*tileptr       & bit) ? 1 : 0;
		bit2  = (*(tileptr + 1) & bit) ? 2 : 0;
		color = bit2 | bit1;
			
		strip[x] = color;
		strip2[x] = (BGRDPAL >> (color << 1)) & 0x03;
	}

	for(; x < 160; x += 8) {				
		tile = *tableptr;
		tableptr++;
		
		if(TileSign) {
			signed char tl = tile;
			tileptr = &tiles[tl << 4];
		} else
			tileptr = &tiles[tile << 4];
			
		tileptr += (window_current_line & 7) << 1;
		
		for(nx = 0; nx < 8; nx++) {
			bit1  = (*tileptr       & (0x80 >> nx)) ? 1 : 0;
			bit2  = (*(tileptr + 1) & (0x80 >> nx)) ? 2 : 0;
			color = bit2 | bit1;
			
			strip[x+nx] = color;
			strip2[x+nx] = (BGRDPAL >> (color << 1)) & 0x03;
		}
		
	}
	window_current_line++;
}

static inline void vram_plot_line_window_color()
{	
	unsigned char *tableptr, *attrptr, *tiles, *tileptr;
	int attr, pal;
	int x;
	
	tiles = BkgTiles;
	tableptr = WindowTable + ((window_current_line >> 3) << 5);
	attrptr = tableptr + 0x2000;
	
	for (x = WNDPOSX - 7; x < 160; x += 8) {
		signed char tile;
		int nx, bit1, bit2, color;
			
		tile = *tableptr;
		attr = *attrptr;
		pal  = attr & 0x07;	
		
		tableptr++;
		attrptr++;
						
		if(attr & 0x08) { /* Using bank 1 */
			if(TileSign) {
				tileptr = &tiles[0x2000 + (tile << 4)];
			} else {
				unsigned char t = tile;
				tileptr = &tiles[0x2000 + (t << 4)];
			}
		} else {
			if(TileSign) {
				tileptr  = &tiles[tile << 4];
			} else {
				unsigned char t = tile;
				tileptr  = &tiles[t << 4];		/* File Tile Data from # */
			}
		}	
		
		if (attr & 0x40)
			tileptr += (7 - (window_current_line & 7)) << 1;
		else
			tileptr += (window_current_line & 7) << 1;
		
		if (attr & 0x20) {
			for(nx = 0; nx < 8; nx++) {
			
				if ((x+nx) < 0)
					continue;
			
				bit1  = (*tileptr       & (0x01 << nx)) ? 1 : 0;
				bit2  = (*(tileptr + 1) & (0x01 << nx)) ? 2 : 0;
				color = bit2 | bit1;
			
				strip[x+nx] = color;
				if (attr & 0x80)
					strip[x+nx] |= 0x80;
			
				strip2[x+nx] = (pal << 2) + color;			
			}
		} else {
			for(nx = 0; nx < 8; nx++) {
			
				if ((x+nx) < 0)
					continue;
			
				bit1  = (*tileptr       & (0x80 >> nx)) ? 1 : 0;
				bit2  = (*(tileptr + 1) & (0x80 >> nx)) ? 2 : 0;
				color = bit2 | bit1;
				
				strip[x+nx] = color;
				if (attr & 0x80)
					strip[x+nx] |= 0x80;
				
				strip2[x+nx] = (pal << 2) + color;			
			}
		}
		
	}
	window_current_line++;
} 

//void plot_line(int line, int *index);
//extern int ready;

void vram_plot_screen()
{	
	if (infogb_ready)
		return;
		
	if (color_gameboy) {	
		vram_plot_line_color();
		
		if (LCDCONT & 0x20) {
			if ((CURLINE >= WNDPOSY) && (WNDPOSX < 167)) {
				vram_plot_line_window_color();
			}
		}
		
		if (LCDCONT & 0x02) {
			if (!(LCDCONT & 0x01)) {
				int i;
				for (i = 0; i < 160; i++) {
					strip[i] = 0;
				}
			}
			vram_plot_line_sprites_color();
		}
	} else {
		if (LCDCONT & 0x01) {
			vram_plot_line();
		} else {
			int i;
			for (i = 0; i < 160; i++) {
				strip[i] = 0;
				strip2[i] = 65;
			}
		}
	
		if (LCDCONT & 0x20) {
			if ((CURLINE >= WNDPOSY) && (WNDPOSX < 167)) {
				vram_plot_line_window();
			}
		}
	
		if (LCDCONT & 0x02) {
			vram_plot_line_sprites();
		}
	}
	
	infogb_plot_line(CURLINE, strip2);
}

//extern void infogb_poll_events();

void vram_sysupdate()
{
	infogb_poll_events();
}
