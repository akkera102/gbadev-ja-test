#ifndef __INFO_H__
#define __INFO_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define INFO_MAX_MES_CNT				42

#define INFO_MAX_BG_CNT					(222+1)		// +1はメニューのゼロ表示用
#define INFO_MAX_CHR_CNT				(148+1)
#define INFO_MAX_MUS_CNT				(34+1)
#define INFO_MAX_SND_CNT				(45+1)
#define INFO_MAX_TXT_CNT				(657+1)

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void  InfoInit(void);

char* InfoGetStrMes(s32 idx);
s32   InfoGetNavi(s32 i, s32 c);
s32   InfoGetBg(s32 idx, s32 mov);
s32   InfoGetChr(s32 idx, s32 mov);
s32   InfoGetMus(s32 idx, s32 mov);
s32   InfoGetSnd(s32 idx, s32 mov);
s32   InfoGetTxt(s32 idx, s32 mov);
s32   InfoGetIdxClmp(s32 idx, s32 mov, s32 max);
s32   InfoGetIdxLoop(s32 idx, s32 mov, s32 max);


#ifdef __cplusplus
}
#endif
#endif
