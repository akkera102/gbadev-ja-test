#ifndef __FILE_H__
#define __FILE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	u16 cx;
	u16 cy;

} __PACKED ST_FILE_IMG_HEADER;


//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void);

EWRAM_CODE u8*   FileGetImg(char* p);
EWRAM_CODE u8*   FileGetMsk(char* p);
EWRAM_CODE u8*   FileGetPat(s32 no);
EWRAM_CODE u8*   FileGetPata(s32 no);
EWRAM_CODE char* FileGetTxt(s32 chap, s32 no);
EWRAM_CODE u8*   FileGetMus(s32 no);
EWRAM_CODE u8*   FileGetSsg(s32 no);
EWRAM_CODE u8*   FileGetFmx(s32 no);
EWRAM_CODE s32   FileGetSize(void);
EWRAM_CODE bool  FileIsFirstPart(void);


#ifdef __cplusplus
}
#endif
#endif
