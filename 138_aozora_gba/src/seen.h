#ifndef __READ_H__
#define __READ_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define SEEN_MAX_FL_CNT						110				// FL変数：最大 102（調査済）
#define SEEN_MAX_FW_CNT						30				// FW変数：最大  29（調査済）
#define SEEN_MAX_READ_SIZE					3000			// 既読　：最大2979（調査済）23833/8+1

//---------------------------------------------------------------------------

typedef struct {
	s8   fl[SEEN_MAX_FL_CNT];
	s8   fw[SEEN_MAX_FW_CNT];
	u8   read[SEEN_MAX_READ_SIZE] ALIGN(4);

} ST_SEEN;

//---------------------------------------------------------------------------
void  SeenInit(void);

void  SeenSetFl(s32 i, s8 n);
void  SeenSetFw(s32 i, s8 n);
void  SeenSetRead(s32 i, u8 b);

s8    SeenGetFl(s32 i);
s8    SeenGetFw(s32 i);
bool  SeenIsRead(s32 i, u8 b);

u32   SeenGetIcoBit(void);


#ifdef __cplusplus
}
#endif
#endif
