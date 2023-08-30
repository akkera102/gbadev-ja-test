/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart.c,v 1.4 2002/07/29 05:24:39 go Exp $
 *
 */

#pragma setlocale("English")

/*
 * To Heart ���ʥꥪ�������󥸥� 
 */

#include <stdio.h>
#include "toheart.h"

/* ���ץ��˥᡼����� */
static LvnsAnimationData clock_anim[] = {
    { LVNS_ANIM_IMAGE_ADD, "OC_00.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_01.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_02.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_03.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_04.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_05.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_06.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_07.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_08.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_09.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_10.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_11.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_12.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_13.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_14.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_15.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_16.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_17.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_18.LF2", 0, 160, 0 },
    { LVNS_ANIM_IMAGE_ADD, "OC_19.LF2", 0, 160, 0 },
    { LVNS_ANIM_NONE }
};

static struct {
    const char *name;
    LvnsImage *image;
} calendar_data[] = {
    { "CBAK.LF2" },
    { "CBAK_00.LF2"},
    { "CBAK_01.LF2"},
    { "CBAK_02.LF2"},
    { "CBAK_03.LF2"},
    { "CBAK_04.LF2"},
    { "CBAK_05.LF2"},
};

/* �����������˥᡼����� */
static LvnsAnimationData calendar_anim[] = {
    /* ���� */
    { LVNS_ANIM_IMAGE, NULL, 0, 0, 0},  /* �ط�  */
    { LVNS_ANIM_IMAGE_ADD, NULL, 10, 192, 80 },
    { LVNS_ANIM_IMAGE_ADD, NULL, 10, 192, 80 },
    { LVNS_ANIM_IMAGE_ADD, NULL, 10, 192, 80 },
    { LVNS_ANIM_IMAGE_ADD, NULL, 10, 192, 56 },
    { LVNS_ANIM_IMAGE_ADD, NULL, 10, 192, 24 },
    { LVNS_ANIM_IMAGE_ADD, NULL, 10, 192, 24 },
    { LVNS_ANIM_IMAGE_ADD, "CBAK_06.LF2", 10, 440, 24 },
    { LVNS_ANIM_IMAGE_ADD, "CBAK_07.LF2", 10, 584, 24 },
    { LVNS_ANIM_WAIT, NULL, 300 },
    { LVNS_ANIM_NONE }
};

/**
 * ̾���ǡ���
 */
static u_char names[][14] = {
    "ƣ��",
    "��Ƿ",
    "�ҥ�",
    "�Ҥ�椭",
    "�ҥ�業"
};

u_char         *posstr[] = {
    "��",
    "��",
    "���"
};

char *
FlgName(int c)
{
    static char     foo[10];
    switch (c) {
    case 0x00:
	return "<������٥�ȥӥå�>";
    case 0x01:
	return "<�����ꥤ�٥�ȥӥå�>";
    case 0x02:
	return "<�ܹᥤ�٥�ȥӥå�>";
    case 0x03:
	return "<�һҥ��٥�ȥӥå�>";
    case 0x04:
	return "<���ݥ��٥�ȥӥå�?>";
    case 0x06:
	return "<�ޥ�����٥�ȥӥå�?>";
    case 0x08:
	return "<��ߥ����٥�ȥե饰>";
    case 0x09:
	return "<��ߥ����٥�ȥ�����2?>";
    case 0x0c:
	return "<���ݥ��٥�ȥӥå�>";
    case 0x0d:
	return "<������vs���٥�ȥե饰>";
    case 0x0e:
	return "<��ߥ�ɬ�ܥ��٥�ȥե饰>";
    case 0x0f:
	return "<����¾vs���٥�ȥե饰>";
    case 0x11:
	return "���磻�٥�ȥӥå�";
    case 0x20:
	return "<�һҥ��٥���̲�>";
    case 0x14:
	return "<�����깥����>";
    case 0x15:
	return "<�ܹṥ����>";
    case 0x16:
	return "<�һҹ�����>";
    case 0x17:
	return "<���ݹ�����>";
    case 0x18:
	return "<��������>";
    case 0x19:
	return "<�ޥ��������>";
    case 0x1a:
	return "<�ײ�������>";
    case 0x1b:
	return "<��ߥ�������>";
    case 0x1d:
	return "<���﹥����>";
    case 0x1e:
	return "<�����������٥��>";
    case 0x1f:
	return "<�ܹ������٥��>";
    case 0x22:
	return "<��������٥��>";
    case 0x23:
	return "<�ޥ��������٥��>";
    case 0x24:
	return "<�ײ�������٥��>";
    case 0x27:
	return "<���磻�٥�ȥ�����>";
    case 0x29:
	return "<�ܹᥤ�٥�ȥ�����>";
    case 0x2a:
	return "<�һҥ��٥�ȥ�����>";
    case 0x2c:
	return "<�����٥�ȥ�����>";
    case 0x2d:
	return "<�ޥ�����٥�ȥ�����>";
    case 0x2e:
	return "<�ײ����٥�ȥ�����>";
    case 0x2f:
	return "<��ߥ����٥�ȥ�����>";
    case 0x33:
	return "<�ܹᥤ�٥�ȥ�����2>";
    case 0x34:
	return "<�һҥ��٥�ȥ�����2>";
    case 0x35:
	return "<�����٥�ȥ�����2>";
    case 0x37:
	return "<�ޥ�����٥�ȥ�����2>";
    case 0x38:
	return "<�ײ����٥�ȥ�����2>";
    case 0x39:
	return "<��ߥ����٥�ȥ�����2>";
    case 0x3b:
	return "<���磻�٥�ȥ�����>";
    case 0x3e:
	return "<�һҥ��٥�ȥ�����3>";
    case 0x42:
	return "<�ײ����٥�ȥ�����3>";
    case 0x4c:
	return "<�ײ����٥�ȥ�����4>";
    case 0x50:
	return "<����ǥ��󥰥ե饰1>";
    case 0x51:
	return "<����ǥ��󥰥ե饰2>";
    case 0xa6:
        return "<�������ι�ư�ѥե饰?>";
    case 0xab:
	return "<���ե�����>";
    case 0xac:
        return "<���ݸ��ư���֥ե饰>?";
    case 0xad:
	return "<����������>";
    case 0xae:
	return "<���֥�����>";
    case 0xaf:
        return "<���ݸ��ư�̥�����>?";
    }
    sprintf(foo, "flg:%02x", c);
    return foo;
}

