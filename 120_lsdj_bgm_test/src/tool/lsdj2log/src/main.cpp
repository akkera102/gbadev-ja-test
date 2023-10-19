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

#include <stdio.h>
#include <malloc.h>

#include "system.h"
#include "joypad.h"
#include "cpu.h"
#include "mem.h"
#include "rom.h"
#include "vram.h"

#define APP_NAME     "InfoGB v0.5J"
#define VBLANK_INT	 16.66667 
force_type force_system           = NONE;
int infogb_ready                  = 0; 

FILE* fpLog;

/* for video */
/* local functions */
void infogb_open_audio();
void infogb_close_audio();

/* main */
static const char* CLASS_NAME = "InfoGB_CLASS";

//---------------------------------------------------------------------------
int infogb_init(char *display)
{
	return 1;
}
//---------------------------------------------------------------------------
int infogb_close()
{
    return 1;
}
//---------------------------------------------------------------------------
int infogb_create_window(char *title, int width, int height)
{
    return 1;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  char szFileName[ 256 ];

	infogb_init(NULL);
	infogb_create_window(APP_NAME, 160, 144);
	infogb_open_audio();

	if(argc != 2)
	{
		printf("input filename\n");
		exit(0);
	}

	printf("input: %s\n", argv[1]);
	strcpy(szFileName, argv[1]);

  if (load_rom(szFileName)) {
    if (initialize_memory() == 0) {
      free_memory();

      printf("Unable to allocate memory\n");
      return 0;
    }


	fpLog = fopen("log.bin", "wb");

	if(fpLog == NULL)
	{
		printf("Error: savname open\n");
		exit(0);
	}

    initialize_rom();
    gameboy_cpu_hardreset();
    gameboy_cpu_run();
  } else {
    printf("Unable to load '%s'\n", szFileName);
  }

	infogb_close_audio();
	infogb_close();

	fputc(0x66, fpLog);
	fclose(fpLog);

	return 1;
}
//---------------------------------------------------------------------------
/* video */
void infogb_vram_blit()
{
		infogb_wait();
}
//---------------------------------------------------------------------------
void infogb_set_color(int x, unsigned short c)
{
	
}
//---------------------------------------------------------------------------
void infogb_plot_line(int y, int *index)
{
	
}
//---------------------------------------------------------------------------
/* key */
int infogb_poll_events()
{
    return 1;
}
//---------------------------------------------------------------------------
void infogb_wait()
{

}
//---------------------------------------------------------------------------
/* sound */
void infogb_open_audio()
{

}
//---------------------------------------------------------------------------
void infogb_write_sample(short int l, short int r)
{

}
//---------------------------------------------------------------------------
void infogb_close_audio()
{

}
//---------------------------------------------------------------------------
void Infogb_gba_savelog(unsigned char c)
{
	fputc(c, fpLog);
}
