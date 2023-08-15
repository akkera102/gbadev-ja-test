/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart_ed.c,v 1.2 2002/07/29 05:24:39 go Exp $
 *
 */

#pragma setlocale("English")

/*
 * ToHeart ¥¨¥ó¥Ç¥£¥ó¥°
 */

#include <stdio.h>
#include "toheart.h"

#define EDCOL 250
#define EDSHA 251

#ifdef USE_MGL
static struct {
  int x;
  int y;
  char str[128];
  int type;
} telop[10];

static int telop_num;
#endif

static int
start(Lvns *lvns, LvnsScript *scr)
{
    lvnsimage_copy(lvns->vram, lvns->background);
#ifdef USE_MGL
    telop_num = 0;
    lvns->latitude = 16;
#endif
    return True;
}

#ifndef USE_MGL
#define XF 192
#define YF 144
#else
#define XF 96
#define YF 72
#endif
static int
ToSmall(Lvns *lvns, LvnsScript *scr, void *param1, void *param2)
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;
#ifndef USE_MGL
    memset(lvns->vram->data, TOHEART_COL_WHITE, 
           lvns->vram->rwidth * lvns->vram->rheight);
#else
    mglimage_clear_color(lvns->vram, COLOR_WHITE);
#endif
    lvnsimage_copy_scale(lvns->background, 0, 0, WIDTH, HEIGHT, 
                         lvns->vram, 0, 0, 
                         WIDTH  - XF * scr->state/24,
                         HEIGHT - YF * scr->state/24);
    lvns->drawWindow(lvns);
    LvnsFlushWindow(lvns);
	
    if (++scr->state > 24) {
        return True;
    } else {
        return False;
    }
}
#undef XF
#undef YF

#ifdef USE_MGL
static void
SetTelop(Lvns *lvns, int x, int y, const char *str, int type)
{
  telop[telop_num].x = x;
  telop[telop_num].y = y;
  strcpy(telop[telop_num].str, str);
  telop[telop_num].type = type;
  telop_num++;
}
#endif

#define XY(x,y) (void*)(x<<8|y)
#ifndef USE_MGL
#define XF 8
#define YB 344
#define YF 30
#else
#define XF 4
#define YB 172
#define YF 15
#define ToHeartPutsVRAM SetTelop
#endif

static int
tputs(Lvns *lvns, LvnsScript *scr, void *param1, void *param2)
{
    int x = ((int)param2 >> 8) * XF;
    int y = YB + ((int)param2 & 0xff) * YF;
    ToHeartPutsVRAM(lvns, x+2, y+2, (u_char*)param1, EDSHA);
    ToHeartPutsVRAM(lvns, x  , y  , (u_char*)param1, EDCOL);
    return True;
}
#undef ToHeartPutsVRAM

static int
white(Lvns *lvns, LvnsScript *scr, 
      void *param1, void *param2)
{
    /* Ê¸»ú¤ò¿¿¤ÃÇò¤Ë¡Ä */
    lvns->vram->palette[EDCOL][0] = 255;
    lvns->vram->palette[EDCOL][1] = 255;
    lvns->vram->palette[EDCOL][2] = 255;
    lvns->vram->palette[EDSHA][0] = 255;
    lvns->vram->palette[EDSHA][1] = 255;
    lvns->vram->palette[EDSHA][2] = 255;
    lvns->vram->palette_num = EDSHA+1;
}

static int
DispSmall(Lvns *lvns, LvnsScript *scr, 
          void *param1, void *param2)
{
    ToHeartLoadBG(lvns, (int)param1);
#ifndef USE_MGL
    memset(lvns->vram->data, TOHEART_COL_WHITE, 
           lvns->vram->rwidth * lvns->vram->rheight);
    lvnsimage_copy_palette(lvns->background, lvns->vram);
    lvnsimage_copy_scale(lvns->background, 0, 0, WIDTH, HEIGHT, 
                         lvns->vram, 0, 0, 448, 336);
#else
    mglimage_clear_color(lvns->vram, COLOR_WHITE);
    lvnsimage_copy_scale(lvns->background, 0, 0, WIDTH, HEIGHT, 
                         lvns->vram, 0, 0, 224, 168);
    telop_num = 0;
#endif
    white(lvns, scr, NULL, NULL);
    return True;
}

static int
SetLogo(Lvns *lvns, LvnsScript *scr, 
        void * param1, void * param2) 
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;
#ifndef USE_MGL
    lvnsimage_clear_index(lvns->background, TOHEART_COL_WHITE);
    lvnsimage_clear_index(lvns->vram,       TOHEART_COL_WHITE);
