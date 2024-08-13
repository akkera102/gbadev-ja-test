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

} __PACKED ST_FILE_LZ7_HEADER;

typedef struct {
	u16 cx;
	u16 cy;

} __PACKED ST_FILE_IMG_HEADER;

typedef struct {
	u16 sx;
	u16 sy;

} __PACKED ST_FILE_MSK_HEADER;


//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void);

EWRAM_CODE u8*  FileGetScn(char* p);
EWRAM_CODE u8*  FileGetLz7(char* p);
EWRAM_CODE u8*  FileGetImg(char* p);
EWRAM_CODE u8*  FileGetMsk(char* p);
EWRAM_CODE u8*  FileGetSnd(char* p);
EWRAM_CODE u8*  FileGetFmx(s32 no);
EWRAM_CODE s32  FileGetSize(void);


#ifdef __cplusplus
}
#endif
#endif
