/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart_menu.c,v 1.2 2002/07/29 05:24:39 go Exp $
 *
 */

#pragma setlocale("English")

/*
 * ToHeart �����������˥塼ɽ��
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "toheart.h"

/* ------------------------------------------------------------ */
/** �����������ѥ�˥塼 */

static MenuLine from_first_menu_line[] = {
	MENULINE(8, "³������Ϥ��", 1),
	MENULINE(9, "��ᤫ��Ϥ��", 2),
	MENULINE(0, NULL, 0),
};

static MenuData from_first_menu = {
	from_first_menu_line,
	2, 1,
	NULL,
};

/* ------------------------------------------------------------ */
/** �����ֳ�ǧ�ѥ�˥塼 */

static MenuLine save_confirm_menu_line[] = {
    MENULINE(4, "�����֤��ޤ���", 0),
    MENULINE(5, "������Ǥ�����", 0),
    MENULINE(7, "�Ϥ�",1),
    MENULINE(8, "������", 2),
	MENULINE(0, NULL, 0),
};

static MenuData save_confirm_menu = {
	save_confirm_menu_line,
	2, 0, 
	NULL,
};

/* ------------------------------------------------------------ */
/** ���ɳ�ǧ�ѥ�˥塼 */

static MenuLine load_confirm_menu_line[] = {
    MENULINE(4, "���ɤ��ޤ���", 0),
    MENULINE(5, "������Ǥ�����", 0),
    MENULINE(7, "�Ϥ�",1),
    MENULINE(8, "������", 2),
	MENULINE(0, NULL, 0),
};

static MenuData load_confirm_menu = {
	load_confirm_menu_line,
	2, 0, 
	NULL,
};

/* ------------------------------------------------------------ */
/** �������˥塼���� */

/** �������˥塼���ΰ���� */
static MenuLine siori_menu_line[] = {
	{ 64, 40+86*0, 512, 82, "", 1 },
	{ 64, 40+86*1, 512, 82, "", 2 },
	{ 64, 40+86*2, 512, 82, "", 3 },
	{ 64, 40+86*3, 512, 82, "", 4 },
	{ 64, 40+86*4, 512, 82, "", 5 },
	{ 0, 0, 0, 0, NULL, 0 },
};

/* ���ɽ�� */
static void
box(Lvns *lvns, int x, int y, int w, int h, int b, int idx)
{
    int i;
    for (i=0;i<b;i++) {
        lvns->drawBox(lvns, x+i, y+i, w-2*i, h-2*i, idx);
    }
}

/* �ֹ������ */
static void
setnum(char *p, int no)
{
    char num[] = "����";

    if (no / 10) {
        *p++ = num[2];
        *p++ = num[3] + no/10;
    } else {
        *p++ = num[0];
        *p++ = num[1];
    }
    *p++ = num[2];
    *p   = num[3] + no%10;
}

/**
 * ����������Ѳ���ɽ��
 */
#ifdef USE_MGL
#define LvnsDrawString(l,x,y,s,c) LvnsDrawString(l,(x)/2,(y)/2,s,c) 
#endif
static void
fileMenuDisp(Lvns *lvns)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    int i;
    char name[] = "�����ꡡ�����ҥ�"; /* XXX ��ȴ���� */
    char date[] = "�������������������ʬ";

    for (i=0;i<5;i++) {
        time_t clock = state->sioris[i];
        struct tm *tm = localtime(&clock);
        int y;
        name[9]++;
        box(lvns, 64+2, (y=40+i*86)+2, 512, 82, 4, TOHEART_COL_BLACK);

        setnum(date +  0, tm->tm_mon+1);
        setnum(date +  6, tm->tm_mday);
        setnum(date + 12, tm->tm_hour);
        setnum(date + 18, tm->tm_min);
		
        if (i+1 == lvns->text_cursor_state) {
            box(lvns, 64,   y,   512, 82, 4, TOHEART_COL_WHITE);
            LvnsDrawString(lvns, 64+32, y+16, name, 0);
            LvnsDrawString(lvns, 64+32+24*7, y+16+30, date, 0);
        } else {
            box(lvns, 64,   40+i*86,   512, 82, 4, TOHEART_COL_GRAY);
            LvnsDrawString(lvns, 64+32, y+16, name, 1);
            LvnsDrawString(lvns, 64+32+24*7, y+16+30, date, 1);
        }
    }
}
#undef LvnsDrawString

/* ------------------------------------------------------------ */
/** ��������¸��˥塼���� */

static int
SioriSaveMenuEngine(Lvns *lvns, int select)
{
	switch (LvnsMenu(lvns, &save_confirm_menu, True)) {
	case -1: /* cancel */
	case 2:			
		break;
	case 1:
		/* �����ֽ��� */
		ToHeartSaveCommon(lvns);
		ToHeartSave(lvns, select);
		break;
	}
	return select;
}

static void
SioriSaveMenuDisp(Lvns *lvns, MenuData *data)
{
    LvnsDrawString(lvns, XPOS(2,0), YPOS(0), 
				   "�����֤��뤷��������򤷤Ƥ�������", 0);
    fileMenuDisp(lvns);
}

static MenuData siori_save_menu = {
	siori_menu_line,
	5, 0, 
	SioriSaveMenuEngine,
	SioriSaveMenuDisp
};