#else
    mglimage_clear_color(lvns->background, COLOR_WHITE);
    mglimage_clear_color(lvns->vram, COLOR_WHITE);
#endif
    lvnsimage_delete(state->title);
    state->title = LvnsLoadImage(lvns, "LEAF.LF2", NULL);
    ToHeartSakuraSetNumber(lvns, 40);
    LvnsSetNextBackEffect(lvns, &toHeartSakuraEffect);
    return True;
}

static int
sakura_start(Lvns *lvns, LvnsScript *scr)
{
}

#define SCR(c,a) (c + (255-c)*a/16)

static int
DispMoji(Lvns *lvns, LvnsScript *scr, 
         void *param1, void *param2)
{
    int al = 16 - scr->state;

    /* Ê¸»ú¤Ë¿§¤òÀßÄê¡Ä */
    lvns->vram->palette[EDCOL][0] = SCR(255,al);
    lvns->vram->palette[EDCOL][1] = SCR(  8,al);
    lvns->vram->palette[EDCOL][2] = SCR(127,al);
    lvns->vram->palette[EDSHA][0] = SCR(255,al);
    lvns->vram->palette[EDSHA][1] = SCR(192,al);
    lvns->vram->palette[EDSHA][2] = SCR(224,al);
    
#ifdef USE_MGL
    {
      int i, color;
      u_char r, g, b;
      for (i = 0; i < telop_num; i++) {
	switch (telop[i].type) {
	case EDCOL:
	  r = (SCR(255,al) >> 4) & 0xf;
	  g = (SCR(  8,al) >> 4) & 0xf;
	  b = (SCR(127,al) >> 4) & 0xf;
	  color = mc_from_rgb(packRGB(r, g, b));
	  ToHeartPutsVRAM(lvns, telop[i].x, telop[i].y, telop[i].str, color);
	  break;
	case EDSHA:
	  r = (SCR(255,al) >> 4) & 0xf;
	  g = (SCR(192,al) >> 4) & 0xf;
	  b = (SCR(224,al) >> 4) & 0xf;
	  color = mc_from_rgb(packRGB(r, g, b));
	  ToHeartPutsVRAM(lvns, telop[i].x-1, telop[i].y, telop[i].str, color);
	  ToHeartPutsVRAM(lvns, telop[i].x, telop[i].y, telop[i].str, color);
	  break;
	}
      }
    }
#endif
    /* ¥Ñ¥ì¥Ã¥ÈÈ¿±Ç */
    lvns->setPalette(lvns);
    lvns->drawWindow(lvns);
    LvnsFlushWindow(lvns);

    if (++scr->state > 16) {
        return True;
    } else {
        return False;
    }
}

#define BASETIME 19000
#define CYCLE    11000 

