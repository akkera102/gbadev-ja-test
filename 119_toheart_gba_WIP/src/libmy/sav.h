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

// SRAM
EWRAM_CODE u8   SavSramRead(u32 adr);
EWRAM_CODE void SavSramWrite(u32 adr, u8 dat);

// FLASH
EWRAM_CODE u8   SavFlashRead(u32 adr);
EWRAM_CODE void SavFlashWrite(u32 adr, u8 dat);

EWRAM_CODE void SavFlashCmd(u32 adr, u8 dat);
EWRAM_CODE void SavFlashEraseSector(u32 sec);
EWRAM_CODE bool SavIsFlash(void);

// ‹¤’Ê
EWRAM_CODE u8*  SavGetPointer(u32 adr);


#ifdef __cplusplus
}
#endif
#endif
