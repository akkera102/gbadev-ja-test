/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart_op.c,v 1.3 2002/07/29 05:24:39 go Exp $
 *
 */

#pragma setlocale("English")

/* 
 * ToHeart オープニング/タイトル
 */

#include <stdio.h>
#include "toheart.h"

/* ------------------------------------------------------------ */
/** しおり初期化用メニュー */

static MenuLine siori_init_menu_line[] = {
    MENULINE( 9, "全てのしおりを初期化します",0),
    MENULINE(10, "よろしいですか？",0),
    MENULINE(11, "はい",1),
    MENULINE(12, "いいえ",2),
	MENULINE(0, NULL, 0),
};

static Bool
SioriInitMenuEngine(Lvns *lvns, int select)
{
    int i;

    if (select == 1) {
        ToHeartSioriInit(lvns);
        /* 全データを保存 */
        for (i=1; i<=5; i++) {
            ToHeartSave(lvns, i);
        }
        ToHeartSaveCommon(lvns);
    }
    /* タイトルメニューに戻る */
	return select;
}

static MenuData siori_init_menu = {
	siori_init_menu_line,
	2, 2,
	NULL,
};

/* ------------------------------------------------------------ */
/**  タイトルメニュー */

static MenuLine title_menu_line[] = {
	MENULINE(8, "ゲームを始める",1),
	MENULINE(9, "しおりの初期化",2),
#if 0
	MENULINE(10, "思い出のアルバム",3),
    MENULINE(13, "フォント変更",4),
#endif
	MENULINE(10, "終了する",3),
	MENULINE(0, NULL, 0),
};

static int
TitleMenuEngine(Lvns *lvns, int select)
{
    switch (select) {
    case 1: /*ゲーム開始 */
		ToHeartSioriDate(lvns);
		return  LvnsMenu(lvns, &toheart_title_load_menu, True) > 0 ? 1: 0;
       
    case 2: /* しおり初期化 */
		ToHeartSioriDate(lvns);
		LvnsMenu(lvns, &siori_init_menu, True);
		return 0;

    case 3: /* 終了 */
        LvnsJump(lvns, LVNS_JUMP_END);
    }

    return select;
}

static MenuData title_menu = {
	title_menu_line,
	3, 1,
	TitleMenuEngine
};

/* ------------------------------------------------------------ */

/*
 * サクラをちらしはじめる
 */
static int
start_sakura(Lvns *lvns, LvnsScript *scr)
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;
    ToHeartSakuraSetNumber(lvns, 0);
    ToHeartSakuraSetNumber(lvns, 30);
    LvnsSetBackEffect(lvns, &toHeartSakuraEffect);
    state->title_mask = 16;
    return True;
}    

static int
start_sakura2(Lvns *lvns, LvnsScript *scr)
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;
    LvnsSetBackEffect(lvns, &toHeartSakuraEffect);
    ToHeartSakuraSetNumber(lvns, 30);
    state->title_mask = 16;
    return True;
}    

/**
 * さくら停止
 */
static int
stop_sakura(Lvns *lvns, LvnsScript *scr)
{
	LvnsSetBackEffect(lvns, NULL);
}


/* 単純画像ロード */
static int
LoadImage(Lvns *lvns, LvnsScript *scr, 
          void * param1, void * param2) 
{
    (void*)LvnsLoadImage(lvns, param1, lvns->background);
    lvns->latitude = 16;
    ToHeartClearCharacter(lvns, 'a');
    return True;
}

/* 画像追加(センタリング) */
static int
AddImage(Lvns *lvns, LvnsScript *scr, 
         void * param1, void * param2) 
{
    LvnsImage *image;
    ToHeartState *state = (ToHeartState*)lvns->system_state;
    lvnsimage_delete(state->title);
    if ((image = LvnsLoadImage(lvns, param1, NULL)) != NULL) {
        image->xoffset = (WIDTH  - image->width)/2;
        image->yoffset = (HEIGHT - image->height)/2;
    }
    state->title = image;
    return True;
}

/* 画像追加(通常) */
static int
AddImage2(Lvns *lvns, LvnsScript *scr, 
          void * param1, void * param2) 
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;
    lvnsimage_delete(state->title);
    state->title = LvnsLoadImage(lvns, param1, NULL);
    return True;
}

/* 画像追加(バグ対処用) */
static int
AddImage3(Lvns *lvns, LvnsScript *scr, 
          void * param1, void * param2) 
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;
    AddImage2(lvns, scr, param1, param2);
    state->title->transparent = 0;
    return True;
}

