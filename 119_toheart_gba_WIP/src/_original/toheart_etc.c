/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart_etc.c,v 1.2 2002/07/29 05:24:39 go Exp $
 */

/* 
 * ToHeart 各種処理ルーチン
 */

#include <stdio.h>
#include <stdlib.h>
#include "toheart.h"

/*
 * ToHeart キャラ/背景合成処理 
 */
void
ToHeartMergeCharacter(Lvns *lvns)
{
	static int xpos[3] = { 0, 320, 160 };
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    int bgtime = lvns->bg_no / 50;
    int cno = lvns->vram->palette_num;

	if (state->title) {
		lvnsimage_set_palette3(lvns->vram,
							   state->title->palette, cno,
							   state->title->palette_num);
		lvnsimage_add_mask(state->title, lvns->vram, 0, 0, 
						   state->title_mask, cno);	
		lvns->vram->palette_num += state->title->palette_num;
	} else {
		int i;
		for (i=0;i<2;i++) {
			int pos = state->colflag[i];
			if (pos >= 0 && state->character[pos]) {
				lvnsimage_set_palette4(lvns->vram, 
									   state->charpal[lvns->character_no[pos]>>8][bgtime],
									   cno, 48);
				lvnsimage_add4(state->character[pos],
							   lvns->vram, xpos[pos], 0, cno);
				cno = lvns->vram->palette_num = cno + 48;
			}
        }
    }
}

/*
 * ToHeart 画像消去 
 */
void
ToHeartClearScreen(Lvns *lvns)
{
    ToHeartLoadBG(lvns, 0);
    ToHeartClearCharacter(lvns, 3);
}

static void
set_colflag(Lvns *lvns, int pos)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
	if (state->colflag[0] < 0 || state->colflag[0] == pos) {
		state->colflag[0] = pos;
	} else if (state->colflag[1] < 0 || state->colflag[1] == pos) {
		state->colflag[1] = pos;
	} else {
		fprintf(stderr, "warning: can't load 3 characters");
	}
}

/*
 * ToHeart キャラクタロード
 */
void
ToHeartLoadCharacter(Lvns *lvns, int no, int pos)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    char name[100];

    if (no == 0xffff) {
        ToHeartClearCharacter(lvns, pos);
        return;
    }

    /* あかり専用処理 */
    if ((no >> 8) == 0) {
        if ((state->flag[TOHEART_FLAG_AKARI] & 0x01)) { /* 髪型変更 */
            no |= 0x80;
        }
        no |= 0x100;
    } 
    sprintf(name, "C%04x.LF2", no);

	lvnsimage_delete(state->character[pos]);
	state->character[pos] = LvnsLoadImage(lvns, name, NULL);
	set_colflag(lvns, pos);
	lvns->character_no[pos] = no;
}

static void
clear_colflag(Lvns *lvns, int pos)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
	if (state->colflag[0] == pos)
		state->colflag[0] = -1;
	if (state->colflag[1] == pos)
		state->colflag[1] = -1;
}

/*
 * ToHeart キャラクタ消去 
 */
void
ToHeartClearCharacter(Lvns *lvns, int pos)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
	if (pos > 2) {
		int i;
		lvnsimage_delete(state->title);
		state->title = NULL;
		for (i=0;i<3;i++) {
			lvnsimage_delete(state->character[i]);
			state->character[i]   = NULL;
			lvns->character_no[i] = NOCHARACTER;
		}
		state->colflag[0] = -1;
		state->colflag[1] = -1;
	} else {
		lvnsimage_delete(state->character[pos]);
		state->character[pos] = NULL;
		clear_colflag(lvns, pos);
		lvns->character_no[pos] = NOCHARACTER;
	}
}

/*
 * ToHeart 背景画像ロード
 */
void
ToHeartLoadBG(Lvns *lvns, int no)
{
    static u_char haikeiflag[] = { 'D', 'E', 'N', 'X', };
    static char name[20] = "S%02dD.LF2";

    lvns->bg_type = LVNS_BACKGROUND;
    lvns->bg_no   = no;

    if (no == 0) {
        lvnsimage_clear(lvns->background);
    } else if (no == 254) {
		char pal[] = {255,255,255};
		lvnsimage_set_palette(lvns->background, pal, 1);
        lvnsimage_clear_index(lvns->background, 0);
    } else {
        name[5] = haikeiflag[no / 50];
        LvnsLoadBackground(lvns, name, no % 50);
    }
    ToHeartClearCharacter(lvns, 3);
}

