#ifndef DME_H
#define DME_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
// https://github.com/Pegmode/-DeflemaskGBVGM-/wiki/Current-Command-Format
#define DME_CMD_2 0x80		// wait for x frames
#define DME_CMD_3 0xA0		// go to next bank
#define DME_CMD_4 0xB0		// write data to 0xFFxy
#define DME_CMD_5 0xC0		// Loop to loop address and bank
#define DME_CMD_6 0xD0		// End song



//---------------------------------------------------------------------------
typedef struct {
	
	u8  id;
	u8  bank;
	s32 wait;

	u8* pVgm;
	u8* pFile;

} ST_DME;

enum {
	DME_ID_STOP,
	DME_ID_PLAY,
	DME_ID_PUASE,
};

//---------------------------------------------------------------------------
EWRAM_CODE void DmeInit(void);
EWRAM_CODE void DmePlay(u8* pFile, u32 time);

IWRAM_CODE void DmeIntrTimer(void);
IWRAM_CODE void DmeStop(void);
IWRAM_CODE void DmeWriteReg(u8 adr, u8 byte);

#ifdef __cplusplus
}
#endif
#endif