static int
LoadChar(Lvns *lvns, LvnsScript *scr, 
        void * param1, void * param2) 
{
    ToHeartLoadCharacter(lvns, (int)param1, (int)param2);
    return True;
}

/* --------------------------------------------------------------------- */

static void
LightPut(LvnsImage *src, LvnsImage *dst, int x, int y, int w, int h, int x2, int y2, int level) {
    int i,j;
    
    if (x2 < 0) {
        x -= x2; 
        w += x2;
        x2 = 0;
    }
    if (y2 < 0) {
        y -= y2;
        h += y2;
        y2 = 0;
    }

    if (w <= 0 || h <= 0)
      return;

    if (x2 + w > dst->rwidth)  w = dst->rwidth - x2;
    if (y2 + h > dst->rheight) h = dst->rheight - y2;

#ifndef USE_MGL
    for (i=0; i<h; i++) {
        u_char *p = src->data + (i + y) * src->rwidth + x;
        u_char *q = dst->data + (i + y2) * dst->rwidth + x2;
        for (j=0; j<w; j++, q++, p++) {
            if (*p > level) {
                int d = *q - (*p - level);
                if (d < 1) d = 1;
                *q = d;
            }
        }
    }
#else
    for (i=0; i<h; i++) {
      int h, s, b, d;
      u_short *p = src->hsb_data + (i + y) * src->rwidth + x;
      u_short *q = dst->hsb_data + (i + y2) * dst->rwidth + x2;
      for (j=0; j<w; j++, q++, p++) {
	unpackMC(*p, h, s, b);
	if (b > level) {
	  unpackMC(*q, h, s, d);
	  b = (b + d > 15) ? 15 : b + d;
	  *q = packMC(h, s, b);
	}
      }
    }
#endif
}

static void
disp(Lvns *lvns, int mask)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    state->title_mask = mask;
    LvnsBackEffect(lvns);
    lvns->setPalette(lvns);
    lvns->drawWindow(lvns);
    LvnsFlushWindow(lvns);
}

/* アルバム表示 */
static int
album_in(Lvns *lvns, LvnsScript *scr)
{
    disp(lvns, scr->state * 2);
    if (++scr->state > 8) {
        return True;
    } else {
        return False;
    }
}

/* アルバム消去 */
static int
album_out(Lvns *lvns, LvnsScript *scr)
{
    disp(lvns, 16 - scr->state * 2);
    if (++scr->state > 8) {
        ToHeartClearCharacter(lvns, 0);
        return True;
    } else {
        return False;
    }
}

/* 空からスクロール初期化 */
static int
init_sky(Lvns *lvns, LvnsScript *scr)
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;

    LvnsImage *img;
    lvns->latitude = 16;

    /* 背景の空*/
    /*
     * ここだけは Lvns.h の #define lvnsimage_add... を使うと破綻
     * (オフクリーンなので，二重でサイズ縮小してしまうことになる)
     */
    state->roll = lvnsimage_new(WIDTH, HEIGHT*2, 0, 0);
    img = LvnsLoadImage(lvns, "S19D.LF2", NULL);
#ifndef USE_MGL
    lvnsimage_add(img, state->roll, 0, 0);
#else
    mglimage_add(img, state->roll, 0, 0);
#endif
    lvnsimage_delete(img);
    LvnsLoadImage(lvns, "S17D.LF2", lvns->background);
#ifndef USE_MGL
    lvnsimage_add(lvns->background, state->roll, 0, HEIGHT);
#else
    mglimage_add(lvns->background, state->roll, 0, HEIGHT);
#endif

    lvns->background->transparent = state->roll->transparent;
    lvns->background->palette_num = state->roll->palette_num;

#ifndef USE_MGL
    memcpy(lvns->background->palette, 
           state->roll->palette, 
           state->roll->palette_num * 3);
#endif

    AddImage2(lvns, NULL, "OP_NAME.LF2", NULL);
    state->title_mask = 16;
    state->light = LvnsLoadImage(lvns, "LIGHT.LFG", NULL);

    /* 前の画面は消しておく */
    lvnsimage_clear_index(lvns->vram, TOHEART_COL_BLACK);

    return True;
}

