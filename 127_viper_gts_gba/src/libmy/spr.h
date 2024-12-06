#ifndef __SPR_H__
#define __SPR_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SPR_MAX_MSG_CNT				(32*4)							// テキストバッファタイル数
#define SPR_MAX_MSG_SIZE			(0x20 * SPR_MAX_MSG_CNT)
#define SPR_MAX_TBL_SIZE			0x3400

#define SPR_FONT_MASK_WHITE			0x7777
#define SPR_FONT_MASK_GRAY			0x5555
#define SPR_FONT_MASK_SELECT		0x3333

//---------------------------------------------------------------------------

typedef struct {
	u16 d0;
	u16 d1;
	u16 d2;
	u16 d3;
} __PACKED ST_SPR_OAM;

typedef struct {

	u16  mask;			// テキストの色マスク

	bool isCur;
	s32  curNo;
	s32  curPat;
	s32  curWait;

} ST_SPR;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void);

EWRAM_CODE void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size);
EWRAM_CODE void SprSetTile(s32 no, s32 tile);
EWRAM_CODE void SprShow(s32 no);
EWRAM_CODE void SprHide(s32 no);
EWRAM_CODE void SprMove(s32 no, s32 x, s32 y);
EWRAM_CODE void SprClearMsg(void);

IWRAM_CODE void SprDrawMsg(s32 x, s32 y, u16 code);

EWRAM_CODE void SprSetWhite(void);
EWRAM_CODE void SprSetGray(void);

EWRAM_CODE void SprShowMsg(void);
EWRAM_CODE void SprShowCur(s32 id);
EWRAM_CODE void SprHideMsg(void);
EWRAM_CODE void SprHideCur(void);


#ifdef __cplusplus
}
#endif
#endif
