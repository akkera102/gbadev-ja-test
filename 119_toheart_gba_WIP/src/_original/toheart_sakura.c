/*
 * LEAF Visual Novel System For X
 * (c) Copyright 1999,2000 Go Watanabe mailto:go@denpa.org
 * All rights reserverd.
 *
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart_sakura.c,v 1.3 2002/07/29 05:24:39 go Exp $
 *
 */

/*
 * To Heart �֤�����׽�����
  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "toheart.h"

#define TOHEART_EXE_NAME "lvns3.exe"

/* EXE �ե����뻲���ѡ� */
static u_char *thexe_addr = NULL;
static size_t thexe_size  = 0;
static off_t sakura_offset;

void *filemap(const char *path, size_t *size);
void  fileunmap(void *addr, size_t size);

/**
 * EXE �ե�������ɤ߹���
 */
static Bool
mapfile(const char *path)
{
	return (thexe_addr = filemap(path, &thexe_size)) != NULL ;
}

static void
unmapfile(void)
{
    if (thexe_size)
        fileunmap(thexe_addr, thexe_size);
}

/*
 * �ǡ����ΰ��פθ��С�
 */
static Bool
check(char *p, char *dat, size_t len)
{
    int i;
    for (i=0; i<len; i++) {
        if (p[len-i] != dat[len-i])
            return False;
    }
    return True;
}

/*
 * start ����ʬ���� MAX �ΰ��֤ޤǤδ֤��鸡��
 */
static off_t 
search(char *start, char *data, size_t len, size_t max)
{
    off_t pos = 0;
    while (pos < max) {
        if (check(start + pos, data, len))
            return pos;
        pos++;
    }
    return 0;
}

#ifdef USE_MGL
static u_short sakura_front[1024];
static u_short sakura_back[256];

static int has_hsb_bitmap = False;

static void
create_hsb_sakura(void)
{
    static u_char sakura_pal[][3] = {
        {  0,   0,   0},
        {224, 151, 175},
        {224, 152, 191},
        {224, 167, 192},
        {239, 176, 207},
        {239, 191, 223},
        {240, 200, 224},
        {240, 216, 240},
        {255, 231, 255},
    };

    int i, j, k;

    /* ��(��) */
    for (i = 0; i < 8; i++) {
      u_char *p = thexe_addr + sakura_offset + i * 16 * 16;
      u_short *q = sakura_front + i * 8 * 8;
      for (j = 0; j < 8; j++, p += 16) {
	for (k = 0; k < 8; k++, p+=2, q++) {
	    *q = mc_from_rgb(packRGB(sakura_pal[*p][0], sakura_pal[*p][1], sakura_pal[*p][2]));
	}
      }
    }
    
    /* ��(��) */
    for (i = 0; i < 8; i++) {
      u_char *p = thexe_addr + sakura_offset + 2048 + i * 8 * 8;
      u_short *q = sakura_back + i * 4 * 4;
      for (j = 0; j < 4; j++, p += 8) {
	for (k = 0; k < 4; k++, p++, q++) {
	  *q = mc_from_rgb(packRGB(sakura_pal[*p][0], sakura_pal[*p][1], sakura_pal[*p][2]));
	}
      }
    }
}
#endif

/*
 * �ǡ��������
 */
void ToHeartSakuraInit(Lvns *lvns)
{
    if (thexe_addr == NULL) {
        /* �ǡ����ɤ߽Ф��ѥѥ� */
        char path[1024];

        snprintf(path, sizeof path, "%s/%s", lvns->data_path, TOHEART_EXE_NAME);
        if (!mapfile(path)) {
            if (!mapfile(TOHEART_EXE_NAME)) {
                fprintf(stderr, "Can't open exefile %s.\n", TOHEART_EXE_NAME);
                exit(1);
            }
        }

        /* ���Υǡ�����õ�� */
        {
            static char sakura_data[] = {
                0, 0, 0, 4, 6, 6, 6, 4, 2, 0, 0, 0, 0, 0, 0, 0
            };

            off_t pos, rdata;

            /* �ޤ� rdata �ΰ��õ���� */
            if ((pos = search(thexe_addr, "rdata", 5, 1024)) == 0) {
                fprintf(stderr, "Can't find rdata segment in %s\n", 
                        TOHEART_EXE_NAME);
                exit(1);
            }
            rdata = (thexe_addr[pos + 11]) +
                    (thexe_addr[pos + 12] << 8) +
                    (thexe_addr[pos + 13] << 16) +
                    (thexe_addr[pos + 14] << 24);

            /* ³���ƺ��Υǡ�����õ�� */
            if ((pos = search(thexe_addr + rdata, sakura_data, 14, 0xffff)) == 0) {
                fprintf(stderr, "Can't find sakura data in %s\n", 
                        TOHEART_EXE_NAME);
                exit(1);
            }
            
            /* ���줬���Υǡ�������Ƭ���֡� */
            sakura_offset = rdata + pos - 16;
        }
    }        
    ToHeartSakuraSetNumber(lvns, 0);

}