/* 空からスクロール*/
#ifndef USE_MGL
#define STEP 2
#else
#define STEP 1
#define LightPut(l,b,x,y,w,h,x2,y2,s) LightPut(l,b,(x)/2,(y)/2,(w)/2,(h)/2,(x2)/2,(y2)/2,s)
#endif
static int
sky(Lvns *lvns, LvnsScript *scr)
{
    long msec  = lvns->getTimer(lvns, LVNSTIMER_SCRIPT);
    long wtime = 15000 + scr->state*80;

    if (msec < wtime) {
        return False;
    } else {
        ToHeartState *state = (ToHeartState*)lvns->system_state;
        int y = scr->state * STEP;

#if 0
		fprintf(stderr, "%d/%d\n", msec, wtime);
#endif

        /* 文字合成 */
        if (scr->state > 140) {
            state->title_mask = 16 - (scr->state - 140);
        }

        /* 背景への光の合成 */
        lvnsimage_copy_area(state->roll, lvns->background, 0, y, WIDTH, HEIGHT, 0, 0);
        if (scr->state < 32) {
            LightPut(state->light, lvns->background,   
                     0, 0, 320, 320, 
                     540 - scr->state * 8 - 160,
                     32  + scr->state * 4  - 160,
                     scr->state/2);
            LightPut(state->light, lvns->background, 
                     320, 0, 200, 200, 
                     540 - scr->state * 5 - 100,
                     32  + scr->state * 2.5  - 100, 
                     scr->state/2);
            LightPut(state->light, lvns->background, 
                     520, 0, 120, 120, 
                     540 - scr->state * 3 - 60,
                     32  + scr->state * 1.5 - 60,
                     scr->state/2);
        }

        LvnsBackEffect(lvns);
        lvns->setPaletteScreen(lvns, (scr->state < 17) ? 16-scr->state : 0);
        lvns->drawWindow(lvns);
        LvnsFlushWindow(lvns);

        if (++scr->state >= 240) {
            ToHeartSakuraSetNumber(lvns, 0);
            ToHeartSakuraSetNumber(lvns, 30);
            LvnsSetBackEffect(lvns, &toHeartSakuraEffect);
            return True;
        } else {
            return False;
        }
    }
}

/* タイトル表示 */
static int
show_title(Lvns *lvns, LvnsScript *scr)
{
    disp(lvns, scr->state * 2);
    if (++scr->state > 8) {
        LvnsSetBackEffect(lvns, &toHeartSakuraEffect);
        return True;
    } else {
        return False;
    }
}

static int
end(Lvns *lvns, LvnsScript *scr)
{       
    ToHeartState *state = (ToHeartState*)lvns->system_state;
    lvnsimage_delete(state->roll);
    lvnsimage_delete(state->light);
    state->roll = state->light = NULL; /* end は 2 回呼ばれる場合がある */
    return True;
}

static LvnsScriptData opdata[] = {

    { LVNS_SCRIPT_MUSIC, (void*)3 },
    { LVNS_SCRIPT_TIMER_INIT },

    { LVNS_SCRIPT_BG, (void*)49 },
    { LVNS_SCRIPT_FUNC, AddImage, "OP00.LF2" },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_PALETTE },
    { LVNS_SCRIPT_FUNC, start_sakura },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)2500 },
    { LVNS_SCRIPT_LOOP_FUNC, album_out },
    { LVNS_SCRIPT_WAIT, (void*)200 },

    { LVNS_SCRIPT_FUNC, AddImage, "OP01.LF2" },
    { LVNS_SCRIPT_LOOP_FUNC, album_in },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)6500 },
    { LVNS_SCRIPT_LOOP_FUNC, album_out },
    { LVNS_SCRIPT_WAIT, (void*)200 },

    { LVNS_SCRIPT_FUNC, AddImage, "OP02.LF2" },
    { LVNS_SCRIPT_LOOP_FUNC, album_in },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)10500 },
    { LVNS_SCRIPT_LOOP_FUNC, album_out },
    { LVNS_SCRIPT_WAIT, (void*)200 },

    { LVNS_SCRIPT_FUNC, AddImage, "OP03.LF2" },
    { LVNS_SCRIPT_LOOP_FUNC, album_in },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)14000 },

    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_FADE_PALETTE },
    { LVNS_SCRIPT_FUNC, stop_sakura },

    { LVNS_SCRIPT_FUNC, init_sky },
    { LVNS_SCRIPT_WHITEOUT },
    { LVNS_SCRIPT_LOOP_FUNC, sky },

    { LVNS_SCRIPT_TIMER_WAIT, (void*)42000 },

    { LVNS_SCRIPT_FUNC, AddImage3, "TITLE.LF2" },
    { LVNS_SCRIPT_LOOP_FUNC, show_title },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)49000 },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_FADE_PALETTE },
    { LVNS_SCRIPT_FUNC, stop_sakura },

