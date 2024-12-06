#ifndef __SAV_H__
#define __SAV_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void SavInit(void);

EWRAM_CODE u8   SavReadSram(u32 adr);
EWRAM_CODE u8   SavReadFlash(u32 adr);
EWRAM_CODE void SavWriteSram(u32 adr, u8 dat);
EWRAM_CODE void SavWriteFlash(u32 adr, u8 dat);
EWRAM_CODE void SavWriteFlashCmd(u32 adr, u8 dat);
EWRAM_CODE void SavWriteFlashEraseSector(s32 sector);
EWRAM_CODE bool SavIsFlash(void);

EWRAM_CODE u8*  SavGetPointer(u32 adr);


#ifdef __cplusplus
}
#endif
#endif
