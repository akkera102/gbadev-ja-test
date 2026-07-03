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
u16  SavReadSram16(u32 adr);
void SavWriteSram(u32 adr, u8 dat);
void SavWriteSram16(u32 adr, u16 dat);

u8*  SavGetPointer(u32 adr);


#ifdef __cplusplus
}
#endif
#endif
