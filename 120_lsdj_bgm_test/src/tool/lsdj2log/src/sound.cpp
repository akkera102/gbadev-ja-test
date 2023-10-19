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

#include "system.h"

#include "system.h"
#include "sound.h"
#include "mem.h"

//void WriteSample(short int l, short int r);

int SoundCycle = 0;

#ifdef AMIGA
int SoundLoader = 4194304/22050;
#else
int SoundLoader = 4194304/44100;
#endif
int SoundEnabled = 1;

int sq[4][8] = {
{1, 0, 0, 0, 0, 0, 0, 0},
{1, 1, 0, 0, 0, 0, 0, 0},
{1, 1, 1, 1, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 0, 0}
};

/* Initialize to 0x00FF x 8 */
int wavram[32] = { 
0x8000, 0x8000, 0x7000, 0x7000, 0x8000, 0x8000, 0x7000, 0x7000, 
0x8000, 0x8000, 0x7000, 0x7000, 0x8000, 0x8000, 0x7000, 0x7000,
0x8000, 0x8000, 0x7000, 0x7000, 0x8000, 0x8000, 0x7000, 0x7000,
0x8000, 0x8000, 0x7000, 0x7000, 0x8000, 0x8000, 0x7000, 0x7000
};

int slack;

int sOn, sLeftVol, sRightVol;

int s1SwTime, s1SwDir, s1SwVal, s1Wav, s1Len, s1Env, s1EnvDir, s1EnvVal,
    s1Freq, s1Cont, s1FCyc, s1LCyc, s1Play, s1Left, s1Right, s1SCyc, s1ECyc;
int s2Wav, s2Len, s2Env, s2EnvDir, s2EnvVal, s2Freq, s2Cont, s2FCyc, 
    s2LCyc, s2Play, s2Left, s2Right, s2ECyc;    
int s3On, s3Len, s3Vol, s3Freq, s3Play, s3Cont, s3FCyc, s3LCyc, 
    s3Left, s3Right;
int s4Play, s4Left, s4Right, s4Len, s4Env, s4EnvDir, s4EnvVal, s4Shift, s4Step, 
    s4Div, s4Cont, s4ECyc, s4LCyc, s4FCyc, s4Bit, s4Freq, s4Pos;

int VolHack = 1;

#include "noise.h"

//int voltab[16] = {0, 8, 17, 25, 34, 42, 51, 59, 68, 
//                    76, 85, 93, 102, 110, 119, 127};
int voltab[16] = { 0, 0x0808, 0x1111, 0x1919, 0x2222, 0x2A2A, 0x3333, 0x3B3B,
              0x4444, 0x4C4C, 0x5555, 0x5D5D, 0x6666, 0x6E6E, 0x7777, 0x7F7F };
//int voltab[16] = { 0, 0x0808, 0x1010, 0x1818, 0x2020, 0x2828, 0x3030, 0x3838,
//        0x4040, 0x4848, 0x5050, 0x5858, 0x6060, 0x6868, 0x7070, 0x7878 };

int mainvol[8] = { 16, 14, 11, 9, 7, 5, 2, 0 };

