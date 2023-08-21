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
#define SPR_FONT_DAT_SIZE			128
#define SPR_FONT_CCT_HEAD_SIZE		16
#define SPR_FONT_INVALID_INDEX		5							// エラー時のインデックスコード "・"
#define SPR_FONT_MASK_WHITE			0x5555
#define SPR_FONT_MASK_GRAY			0x3333


//---------------------------------------------------------------------------

typedef struct {
	u16 d0;
	u16 d1;
	u16 d2;
	u16 d3;
} __PACKED ST_SPR_OAM;

typedef struct {
	bool isDrawOam;
	bool isDrawDat;

	ST_SPR_OAM oam[SPR_MAX_OAM_CNT] ALIGN(4);
	u8  dat[SPR_MAX_DAT_SIZE] ALIGN(4);
	u16 tbl[SPR_MAX_TBL_SIZE/2] ALIGN(4);

	u16  mask;			// テキストの色マスク

} ST_SPR;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void);
EWRAM_CODE void SprExec(void);

EWRAM_CODE void SprSetChr(u32 no, u32 x, u32 y, u16 tile, u16 shape, u16 size);
EWRAM_CODE void SprShow(u32 no);
EWRAM_CODE void SprHide(u32 no);
EWRAM_CODE void SprMove(u32 no, u32 x, u32 y);
EWRAM_CODE void SprClearDat(void);
IWRAM_CODE void SprDrawDatChr(u32 x, u32 y, u16 code);

EWRAM_CODE void SprSetImgWhite(void);
EWRAM_CODE void SprSetImgGray(void);
EWRAM_CODE bool SprIsImgWhite(void);

EWRAM_CODE void SprShowCursor(void);
EWRAM_CODE void SprHideCursor(void);
EWRAM_CODE void SprMoveCursor(u32 x, u32 y);

EWRAM_CODE void SprShowWindow(void);
EWRAM_CODE void SprHideWindow(void);

// sakura用
IWRAM_CODE void SprDirectSetSize(u32 no, u32 size, u32 form, u32 col);
IWRAM_CODE void SprDirectSetChr(u32 no, u32 ch);
IWRAM_CODE void SprDirectMove(u32 no, s32 x, s32 y);


#ifdef __cplusplus
}
#endif
#endif