/* ------------------------------------------------------------ */
/** �������ɤ߹��ߥ�˥塼 */

static int
SioriLoadMenuEngine(Lvns *lvns, int select)
{
	switch (LvnsMenu(lvns, &load_confirm_menu, True)) {
	case -1: /* cancel */
	case 2:			
		break;
	case 1:
		/* ���ɽ��� */
		ToHeartLoadCommon(lvns);
		ToHeartLoad(lvns, select);
		LvnsClear(lvns, LVNS_EFFECT_WIPE_TTOB);
		LvnsJump(lvns, LVNS_JUMP_RESTART);
		break;
	}
	return select;
}

/**
 * ���ɥ�˥塼ɽ���� 
 */
static void
SioriLoadMenuDisp(Lvns *lvns, MenuData *data)
{
    LvnsDrawString(lvns, XPOS(2,0), YPOS(0), 
				   "���ɤ��뤷��������򤷤Ƥ�������", 0);
    fileMenuDisp(lvns);
}

static MenuData siori_load_menu = {
	siori_menu_line,
	5, 0, 
	SioriLoadMenuEngine,
	SioriLoadMenuDisp,
};

/* ------------------------------------------------------------ */
/** �����ȥ��Ѥ������ɤ߹��ߥ�˥塼 */

static int
TitleSioriLoadMenuEngine(Lvns *lvns, int select)
{
	ToHeartLoadCommon(lvns);
	ToHeartLoad(lvns, select);
	if (lvns->savepoint.scn) { /* ���ʥꥪ����Ƭ��? */
		switch (LvnsMenu(lvns, &from_first_menu, True)) {
		case -1: /* cancel */
			return False;
		case 1:
			break;
		case 2:			
			ToHeartScenarioInit(lvns);
		}
	}
	LvnsClear(lvns, LVNS_EFFECT_FADE_PALETTE);
	LvnsJump(lvns, LVNS_JUMP_RESTART);

	return select;
}

MenuData toheart_title_load_menu = {
	siori_menu_line,
	5, 0, 
	TitleSioriLoadMenuEngine,
	SioriLoadMenuDisp,
};

/* ------------------------------------------------------------ */
/** ��λ��ǧ��˥塼 */

static MenuLine end_confirm_menu_line[] = {
    MENULINE(4, "��λ���ޤ���", 0),
    MENULINE(5, "������Ǥ�����", 0),
    MENULINE(7, "�Ϥ�",1),
    MENULINE(8, "������", 2),
	MENULINE(0, NULL, 0),
};

static MenuData end_confirm_menu = {
	end_confirm_menu_line,
	2, 0, 
	NULL,
};


/* ------------------------------------------------------------ */
/** �ᥤ���˥塼 */

static MenuLine toheart_menu_line[] = {
	MENULINE(5, "ʸ����ä�",1),
	MENULINE(6, "���ɤ���", 2),
	MENULINE(7, "�����֤���", 3),
    MENULINE(8, "���ʥꥪ����", 4),
    MENULINE(9, "����������������", 5),
    MENULINE(10, "�����ཪλ", 6),
    MENULINE(0, NULL, 0),
};

static void
ToHeartMenuDisp(Lvns *lvns, MenuData *data)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    char date[] = "�����������";
    int mon;
    int day = state->flag[TOHEART_FLAG_DATE];
    if (day <= 31) {
        mon = 3;
    } else if (day <= 61) {
        mon = 4;
        day -= 31;
    } else {
        mon = 5;
        day -= 61;
    }
    setnum(date, mon);
    setnum(date+6,day);

    LvnsDrawStringCenter(lvns, YPOS(3), date, 0);
	LvnsDefaultMenuDisp(lvns, data);
}

static int
ToHeartMenuEngine(Lvns *lvns, int select)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    switch (select) {
    case 1:
		LvnsImageMode(lvns);
		break;

    case 2:
		/* ���� */
		ToHeartSioriDate(lvns);
		if (LvnsMenu(lvns, &siori_load_menu, True) <= 0)
			return 0;
		break;

    case 3:
        /* ������ */
		ToHeartSioriDate(lvns);
		if (LvnsMenu(lvns, &siori_save_menu, True) <= 0)
			return 0;
		break;

	case 4:
		/* ���ۥ⡼�� */
		LvnsHistoryMode(lvns);
		break;
		
    case 5:
        /* ��������� */
        lvns->savepoint = lvns->selectpoint;
        memcpy(state->flag_save, state->flag_select, sizeof state->flag);
		LvnsClear(lvns, LVNS_EFFECT_WIPE_TTOB);
		LvnsJump(lvns, LVNS_JUMP_RESTART);

    case 6:
        /* �����ȥ����� */
		switch (LvnsMenu(lvns, &end_confirm_menu, True)) {
		case -1: /* cancel */
			return 0;
		case 1:
			LvnsClear(lvns, LVNS_EFFECT_WIPE_TTOB);
			LvnsJump(lvns, LVNS_JUMP_TITLE);
		case 2:			
			break;
		}
		break;

    default:;
    }
	return select;
}

MenuData toheart_menu = {
	toheart_menu_line,
	6, 0, 
	ToHeartMenuEngine,
	ToHeartMenuDisp
};

