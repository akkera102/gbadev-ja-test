#ifndef __SPR_H__
#define __SPR_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SPR_MAX_OAM_CNT				12
#define SPR_MAX_DAT_CNT				424							// テキストバッファタイル数
#define SPR_MAX_DAT_SIZE			(0x20 * SPR_MAX_DAT_CNT)
#define SPR_MAX_TBL_SIZE			0x3400

#define SPR_FONT_IMG_CX				12
#define SPR_FONT_IMG_CY				10
#define SPR_FONT_IMG_BLANK_CY		2

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

	u16 tbl[SPR_MAX_TBL_SIZE/2] ALIGN(4);
	u16 mask;			// テキストの色マスク

} ST_SPR;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void);

EWRAM_CODE void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size);
EWRAM_CODE void SprShow(s32 no);
EWRAM_CODE void SprHide(s32 no);
EWRAM_CODE void SprMove(s32 no, s32 x, s32 y);
EWRAM_CODE void SprClearDat(void);
IWRAM_CODE void SprDrawDatChr(s32 x, s32 y, u16 code);

EWRAM_CODE void SprSetWhite(void);
EWRAM_CODE void SprSetGray(void);
EWRAM_CODE void SprSetSelect(void);
EWRAM_CODE void SprSetHowto(s32 ans, s32 reg);

EWRAM_CODE void SprShowMsg(void);
EWRAM_CODE void SprShowCur(void);
EWRAM_CODE void SprShowHowto(void);

EWRAM_CODE void SprHideMsg(void);
EWRAM_CODE void SprHideCur(void);
EWRAM_CODE void SprHideHowto(void);

EWRAM_CODE void SprMoveCur(s32 x, s32 y);


#ifdef __cplusplus
}
#endif
#endif
