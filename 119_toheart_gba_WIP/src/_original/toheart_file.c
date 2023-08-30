/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart_file.c,v 1.2 2002/07/29 05:24:39 go Exp $
 *
 */

/* 
 * ToHeart しおり処理用
 */

#include <stdio.h>
#include "toheart.h"

/**
 * ファイル名の決定
 */
static void
ToHeartFileName(Lvns *lvns, char *dst, size_t len, int no)
{
    snprintf(dst, len, "%s/toheart%d.dat", lvns->savedata_path, no);
}

#define PUTLONG(d,fp) putc(((d) >> 24) & 0xff, fp); putc(((d) >> 16) & 0xff, fp); putc(((d) >> 8) & 0xff, fp); putc(((d) >> 0) & 0xff, fp)

#define PUTWORD(d,fp) putc(((d) >> 8) & 0xff, fp); putc(((d) >> 0) & 0xff, fp)

static int
getword(FILE *fp)
{
    int h = getc(fp);
    return h<<8 | getc(fp);
}

void
ToHeartSioriDate(Lvns *lvns)
{
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    for (i=0;i<5;i++) {
        char name[FILENAME_MAX];
        ToHeartFileName(lvns, name, sizeof name, i);
        state->sioris[i] = lvns->getFileTime(lvns, name);
    }
}


/*
 * 共通しおりへの状態の保存
 */
void
ToHeartSaveCommon(Lvns *lvns)
{
    char name[FILENAME_MAX];
    FILE *fp;
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;
   
    ToHeartFileName(lvns, name, sizeof name, 99);
    dprintf((stderr, "save: %s\n", name));

    if ((fp = fopen(name, "w")) == NULL) {
	perror("ToHeartSave");
	return;
    }

    /* エンディングフラグ */
    putc(state->flag[0x50], fp); 
    putc(state->flag[0x51], fp);

    /* 未見フラグ */
    for (i=0; i<sizeof state->seen_flag / sizeof state->seen_flag[0];i++) {
	putc(state->seen_flag[i], fp);
    }

    fclose(fp);
}

/**
 * しおりへの状態の保存
 */
void
ToHeartSave(Lvns *lvns, int no)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    char name[FILENAME_MAX];
    FILE *fp;
    int i;
   
    ToHeartFileName(lvns, name, sizeof name, no-1);
    dprintf((stderr, "save: %s\n", name));

    if ((fp = fopen(name, "w")) == NULL) {
	perror("ToHeartSave");
	return;
    }

    /* シナリオ番号    */
    PUTWORD(lvns->savepoint.scn, fp);

    /* ブロック番号 */  
    PUTWORD(lvns->savepoint.blk, fp);
    
    /* シナリオのオフセット */
    PUTLONG(lvns->savepoint.scn_offset, fp);

    /* 画像状態 */
    PUTWORD(lvns->savepoint.bg_no,     fp);
    PUTWORD(lvns->savepoint.character_no[0],   fp);
    PUTWORD(lvns->savepoint.character_no[1],   fp);
    PUTWORD(lvns->savepoint.character_no[2],   fp);
    putc(lvns->savepoint.bg_type,      fp);

    /* BGM の状態 */
    putc(lvns->savepoint.current_music, fp);

    /* 制御フラグ */
    for (i=0; i<TOHEART_FLAG_NO;i++) {
	putc(state->flag_save[i], fp);
    }

    fclose(fp);
}

/*
 * 共通しおりからのロード
 */
void
ToHeartLoadCommon(Lvns *lvns)
{
    char name[FILENAME_MAX];
    FILE *fp;
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    ToHeartFileName(lvns, name, sizeof name, 99);
    dprintf((stderr, "load: %s\n", name));

    if ((fp = fopen(name, "r")) == NULL) {
        ToHeartSioriInit(lvns);
	return;
    }
    
    state->flag[0x50] = getc(fp); /* エンディングフラグ */
    state->flag[0x51] = getc(fp);

    /* 未見フラグ */
    for (i=0; i<sizeof state->seen_flag / sizeof state->seen_flag[0];i++) {
	state->seen_flag[i] = getc(fp);
    }

    fclose(fp);
}


/**
 * しおりからの状態のロード
 */
void
ToHeartLoad(Lvns *lvns, int no)
{
    char name[FILENAME_MAX];
    FILE *fp;
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    ToHeartFileName(lvns, name, sizeof name, no-1);
    dprintf((stderr, "load: %s\n", name));

    if ((fp = fopen(name, "r")) == NULL) {
        ToHeartScenarioInit(lvns);
	return;
    }

    /* 現在のシナリオ番号    */
    lvns->savepoint.scn = getword(fp);

    /* 現在のブロック番号    */
    lvns->savepoint.blk = getword(fp);

    /* シナリオオフセット */
    {
        int a,b,c,d;
        a = getc(fp);
        b = getc(fp);
        c = getc(fp);
        d = getc(fp);
        lvns->savepoint.scn_offset = (a <<24) + (b<<16) + (c<<8) + d;
    }

    /* 画像状態 */
    lvns->savepoint.bg_no     = getword(fp);
    lvns->savepoint.character_no[0] = getword(fp);
    lvns->savepoint.character_no[1] = getword(fp);
    lvns->savepoint.character_no[2] = getword(fp);
    lvns->savepoint.bg_type   = getc(fp);

    /* BGM の状態 */
    lvns->savepoint.current_music = getc(fp);

    /* 制御フラグ */
    for (i=0; i<TOHEART_FLAG_NO;i++) {
	state->flag_save[i] = getc(fp);
    }

    fclose(fp);
}


