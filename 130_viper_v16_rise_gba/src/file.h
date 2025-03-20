#ifndef __FILE_H__
#define __FILE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void);

EWRAM_CODE u16* FileGetImg(char* p, s32 no);
EWRAM_CODE u16* FileGetDat(char* p);
EWRAM_CODE u8*  FileGetScn(char* p);
EWRAM_CODE u8*  FileGetRaw(char* p);
EWRAM_CODE u8*  FileGetBgm(s32 no);
EWRAM_CODE s32  FileGetSize(void);


#ifdef __cplusplus
}
#endif
#endif
