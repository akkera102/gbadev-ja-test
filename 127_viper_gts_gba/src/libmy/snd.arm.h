#ifndef __SND_H__
#define __SND_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SND_CPU_CLOCK			(16 * 1024 * 1024)
#define SND_AUDIO_RATE			10512
#define SND_FPS					60

enum {
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
EWRAM_CODE void SndInit(void);
EWRAM_CODE void SndPlay(u8* pSnd, s32 size, s32 adjust, bool isLoop);
EWRAM_CODE void SndStop(void);

IWRAM_CODE void SndIntrVblank(void);

EWRAM_CODE bool SndIsPlay(void);


#ifdef __cplusplus
}
#endif
#endif