char *
FlgBit(int flg, int c)
{
    static char     foo[10];
    switch (flg) {
    case 0x00:
	switch (c) {
	case 2:	    return "<����������Ƥ��줿����򲰾��>";
	case 6:
	    return "<�ײ������Ƚв�>";
	}
    case 0x01:
	switch (c) {
	case 0:
	    return "<ȱ���ѹ�>";
	case 1:
	    return "<��ٶ�>";
	case 2:
	    return "<����ι������>";
	case 3:
	    return "<���ٰ�����>";
	}
	break;
    case 0x02:
	switch (c) {
	case 0:
	    return "<4/1�ι����>";
	case 1:
	    return "<4/1�ι����Τ��ͤ�>";
	}
    case 0x04:
	switch (c) {
	case 0:
	    return "<�佬�������>";
	case 1:
	    return "<���饪���Ǿ���>";
	}
    case 0x06:
	switch (c) {
	case 0:
	    return "<´�ȼ���ޤ���>";
	}
    case 0x08:
	switch (c) {
	case 0:
	    return "<�ϥ󥿡����٥��1>";
	case 1:
	    return "<�ϥ󥿡����٥��2>";
	case 2:
	    return "<�ǡ�����«>";
	case 3:
	    return "<�ǡ���>";
	case 4:
	    return "<��ߥ��Ф���뤳�Ȥ�ʹ��>";
	case 5:
	    return "<�������٥��>";
	case 6:
	    return "<��ߥ����»Ҥ��ܤ�>";
	}
    case 0x0c:
	switch (c) {
	case 0:
	    return "<����ǥѥ�ĸ���>";
	case 1:
	    return "<�Ŀ;����>";
	case 2:
	    return "<��������>";
	case 3:
	    return "<��������Ǿ�����«>";
	case 4:
	    return "<��������Ǿ���>";
	case 5:
	    return "<��������Ǿ���2>";
	case 6:
	    return "<��ͤǥ��饪��>";
	}
    case 0x0d:
	switch (c) {
	case 0:
	    return "<vs�һ�>";
	case 1:
	    return "<vs��ߥ�>";
	case 2:
	    return "<vs��>";
	case 3:
	    return "<vs�ײ�>";
	case 4:
	    return "<vs����>";
	}
	break;
    case 0x0e:
	switch (c) {
	case 0:
	    return "<�������٥��>";
	case 1:
	    return "<��ƻ�����٥��>";
	case 2:
	    return "<��ߥ����»Ҥ��ܤ�>";
	case 3:
	    return "<��ߥ��ФȲ�>";
	case 4:
	    return "<ž������ΤǸ������ʤ���ߥ��˲�>";
	}
    case 0x0f:
	switch (c) {
	case 0:
	    return "<��vs�ײ�>";
	case 1:
	    return "<�һ�vs����>";
	case 2:
	    return "<�ܹ�vs�ޥ��>";
	case 3:
	    return "<�ޥ��vs��ߥ�>";
	}
    case 0x50:
	switch (c) {
	case 0:
	    return "<�����ꥨ���>";
	case 1:
	    return "<�ܹᥨ���>";
	case 2:
	    return "<�һҥ����>";
	case 3:
	    return "<���ݥ����>";
	case 4:
	    return "<�������>";
        case 5:
	    return "<�ޥ�������>";
	case 6:
	    return "<�ײ������>";
	case 7:
	    return "<��ߥ������>";
	}
    case 0x51:
	switch (c) {
	case 0:
	    return "<��˥����>";
	case 1:
	    return "<���泌���>";
	case 7:
	    return "<���ޤ����ʥꥪ>";
	}
    }
    sprintf(foo, "%d", c);
    return foo;
}

/**
 * ���ե����ȥѥ�᡼���Ѵ�
 */
static LvnsEffectType
text_effect(int no)
{
    static LvnsEffectType toheart_effect[] = {
        LVNS_EFFECT_FADE_PALETTE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_FADE_MASK,
        LVNS_EFFECT_FADE_SQUARE,
        LVNS_EFFECT_WIPE_SQUARE_LTOR,
        LVNS_EFFECT_FADE_MASK,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_WIPE_MASK_LTOR,
        LVNS_EFFECT_SLIDE_LTOR,

        LVNS_EFFECT_WIPE_LTOR,
        LVNS_EFFECT_NO_EFFECT,
        LVNS_EFFECT_FADE_MASK,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_TOP_SCROLL,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,

        LVNS_EFFECT_BLOOD,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,
        LVNS_EFFECT_NONE,

        LVNS_EFFECT_NONE,
        LVNS_EFFECT_FADE_PALETTE
    };

    LvnsEffectType ret;
    if (no == 255) {
        ret = LVNS_EFFECT_NONE;
    } else {
        ret = toheart_effect[no];
    }
    dprintf((stderr, "(%2d)%s\n", no, LvnsEffectName(ret)));
    return ret;
}

/*
 * bgm �ѥ�᡼���Ѵ�
 */
static int
bgmmap(int no)
{
    switch (no) {
    case 27:
        return 31;
    case 28:
        return 32;
    case 29:
        return 33;
    case 30:
        return 34;
    case 31:
        return 35;
    case 32:
        return 29; /* ??? */
    case 33:
        return 30;
    default:
        return no+2;
    }
}

/* ---------------------------------------------------------------- */
/* ������������ */

static void
init_calendar(Lvns *lvns)
{
    int i;
    for (i=0; i< sizeof calendar_data / sizeof calendar_data[0]; i++) {
        lvnsimage_copy(calendar_data[i].image,
                       calendar_anim[i].image);
    }
}

static void
set_calendar(Lvns *lvns, int day, int trans)
{
    char name[20];
    int i, col, mon, weekday;

    LvnsImage *week;
    LvnsImage *month;
    LvnsImage *day1;
    LvnsImage *day2;

    weekday = (day + 5) % 7;
   
    /* ���� */
    if (weekday == 0) {        /* ���� */
        col = 1;
    } else if (weekday == 6) { /* ���� */
        col = 2;
    } else {                                              /* ʿ�� */
        col = 0; 
    }

    if (day <= 31) {
        mon = 3;
    } else if (day <= 61) {
        mon = 4;
        day -= 31;
    } else {
        mon = 5;
        day -= 61;
    }

    snprintf(name, sizeof name, "CWEEK_%02d.LF2", weekday);
    week = LvnsLoadImage(lvns, name, NULL);
    snprintf(name, sizeof name, "CMON_%02d.LF2", mon);
    month = LvnsLoadImage(lvns, name, NULL);
#if 0
    dprintf((stderr, "day: %d\n", day));
#endif
    if (day <= 9) {
        snprintf(name, sizeof name, "CLNO_%02d.LF2", day);
        day1 = NULL;
        day2 = LvnsLoadImage(lvns, name, NULL);
    } else {
        snprintf(name, sizeof name, "CSNO_%02d.LF2", day / 10);
        day1 = LvnsLoadImage(lvns, name, NULL);
        snprintf(name, sizeof name, "CSNO_%02d.LF2", day % 10);
        day2 = LvnsLoadImage(lvns, name, NULL);
    }

    /* �������� */
    for (i=0; i< sizeof calendar_data / sizeof calendar_data[0]; i++) {
        if (day1) {
            lvnsimage_add3(day1, calendar_anim[i].image, 
                           232-calendar_anim[i].x, 
                           196-calendar_anim[i].y, 
                           col * 26,
                           trans, i);
            lvnsimage_add3(day2, calendar_anim[i].image, 
                           320-calendar_anim[i].x, 
                           196-calendar_anim[i].y, 
                           col * 26,
                           trans, i);
        } else {
            lvnsimage_add3(day2, calendar_anim[i].image, 
                           264-calendar_anim[i].x, 
                           196-calendar_anim[i].y, 
                           col * 26,
                           trans, i);
        }
        lvnsimage_add3(week, calendar_anim[i].image, 
                       280-calendar_anim[i].x, 
                       344-calendar_anim[i].y, 
                       col * 26,
                       trans, i);
        lvnsimage_add3(month, calendar_anim[i].image, 
                       200-calendar_anim[i].x, 
                       88-calendar_anim[i].y, 
                       col * 26,
                       trans, i);
    }

    lvnsimage_delete(week);
    lvnsimage_delete(month);
    lvnsimage_delete(day1);
    lvnsimage_delete(day2);
}

