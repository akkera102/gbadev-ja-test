#ifndef __IMG_H__
#define __IMG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

enum {
	IMG_EFFECT_BOOT,
	IMG_EFFECT_ANIME,
	IMG_EFFECT_EXIT,
};

//---------------------------------------------------------------------------

typedef struct {

	bool isExec;

	s32  eff;
	s32  step;
	s32  var;
	s32  cnt;

	s32  bg;

} ST_IMG;

typedef struct {

	u16* pImg[8500];
	u16* pPal[8500];
	bool isUse[8500];

} ST_IMG2;


//---------------------------------------------------------------------------
void ImgInit(void);

           void ImgExec(void);
           void ImgExecBoot(void);
IWRAM_CODE void ImgExecAnime(void);
           void ImgExecExit(void);

IWRAM_CODE void ImgDrawBg(s32 no);
IWRAM_CODE void ImgDrawPal(void);
           void ImgDrawClrBg(void);
           void ImgDrawClrPal(void);

void ImgSetExec(s32 no);
bool ImgIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
