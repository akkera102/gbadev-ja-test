#ifndef __FILE_H__
#define __FILE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	u8 evtMax;
	u8 msgMax;

} __PACKED ST_FILE_SCN_HEADER;


typedef struct {
	u16 cx;
	u16 cy;

} __PACKED ST_FILE_IMG_HEADER;



//---------------------------------------------------------------------------
EWRAM_CODE void FileInit(void);

EWRAM_CODE u8*  FileGetTxt(u32 no);
EWRAM_CODE u8*  FileGetBg(u32 no);
EWRAM_CODE u8*  FileGetChr(u32 no);
EWRAM_CODE u8*  FileGetChrMask(u32 no);
EWRAM_CODE u8*  FileGetVis(u32 no);
EWRAM_CODE u8*  FileGetMus(u32 no);
EWRAM_CODE u8*  FileGetSe(u32 no);

EWRAM_CODE u32  FileGetSize(void);


#ifdef __cplusplus
}
#endif
#endif