/* 
 * ToHeart 通常ビジュアルシーンロード
 */
void
ToHeartLoadVisual(Lvns *lvns, int no)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    lvns->bg_type = LVNS_VISUAL;
    lvns->bg_no   = no;
    if (no == 0) {
        lvnsimage_clear(lvns->background);
    } else {
        /* あかりの髪型処理… */
        if ((no == 0x11 || no == 0x13) && 
            (state->flag[TOHEART_FLAG_AKARI] & 0x01)) {
            no = 0x12;
        }
        /* レミィパンティ */
        if (no == 0x80) {
        }
        LvnsLoadBackground(lvns, "V%02x.LF2", no);
    }
    ToHeartClearCharacter(lvns, 3);
}

/* 
 * ToHeart Hビジュアルシーンロード
 */
void
ToHeartLoadHVisual(Lvns *lvns, int no)
{
    lvns->bg_type = LVNS_HCG;
    lvns->bg_no   = no;
    LvnsLoadBackground(lvns, "H%02x.LF2", no);
    ToHeartClearCharacter(lvns, 3);
}

/*
 * ToHeart シナリオのテキストロード 
 */
void
ToHeartSetTextScenarioState(Lvns *lvns, int no)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    /* 既読情報登録 */
    if (!lvns->seen_mode && 
        !(state->seen_flag[lvns->scn_current/8] & (1 << (lvns->scn_current%8)))) {
		lvns->seen = False;
        if (!lvns->force_skip)
            lvns->skip = False; /* すっ飛ばし解除 */
        lvns->fast_text = False;
    } else {
		lvns->seen = True;
		if (lvns->fast_when_seen)
			lvns->fast_text = True; /* 見た文書は速く表示する */
	}
}

void
ToHeartLoadScenario(Lvns *lvns, int no, int blk)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    /* 現在のシナリオを既読化… */
    state->seen_flag[lvns->scn_current/8] |= (1 << (lvns->scn_current%8));
    LvnsLoadScenario(lvns, no, blk);
}

#ifndef USE_MGL
static void
drawChar(Lvns *lvns, int x, int y, int code, int attr) 
{
    u_char *data = lvns->leaf_font_data + (code - 1) * 24 * 3;
    lvns->putPattern2(lvns, x+1, y+1, TOHEART_COL_BLACK, data);
    lvns->putPattern2(lvns, x+2, y+1, TOHEART_COL_BLACK, data);
    if (!attr)
        lvns->putPattern2(lvns, x, y, TOHEART_COL_WHITE, data);
    else
        lvns->putPattern2(lvns, x, y, TOHEART_COL_GRAY, data);
}
#else
static void
drawChar(Lvns *lvns, int x, int y, int code, int attr) 
{
    static int black[] = {
	 COLOR_TRANSPARENT, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK
    };

    static int gray[] = {
	 COLOR_TRANSPARENT, 0x00000006, 0x00000007, 0x0000008
    };

    static int white[] = {
	 COLOR_TRANSPARENT, 0x00000008, 0x0000000c, 0x000000f
    };
#ifdef FONT_PLUS
    if( lvns->font){
        x += MGL_XOFFSET;
        y += MGL_YOFFSET;
        code--;

        lvnsfont_draw( lvns->font, x + 1, y + 1, code, black);
        if( !attr){
        	lvnsfont_draw( lvns->font, x, y, code, white);
        } else {
        	lvnsfont_draw( lvns->font, x, y, code, gray);
        }
     } else {
#endif /* FONT_PLUS */
    char buf[3];

#if 0
    if (lvns->skip && !attr)
      MglGetEvent(lvns, 1);
#endif

    buf[0] = lvns->leaf_to_euc[code * 2];
    buf[1] = lvns->leaf_to_euc[code * 2 + 1];
    buf[2] = 0;

    x += MGL_XOFFSET;
    y += MGL_YOFFSET;

    set_font(12, 0);

    set_color(COLOR_BLACK);
    draw_string(x + 1, y + 1, buf, DIR_NORTH);
    draw_string(x + 2, y + 1, buf, DIR_NORTH);

    if (!attr) {
	set_color(COLOR_WHITE);
    } else {
	set_color(COLOR_LIGHTGRAY);
    }
    draw_string(x, y, buf, DIR_NORTH);
#ifdef FONT_PLUS
    }
#endif /* FONT_PLUS */
}
#endif

/*
 * 仮想 VRAM に直接 EUC 文字列を描画
 */
