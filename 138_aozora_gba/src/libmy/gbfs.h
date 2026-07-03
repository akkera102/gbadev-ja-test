#ifndef __GBFS_H__
#define __GBFS_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
typedef struct {
	char sig[16];				// "PinEightGBFS" + 0x0d + 0x0a + 0x1a + 0x0a
	u32  size;
	u16  dirOff;
	u16  fileCnt;
	u8   noUse[8];
} __PACKED ST_GBFS_HEADER;

typedef struct {
	char fname[24];
	u32  size;
	u32  dataOff;
} __PACKED ST_GBFS_LIST;

typedef struct {
	ST_GBFS_HEADER* pHeader;
	ST_GBFS_LIST*   pList;
	u32             pos;
} ST_GBFS;

//---------------------------------------------------------------------------
void  GbfsInit(void);

IWRAM_CODE void* GbfsGetPointer(char* fname);
IWRAM_CODE void* GbfsGetPointer2(s32 cnt);
IWRAM_CODE void* GbfsGetSafePointer(char* fname);
IWRAM_CODE void* GbfsGetSafePointer2(s32 cnt);

char* GbfsGetFileName(void);
u32   GbfsGetFileSize(void);
u32   GbfsGetArcSize(void);
u32   GbfsGetArcCnt(void);


#ifdef __cplusplus
}
#endif
#endif