/*
 * ��������ɽ��
 * ���祵�������̾���᤯�ꢪ����
 */
static Bool
calendar(Lvns *lvns, int *effect_state)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    if (*effect_state < 16) {
        double ratio = (16 - *effect_state) / 4.0 + 1.0;
        int width  = WIDTH * ratio;
        int height = HEIGHT * ratio;
        lvnsimage_copy_palette(calendar_anim[0].image, lvns->vram);
        lvnsimage_copy_scale(calendar_anim[0].image, 0, 0, 
                             calendar_anim[0].image->rwidth,
                             calendar_anim[0].image->rheight,
                             lvns->vram, 
                             -(width-WIDTH)/2,
                             -(height-HEIGHT)/2,
                             width, height);
        lvns->setPaletteMulti(lvns, *effect_state);
        lvns->drawWindow(lvns);
        LvnsFlushWindow(lvns);
        (*effect_state)++;
        return False;
    } else if (*effect_state == 16)        {
		if (state->flag[TOHEART_FLAG_DATE] == state->calendar_day) {
			state->flag[TOHEART_FLAG_WEEKDAY] = 
				(state->flag[TOHEART_FLAG_DATE] + 5) % 7;
			lvnsimage_copy(lvns->vram, lvns->background);
			(*effect_state)++;
		} else {
			init_calendar(lvns);
			set_calendar(lvns, state->flag[TOHEART_FLAG_DATE]++, 209);
			set_calendar(lvns, state->flag[TOHEART_FLAG_DATE], 211);
			// lvns->anim_data = calendar_anim;
        }
        return False;
    } else if (!state->fast_calendar && *effect_state <= 32) {
        int st = 32 - *effect_state;
        double ratio = (16 - st) / 4.0 + 1.0;
        int width  = WIDTH * ratio;
        int height = HEIGHT * ratio;
        lvnsimage_copy_palette(lvns->background, lvns->vram);
        lvnsimage_copy_scale(lvns->background, 0, 0, 
                             lvns->background->rwidth,
                             lvns->background->rheight,
                             lvns->vram, 
                             -(width-WIDTH)/2,
                             -(height-HEIGHT)/2,
                             width, height);
        lvns->setPaletteMulti(lvns, st);
        lvns->drawWindow(lvns);
        LvnsFlushWindow(lvns);
        (*effect_state)++;
        return False;
    } else {
        lvnsimage_clear(lvns->background);
        return True;
    }
}

/* ---------------------------------------------------------------- */

/**
 * ���ʥꥪ�����
 */
void
ToHeartScenarioInit(Lvns *lvns)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    int i;

    /* �����־��־��ֽ���� */
    LvnsInitSavePoint(lvns, &lvns->savepoint);

    for (i=0; i<TOHEART_FLAG_NO; i++) {
        state->flag_save[i] = 0;
    }
    
    state->flag_save[TOHEART_FLAG_DATE] = 3;
    state->flag_save[TOHEART_FLAG_WEEKDAY] = 
        (state->flag_save[TOHEART_FLAG_DATE] + 5) % 7;
}

/**
 * ���������� (���ե饰�õ�)
 * ToHeart�����������Ʊ���˽��������
 */
void
ToHeartSioriInit(Lvns *lvns)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    int i;
    
    /* ���ʥꥪ�ǡ�������� */
    ToHeartScenarioInit(lvns);

    /* ̤���ե饰���õ� */
    for (i=0;i<sizeof state->seen_flag / sizeof state->seen_flag[0];i++) {
        state->seen_flag[i] = 0;
    }

    /* �Ĥ������ե饰�ξõ� */
}

static void TextParser(Lvns *lvns, int no, Bool history_mode);

/*
 * ToHeart ���ޥ�ɽ���
 */
