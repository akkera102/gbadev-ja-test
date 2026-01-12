#ifndef __SND_H__
#define __SND_H__

#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SND_MAX_CHANNEL				8

#define SND_BUF_SIZE				224
#define SND_SAMPLE_TIME				(280896 / SND_BUF_SIZE)

enum {
    SND_NOTE_C2,
    SND_NOTE_CS2,
    SND_NOTE_D2,
    SND_NOTE_DS2,
    SND_NOTE_E2,
    SND_NOTE_F2,
    SND_NOTE_FS2,
    SND_NOTE_G2,
    SND_NOTE_GS2,
    SND_NOTE_A2,
    SND_NOTE_AS2,
    SND_NOTE_B2,
    SND_NOTE_C3,
    SND_NOTE_CS3,
    SND_NOTE_D3,
    SND_NOTE_DS3,
    SND_NOTE_E3,
    SND_NOTE_F3,
    SND_NOTE_FS3,
    SND_NOTE_G3,
    SND_NOTE_GS3,
    SND_NOTE_A3,
    SND_NOTE_AS3,
    SND_NOTE_B3,
    SND_NOTE_C4,
    SND_NOTE_CS4,
    SND_NOTE_D4,
    SND_NOTE_DS4,
    SND_NOTE_E4,
    SND_NOTE_F4,
    SND_NOTE_FS4,
    SND_NOTE_G4,
    SND_NOTE_GS4,
    SND_NOTE_A4,
    SND_NOTE_AS4,
    SND_NOTE_B4,
    SND_NOTE_C5,
    SND_NOTE_CS5,
    SND_NOTE_D5,
    SND_NOTE_DS5,
    SND_NOTE_E5,
    SND_NOTE_F5,
    SND_NOTE_FS5,
    SND_NOTE_G5,
    SND_NOTE_GS5,
    SND_NOTE_A5,
    SND_NOTE_AS5,
    SND_NOTE_B5,
    SND_NOTE_C6,
    SND_NOTE_CS6,
    SND_NOTE_D6,
    SND_NOTE_DS6,
    SND_NOTE_E6,
    SND_NOTE_F6,
    SND_NOTE_FS6,
    SND_NOTE_G6,
    SND_NOTE_GS6,
    SND_NOTE_A6,
    SND_NOTE_AS6,
    SND_NOTE_B6,
    SND_NOTE_C7,
    SND_NOTE_MAX
};
enum {
	SND_ACT_IDLE = 0,
	SND_ACT_ATTACK,
	SND_ACT_DECAY,
	SND_ACT_SUSTAIN,
	SND_ACT_RELEASE,
};

//---------------------------------------------------------------------------

typedef struct {
	s8* pWav;

	u32 cur;
	u32 step;

	s32 act;
	s32 vol;
	u32 note;

	s32 atkStep;
	s32 decStep;
	s32 susStep;
	s32 relStep;

	s32 atkLvl;
	s32 susLvl;

} ST_SND_CH;

typedef struct {
	s32 act;
	s32 cnt;
	s32 tmp[SND_BUF_SIZE] ALIGN(4);
	s8  buf[SND_BUF_SIZE * 2] ALIGN(4);

	ST_SND_CH ch[SND_MAX_CHANNEL];

} ST_SND;


//---------------------------------------------------------------------------
void SndInit(void);
void SndPlay(u32 note, s8* pWav, s32 atkS, s32 decS, s32 susS, s32 relS, s32 atkL, s32 susL);
void SndStop(void);
s32  SndGetCnt(void);

IWRAM_CODE void SndMix(void);
IWRAM_CODE void SndVSync(void);


#ifdef __cplusplus
}
#endif
#endif