#define RPOS (void *)1
#define LPOS (void *)0

    /* あかり */
    { LVNS_SCRIPT_BG, (void*)35 }, /* 校門(内側) */
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0181, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0182, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0186, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT,(void*)(50000 + 6250) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    /* 先輩 */
    { LVNS_SCRIPT_BG, (void*)9 }, /* 渡り廊下 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0202, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0204, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0203, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(50000 + 6250*2) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    /* いいんちょ */
    { LVNS_SCRIPT_BG, (void*)15 }, /* 屋上 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0301, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0303, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0302, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(50000 + 6250*3) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    /* 志保 */
    { LVNS_SCRIPT_BG, (void*)21 }, /* 坂道 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0402, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0403, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0401, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 }, 
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(50000 + 6250*4) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    /* 葵 */
    { LVNS_SCRIPT_BG, (void*)29 }, /* 神社 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0501, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0508, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x050C, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(50000 + 6250*5) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    /* マルチ */
    { LVNS_SCRIPT_BG, (void*)10 }, /* 図書室 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0604, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0603, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar,(void*) 0x0602, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(50000 + 6250*6) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    /* 琴音 */
    { LVNS_SCRIPT_BG, (void*)26 }, /* 公園 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0701, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0702, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0706, RPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(50000 + 6250*7) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    /* レミィ */
    { LVNS_SCRIPT_BG, (void*)14 }, /* 中庭 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar,(void*) 0x0801, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0802, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)600 },
    { LVNS_SCRIPT_FUNC, LoadChar, (void*)0x0803, LPOS },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_MASK, (void*)0 },
    { LVNS_SCRIPT_WAIT, (void*)1000 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(50000 + 6250*8) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V31.LF2" }, /* いいんちょ */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(100000 + 3250) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V70.LF2" }, /* 琴音 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(100000 + 3250*2) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V50.LF2" }, /* 葵 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(100000 + 3250*3) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V41.LF2" }, /* 志保 */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(100000 + 3250*4) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V60.LF2" }, /* マルチ */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(100000 + 3250*5) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V80.LF2" }, /* レミィ */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(100000 + 3250*6) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V20.LF2" }, /* せんぱい */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },
    { LVNS_SCRIPT_TIMER_WAIT, (void*)(100000 + 3250*7) },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_SLIDE_LTOR },

    { LVNS_SCRIPT_FUNC, LoadImage, "V12.LF2" }, /* あかり */
    { LVNS_SCRIPT_DISP,  (void*)LVNS_EFFECT_SLIDE_LTOR, (void*)0 },

    { LVNS_SCRIPT_TIMER_WAIT, (void*)126000 },

    { LVNS_SCRIPT_WHITEOUT },
    { LVNS_SCRIPT_WAIT, (void*)200 },
    { LVNS_SCRIPT_BG, (void*)17 },
    { LVNS_SCRIPT_FUNC, AddImage3, "TITLE.LF2" },
    { LVNS_SCRIPT_FUNC, start_sakura2 },
    { LVNS_SCRIPT_WHITEIN },
    { LVNS_SCRIPT_WAIT_CLICK },
    { LVNS_SCRIPT_FUNC, end },
    { LVNS_SCRIPT_EXIT },

    /* OP を中断した場合 … */
    { LVNS_SCRIPT_CLICK_JUMP },
    { LVNS_SCRIPT_MUSIC_FADE },
    { LVNS_SCRIPT_CLEAR, (void*)LVNS_EFFECT_FADE_PALETTE },
    { LVNS_SCRIPT_BG, (void*)17 },
    { LVNS_SCRIPT_FUNC, AddImage3, "TITLE.LF2" },
    { LVNS_SCRIPT_FUNC, start_sakura2 },
    { LVNS_SCRIPT_DISP, (void*)LVNS_EFFECT_FADE_PALETTE },
    { LVNS_SCRIPT_WAIT_CLICK },
    { LVNS_SCRIPT_FUNC, end },
    { LVNS_SCRIPT_END },
};

/* ToHeart オープニング */
void
ToHeartOpening(Lvns *lvns)
{
	LvnsScriptRun(lvns, opdata);
	LvnsMenu(lvns, &title_menu, False);
}

/* ------------------------------------------------------------ */

/* ToHeartタイトル用スクリプト */
static LvnsScriptData titledata[] = {
    { LVNS_SCRIPT_BG, (void*)17 },
    { LVNS_SCRIPT_FUNC, AddImage3, "TITLE.LF2" },
    { LVNS_SCRIPT_FUNC, start_sakura },
    { LVNS_SCRIPT_DISP, (void *)LVNS_EFFECT_FADE_PALETTE },
    { LVNS_SCRIPT_WAIT_CLICK },
    { LVNS_SCRIPT_END }
};

void
ToHeartTitle(Lvns *lvns)
{
    LvnsScriptRun(lvns, titledata);
	LvnsMenu(lvns, &title_menu, False);
}