/* ToHeart ¥¨¥ó¥Ç¥£¥ó¥°¥¹¥¯¥ê¥×¥È */
static LvnsScriptData eddata[] = {

    { LVNS_SCRIPT_MUSIC, (void*)35 },
    { LVNS_SCRIPT_TIMER_INIT },

    { LVNS_SCRIPT_TIMER_WAIT, (void*)16000 },
    { LVNS_SCRIPT_FUNC, start },
    { LVNS_SCRIPT_LOOP_FUNC, ToSmall },
    { LVNS_SCRIPT_FUNC, white },


    /* ´ë²è */
    { LVNS_SCRIPT_FUNC, tputs, "´ë²è", XY(50, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¹â¶¶¡¡Î¶Ìé", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*0 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*0 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* µÓËÜ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)31 },
    { LVNS_SCRIPT_FUNC, tputs, "µÓËÜ", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¹â¶¶¡¡Î¶Ìé", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "ÀÄ¡¡»ç", XY(54, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "°ª¡¡¤â¤ê¤Õ¤ß", XY(54, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*1) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*1 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*1 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ¸¶²è */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)8 },
    { LVNS_SCRIPT_FUNC, tputs, "¸¶²è", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¿åÌµ·î¡¡Å°", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¥é¡¼¡¦£Ù£Ï£Õ", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*2) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*2 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*2 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ¥·¡¼¥ó¹½À® */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)9 },
    { LVNS_SCRIPT_FUNC, tputs, "¥·¡¼¥ó¹½À®", XY(32, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¹â¶¶¡¡Î¶Ìé¡¡¡¡¿åÌµ·î¡¡Å°", XY(36, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "°¡³¨Íý¡¡¡¡¡¡¡¡¥é¡¼¡¦£Ù£Ï£Õ", XY(36, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*3) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*3 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*3 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ¥×¥í¥°¥é¥à */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)10 },
    { LVNS_SCRIPT_FUNC, tputs, "¥×¥í¥°¥é¥à", XY(30, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "£È£á£ê£é£í£å¡¡£Î£é£î£ï£í£á£å", XY(34, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*4) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*4 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*4 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ¥°¥é¥Õ¥£¥¯¥¹ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)11 },
    { LVNS_SCRIPT_FUNC, tputs, "¥°¥é¥Õ¥£¥¯¥¹", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "£Ë£Å£Î£Ë£Å£Î", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "À¸ÇÈÌ´", XY(54, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "Ä»Ìî¡¡Àµ¿®", XY(54, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*5) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*5 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*5 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ¥°¥é¥Õ¥£¥¯¥¹ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)12 },
    { LVNS_SCRIPT_FUNC, tputs, "¥°¥é¥Õ¥£¥¯¥¹", XY(47, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¤Í¤Î¤Ä¤­¤æ¤­¤·¤í", XY(51, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¤í¤ß¤å", XY(51, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¥ô¥£¡¼¥Ê¥¹", XY(51, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*6) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*6 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*6 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ¥°¥é¥Õ¥£¥¯¥¹ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)13 },
    { LVNS_SCRIPT_FUNC, tputs, "¥°¥é¥Õ¥£¥¯¥¹", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "£Ä£Ï£Ú£Á", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¿ÆÉã", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*7) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*7 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*7 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ÇØ·Ê¥°¥é¥Õ¥£¥¯¥¹ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)14 },
    { LVNS_SCRIPT_FUNC, tputs, "ÇØ·Ê¥°¥é¥Õ¥£¥¯¥¹", XY(50, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "Ä»Ìî¡¡Àµ¿®", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*8) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*8 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*8 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ²»³Ú */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)15 },
    { LVNS_SCRIPT_FUNC, tputs, "²»¡¡³Ú", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "²¼Àî¡¡Ä¾ºÈ", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "Ãæ¾å¡¡ÏÂ±Ñ", XY(54, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "ÀÐÀî¡¡¿¿Ìé", XY(54, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*9) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*9 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*9 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ED¥½¥ó¥° */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)7 },
    { LVNS_SCRIPT_FUNC, tputs, "£Å£Ä¥½¥ó¥°", XY(21, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "ºî¡¡»ì¡§£Î£Å£Ë£Ï¡¡ºîÊÔ¶Ê¡§²¼ÀîÄ¾ºÈ", XY(25, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¥®¥¿¡¼¡§Ê¡¸¶¿Â¸ã¡¡Ï¿¡¡²»¡§Í­Â¼·ò°ì", XY(25, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¡¡²Î¡¡¡§¤¢¤Ã¤³", XY(25, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*10) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*10 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*10 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ¥¿¥¤¥È¥ë¥í¥´ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)21 },
    { LVNS_SCRIPT_FUNC, tputs, "¥¿¥¤¥È¥ë¥í¥´", XY(47, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "¥¯¥é¥Õ¥È¥Þ¥ó", XY(51, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*11) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*11 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*11 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* TEST PLAY */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)32 },
    { LVNS_SCRIPT_FUNC, tputs, "£Ô£Å£Ó£Ô¡¡£Ð£Ì£Á£Ù", XY(30, 1) },  
    { LVNS_SCRIPT_FUNC, tputs, "£Á£Ì£Ì¡¡£Ì£Å£Á£Æ¡¡£Ó£Ô£Á£Æ£Æ", XY(34, 2) },  
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*12) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*12 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*12 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ³«È¯ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)17 },
    { LVNS_SCRIPT_FUNC, tputs, "³«¡¡È¯", XY(44, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "£±£¹£¹£·¡¡£Ì£Å£Á£Æ", XY(48, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*13) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*13 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*13 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* Leaf ¥í¥´ */
    { LVNS_SCRIPT_FUNC, SetLogo },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*14) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_FUNC, sakura_start },

    { LVNS_SCRIPT_WAIT_CLICK },
    { LVNS_SCRIPT_CLICK_JUMP },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_FADE_PALETTE },
    { LVNS_SCRIPT_END },
};

void
ToHeartEnding(Lvns *lvns)
{
	LvnsScriptRun(lvns, eddata);
}