/**
 * ������ο������
 */
void
ToHeartSakuraSetNumber(Lvns *lvns, int num)
{
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;
    if (num < state->sakura_disp_num) 
        state->sakura_disp_num = num;
    for (i=state->sakura_num; i<num; i++)
        state->sakura[i].position = SAKURA_NONE;
    state->sakura_num = num;
}

/**
 * ������ο������ (����������)
 */
void
ToHeartSakuraSetRandomNumber(Lvns *lvns, int num)
{
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    state->sakura_num =
    state->sakura_disp_num = num;
    for (i=0; i<num; i++) {
        if (random() % 3 > 0) {
            state->sakura[i].position = SAKURA_BEFORE;
        } else {
            state->sakura[i].position = SAKURA_BACK;
        }
        if (random() % 2) {
            state->sakura[i].x = random() % WIDTH;
            state->sakura[i].y = random() % HEIGHT;
            state->sakura[i].state = random() % 8;
        } else {
            state->sakura[i].x = random() % WIDTH;
            state->sakura[i].y = random() % HEIGHT;
            state->sakura[i].state = random() % 8;
        }
    }
}    

/**
 * ���̤κ���ɽ��
 */
#ifndef USE_MGL
#define SSIZE_F 16
#define SSIZE_B 8
#else
#define SSIZE_F 8
#define SSIZE_B 4
#endif
static void
put_sakura_before(LvnsImage *dst, int x2, int y2, int state)
{
    u_char *base;
    int i, j;
    int x = 0;
    int y = 0;
    int w = SSIZE_F;
    int h = SSIZE_F;

    if (x2 < 0) {
        w += x2;
        x -= x2;
        x2 = 0;
        
    }
    if (y2 < 0) {
        h += y2;
        y -= y2;
        y2 = 0;
    }
    if (w <= 0 || h <= 0)
      return;

    if (x2 + w > dst->rwidth)  w = dst->rwidth - x2;
    if (y2 + h > dst->rheight) h = dst->rheight - y2;

#ifndef USE_MGL
    base = thexe_addr + sakura_offset + state * 16 * 16;
    for (i=0; i<h; i++) {
        u_char *p = base + (i + y) * 16 + x;
        u_char *q = dst->data + (i + y2) * dst->rwidth + x2;
        for (j=0; j<w; j++, q++, p++) {
            if (*p)
                *q = TOHEART_COL_SAKURA-1 + *p;
        }
    }
#else
    {
      u_short *base = sakura_front + state * 8 * 8;
      for (i=0; i<h; i++) {
        u_short *p = base + (i + y) * 8 + x;
	u_short *q = dst->hsb_data + (i + y2) * dst->rwidth + x2;
	for (j=0; j<w; j++, q++, p++) {
	  if (*p)
	    *q = *p;
	}
      }
    }
#endif
}

/*
 * ���̤κ���ɽ��
 */
static void
put_sakura_back(LvnsImage *dst, int x2, int y2, int state) 
{
    u_char *base;
    int i, j;
    int x = 0;
    int y = 0;
    int w = SSIZE_B;
    int h = SSIZE_B;

    if (x2 < 0) {
        w += x2;
        x -= x2;
        x2 = 0;
        
    }
    if (y2 < 0) {
        h += y2;
        y -= y2;
        y2 = 0;
    }
    if (w <= 0 || h <= 0)
      return;

    if (x2 + w > dst->rwidth)  w = dst->rwidth - x2;
    if (y2 + h > dst->rheight) h = dst->rheight - y2;

#ifndef USE_MGL
    base = thexe_addr + sakura_offset + 2048 + state * 8 * 8;
    for (i=0; i<h; i++) {
        u_char *p = base + (i + y) * 8 + x;
        u_char *q = dst->data + (i + y2) * dst->rwidth + x2;
        for (j=0; j<w; j++, q++, p++) {
            if (*p)
                *q = TOHEART_COL_SAKURA-1 + *p;
        }
    }
#else
    {
      u_short *base = sakura_back + state * 4 * 4;
      for (i=0; i<h; i++) {
        u_short *p = base + (i + y) * 4 + x;
	u_short *q = dst->hsb_data + (i + y2) * dst->rwidth + x2;
	for (j=0; j<w; j++, q++, p++) {
	  if (*p)
	    *q = *p;
	}
      }
    }
#endif
}

