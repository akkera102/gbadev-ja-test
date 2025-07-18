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

typedef struct {
	u16 sx;
	u16 sy;

} __PACKED ST_FILE_MSK_HEADER;

typedef struct {
	u16 cx;
	u16 cy;
	u16 max;
	u16 dmy;

} __PACKED ST_FILE_EFF_HEADER;


//---------------------------------------------------------------------------
void FileInit(void);

u8*  FileGetScn(s32 no);
u8*  FileGetImg(s32 no);
u8*  FileGetMsk(s32 no);
u8*  FileGetEff(s32 no);
u8*  FileGetBgm(s32 no);
u8*  FileGetFmx(s32 no);
s32  FileGetSize(void);


#ifdef __cplusplus
}
#endif
#endif
