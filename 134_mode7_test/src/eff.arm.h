#ifndef __EFF_H__
#define __EFF_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
typedef s32 Fix;

typedef struct {
	Fix x;		// 24.8
	Fix y;		// 24.8
	Fix z;		// 24.8
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