void ProcessSound(int cycles)
{
     int l, r, x;
     short int dat, snd = 0;

     cycles += slack;
     
     while (cycles >= SoundLoader) {
          l = 0; r = 0;
          dat = 0; snd = 0;
          
          if (sOn) {
               #if 1
               if (s1Play) {
                    if (s1Freq < 2043) {
                         dat = sq[s1Wav][(s1FCyc / (2048 - s1Freq)) >> 2];
                         
                         if (dat) 
                              snd = voltab[s1Env];
                         else
                              snd = -voltab[s1Env];
                         if (s1Left)
                              l += snd;
                         if (s1Right)
                              r += snd;
                    } else {
                    }
                    
                    s1FCyc += SoundLoader;
                    while (s1FCyc >= 32*(2048-s1Freq)) {
                         s1FCyc -= 32*(2048-s1Freq);
                    }
                    
                    if (s1SwTime && s1SwVal) {
                         s1SCyc += SoundLoader;
                         while (s1SCyc >= 32768*s1SwTime) {
                              s1SCyc -= 32768*s1SwTime;
                              if (s1SwDir) {
                                   int t = s1Freq;
                                   s1Freq -= s1Freq>>s1SwVal;
                                   if (s1Freq < 0)
                                        s1Freq = t;
                              } else {
                                   s1Freq +=  s1Freq>>s1SwVal;
                                   if (s1Freq > 2047) {
                                        s1Play = 0;
                                   }
                              }
                         }
                    }
                                   
                    if (s1EnvVal) {
                         s1ECyc += SoundLoader;
                         while (s1ECyc >= s1EnvVal*(4194304/64)) {
                              s1ECyc -= s1EnvVal*(4194304/64);
                              if (s1EnvDir)
                                   s1Env++;
                              else
                                   s1Env--;
                              if (s1Env > 0x0F) {
                                   s1Env = 0x0F;
                                   s1EnvVal = 0;
                              } else if (s1Env < 0) {
                                   s1EnvVal = 0;
                                   s1Env = 0;
                              }
                              if (s1EnvVal == 0)
                                   break;
                         }
                    }
                                             
                    if (s1Cont) {
                         s1LCyc += SoundLoader;
                         while (s1LCyc >= (4194304/256)) {
                              s1LCyc -= (4194304/256);
                              s1Len++;
                              if (s1Len == 64) {
                                   s1Play = 0;
                                   break;
                              }
                         }
                    }
               }
               #endif
               #if 1
               if (s2Play) {
                    if (s2Freq < 2043) {
                         dat = sq[s2Wav][(s2FCyc / (2048 - s2Freq)) >> 2];
                         
                         if (dat) 
                              snd = voltab[s2Env];
                         else
                              snd = -voltab[s2Env];
                         if (s2Left)
                              l += snd;
                         if (s2Right)
                              r += snd;
                    } else {
                    }
                    
                    s2FCyc += SoundLoader;
                    while (s2FCyc >= 32*(2048-s2Freq)) {
                         s2FCyc -= 32*(2048-s2Freq);
                    }
                    
                    if (s2EnvVal) {
                         s2ECyc += SoundLoader;
                         while (s2ECyc >= s2EnvVal*(4194304/64)) {
                              s2ECyc -= s2EnvVal*(4194304/64);
                              if (s2EnvDir)
                                   s2Env++;
                              else
                                   s2Env--;
                              if (s2Env > 0x0F) {
                                   s2EnvVal = 0;
                                   s2Env = 0x0F;
                              } else if (s2Env < 0) {
                                   s2EnvVal = 0;
                                   s2Env = 0;
                              }
                              if (s2EnvVal == 0)
                                   break;
                         }
                    }    
                    
                    if (s2Cont) {
                         s2LCyc += SoundLoader;
                         while (s2LCyc >= (4194304/256)) {
                              s2LCyc -= (4194304/256);
                              s2Len++;
                              if (s2Len == 64) {
                                   s2Play = 0;
                                   break;
                              }
                         }
                    }
               }
               #endif
               #if 1
               if (s3Play) {
                    if (s3Freq < 2045) {
                         int pos = (s3FCyc / (2048 - s3Freq)) >> 1;
                         dat = wavram[pos];
                         switch(s3Vol) {
                              case 0:
                                   dat = 0;
                                   break;
                              case 1:
                                   break;
                              case 2:
                                   dat >>= 1;
                                   break;
                              case 3:
                                   dat >>= 2;
                                   break;
                         }
                         
                         if (s3Left)
                              l += dat;
                         if (s3Right)
                              r += dat;
                    } else {
                    }
                    
                    s3FCyc += SoundLoader;
                    while (s3FCyc >= 64*(2048-s3Freq)) {
                         s3FCyc -= 64*(2048-s3Freq);
                    }
                    
                    if (s3Cont) {
                         s3LCyc += SoundLoader;
                         while (s3LCyc >= (4194304/256)) {
                              s3LCyc -= (4194304/256);
                              s3Len++;
                              if (s3Len == 256) {
                                   s3Play = 0;
                                   break;
                              }
                         }
                    }              
               }
               #endif
               #if 1
               if (s4Play) {
                    
                    if (s4Left)  {
                         if (s4Bit) {
                              l += voltab[s4Env];
                         } else {
                              l -= voltab[s4Env];
                         }
                    }
                    if (s4Right) {
                         if (s4Bit) {
                              r += voltab[s4Env];
                         } else {
                              r -= voltab[s4Env];
                         }
                    }
                    
                    s4FCyc += SoundLoader;
                    while (s4FCyc >= s4Freq) {
                         s4Pos++;
                         if (s4Step) {
                              s4Pos &= 127;
                              s4Bit = Sev[s4Pos];
                         } else {
                              s4Pos &= 32767;
                              s4Bit = Fif[s4Pos];
                         }
                         s4FCyc -= s4Freq;
                    }
                    
                    if (s4EnvVal) {
                         s4ECyc += SoundLoader;
                         while (s4ECyc >= s4EnvVal*(4194304/64)) {
                              s4ECyc -= s4EnvVal*(4194304/64);
                              if (s4EnvDir)
                                   s4Env++;
                              else
                                   s4Env--;
                              if (s4Env > 0x0F) {
                                   s4Env = 0x0F;
                                   s4EnvVal = 0;
                              } else if (s4Env < 0) {
                                   s4Env = 0;
                                   s4EnvVal = 0;
                              }
                              if (s4EnvVal == 0)
                                   break;
                         }
                    }
                    
                    if (s4Cont) {
                         s4LCyc += SoundLoader;
                         while (s4LCyc >= (4194304/256)) {
                              s4LCyc -= (4194304/256);
                              s4Len++;
                              if (s4Len == 64) {
                                   s4Play = 0;
                                   break;
                              }
                         }
                    }
               }
               #endif
          }
                    
          l >>= 2;
          r >>= 2;
          
          l >>= mainvol[sLeftVol];
          r >>= mainvol[sRightVol];

          #if 1
          if (VolHack) {
               /* Volume Hack! */
               x = (sLeftVol << 13) - 32768;
               l += x >> 1;
               x = (sRightVol << 13) - 32768;
               r += x >> 1;
          }
          #endif
          
          if (l > 32767)
               l = 32767;
          else if (l < -32768)
               l = -32768;
          if (r > 32767)
               r = 32767;
          else if (r < -32768)
               r = -32768;

          infogb_write_sample(l, r);
          cycles -= SoundLoader;
     }
     slack = cycles;     
}

