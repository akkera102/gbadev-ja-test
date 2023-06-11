#ifndef __SIORI_H__
#define __SIORI_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SIORI_MAX_CNT				8
#define SIORI_MAX_SIZE				0x1000


//---------------------------------------------------------------------------

typedef struct {
	s32 size;
	u8  id;

} ST_SIORI;



//---------------------------------------------------------------------------
EWRAM_CODE void  SioriInit(void);
EWRAM_CODE void  SioriSave(u32 no);
EWRAM_CODE bool  SioriLoad(u32 no);

EWRAM_CODE char* SioriGetStr(u32 no);

EWRAM_CODE bool  SioriIsInit(void);
EWRAM_CODE bool  SioriIsItem(u32 no);


#ifdef __cplusplus
}
#endif
#endif
