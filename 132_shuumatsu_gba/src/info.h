#ifndef __INFO_H__
#define __INFO_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define INFO_MAX_IMG_CNT			(100-13)
#define INFO_MAX_BGM_CNT			20
#define INFO_MAX_FMX_CNT			12


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void InfoInit(void);

s32  InfoGetImg(s32 idx);
s32  InfoGetBgm(s32 idx);
s32  InfoGetFmx(s32 idx);
s32  InfoGetMskNo(s32 no);


#ifdef __cplusplus
}
#endif
#endif
