#ifndef BAK_H
#define BAK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------

enum {
	BAK_TYPE_SRAM,
	BAK_TYPE_FLASH,
};

//---------------------------------------------------------------------------

typedef struct {
	u16 id;
	u8* p;
} ST_BAK;


//---------------------------------------------------------------------------
EWRAM_CODE void BakInit(void);

EWRAM_CODE void BakSeek(u32 adr);
EWRAM_CODE u8   BakRead(void);
EWRAM_CODE u8   BakRead2(u32 adr);
EWRAM_CODE void BakWrite(u8 dat);
EWRAM_CODE void BakWrite2(u32 adr, u8 dat);
EWRAM_CODE void BakWriteCmd(u32 adr, u8 cmd);

EWRAM_CODE u8*  BakGetPointer(void);
EWRAM_CODE u8   BakGetId(void);
EWRAM_CODE void BakSetId(u8 id);

EWRAM_CODE void BakEraseAll(void);
EWRAM_CODE void BakEraseSector(u32 sec);

EWRAM_CODE void BakWait20us(void);
EWRAM_CODE void BakWait25ms(void);
EWRAM_CODE void BakWait100ms(void);

EWRAM_CODE bool BakIsFlash(void);


#ifdef __cplusplus
}
#endif
#endif
