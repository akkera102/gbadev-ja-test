#ifndef __EFF_H__
#define __EFF_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// 24.8
typedef s32 Fix;

typedef struct {
	Fix x;
	Fix y;
	Fix z;
} ST_VEC;

typedef struct {
	ST_VEC cam;
	s32    rot;
	s32    dis;
} ST_EFF;

//---------------------------------------------------------------------------
void EffInit(void);

IWRAM_CODE void EffInitCam(void);
IWRAM_CODE void EffAddCamZ(void);

IWRAM_CODE void EffIntrHblank(u32 y);


#ifdef __cplusplus
}
#endif
#endif
