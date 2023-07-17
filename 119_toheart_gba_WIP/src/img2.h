#ifndef __IMG2_H__
#define __IMG2_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void ImgDirectCrop(char* pStr, u32 x, u32 y);
EWRAM_CODE void ImgDirectClip(char* pStr, u32 x, u32 y, u32 gx, u32 gy, u32 gs);
EWRAM_CODE void ImgDirectBlend(char* pStr, u32 x, u32 y);
EWRAM_CODE void ImgDirectLine(u32 no, u32 cnt);
EWRAM_CODE void ImgDirectFill(u32 col);


#ifdef __cplusplus
}
#endif
#endif
