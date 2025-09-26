#ifndef __BGM_H__
#define __BGM_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	s32  no;
	s32  vol;

} ST_BGM;


//---------------------------------------------------------------------------
void BgmInit(void);

void BgmPlay(s32 no);
void BgmPlayRaw(s32 no);
void BgmPlayVgm(s32 no);

void BgmSetVol(s32 vol);
s32  BgmGetVol(void);

void BgmLoadPlay(void);

void BgmStop(void);


#ifdef __cplusplus
}
#endif
#endif
