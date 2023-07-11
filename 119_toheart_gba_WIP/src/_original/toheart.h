/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart.h,v 1.3 2002/07/29 05:24:39 go Exp $
 *
 */

#ifndef __toheart_h
#define __toheart_h

#include "Lvns.h"
#include "LvnsEffect.h"
#include "LvnsAnim.h"
#include "LvnsScript.h"

#define TOHEART_SCN_NO  0xA96   /* シナリオの個数 */
#define TOHEART_FLAG_NO  256  /* フラグの個数   */

#define TOHEART_FLAG_EVENT_DONE 0xa6
#define TOHEART_FLAG_IDOU 0xaf

#define TOHEART_FLAG_DATE    0xab
#define TOHEART_FLAG_WEEKDAY 0xad
#define TOHEART_FLAG_TIME    0xae

#define TOHEART_FLAG_VSELECT_MSG 0xb1
#define TOHEART_FLAG_VSELECT_OFF 0xbd

#define TOHEART_FLAG_AKARI 0x01

#define TOHEART_FLAG_2D_SCN 0xf0
#define TOHEART_FLAG_2D_BLK 0xf2
#define TOHEART_FLAG_2F_SCN 0xf4
#define TOHEART_FLAG_2F_BLK 0xf6

#define TOHEART_COL_SAKURA 224

#ifndef USE_MGL
#define TOHEART_COL_BLACK  232
#define TOHEART_COL_GRAY   233
#define TOHEART_COL_WHITE  234
#else
#define TOHEART_COL_BLACK  COLOR_BLACK
#define TOHEART_COL_GRAY   COLOR_LIGHTGRAY
#define TOHEART_COL_WHITE  COLOR_WHITE
#endif

typedef u_char THCharPal[5][48][3];

/* ------------------------------------------------------- */

typedef struct {
    LvnsSystemState state;

    int seen_flag[(TOHEART_SCN_NO+7)/8]; /* シナリオ既読フラグ */

    /* フラグ情報 */
    int flag[TOHEART_FLAG_NO];
    int flag_save[TOHEART_FLAG_NO];
    int flag_select[TOHEART_FLAG_NO];

    /* 桜の状態 */
    int sakura_num;
    int sakura_disp_num;
    struct {
        enum { SAKURA_NONE, SAKURA_BEFORE, SAKURA_BACK } position;
        int x, y;
        int state;
    } sakura[50];
    
    /* キャラクタパレット情報 */
    THCharPal *charpal;

    /* キャラクタ合成用 */
    LvnsImage *character[3];

    /* その他合成用 */
    LvnsImage *title;
    int title_mask;

	int colflag[2]; /* キャラクタ表示用パレットの選択 */
	
    /* op 作業データ */
    LvnsImage *roll;    /* OP スクロール用バッファ */
    LvnsImage *light;   /* OP 光の輪 */

    int fast_calendar;  /* 日付を高速表示 */
    int calendar_day;
    int fast_clock;     /* 時間を高速表示 */

    time_t sioris[5];   /* 各しおりの日付情報 */

} ToHeartState;


void ToHeartScenarioInit(Lvns *lvns);
void ToHeartSioriInit(Lvns *lvns);
void ToHeartLoad(Lvns *lvns, int no);
void ToHeartSave(Lvns *lvns, int no);
void ToHeartLoadCommon(Lvns *lvns);
void ToHeartSaveCommon(Lvns *lvns);
void ToHeartSioriDate(Lvns *lvns);

void ToHeartStart(Lvns *lvns);
void ToHeartJingle(Lvns *lvns);
void ToHeartOpening(Lvns *lvns);
void ToHeartTitle(Lvns *lvns);
void ToHeartMain(Lvns *lvns);
void ToHeartEnding(Lvns *lvns);

/* toheart_sakura.c */
void ToHeartSakuraInit(Lvns *lvns);
void ToHeartSakuraSetNumber(Lvns *lvns, int num);
void ToHeartSakuraSetRandomNumber(Lvns *lvns, int num);
extern LvnsBackEffectInfo toHeartSakuraEffect;

/* toheart_rain.c */
extern LvnsBackEffectInfo toHeartRainEffect;

/* toheart_etc.c */
void ToHeartMergeCharacter(Lvns *lvns);
void ToHeartClearScreen(Lvns *lvns);

void ToHeartLoadCharacter(Lvns *lvns, int no, int pos);
void ToHeartClearCharacter(Lvns *lvns, int pos);
void ToHeartLoadBG(Lvns *lvns, int no);
void ToHeartLoadVisual(Lvns *lvns, int no);
void ToHeartLoadHVisual(Lvns *lvns, int no);
void ToHeartClearScreen(Lvns *lvns);

void ToHeartLoadScenario(Lvns *lvns, int no, int blk);
void ToHeartSetTextScenarioState(Lvns *lvns, int no);

void ToHeartPutsVRAM(Lvns *lvns, int x, int y, const u_char *str, int idx);
void ToHeartPutsTEXT(Lvns *lvns, int x, int y, const u_char *str, int atr);

extern MenuData toheart_title_load_menu;

void ToHeartDispHistory(Lvns *lvns, int pos);

#endif
