#ifndef __SND_H__
#define __SND_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SND_CPU_CLOCK			(16 * 1024 * 1024)
#define SND_AUDIO_RATE			21024
#define SND_FPS					60

enum {
	SND_ID_FMX,
	SND_ID_BGM,
};

enum {
	SND_ACT_DONOTHING,
	SND_ACT_STOP,
	SND_ACT_START,
	SND_ACT_PLAY,
};


//---------------------------------------------------------------------------
typedef struct {
	s32  act;
	s32  cnt;
	s32  size;
	u8*  pSnd;
	bool isLoop;

} ST_SND;


//---------------------------------------------------------------------------
void SndInit(void);

IWRAM_CODE void SndPlay(s32 no, u8* pSnd, s32 size, s32 adjust, bool isLoop);
IWRAM_CODE void SndStop(s32 no);
IWRAM_CODE bool SndIsPlay(s32 no);

IWRAM_CODE void SndIntrVblank(void);


#ifdef __cplusplus
}
#endif
#endif
