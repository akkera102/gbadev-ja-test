#ifndef __FILE_H__
#define __FILE_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define FILE_MAX_WORK_SIZE				0x4000			// スクリプトの解凍：最大16166（調査済）


//---------------------------------------------------------------------------

typedef struct {
	u16 cx;
	u16 cy;

} __PACKED ST_FILE_BG_HEADER;


typedef struct {
	u16 cx;
	u16 cy;

} __PACKED ST_FILE_CHR_HEADER;


typedef struct {
	char work[FILE_MAX_WORK_SIZE] ALIGN(4);
	s32  size;

} ST_FILE;

//---------------------------------------------------------------------------
void FileInit(void);

u8*   FileGetBg(s32 no);
u8*   FileGetChr(s32 no);
u8*   FileGetMsk(s32 no);
u8*   FileGetMus(s32 no);
u8*   FileGetSnd(s32 no);
char* FileGetTxt(s32 no);
s32   FileGetTxtSize(void);
s32   FileGetSize(void);


#ifdef __cplusplus
}
#endif
#endif
