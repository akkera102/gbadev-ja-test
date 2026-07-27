#ifndef __MODE4_H__
#define __MODE4_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define MODE4_BUF_ADR1			((u16*)0x6000000)
#define MODE4_BUF_ADR2			((u16*)0x600A000)


//---------------------------------------------------------------------------
typedef struct {

	u16* pFront;
	u16* pBack;

	u16  buf[180*120/2];

} ST_MODE4;


//---------------------------------------------------------------------------
void Mode4Init(void);

IWRAM_CODE void Mode4Exec(void);

IWRAM_CODE void Mode4Draw(u16* pImg);
IWRAM_CODE void Mode4DrawClr(void);

IWRAM_CODE void Mode4Pal(u16* pPal);
IWRAM_CODE void Mode4PalClr(void);


#ifdef __cplusplus
}
#endif
#endif