#ifndef USE_MGL
void
ToHeartPutsVRAM(Lvns *lvns, int x, int y, const u_char *str, int idx) 
{
    int code;  
    u_char *data;
    while (*str) {
        code = ((str[0]&0x7f)-33) * 94 + (str[1]&0x7f)-33;
        code = lvns->jis_to_leaf[code];
        data = lvns->leaf_font_data + (code - 1) * 24 * 3;
        lvnsimage_put_pattern24(lvns->vram, x, y, idx, data);
        x += 24;
        str += 2;
    }
}
#else
void
ToHeartPutsVRAM(Lvns *lvns, int x, int y, const u_char *str, int color) 
{
  mglimage_draw_string(lvns->vram, x, y, str, color);
}
#endif

/*
 * テキストレイヤに直接 EUC 文字列を描画
 */
void
ToHeartPutsTEXT(Lvns *lvns, int x, int y, const u_char *str, int attr) 
{
    int code;  
    u_char *data;
    while (*str) {
        code = ((str[0]&0x7f)-33) * 94 + (str[1]&0x7f)-33;
        code = lvns->jis_to_leaf[code];
        drawChar(lvns, x, y, code, attr);
        x += 24;
        str += 2;
    }
}

static
LvnsCommandInfo command[] = {
    { "select",  False },   /* 次の選択肢までとばす */
    { "image",  False },    /* 画像表示             */
    { "before", False },    /* 前の選択肢まで戻る */
    { "title",  False },    /* タイトルに戻る */
    { NULL,  False }
};

LvnsCommandInfo *
ToHeartGetCommandList(Lvns *lvns)
{
    command[0].enable =
	command[1].enable =
	command[2].enable =
	command[3].enable = False;

#if 0    
    if (lvns->scn_func == ToHeartScenarioEngine) {
        if (LVNSSTATE == LVNS_WAIT_KEY ||
            LVNSSTATE == LVNS_WAIT_PAGE ||
            LVNSSTATE == LVNS_WAIT_SELECT) {
            if (!lvns->select_mode) {
                command[0].enable = True;
            }
            command[1].enable = 
                command[2].enable =
                    command[3].enable = True;
        }
    }
#endif
    return command;
}

void
ToHeartExecCommand(Lvns *lvns, const char *command)
{
    if (!strcmp(command, "select")) {
		LvnsSkipTillSelect(lvns);
    } else if (!strcmp(command, "image")) {
		LvnsImageMode(lvns);
    } else if (!strcmp(command, "before")) {
        /* 選択肢に戻る */
		ToHeartState *state = (ToHeartState*)lvns->system_state;
		lvns->savepoint = lvns->selectpoint;
        memcpy(state->flag_save, state->flag_select, sizeof state->flag);
    } else if (!strcmp(command, "title")) {
        /* タイトルに戻る */
    }
}

void KizuatoJingle(Lvns *lvns);
extern MenuData toheart_menu;

static LvnsSystemState toheart_state_base = {
#ifndef USE_MGL
    640,
    480,
#else
    320,
    240,
#endif
    235, /* XXX */
    "LVNS3DAT.PAK",
    "LVNS3SCN.PAK",
    "%04x.SCN",
    "thfont.tbl",

	&toheart_menu,

	ToHeartStart,
	KizuatoJingle,
	ToHeartOpening,
	ToHeartTitle,
	ToHeartMain,

    ToHeartMergeCharacter,
    ToHeartClearScreen,
    ToHeartLoadBG,
    ToHeartGetCommandList,
    ToHeartExecCommand,
    drawChar,
	ToHeartDispHistory,

#if !defined(USE_MGL) || defined(FONT_PLUS)
    250, /* キー入力待ち */
    253  /* 改ページ待ち */
#else
    2770, /* キー入力待ち */
    1, /* 改ページ待ち */
#endif
};

void ToHeartInitialize(Lvns *lvns)
{
    ToHeartState *state;
      
    lvns->system_state = (ToHeartState *)malloc(sizeof(ToHeartState));
    state = lvns->system_state;

    state->state = toheart_state_base;

    state->sakura_num = 0;
    state->sakura_disp_num = 0;
    state->character[0] = NULL;
    state->character[1] = NULL;
    state->character[2] = NULL;
    state->title = NULL;
    state->title_mask = 16;
    state->roll = NULL;
    state->light = NULL;
    state->fast_calendar = False;
    state->fast_clock = False;
    ToHeartSioriInit(lvns);
}

