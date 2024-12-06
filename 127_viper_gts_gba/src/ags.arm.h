#ifndef __AGS_H__
#define __AGS_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------

enum {
	AGS_ACT_NOVEL = 1,
	AGS_ACT_SELECT,
	AGS_ACT_MENU,
	AGS_ACT_LOAD,
};


//---------------------------------------------------------------------------

typedef struct {
	s32 act;

} ST_AGS;


//---------------------------------------------------------------------------
EWRAM_CODE void AgsInit(void);
EWRAM_CODE void AgsIntrVblank(void);

EWRAM_CODE void AgsExecNovel(void);
EWRAM_CODE void AgsExecSelect(void);
EWRAM_CODE void AgsExecMenu(void);
EWRAM_CODE void AgsExecLoad(void);

EWRAM_CODE void AgsSetNovel(void);
EWRAM_CODE void AgsSetSelect(void);
EWRAM_CODE void AgsSetMenu(void);
EWRAM_CODE void AgsSetLoad(void);


#ifdef __cplusplus
}
#endif
#endif
