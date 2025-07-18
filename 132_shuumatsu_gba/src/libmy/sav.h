#ifndef __SAV_H__
#define __SAV_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void SavInit(void);

u8   SavReadSram(u32 adr);
u8   SavReadFlash(u32 adr);
void SavWriteSram(u32 adr, u8 dat);
void SavWriteFlash(u32 adr, u8 dat);
void SavWriteFlashCmd(u32 adr, u8 dat);
void SavWriteFlashEraseSector(s32 sector);
bool SavIsFlash(void);

u8*  SavGetPointer(u32 adr);


#ifdef __cplusplus
}
#endif
#endif
