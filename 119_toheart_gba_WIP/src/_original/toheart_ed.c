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
 * ToHeart ����ǥ���
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
    /* ʸ���򿿤���ˡ� */
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

    /* ʸ���˿�������� */
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
    /* �ѥ�å�ȿ�� */
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

/* ToHeart ����ǥ��󥰥�����ץ� */
static LvnsScriptData eddata[] = {

    { LVNS_SCRIPT_MUSIC, (void*)35 },
    { LVNS_SCRIPT_TIMER_INIT },

    { LVNS_SCRIPT_TIMER_WAIT, (void*)16000 },
    { LVNS_SCRIPT_FUNC, start },
    { LVNS_SCRIPT_LOOP_FUNC, ToSmall },
    { LVNS_SCRIPT_FUNC, white },


    /* ��� */
    { LVNS_SCRIPT_FUNC, tputs, "���", XY(50, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ⶶ��ζ��", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*0 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*0 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ���� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)31 },
    { LVNS_SCRIPT_FUNC, tputs, "����", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ⶶ��ζ��", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ġ���", XY(54, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�������դ�", XY(54, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*1) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*1 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*1 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ���� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)8 },
    { LVNS_SCRIPT_FUNC, tputs, "����", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "��̵�Ű", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�顼���٣ϣ�", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*2) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*2 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*2 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* �������� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)9 },
    { LVNS_SCRIPT_FUNC, tputs, "��������", XY(32, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ⶶ��ζ�顡����̵�Ű", XY(36, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "���������������顼���٣ϣ�", XY(36, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*3) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*3 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*3 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* �ץ���� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)10 },
    { LVNS_SCRIPT_FUNC, tputs, "�ץ����", XY(30, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ȣ����塡�Σ������", XY(34, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*4) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*4 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*4 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ����ե����� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)11 },
    { LVNS_SCRIPT_FUNC, tputs, "����ե�����", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ˣţΣˣţ�", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "����̴", XY(54, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "Ļ�����", XY(54, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*5) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*5 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*5 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ����ե����� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)12 },
    { LVNS_SCRIPT_FUNC, tputs, "����ե�����", XY(47, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ͤΤĤ��椭����", XY(51, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "��ߤ�", XY(51, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�������ʥ�", XY(51, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*6) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*6 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*6 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ����ե����� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)13 },
    { LVNS_SCRIPT_FUNC, tputs, "����ե�����", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�ģϣڣ�", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "����", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*7) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*7 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*7 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* �طʥ���ե����� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)14 },
    { LVNS_SCRIPT_FUNC, tputs, "�طʥ���ե�����", XY(50, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "Ļ�����", XY(54, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*8) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*8 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*8 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ���� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)15 },
    { LVNS_SCRIPT_FUNC, tputs, "������", XY(50, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "���ľ��", XY(54, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "��塡�±�", XY(54, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�������", XY(54, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*9) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*9 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*9 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ED���� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)7 },
    { LVNS_SCRIPT_FUNC, tputs, "�ţĥ���", XY(21, 0) }, 
    { LVNS_SCRIPT_FUNC, tputs, "��졧�Σţˣϡ����Զʡ�����ľ��", XY(25, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "��������ʡ���¸㡡Ͽ������ͭ¼���", XY(25, 2) }, 
    { LVNS_SCRIPT_FUNC, tputs, "���Ρ������ä�", XY(25, 3) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*10) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*10 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*10 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* �����ȥ�� */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)21 },
    { LVNS_SCRIPT_FUNC, tputs, "�����ȥ��", XY(47, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "����եȥޥ�", XY(51, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*11) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*11 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*11 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* TEST PLAY */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)32 },
    { LVNS_SCRIPT_FUNC, tputs, "�ԣţӣԡ��У̣���", XY(30, 1) },  
    { LVNS_SCRIPT_FUNC, tputs, "���̡̣��̣ţ��ơ��ӣԣ��ƣ�", XY(34, 2) },  
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*12) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*12 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*12 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* ��ȯ */
    { LVNS_SCRIPT_FUNC, DispSmall, (void*)17 },
    { LVNS_SCRIPT_FUNC, tputs, "����ȯ", XY(44, 1) }, 
    { LVNS_SCRIPT_FUNC, tputs, "�����������̣ţ���", XY(48, 2) }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*13) },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*13 + 3000) },
    { LVNS_SCRIPT_LOOP_FUNC, DispMoji },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(BASETIME + CYCLE*13 + 9500) },
    { LVNS_SCRIPT_WHITEOUT },

    /* Leaf �� */
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
