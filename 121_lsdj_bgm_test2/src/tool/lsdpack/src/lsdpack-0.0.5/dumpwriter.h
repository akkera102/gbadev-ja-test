/* lsdpack - standalone LSDj (Little Sound Dj) recorder + player {{{
   Copyright (C) 2018  Johan Kotlinski
   https://www.littlesounddj.com

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. }}} */

#include "iwriter.h"

class DumpWriter : public IWriter {
    public:
        void record_song_start(const char* out_path) override {
            last_cycle = 0;

            if (f == 0) {
//                f = fopen(out_path, "w");
                f = fopen(out_path, "wb");
                if (f == 0) {
                    char errormsg[1024];
                    snprintf(errormsg, sizeof(errormsg),
                            "Opening '%s' for write failed",
                            out_path);
                    perror(errormsg);
                    exit(1);
                }
            }
        }

        void record_write(unsigned char addr, unsigned char data, unsigned long cycle) override {
            if (last_cycle == 0) {
                last_cycle = cycle;
            }
//            fprintf(f, "%08lx ff%02x=%02x\n", cycle - last_cycle, addr, data);
            gba_patch(addr, data);

            last_cycle = cycle;
        }

        void record_song_stop() override {
			fputc(0x66, f);
            fclose(f);
        }

        void record_lcd() override {
			fputc(0x61, f);
//			fprintf(f, "!!\n");
		}

        void write_music_to_disk() override {}


		void gba_patch(unsigned char reg, unsigned char value)
		{
			unsigned char adr;
			unsigned char dat;

			switch(reg)
			{
			case 0x10: adr = 0x60; break;	// NR 10
			case 0x11: adr = 0x62; break;	// NR 11
			case 0x12: adr = 0x63; break;	// NR 12
			case 0x13: adr = 0x64; break;	// NR 13
			case 0x14: adr = 0x65; break;	// NR 14
			case 0x16: adr = 0x68; break;	// NR 21
			case 0x17: adr = 0x69; break;	// NR 22
			case 0x18: adr = 0x6c; break;	// NR 23
			case 0x19: adr = 0x6d; break;	// NR 24
			case 0x1a: adr = 0x70; break;	// NR 30
			case 0x1b: adr = 0x72; break;	// NR 31
			case 0x1c: adr = 0x73; break;	// NR 32
			case 0x1d: adr = 0x74; break;	// NR 33
			case 0x1e: adr = 0x75; break;	// NR 34
			case 0x20: adr = 0x78; break;	// NR 41
			case 0x21: adr = 0x79; break;	// NR 42
			case 0x22: adr = 0x7c; break;	// NR 43
			case 0x23: adr = 0x7d; break;	// NR 44
			case 0x24: adr = 0x80; break;	// NR 50
			case 0x25: adr = 0x81; break;	// NR 51
			case 0x26: adr = 0x84; break;	// NR 52

			// RAM
			case 0x30:
			case 0x31:
			case 0x32:
			case 0x33:
			case 0x34:
			case 0x35:
			case 0x36:
			case 0x37:
			case 0x38:
			case 0x39:
			case 0x3a:
			case 0x3b:
			case 0x3c:
			case 0x3d:
			case 0x3e:
			case 0x3f:
				adr = 0x90 + reg - 0x30;
				break;

			default:
				return;
			}

			dat = value;

			// NR 30
			if(adr == 0x70)
			{
				dat &= 0x80;
			}

			// NR 32
			if(adr == 0x73)
			{
				dat &= 0x60;
			}

			// NR 50
			if(adr == 0x80 && dat & 0x08)
			{
				printf("Warning: no use GBA bit. NR 50(FF24) Right Flag.\n");
			}

			// NR 50
			if(adr == 0x80 && dat & 0x80)
			{
				printf("Warning: no use GBA bit. NR 50(FF24) Left Flag.\n");
			}

		//	printf("%02X = %02X\n", adr, dat);

			fputc(0xb3, f);
			fputc(adr, f);
			fputc(dat, f);

			// add REG_SOUND3CNT_L = 0x40;
			if(adr >= 0x90 && adr <= 0x9f)
			{
				fputc(0xb3, f);
				fputc(0x70, f);
				fputc(0x40, f);
			}
		}



    private:
        FILE* f;
        unsigned long last_cycle;
};
