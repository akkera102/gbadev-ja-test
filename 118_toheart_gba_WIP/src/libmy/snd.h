#ifndef __SND_H__
#define __SND_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SND_CPU_CLOCK			(16 * 1024 * 1024)
#define SND_AUDIO_RATE			8192


enum {
	SND_ACT_STOP,
	SND_ACT_START,
	SND_ACT_PLAY,
};


//---------------------------------------------------------------------------
typedef struct {
	u32  act;
	s32  cnt;

    u8*  data;
    u32  size;
    s32  frameSize;

    u32  loop;
    bool isLoop;
} ST_SND;


//---------------------------------------------------------------------------
EWRAM_CODE void SndInit(void);
EWRAM_CODE void SndSetData(u8* data, u32 size, s32 adjust, u32 loop);
EWRAM_CODE void SndPlay(void);
EWRAM_CODE void SndStop(void);

IWRAM_CODE void SndIntr(void);
IWRAM_CODE void SndIntrStart(void);
IWRAM_CODE void SndIntrStop(void);

EWRAM_CODE bool SndIsEnd(void);


#ifdef __cplusplus
}
#endif
#endif
