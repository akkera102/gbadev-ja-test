/*
 * Rain Effect for 
 * (c) Copyright 2001 TF mailto:tf@denpa.org
 * All rights reserverd.
 *
 * LEAF Visual Novel System For X (c) Copyright 1999-2001 Go Watanabe
 * ORIGINAL LVNS (c) Copyright 1996-1999 LEAF/AQUAPLUS Inc.
 *
 * $Id: toheart_rain.c,v 1.1 2002/07/29 05:24:39 go Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include "Lvns.h"

#include "toheart.h"

#define RAIN_MAX 50
#define RAIN_LIFETIME 10

#define RAIN_PAL_SIZE 8

#define RAIN_FRONT 0
#define RAIN_BACK 1

static struct Rain {
  int x;
  int y;
  int pos;
  int lifetime;
} rain[RAIN_MAX];

static int rain_num = 0;

/*
 * 雨エフェクト
 */

static
void setRain(Lvns *lvns, int idx)
{
  rain[idx].x = (random() % WIDTH/2) * 2;
  rain[idx].y = (random() % HEIGHT/2) * 2;
  if (random() % 2) {
    rain[idx].pos = RAIN_FRONT;
  } else {
    rain[idx].pos = RAIN_BACK;
  }
  rain[idx].lifetime = RAIN_LIFETIME;
}

/* 初期化 */
void
ToHeartRainEffectInit(Lvns *lvns, int num)
{
  int i;
  
  rain_num = num;

  for (i = 0; i < rain_num; i++) {
    setRain(lvns, i);
    rain[i].lifetime = random() % RAIN_LIFETIME;
  }
}

/* 状態遷移 */
static void
ToHeartRainEffectSetState(Lvns *lvns)
{
  int i;
  
  for (i = 0; i < rain_num; i++) {
    if (--rain[i].lifetime == 0) {
      setRain(lvns, i);
    }
  }
}  

#ifndef USE_MGL
static void
drawRain(Lvns *lvns, int idx)
{
  int i, w = 32;
  u_char *dst;

  if (rain[idx].x + w > WIDTH) w = WIDTH - rain[idx].x;
  if (rain[idx].y + w * 2 > HEIGHT) w = (HEIGHT - rain[idx].y) / 2;
  
  dst = lvns->vram->data + lvns->vram->rwidth * rain[idx].y + rain[idx].x;
  for (i = 0; i < w; i++) {
    u_char pixel = TOHEART_COL_SAKURA + i / 8;
    *dst = pixel;
    *(dst + lvns->vram->rwidth) = pixel;
    dst += lvns->vram->rwidth * 2 + 1;
  }
}
#else
static void
drawRain(Lvns *lvns, int idx)
{
  int i, w = 16;
  u_short *dst;
  static u_short rain_pal[RAIN_PAL_SIZE] = {
    1919, 1903, 1887, 1871, 1599, 1839, 1567, 15
  };
  
  if (rain[idx].x + w > WIDTH) w = WIDTH - rain[idx].x;
  if (rain[idx].y + w * 2 > HEIGHT) w = (HEIGHT - rain[idx].y) / 2;
  
  
  dst = lvns->vram->hsb_data + lvns->vram->rwidth * rain[idx].y + rain[idx].x;
  for (i = 0; i < w; i++) {
    u_short pixel = rain_pal[i / 2];
    *dst = pixel;
    *(dst + lvns->vram->rwidth) = pixel;
    dst += lvns->vram->rwidth * 2 + 1;
  }
}
#endif

/* 
 * 描画処理 
 */
static void
ToHeartRainEffect(Lvns *lvns)
{
    int i;

    static u_char rain_pal[RAIN_PAL_SIZE][3] = {
      {143, 199, 255},
      {159, 207, 255},
      {175, 215, 255},
      {191, 223, 255},
      {207, 231, 255},
      {223, 239, 255},
      {239, 247, 255},
      {255, 255, 255}
    };

    lvnsimage_copy_palette(lvns->background, lvns->vram);

    /* 背景 */
    lvnsimage_copy(lvns->background, lvns->vram);

    /* 背面の雨 */
    for (i = 0; i < rain_num; i++) {
      if (rain[i].pos == RAIN_BACK) drawRain(lvns, i);
    }

    /* キャラクタ立ち絵を追加 */
    LVNS->mergeCharacter(lvns);

    /* 前面の雨 */
    for (i = 0; i < rain_num; i++) {
      if (rain[i].pos == RAIN_FRONT) drawRain(lvns, i);
    }

    /* 雨用パレット追加 */
    lvnsimage_set_palette3(lvns->vram, rain_pal, TOHEART_COL_SAKURA, RAIN_PAL_SIZE);
    lvns->vram->palette_num = TOHEART_COL_SAKURA + RAIN_PAL_SIZE;
}   

LvnsBackEffectInfo toHeartRainEffect = {
    ToHeartRainEffectSetState,
    ToHeartRainEffect
};