void SoundWrite(unsigned char reg, unsigned char v)
{
     int x = v;
     
     //printf("reg write = %02X <- %02X\n", reg, v);
     switch(reg) {
          case 0x10:
               s1SwTime = (v & 0x70) >> 4;
               s1SwDir = (v & 0x08) ? 1 : 0;
               s1SwVal = v & 0x07;
               break;
          case 0x11:
               s1Wav = (v & 0xC0) >> 6;
               s1Len = (v & 0x3F);
               break;
          case 0x12:
               s1Env = (v & 0xF0) >> 4;
               s1EnvDir = (v & 0x08) ? 1 : 0;
               s1EnvVal = v & 0x07;
               break;
          case 0x13:
               s1Freq = (s1Freq & 0x700) | v;
               break;
          case 0x14:
               //printf("hit 1 %02X\n", v);
               s1Freq = (s1Freq & 0x0FF) | ((v & 0x07) << 8);
               s1Cont = (v & 0x40) ? 1 : 0;
               if (v & 0x80) {
                    //s1Cont = (v & 0x40) ? 1 : 0;
                    //s1Freq = ((v & 0x07) << 8) | hiram[0xF13];
                    
                    s1Play = 1;
                    
                    s1FCyc = 0;
                    s1LCyc = 0;
                    s1ECyc = 0;
                    s1SCyc = 0;
                    
                    //s1SwTime     = (hiram[0xF10] & 0x70) >> 4;
                    //s1SwDir      = (hiram[0xF10] & 0x08) ? 1 : 0;
                    //s1SwVal      = (hiram[0xF10] & 0x07);
                    
                    //s1Wav        = (hiram[0xF11] & 0xC0) >> 6;
                    //s1Len        = (hiram[0xF11] & 0x3F);
                    
                    s1Env          = (hiram[0xF12] & 0xF0) >> 4;
                    s1EnvDir  = (hiram[0xF12] & 0x08) ? 1 : 0;
                    s1EnvVal  = (hiram[0xF12] & 0x07);
               }
               break;
          
          case 0x16:
               s2Wav = (v & 0xC0) >> 6;
               s2Len = (v & 0x3F);
               break;
          case 0x17:
               s2Env = (v & 0xF0) >> 4;
               s2EnvDir = (v & 0x08) ? 1 : 0;
               s2EnvVal = v & 0x07;
               break;
          case 0x18:
               s2Freq = (s2Freq & 0x700) | v;
               break;
          case 0x19:
               //printf("hit 2 %02X\n", v);
               s2Freq = (s2Freq & 0x0FF) | ((v & 0x07) << 8);
               s2Cont = (v & 0x40) ? 1 : 0;
               if (v & 0x80) {
                    //s2Freq = (s2Freq & 0x0FF) | ((v & 0x07) << 8);
                    //s2Cont = (v & 0x40) ? 1 : 0;
                    
                    s2Play = 1;
                    
                    s2FCyc = 0;
                    s2LCyc = 0;
                    s2ECyc = 0;
                    
                    //s2Wav        = (hiram[0xF16] & 0xC0) >> 6;
                    //s2Len        = (hiram[0xF16] & 0x3F);
                    
                    s2Env          = (hiram[0xF17] & 0xF0) >> 4;
                    s2EnvDir  = (hiram[0xF17] & 0x08) ? 1 : 0;
                    s2EnvVal  = (hiram[0xF17] & 0x07);
               }
               break;
               
          case 0x1A:
               if (v & 0x80)
                    s3On = 1;
               else {
                    s3On = 0;
                    s3Play = 0;
               }    
               break;         
          case 0x1B:
               s3Len = v;
               break;
          case 0x1C:
               s3Vol = (v & 0x60) >> 5;
               break;
          case 0x1D:
               s3Freq = (s3Freq & 0x700) | v;
               break;
          case 0x1E:
               //printf("hit 3 %02X\n", v);
               s3Freq = (s3Freq & 0x0FF) | ((v & 0x07) << 8);
               s3Cont = (v & 0x40) ? 1 : 0;
               if ((v & 0x80) && s3On) { /* TODO: check */
                    s3Play = 1;
                    //s3Len = hiram[0xF1B];
                    s3LCyc = 0;
                    s3FCyc = 0;
               }
               break;

          case 0x20:
               s4Len = v & 0x3F;
               break; 
          case 0x21:
               s4Env = (v & 0xF0) >> 4;
               s4EnvDir = (v & 0x08) ? 1 : 0;
               s4EnvVal = v & 7;
               break;
          case 0x22:
               s4Shift = (v & 0xF0) >> 4;
               s4Step = (v & 0x08) ? 1 : 0;
               s4Div = (v & 0x07);

               switch(s4Div) {
                    /* 524288 = (4194304 / 2^3) */
                    case 0: s4Freq = (524288*2); break;
                    case 1: s4Freq = (524288*1); break;
                    case 2: s4Freq = (524288/2); break;
                    case 3: s4Freq = (524288/3); break;
                    case 4: s4Freq = (524288/4); break;
                    case 5: s4Freq = (524288/5); break;
                    case 6: s4Freq = (524288/6); break;
                    case 7: s4Freq = (524288/7); break;                    
               }
               s4Freq >>= (s4Shift+1);
               s4Freq = 4194304 / s4Freq;
               break;
          case 0x23:
               //printf("hit 4 %02X\n", v);
               s4Cont = (v & 0x40) ? 1 : 0;
               if (v & 0x80) {
                    s4Play = 1;
                    s4LCyc = 0;
                    //s4Len = hiram[0xF20] & 0x3F;
                    s4ECyc = 0;
                    //s4Env = (hiram[0xF21] & 0xF0) >> 4;
                    //s4EnvVal = (hiram[0xF21] & 0x07);
                    s4FCyc = 0;
               }    
               break;
               
          case 0x24:
               sLeftVol = (v & 0x07);
               sRightVol = (v & 0x70) >> 4;
               //printf("Sound: %d %d\n", sLeftVol, sRightVol);
               //if (v & 0x88) printf("Vin enabled!\n");
               break;
          case 0x25:
               s1Left = (v & 0x01) ? 1 : 0;
               s2Left = (v & 0x02) ? 1 : 0;
               s3Left = (v & 0x04) ? 1 : 0;
               s4Left = (v & 0x08) ? 1 : 0;
               s1Right = (v & 0x10) ? 1 : 0;
               s2Right = (v & 0x20) ? 1 : 0;
               s3Right = (v & 0x40) ? 1 : 0;
               s4Right = (v & 0x80) ? 1 : 0;
               break;
          case 0x26:
               if (v & 0x80) {
                    sOn = 1;
               } else {
                    sOn = 0;
                    s1Play = 0;
                    s2Play = 0;
                    s3On = 0;
                    s3Play = 0;
                    s4Play = 0;
               }
               x &= 0x80;
               break;
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
          case 0x3A:
          case 0x3B:
          case 0x3C:
          case 0x3D:
          case 0x3E:
          case 0x3F:
               //printf("wavram = %02X\n", v);
               {
                    int a, b;
                    a = (v & 0xF0) >> 4;
                    b = (v & 0x0F);
                    a -= 8;
                    b -= 8;
                    wavram[((reg & 0x0F) << 1) + 0] = a << 12;
                    wavram[((reg & 0x0F) << 1) + 1] = b << 12;
               }
               //wavram[((reg & 0x0F) << 1) + 0] = ((v & 0xF0) << 8)  | ((v & 0xF0) << 4) | ((v & 0xF0) << 0) | ((v & 0xF0) >> 4);
               //wavram[((reg & 0x0F) << 1) + 1] = ((v & 0x0F) << 12) | ((v & 0x0F) << 8) | ((v & 0x0F) << 4) | ((v & 0x0F) << 0);
               break;
          default:
               hiram[reg | 0xF00] = v;
               return;
     }
     hiram[reg | 0xF00] = x;
}

unsigned char SoundRead(int reg)
{
     int i;
     
     //printf("reg read  = %02X -> %02X\n", reg, hiram[reg | 0xF00]);
     switch(reg) {
          case 0x26:
               i = 0;
               i |= sOn ? 0x80 : 0x00;
               if (sOn) {
                    i |= s1Play ? 0x01 : 0x00;
                    i |= s2Play ? 0x02 : 0x00;
                    i |= s3Play ? 0x04 : 0x00;
                    i |= s4Play ? 0x08 : 0x00;
               }
               return i;
     }    
     return hiram[reg | 0xF00];
}
