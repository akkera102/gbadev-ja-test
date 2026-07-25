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
	s32  pal;

} ST_IMG;


//---------------------------------------------------------------------------
void ImgInit(void);

IWRAM_CODE void ImgExec(void);
IWRAM_CODE void ImgExecBoot(void);
IWRAM_CODE void ImgExecAnime(void);
IWRAM_CODE void ImgExecExit(void);

IWRAM_CODE void ImgDrawBg(s32 no);
IWRAM_CODE void ImgDrawPal(void);
IWRAM_CODE void ImgSetExec(s32 no);

bool ImgIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
