#ifndef __SFX_H__
#define __SFX_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SFX_SAMPLE_TIME			(280896 / 224)
#define SFX_FREQ				13379


//---------------------------------------------------------------------------

enum {
	SFX_ACT_DONOTHING,
	SFX_ACT_STOP,
	SFX_ACT_START,
	SFX_ACT_PLAY,
};

typedef struct {
	s32  act;
	u8*  pSfx;
	bool isLoop;
	s32  size;
	s32  cnt;

} ST_SFX;


//---------------------------------------------------------------------------
void SfxInit(void);
void SfxPlay(u8* pSfx, s32 size, bool isLoop);
void SfxStop(void);

bool SfxIsPlay(void);

IWRAM_CODE void SfxIntrVblank(void);


#ifdef __cplusplus
}
#endif
#endif
