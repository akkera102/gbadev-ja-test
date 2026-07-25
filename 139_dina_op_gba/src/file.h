#ifndef __FILE_H__
#define __FILE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FileInit(void);

u16* FileGetImg(s32 no);
u16* FileGetPal(s32 no);
u8*  FileGetMus(void);
s32  FileGetSize(void);


#ifdef __cplusplus
}
#endif
#endif
