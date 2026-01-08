#ifndef __SND_H__
#define __SND_H__

#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SND_MAX_CHANNEL				8

#define SND_BUF_SIZE				224
#define SND_SAMPLE_TIME				(280896 / SND_BUF_SIZE)
#define SND_WAVE_SIZE				13359
#define SND_FP_SHIFT				10

#define SND_NOTE_C4					1000
#define SND_NOTE_CS					1062
#define SND_NOTE_D					1127
#define SND_NOTE_DS					1196
#define SND_NOTE_E					1270
#define SND_NOTE_F					1348
#define SND_NOTE_FS					1431
#define SND_NOTE_G					1519
#define SND_NOTE_GS					1613
#define SND_NOTE_A					1712
#define SND_NOTE_AS					1817
#define SND_NOTE_B					1929
#define SND_NOTE_C5					2048

enum {
	SND_ENV_OFF = 0,
	SND_ENV_ATTACK,
	SND_ENV_DECAY,
	SND_ENV_SUSTAIN,
	SND_ENV_RELEASE,
};

//---------------------------------------------------------------------------

typedef struct {
	u32 act;
	u32 cur;
	u32 end;
	u32 step;
	s8* pSrc;

	s32 vol;
	s32 state;
	s32 atkStep;
	s32 decStep;
	s32 susStep;
	s32 relStep;
	s32 susLvl;

} ST_SND_CH;

typedef struct {
	s32  act;
	bool isAdsr;

	s8* pInst;
	s32 atkStep;
	s32 decStep;
	s32 susLvl;
	s32 susStep;
	s32 relStep;

	ST_SND_CH ch[SND_MAX_CHANNEL];

	s32 idx;
	s8  buf[SND_BUF_SIZE * 2] ALIGN(4);
	s32 tmp[SND_BUF_SIZE] ALIGN(4);

} ST_SND;


//---------------------------------------------------------------------------
void SndInit(void);
void SndPlay(u32 note);
void SndStop(void);

void SndSetInst(s8* pInst, s32 atk, s32 dec, s32 susl, s32 suss, s32 rel);
void SndSetAdsr(void);
s32  SndGetActCnt(void);

bool SndIsAdsr(void);

IWRAM_CODE void SndMix(void);
IWRAM_CODE void SndVSync(void);


#ifdef __cplusplus
}
#endif
#endif