#define c (*p)
static int
CommandParser(Lvns *lvns, const u_char **p, Bool history_mode)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    switch (c[0]) {
    case 0x20:
        dprintf((stderr, "[END()]\n"));	/* ���ʥꥪ��λ */
        c++;
        return True;

    case 0x21:
        if (c[1] == 3) {
            ToHeartState *state = (ToHeartState *)lvns->system_state;
            dprintf((stderr, "[�����ȥ����? 0x21,0x03]\n"));

			if (!history_mode) {
				// ��������ط�
				ToHeartLoadBG(lvns, 254);
				
				// �����ȥ��
				lvnsimage_delete(state->title);
				state->title = LvnsLoadImage(lvns, "TITLE2.LF2", NULL);
				state->title_mask = 16;
				lvns->latitude = 16;
				
				ToHeartSakuraSetRandomNumber(lvns, 40);
				LvnsSetBackEffect(lvns, &toHeartSakuraEffect);
				LvnsWhiteIn(lvns);
				LvnsWait(lvns, 120);

				lvnsimage_delete(state->title);
				state->title = NULL;
			}
            c += 2;
        } else if (c[1] == 8) { /* �� �����ꥷ�ʥꥪ���פ����Ѥ���� */
            dprintf((stderr, "[�����ꥷ�ʥꥪ���� 0x21,0x08,%x,%x,%x,%x]\n",
                     c[2],c[3],c[4],c[5]));
            c += 6;
        }
        break;

    case 0x23:
        dprintf((stderr, "[��23(%02x)]\n", c[1]));
        c += 2;
        break;

    case 0x24:		/* ����� */
		dprintf((stderr, "[�����(%d)]-[��å�����:%d]\n", c[2], c[1]));
        LvnsSetSavePoint(lvns, &lvns->selectpoint);
        memcpy(state->flag_select, state->flag, sizeof state->flag);
        {
            int i;
            TextParser(lvns, c[1], True);
            for (i = 0; i < c[2]; i++) {
                dprintf((stderr, 
                         "[����� %d]-[��å�����:%d]-[���ե��å�:%02x]\n", 
                         i, c[3 + i*2], c[4 + i*2]));
				lvns->text_attr = i+1;
				TextParser(lvns, c[3+i*2], False);
            }
			lvns->text_attr = 0;
			i = LvnsWaitSelect(lvns, c[2]);
			LvnsAddHistory(lvns, c[3+i*2]);

			dprintf((stderr, "����ʬ��: %d (+%02x)\n", i, c[4 + i*2]));
            c = c + 3 + c[2] * 2 + c[4+i*2];
        }
        break;

    case 0x26:
        dprintf((stderr, "[��26()]\n"));
        c++;
        break;

    case 0x27:
        dprintf((stderr, "[1���������������ޡ���????]\n"));
        c++;
        break;

    case 0x28:
        dprintf((stderr, "[������ %04x - Block %d]\n", 
                 c[1]*256 + c[2], c[3]));
        ToHeartLoadScenario(lvns, c[1] * 256 + c[2], c[3]);
        break;

    case 0x29:
        dprintf((stderr, "[�֥�å�������- Block %d]\n", c[1]));
        LvnsLoadScenarioBlock(lvns, c[1]);
        break;

    case 0x2b:
		dprintf((stderr, "[���������(����襪�ե��å�:%d)] - [��å�����:%d]\n", c[1], c[2]));
        {
			int i, select_num = 0;
			int selmap[12];
			TextParser(lvns, c[2], True);
            for (i = 0; i < 12; i++) {
				int msg = state->flag[TOHEART_FLAG_VSELECT_MSG + i];
				if (msg != 0) {
                    dprintf((stderr, 
                             "[����� %d][��å�����:%d][���ե��å�:%02x]\n", 
                             i, msg, 
							 state->flag[TOHEART_FLAG_VSELECT_OFF + i]));
					selmap[select_num++] = i;
					lvns->text_attr = select_num;
					TextParser(lvns, msg, False);
                }
            }
			lvns->text_attr = 0;
			i = selmap[LvnsWaitSelect(lvns, select_num)];
			LvnsAddHistory(lvns, state->flag[TOHEART_FLAG_VSELECT_MSG + i]);

			c = c + 3 + state->flag[TOHEART_FLAG_VSELECT_OFF + i] * c[1];
		}
        break;

    case 0x2c:
		dprintf((stderr, "[�����������()]\n"));
        {
            int i;
            LvnsSetSavePoint(lvns, &lvns->selectpoint);
            memcpy(state->flag_select, state->flag, sizeof state->flag);
            for (i=0; i<12; i++)
                state->flag[TOHEART_FLAG_VSELECT_MSG + i] = 0;
        }
        c++;
        break;

    case 0x2d:
        dprintf((stderr,
                 "[PUSH(2d)(%02x%02x, Block - %02d)]\n", c[1], c[2], c[3]));
        state->flag[TOHEART_FLAG_2D_SCN]   = c[1];
        state->flag[TOHEART_FLAG_2D_SCN+1] = c[2];
        state->flag[TOHEART_FLAG_2D_BLK]   = c[3];
        c += 4;
        break;

    case 0x2e:
        dprintf((stderr, "[RETURN-2d()]\n"));
        ToHeartLoadScenario(lvns, 
                            state->flag[TOHEART_FLAG_2D_SCN] * 256 +
                            state->flag[TOHEART_FLAG_2D_SCN+1],
                            state->flag[TOHEART_FLAG_2D_BLK]);
        break;
        
    case 0x2f:
        dprintf((stderr, 
                 "[PUSH(2f)(%02x%02x, Block - %02d)]\n", c[1], c[2], c[3]));
        state->flag[TOHEART_FLAG_2F_SCN]   = c[1];
        state->flag[TOHEART_FLAG_2F_SCN+1] = c[2];
        state->flag[TOHEART_FLAG_2F_BLK]   = c[3];
        c += 4;
        break;

    case 0x30:
        dprintf((stderr, "[RETURN-2f()]\n"));
        ToHeartLoadScenario(lvns, 
                            state->flag[TOHEART_FLAG_2F_SCN] * 256 +
                            state->flag[TOHEART_FLAG_2F_SCN+1],
                            state->flag[TOHEART_FLAG_2F_BLK]);
        break;
        
    case 0x32: /* ���դ����ꤹ�� */
        dprintf((stderr, "[��������(��������̵)(%02x)]\n", c[1]));
        if (c[1] == 0xf0) {
            state->flag[TOHEART_FLAG_DATE] = 3; /* ���ս���� */
        } else {
            state->flag[TOHEART_FLAG_DATE] ++;  /* �����ɲ� */
        }       
        state->flag[TOHEART_FLAG_WEEKDAY] = 
            (state->flag[TOHEART_FLAG_DATE] + 5) % 7;
        c+=2;   
        break;
        
    case 0x33: /* ��������ꤹ�� */
        dprintf((stderr, "[��������(%02x)]\n", c[1]));

        /* ��ư�ե饰��������������ɤ��Τ��ɤ��������� */
        state->flag[TOHEART_FLAG_EVENT_DONE] = 0;
        state->flag[TOHEART_FLAG_IDOU] = 0;

        if (c[1] >= 0xf0) {  
            /* ɽ��̵������ */
            state->flag[TOHEART_FLAG_TIME] = c[1] - 0xf0;
        } else {  
            /* ɽ��ͭ�깹�� */
            int i;
            int start;
            
            if (state->fast_clock) {
                start = c[1];
            } else {
                start = state->flag[TOHEART_FLAG_TIME];
            }
            
            state->flag[TOHEART_FLAG_TIME] = c[1];
            for (i=start; i<c[1]+1;i++) {
                clock_anim[i].type = LVNS_ANIM_IMAGE_ADD;
            }
            clock_anim[i].type = LVNS_ANIM_NONE;
            LvnsAnimation(lvns, clock_anim + start);
        }

        c += 2;
        break;
        
    case 0x34:		/* �ե饰�û� */
        dprintf((stderr, "[%s += %d]\n", FlgName(c[1]), c[2]));
        state->flag[c[1]] += c[2];
        c += 3;
        break;
        
    case 0x35:          /* �ե饰���� */
        dprintf((stderr, "[%s -= %d]\n", FlgName(c[1]), c[2]));
        state->flag[c[1]] -= c[2];
        c += 3;
        break;

    case 0x3c:/* �طʥ��� */
        dprintf((stderr, "[�طʥ��� to VRAM? 0x3c(%d/%d)]\n", c[1]/50, c[1]%50));
		if (!history_mode) {
			ToHeartLoadBG(lvns, c[1]);
			/* ������VRAM������ */
			lvnsimage_copy(lvns->background, lvns->vram);
			LVNS->mergeCharacter(lvns);
		}
        c += 2;
        break;

    case 0x3d:
        dprintf((stderr, "[����饯���õ� 0x3d(%d)]\n", c[1]));
		if (!history_mode) {
			ToHeartClearCharacter(lvns, c[1]);
		}
        c += 2;
        break;

    case 0x40:
        dprintf((stderr, "[��40(%02x)]\n", c[1]));
        c += 2;
        break;

    case 0x42:
        dprintf((stderr, "[VISUAL���� 0x42 (V%02x.LF2)]\n", c[1]));
		if (!history_mode) { 
			ToHeartLoadVisual(lvns, c[1]);
		}
        c += 2;
        break;

    case 0x43:	
        dprintf((stderr, "[����饯��ɽ�� 0x43 (%s, C%02x%02x.LF2)]\n", 
                 posstr[c[1]], c[2], c[3]));
		if (!history_mode) {
			ToHeartLoadCharacter(lvns, c[2]<<8|c[3], c[1]);
		}
        c += 4;
        break;

    case 0x44: /* �õ�ɽ������ */
        dprintf((stderr, "[???? 0x44 ��ɽ������?(%02x, %02x)]\n", c[1], c[2]));
		c += 3;
        break;

    case 0x45:
        dprintf((stderr, "[ɽ������(%02x)]\n", c[1]));
		if (!history_mode) {
			LvnsDisp(lvns, text_effect(c[1]));
		}
        c += 2;
        break;

    case 0x47:
	switch (c[1]) {
	case 1:
		dprintf((stderr, "[���ԥ�ɽ��]\n"));
		lvns->sepia_mode_next = True;
		break;
	default:
		dprintf((stderr, "[�ѥ�åȽ���? 0x47(%02x)]\n", c[1]));
	}
        c += 2;
        break;

    case 0x50:
        dprintf((stderr, "[�� 0x50]\n"));
        c ++;
        break;
        
    case 0x55:
        dprintf((stderr, "[Ʊ��֥�å�����������?(%02x)]\n", c[1]));
        lvns->scn_cur += c[1];
        c += 2;
        break;

    case 0x56:
        c++;
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s(%d) == %d) pc += %02d)]\n",
                     FlgName(flag), state->flag[flag], data, offset));
            if (state->flag[flag] == data)
                lvns->scn_cur += offset;
        }
        break;

    case 0x57:
        c++;
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s(%d) != %d) pc += %02d)]\n",
                     FlgName(flag),state->flag[flag], data, offset));
            if (state->flag[flag] != data)
                lvns->scn_cur += offset;
        }
        break;

    case 0x58:
        c++; 
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s(%d) > %d) pc += %02d)]\n", 
                     FlgName(flag), state->flag[flag], data, offset));
            if (state->flag[flag] > data)
                lvns->scn_cur += offset;
                   
        }
        break;

    case 0x59:
        c++;
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s(%d) < %d) pc += %02d)]\n", 
                     FlgName(flag), state->flag[flag], data, offset));
            if (state->flag[flag] < data)
                lvns->scn_cur += offset;
        }
        break;

    case 0x5a:
        c++;
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s(%2d) >= %d) pc += %02d)]\n", 
                     FlgName(flag), state->flag[flag], data, offset));
            if (state->flag[flag] >= data)
                lvns->scn_cur += offset;
        }
        break;

    case 0x5b:
        c++;
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s(%2d) <= %d) pc += %02d)]\n",
                     FlgName(flag), state->flag[flag], data, offset));
            if (state->flag[flag] <= data)
                lvns->scn_cur += offset;
        }
        break;

    case 0x5e:
        c++;
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s �� %s bit��ON) pc += %02d)]\n",
                     FlgName(flag), FlgBit(flag, data), offset));
            if ((state->flag[flag] & (1 << data))) 
                lvns->scn_cur += offset;
        }
        break;

    case 0x5f:
        c++;
        {
            int flag = *c++;
            int data = *c++;
            int offset = *c++;
            dprintf((stderr, "[if (%s �� %s bit��OFF) pc += %02d)]\n",
                     FlgName(flag), FlgBit(flag, data), offset));
            if (!(state->flag[flag] & (1 << data))) 
                lvns->scn_cur += offset;
        }
        break;

    case 0x61:
        dprintf((stderr, "[%s = %d)]\n", FlgName(c[1]), c[2]));
        state->flag[c[1]] = c[2];
        c += 3;
        break;

    case 0x62:
        dprintf((stderr, "[%s += %d]??(62)\n", FlgName(c[1]), c[2]));
        state->flag[c[1]] += c[2];
        c += 3;
        break;

    case 0x63:
        dprintf((stderr, "[%s��%sbit�ܤ�%02x��)]\n", 
                 FlgName(c[1]), FlgBit(c[1], c[2]), c[3]));
        if (c[3]) {
            state->flag[c[1]] |= (1 << c[2]);
        } else {
            state->flag[c[1]] &= ~(1 << c[2]);
        }
        c += 4;
        break;

    case 0x69:
        dprintf((stderr, "[��å�����ɽ���奯�ꥢ]\n"));
		TextParser(lvns, c[1], True);
		if (!history_mode) {
			LvnsClearText(lvns);
			LvnsClear(lvns, LVNS_EFFECT_NORMAL);
		}
        c += 2;
        break;

    case 0x6a:		/* ��å�����ɽ�� */
        dprintf((stderr, "[��å�����:%d]\n", c[1]));
		TextParser(lvns, c[1], True);
        c += 2;
        break;

    case 0x6c:
        dprintf((stderr, "[��6c(%02x)]\n", c[1]));
        c += 2;
        break;
        
    case 0x6b:
        dprintf((stderr, "[��������̾õ�?]\n"));
        c++;
        break;

    case 0x70:
        dprintf((stderr, "[��%2x()]\n", c[0]));
        c ++;
        break;

    case 0x71:
        dprintf((stderr, "[��%2x()]\n", c[0]));
        c ++;
        break;

    case 0x72:
        dprintf((stderr, "[��%2x(%x)]\n", c[0], c[1]));
        c += 2;
		break;

    case 0x73:
        dprintf((stderr, "[���̤����뤯����? ��%2x(%x)]\n", c[0], c[1]));
		if (!history_mode) {
			lvns->latitude = 0;
			LvnsLighten(lvns);
		}
        c += 2;
		break;

    case 0x74:
        dprintf((stderr, "[��%2x()]\n", c[0]));
        c ++;
        break;

    case 0x75:
        dprintf((stderr, "[��%2x()]\n", c[0]));
        c ++;
        break;

    case 0x76:
        dprintf((stderr, "[��%2x()]\n", c[0]));
        c ++;
        break;

    case 0x77:
        dprintf((stderr, "[WhiteOut? ��%2x(%x)]\n", c[0], c[1]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			LvnsWhiteOut(lvns);
		}
        c += 2;
        break;

    case 0x78:
        dprintf((stderr, "[WhiteIn? ��%02x(%x)]\n", c[0], c[1]));
		if (!history_mode) {
			LvnsWhiteIn(lvns);
		}
        c += 2;
        break;

    case 0x79: 
        dprintf((stderr, "[??�ƥ����Ⱦõ�? %2x]\n", c[0]));
        c ++;
        break;

    case 0x7a:
        dprintf((stderr, "[??�ƥ�����ɽ��? %2x]\n", c[0]));
        c ++;
        break;

    case 0x80:
        dprintf((stderr, "BGM ����(%d)\n", c[1]));
		if (!history_mode)
			LvnsStartMusicLoop(lvns, bgmmap(c[1]));
        c += 2;
        break;

    case 0x81:
        dprintf((stderr, "BGM �ե���������\n"));
		if (!history_mode)
			LvnsFadeMusic(lvns);
        c++;
        break;

    case 0x82:
        dprintf((stderr, "BGM���\n"));
		if (!history_mode)
			LvnsPauseMusic(lvns);
        c++;
        break;

    case 0x85:
        dprintf((stderr, "BGM �ե����ɽ�����λ�Ԥ�\n"));
		if (!history_mode)
			LvnsWaitMusicFade(lvns);
        c++;
        break;

    case 0x87:
        dprintf((stderr, "BGM ����(fadein)(%d)\n", c[1]));
		if (!history_mode) {
			LvnsStartMusicLoop2(lvns, bgmmap(c[1]));
			LvnsFadeMusic(lvns);
		}
        c += 2;
        break;

    case 0x88:
        dprintf((stderr, "NEXT BGM ����?(%d)\n", c[1]));
		if (!history_mode)
			LvnsSetNextMusicLoop(lvns, bgmmap(c[1]));
        c += 2;
        break;

    case 0x94:
        dprintf((stderr, "[�����ཪλ(94)?()]\n"));
        c++;
        break;

    case 0x95:
        dprintf((stderr, "[����ǥ��󥰳���(95)(%02x)]\n", c[1]));
		if (!history_mode) {
			/* ����ǥ��󥰵�ư */
			ToHeartEnding(lvns);
			/* ����ǥ�����ã�ˤĤ����̥ǡ�����¸ */
			ToHeartSaveCommon(lvns);
		}
        c += 2;
        return True;

    case 0xa0:		/* PCM��������? */
        dprintf((stderr, "[A0 PCM�ɤ߹���(%02d)]\n", c[1]));
		if (!history_mode)
			LvnsLoadSound(lvns, "TH_VD%02d.P16", c[1]);
        c += 2;
        break;

    case 0xa1:
        dprintf((stderr, "[A1 PCM��λ]\n"));
		if (!history_mode) 
			LvnsStopSound(lvns);
        c++;
        break;

    case 0xa2:
        dprintf((stderr, "[A2 PCM���� %x %x]\n",c[1],c[2]));
		if (!history_mode)
			LvnsStartSound(lvns, c[1]); 
        c+=3;
        break;

    case 0xa3:
        dprintf((stderr, "[A3 PCM����Ԥ�]\n"));
		if (!history_mode)
			LvnsWaitSound(lvns);
        c++;
        break;

    case 0xA6:
        dprintf((stderr, "[A6 PCM��Ϣ?]\n"));
        c++;
        break;

    case 0xa7:	        	/* �����餯PCM�ط� */
        dprintf((stderr, "[A7 PCM��Ϣ?(%02x, %02x)]", c[1], c[2]));
        c+= 3;
        break;

    case 0xa8:
        dprintf((stderr, "[A8 PCM��Ϣ?]"));
        c++;
        break;
        
    case 0xaf:		/* �֥�å���λ */
        return True;
        break;

    case 0xb0:
        LvnsNewLineText(lvns); /* ���� */
        c++;
        break;

    case 0xb2:                    /* ��������å��Ԥ� */
		if (!history_mode) {
			if (!lvns->fast_text)
				LvnsWaitKey(lvns);
		}
        c++;
        break;

    case 0xb3:		      /* ���ڡ��� */
		if (!history_mode) {
			LvnsWaitPage(lvns);
			lvns->savepoint_flag = True;
		}
        c++;
        break;

    case 0xb4:
        dprintf((stderr, "[��b4(%02x)]", c[1]));
        c += 2;
        break;

    case 0xb6:	
        dprintf((stderr, "[ʸ������®���ѹ�(%d*10ms)]\n", c[1]));
		if (!history_mode) {
			lvns->char_wait_time = c[1];
		}
        c += 2;
        break;

    case 0xb7:		/* �����Ԥ� */
        dprintf((stderr, "[�����Ԥ�(%d*10ms)]\n", c[1]));
		if (!history_mode) {
			if (!lvns->fast_text && !lvns->skip) {
				LvnsWait(lvns, c[1]);
			}
		}
        c += 2;
        break;

    case 0xb8:
        dprintf((stderr, "[��b8()]"));
        c++;
        break;

    case 0xb9:
        dprintf((stderr, "[ʸ�������ѹ�(x=%d*8)]\n", c[1]));
		if (!history_mode) {
			LvnsSetTextOffset(lvns, c[1]*8);
		}
        c += 2;
        break;

    case 0xba:
        dprintf((stderr, "[��ba(%02x,%02x)]", c[1], c[2]));
        c += 3;
        break;

    case 0xbb:		/* �ե�å��奨�ե����� */
        dprintf((stderr, "�ե�å���(0xbb)\n"));
		if (!history_mode) {
			LvnsWhiteOut(lvns);
			LvnsWhiteIn(lvns);
		}
		c++;
        break;

    case 0xbc:		/* �С��󡢥��ե�����?*/
        dprintf((stderr, "�֤ɤ��áײ��̿�ư(0xbc:%x)\n", c[1]));
		if (!history_mode) {
			LvnsClearCursor(lvns);
			LvnsVibrato(lvns);
		}
        c+=2;
        break;

    case 0xbd:		/* �طʥ��ɤ���2 */
		dprintf((stderr, "[�طʥ���2 (%d/%d, %02x, %02x)]\n",
				 c[1]/50, c[1]%50, c[2], c[3]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			LvnsClear(lvns, text_effect(c[2]));
			ToHeartLoadBG(lvns, c[1]);
			LvnsDisp(lvns, text_effect(c[3]));
		}
		c += 4;
        break;

    case 0xbe:
        dprintf((stderr, "[��be()]"));
        c++;
        break;

    case 0xbf:		/* �ӥ��奢�륷����������� */
		dprintf((stderr,
				 "[VISUAL����(V%02x.LF2, %02x, %02x)]\n", c[1], c[2], c[3]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			LvnsClear(lvns, text_effect(c[2]));
			ToHeartLoadVisual(lvns, c[1]);
			LvnsDisp(lvns, text_effect(c[3]));
		}
		c += 4;
        break;

    case 0xc0:		/* H������������� */
		dprintf((stderr, "[H������c0(%02x, %02x, %02x)]\n", c[1], c[2], c[3]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			LvnsClear(lvns, text_effect(c[2]));
			ToHeartLoadHVisual(lvns, c[1]);
			LvnsDisp(lvns, text_effect(c[3]));
		}
		c += 4;
        break;

    case 0xc1:		/* ����饯���ѹ� */
		dprintf((stderr, "[����饯���ѹ�(%s, C%02x%02x.LF2)]\n", 
				 posstr[c[1]], c[2], c[3]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			ToHeartLoadCharacter(lvns, c[2]<<8|c[3], c[1]);
			LvnsDisp(lvns, LVNS_EFFECT_FADE_MASK);
		}
		c += 4;
        break;

    case 0xc2:
		dprintf((stderr, "[����饯��ɽ��(%s, C%02x%02x.LF2)]\n", 
				 posstr[c[1]], c[2], c[3]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			ToHeartLoadCharacter(lvns, c[2]<<8|c[3], c[1]);  
			LvnsDisp(lvns, LVNS_EFFECT_FADE_MASK);
		}
		c += 4;
        break;

    case 0xc3:
		dprintf((stderr, "[���õ�奭���ɽ��(%s, C%02x%02x.LF2)]\n", 
				 posstr[c[1]], c[2], c[3]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			ToHeartClearCharacter(lvns, 3);
			ToHeartLoadCharacter(lvns, c[2]<<8|c[3], c[1]);
			LvnsDisp(lvns, LVNS_EFFECT_FADE_MASK);
		}
		c += 4;
        break;

    case 0xc4:		/* �ط��դ����̥��� */
		dprintf((stderr, 
				 "[�ط��դ�������ѹ�(%s, C%02x%02x.LF2, S%02d?.LF2, %02x, %02x)]\n",
				 posstr[c[1]], c[2], c[3], c[4], c[5], c[6]));
		if (!history_mode) {
			LvnsUndispText(lvns);
			LvnsClear(lvns, text_effect(c[5]));
			ToHeartLoadBG(lvns, c[4]);
			ToHeartLoadCharacter(lvns, c[2]<<8|c[3], c[1]);
			LvnsDisp(lvns, text_effect(c[6]));
		}
		c += 7;
        break;

    case 0xc6:  /* 3����� */
		dprintf((stderr, "3�����Ʊ��ɽ��\n"));
		LvnsUndispText(lvns);
		if (!history_mode) {
			ToHeartLoadCharacter(lvns, c[2]<<8|c[3], c[1]);
			ToHeartLoadCharacter(lvns, c[5]<<8|c[6], c[4]);
			ToHeartLoadCharacter(lvns, c[8]<<8|c[9], c[7]);
			LvnsDisp(lvns, LVNS_EFFECT_FADE_MASK);
		}
		c += 10;
        break;

    case 0xc7:
        dprintf((stderr, "[��c7()]\n"));
        c++;
        break;

    case 0xc9:
        dprintf((stderr, "[��c9()]\n"));
        c++;
        break;

    case 0xcc:
        dprintf((stderr, "[��cc(%02x, %02x)]\n", c[1], c[2]));
        c += 3;
        break;

    case 0xcf:
        dprintf((stderr, "[��cf(%02x)]", c[1]));
        c += 2;
        break;

    case 0xf5:
        dprintf((stderr, "[���չ���(��������ͭ)(%02x/%02x)]\n", c[1],
                 state->flag[TOHEART_FLAG_DATE]));
		if (!history_mode) {
			int effect_state;
			if (state->fast_calendar) {
				effect_state = 16;
			} else {
				effect_state = 0;
			}

			if (c[1] > state->flag[TOHEART_FLAG_DATE]) {
				state->calendar_day = c[1];
				init_calendar(lvns);
				set_calendar(lvns, state->flag[TOHEART_FLAG_DATE]++, 209);
				set_calendar(lvns, state->flag[TOHEART_FLAG_DATE], 211);
				LvnsAnimation(lvns,  calendar_anim);
				while (!calendar(lvns, &effect_state));
			}
		}
		c += 2;
		break;

    case 0xf7:		
	switch (c[1]) {
	case 01:
		dprintf((stderr, "[��(%02x)]\n", c[1]));
		ToHeartRainEffectInit(lvns, 50);
		LvnsSetNextBackEffect(lvns, &toHeartRainEffect);
		break;
	case 04:
		dprintf((stderr, "[��(%02x)]\n", c[1]));
		ToHeartSakuraSetRandomNumber(lvns, 15);
		LvnsSetNextBackEffect(lvns, &toHeartSakuraEffect);
		break;
	default:
		dprintf((stderr, "[�� (%02x)]\n", c[1]));
	}
        c += 2;
        break;

    case 0xf8:
        dprintf((stderr, "[��f8(%02x)]\n", c[1]));
        c += 2;
        break;

    case 0xff:
        dprintf((stderr, "[END(0xff)]\n"));
		return True;

    default:
        fprintf(stderr, "����å�����ʤ��ä����ޥ�ɤǤ�(%02x)\n", c[0]);
		return True;
    }
    return False;
}
#undef c

/*
 * ��§ʸ����Ƚ��
 */
static Bool
isKinsoku(int code)
{
    if ((code >= 239 && code <= 242) ||
        (code >= 135 && code <= 143) ||
        (code >= 216 && code <= 225) ||
        code == 228 || code == 230 || 
        code == 232 || code == 233 ||
        code == 234) {
        return True;
    }
    return False;
}

static void
ToHeartDispText(Lvns *lvns, const u_char *c, Bool history_mode)
{
	while(1) {
		int code = c[0];
		if (code >= 0 && code < 0x20) {
			int FontCode = (code << 8) + c[1];
			/* �ʰ׶�§ & ��ư���Խ���
			   �����������ä��祡���������å��硢�������ס� */
			LvnsDispText(lvns);
			if (lvns->tvram[lvns->current_tvram].cur_x + 
				lvns->tvram[lvns->current_tvram].row[lvns->tvram[lvns->current_tvram].cur_y].offset / 24 >= TEXT_WIDTH - 2) {
				if (!isKinsoku(FontCode)) {
					lvns->tvram[lvns->current_tvram].cur_x = 0;
					lvns->tvram[lvns->current_tvram].cur_y++;
				}   
			}
			c += 2;
			LvnsPutChar(lvns, FontCode,  lvns->text_attr);
		} else switch (code) {
		case 0xd1:
		case 0xd2:
		case 0xd3:
		case 0xd4:
		case 0xd5:
		case 0xd6:
		case 0xd8:
		case 0xd9:
		case 0xda:
		case 0xdb:
		case 0xdc:
		case 0xdd:
		case 0xdf:
		case 0xe0:
		case 0xe1:
		case 0xe2:
		case 0xe3:
		case 0xe4:
		case 0xe6:
		case 0xe7:
		case 0xe8:
		case 0xe9:
		case 0xea:
		case 0xeb:
		case 0xed:
		case 0xee:
		case 0xef:
		case 0xf0:
		case 0xf1:
		case 0xf2:
			/* dprintf((stderr, "[��͸�̾��(%02x)]", code));*/
			code = (code - 0xd1)*2;
			code = (((u_char*)names)[code] << 8) + ((u_char*)names)[code+1];
			if (code) {
				if (lvns->tvram[lvns->current_tvram].cur_x >= TEXT_WIDTH - 1) {
					lvns->tvram[lvns->current_tvram].cur_x = 0;
					lvns->tvram[lvns->current_tvram].cur_y++;
				}
				LvnsPutCharNormal(lvns, code, lvns->text_attr);
			}   
			c ++;
			break;
		case 0x32:
			dprintf((stderr, "�楳�ޥ��\n"));
			c ++;
			break;
		default:
			if (CommandParser(lvns, &c, history_mode))
				return;
		}
	} /* while (1) */
}


/*
 * �ƥ����ȥ��ʥꥪ�ѡ���
 * ɽ������λ������ True ���֤�
 */
static void
TextParser(Lvns *lvns, int no, Bool add_history)
{
	ToHeartSetTextScenarioState(lvns, no);
	ToHeartDispText(lvns, LvnsGetScenarioText(lvns, no), False);
	if (add_history)
		LvnsAddHistory(lvns, no);
}

/* ------------------------------------------------------------ */
/** ���ʥꥪ���󥸥󳫻��� */
static void
ToHeartStartScenario(Lvns *lvns)
{
    ToHeartState *state = (ToHeartState*)lvns->system_state;

    /* ���ʥꥪ�������� */
    LvnsLoadScenario(lvns, lvns->savepoint.scn, lvns->savepoint.blk);
    lvns->scn_cur = lvns->scn_cur_head + lvns->savepoint.scn_offset;

	LvnsClearText(lvns);

    /* �������� */
    if (lvns->savepoint.bg_no) {
		int i;
        switch (lvns->savepoint.bg_type) {
        case LVNS_VISUAL:
	    ToHeartLoadVisual(lvns, lvns->savepoint.bg_no);
            break;
        case LVNS_HCG:
            ToHeartLoadHVisual(lvns, lvns->savepoint.bg_no);
            break;
        default:
            ToHeartLoadBG(lvns, lvns->savepoint.bg_no);
            break;
        }
        ToHeartClearCharacter(lvns, 3);
		for (i=0;i<3;i++) {
			if (lvns->savepoint.character_no[i] != NOCHARACTER)
				ToHeartLoadCharacter(lvns, lvns->savepoint.character_no[i], i);
		}
		LvnsDisp(lvns, LVNS_EFFECT_FADE_PALETTE);
    } else {
        ToHeartLoadBG(lvns, 0);       
        ToHeartClearCharacter(lvns, 3);
    }

    /* BGM ���� */
    if (lvns->savepoint.current_music)
        LvnsSetNextMusicLoop(lvns, lvns->savepoint.current_music);

    /* �ե饰���� */
    memcpy(state->flag, state->flag_save, sizeof state->flag);

    /* ���̥ǡ����ɤ߹��� */
    ToHeartLoadCommon(lvns);

    /* �����������׽���� */
    lvns->selectpoint = lvns->savepoint;
    memcpy(state->flag_select, state->flag_save, sizeof state->flag);

}

/* 
 * ToHeart ���ʥꥪ�ѡ��� 
 */
void 
ToHeartMain(Lvns *lvns)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;
	ToHeartStartScenario(lvns);

	while (1) {
		
		lvns->inside_state = LVNS_MAIN;

		/* �����֥ݥ�������� */
		if (lvns->savepoint_flag) {
			LvnsSetSavePoint(lvns, &lvns->savepoint);
			memcpy(state->flag_save, state->flag, sizeof state->flag);
			lvns->savepoint_flag = False;
		}
        if (CommandParser(lvns, &lvns->scn_cur, False)) 
            return;

    } /* while(1) */
}

/**
 * ToHeart �Υ��󥸥����������Ѥ���ǡ����ν������Ԥ�
 */
void
ToHeartStart(Lvns *lvns)
{
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    /* ������ */
    lvns->setPaletteIndex(lvns, TOHEART_COL_BLACK,   0,   0,   0);
    lvns->setPaletteIndex(lvns, TOHEART_COL_WHITE, 255, 255, 255);
    lvns->setPaletteIndex(lvns, TOHEART_COL_GRAY,  127, 127, 127);
    lvns->vram->black       = TOHEART_COL_BLACK;
    lvns->background->black = TOHEART_COL_BLACK;

    /* ���ץ��˥����� */
    LvnsInitAnimation(lvns, clock_anim);

    /* �����������˥��Ϣ����� */
    LvnsInitAnimation(lvns, calendar_anim);
    for (i=0; i< sizeof calendar_data / sizeof calendar_data[0]; i++) {
        if ((calendar_data[i].image = 
             LvnsLoadImage(lvns, calendar_data[i].name, NULL)) == NULL ||
            (calendar_anim[i].image = 
             lvnsimage_new(calendar_data[i].image->width, calendar_data[i].image->height,
                           calendar_data[i].image->xoffset, calendar_data[i].image->yoffset)) == NULL ) {
            fprintf(stderr, "can't load calendar images...\n");
            exit(1);
        }
    }

    /* ����Ϣ����� */
    ToHeartSakuraInit(lvns);

    /* ����饯���ѥ�åȾ����ɤ߽Ф� */
    if (!(state->charpal = (void*)LvnsLoadData(lvns, "CHR_PAL.DAT", NULL))) {
        fprintf(stderr, "Can't open CHR_PAL.DAT.\n");
        exit(1);
    }
}

void
ToHeartDispHistory(Lvns *lvns, int pos)
{
	LvnsClearText(lvns);         /* �õ� */
	LvnsDispWindow(lvns);
	if (pos >= 0 && pos < lvns->history_pos) {
		LvnsLoadScenario(lvns, lvns->history[pos].scn, lvns->history[pos].blk);
		ToHeartDispText(lvns, LvnsGetScenarioText(lvns, lvns->history[pos].no), True);
	}

	// ��������ɽ��
#ifndef USE_MGL
#define CUR_X 25
#else
#define CUR_X 24
#endif
	LvnsLocate(lvns, CUR_X, 0);
	LvnsPuts(lvns, "��", 1);
	LvnsLocate(lvns, CUR_X, 11);
	LvnsPuts(lvns, "��", 2);
}
