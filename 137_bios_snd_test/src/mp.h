#ifndef __MP_H__
#define __MP_H__
#ifdef __cplusplus
extern "C" {
#endif


// Adapted from the libgba header, and therefore licensed under GPLv2 or later.
// https://github.com/devkitPro/libgba/blob/master/include/gba_sound.h

// The performance template is based on the following:
// https://github.com/ipatix/gba-template/tree/biossnddemo


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define MP_MAX_CH								12
#define MP_MAX_TRACK							16
#define MP_PCM_DMA_BUF							1584

//---------------------------------------------------------------------------

typedef struct {
	u16 type;
	u16 stat;
	u32 freq;
	u32 loop;
	u32 size;
	s8  data[];
} ALIGN(4) ST_MP_WAVE;

typedef struct {
	u8  ctl[4];
	ST_MP_WAVE* wp;

	u8  Attack;
	u8  Decay;
	u8  Sustain;
	u8  Release;
} ALIGN(4) ST_MP_TONE;

typedef struct {
	u8  Status;
	u8  reserved1;
	u8  RightVol;
	u8  LeftVol;
	u8  Attack;
	u8  Decay;
	u8  Sustain;
	u8  Release;
	u8  reserved2[24];
	u32 fr;

	ST_MP_WAVE* wp;
	u32 reserved3[6];

} ALIGN(4) ST_MP_CH;

typedef struct {
	u32 ident;
	vu8 DmaCount;
	u8  reverb;
	u8  maxchn;
	u8  masvol;
	u8  freq;
	u8  mode;
	u8  r2[6];
	u32 r3[16];

	ST_MP_CH vchn[MP_MAX_CH];
	s8 pcmbuf[MP_PCM_DMA_BUF*2];

} ALIGN(4) ST_MP_AREA;

typedef struct {
	u8 numTracks;
	u8 dummy;
	u8 prio;
	u8 reverb;

	ST_MP_TONE* tone;
	u8 *tracks[];

} ALIGN(4) ST_MP_SONG;

typedef struct {
	u32 dummy[16];
} ALIGN(4) ST_MP_PLAYER;

typedef struct {
	u32 dummy[20];
} ALIGN(4) ST_MP_TRACK;

//---------------------------------------------------------------------------
void MpInit(void);

void MpPlayAdr(u32 adr);
void MpPlayMus(void);
void MpPlayKey(u32 ch, u32 freq);
void MpStopKey(u32 ch);
void MpStopAll(void);

void MpSetModeNor(void);
void MpSetModeRev(void);
u32  MpGetActiveCnt(void);

void MpExecSwi1A(ST_MP_AREA* a);
void MpExecSwi1B(u32 mode);
void MpExecSwi1C(void);
void MpExecSwi1D(void);
u32  MpExecSwi1F(ST_MP_WAVE* w, u32 key, u32 tune);
void MpExecSwi20(ST_MP_PLAYER* p, ST_MP_TRACK* t, u32 cnt);
void MpExecSwi21(ST_MP_PLAYER* p, ST_MP_SONG* s);


#ifdef __cplusplus
}
#endif
#endif