#ifndef USE_MGL
#define SWIDTH 600
#define SHEIGHT 440
#else
#define SWIDTH 300
#define SHEIGHT 220
#endif
static void 
NewSakura(Lvns *lvns, int num)
{
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    /* �����֤Ӥ� */
    int size;
    if (random() % 3 > 0) {
        state->sakura[num].position = SAKURA_BEFORE;
        size = SSIZE_F;
    } else {
        state->sakura[num].position = SAKURA_BACK;
        size = SSIZE_B;
    }
    if (random() % 2) {
        state->sakura[num].x = random() % SWIDTH - size;
        state->sakura[num].y = -size;
        state->sakura[num].state = random() % 8;
    } else {
        state->sakura[num].x = -size;
        state->sakura[num].y = random() % SHEIGHT - size;
        state->sakura[num].state = random() % 8;
    }
}    

/**
 * ���ι�������
 */
static void
ToHeartSakuraEffect(Lvns *lvns)
{
    static u_char sakura_pal[][3] = {
        {224, 151, 175},
        {224, 152, 191},
        {224, 167, 192},
        {239, 176, 207},
        {239, 191, 223},
        {240, 200, 224},
        {240, 216, 240},
        {255, 231, 255},
    };

    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;

    /* �ط� */
    lvnsimage_copy(lvns->background, lvns->vram);

    /* ���̤κ� */
    for (i=0; i<state->sakura_disp_num; i++) {
        if (state->sakura[i].position == SAKURA_BACK) {
            put_sakura_back(lvns->vram, 
                            state->sakura[i].x,
                            state->sakura[i].y,
                            state->sakura[i].state);
        }
    }

    /* ����饯��Ω�������ɲ� */
    LVNS->mergeCharacter(lvns);

    /* ���̤κ� */
    for (i=0; i<state->sakura_disp_num; i++) {
        if (state->sakura[i].position == SAKURA_BEFORE) {
            put_sakura_before(lvns->vram, 
                              state->sakura[i].x,
                              state->sakura[i].y,
                              state->sakura[i].state);
        }
    }

    /* ���ѥѥ�å��ɲ� */
    lvnsimage_set_palette3(lvns->vram, sakura_pal, TOHEART_COL_SAKURA, 8);
    lvns->vram->palette_num = TOHEART_COL_SAKURA + 8;
}   

#ifndef USE_MGL
#define SAKURA_VX_BEFORE 10
#define SAKURA_VX_BACK 4
#define SAKURA_VY_BEFORE 4
#define SAKURA_VY_BACK 2
#else
#define SAKURA_VX_BEFORE 5
#define SAKURA_VX_BACK 2
#define SAKURA_VY_BEFORE 2
#define SAKURA_VY_BACK 1
#endif

static void
ToHeartSakuraEffectSetState(Lvns *lvns)
{
    int i;
    ToHeartState *state = (ToHeartState *)lvns->system_state;
#if 0
    dprintf((stderr, "SakuraEffect setstate: %d\n", state->sakura_disp_num));
#endif

#ifdef USE_MGL
    if (!has_hsb_bitmap) {
      create_hsb_sakura();
      has_hsb_bitmap = True;
    }
#endif

    /* �������֤Ӥ� */
    if (state->sakura_disp_num < state->sakura_num) {
        NewSakura(lvns, state->sakura_disp_num);
        state->sakura_disp_num++;
    }

    /* ���̤κ� */
    for (i=0; i<state->sakura_disp_num; i++) {
        if (state->sakura[i].position == SAKURA_BACK) {
            state->sakura[i].x += SAKURA_VX_BACK;
            state->sakura[i].y += SAKURA_VY_BACK;
            state->sakura[i].state++;
            state->sakura[i].state %= 8;
            if (state->sakura[i].x >= WIDTH ||
                state->sakura[i].y >= HEIGHT) {
                NewSakura(lvns, i);
            }
        } else if (state->sakura[i].position == SAKURA_BEFORE) {
            state->sakura[i].x += SAKURA_VX_BEFORE;
            state->sakura[i].y += SAKURA_VY_BEFORE;
            state->sakura[i].state++;
            state->sakura[i].state %= 8;
            if (state->sakura[i].x >= WIDTH ||
                state->sakura[i].y >= HEIGHT) {
                NewSakura(lvns, i);
            }
        }

    }
}   

LvnsBackEffectInfo toHeartSakuraEffect = {
    ToHeartSakuraEffectSetState,
    ToHeartSakuraEffect
};

