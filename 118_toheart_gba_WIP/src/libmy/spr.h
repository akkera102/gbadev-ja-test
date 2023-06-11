#ifndef __SPR_H__
#define __SPR_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SPR_MAX_ATTR_CNT			10
#define SPR_MAX_DAT_SIZE			(((256/2) * 128) - ((16/2) * 16))	// スプライト全体バッファ - カーソルサイズ

#define SPR_FONT_IMG_CX				12
#define SPR_FONT_IMG_CY				10
#define SPR_FONT_IMG_BLANK_CY		2
#define SPR_FONT_DAT_SIZE			128
#define SPR_FONT_CCT_HEAD_SIZE		16
#define SPR_FONT_INVALID_INDEX		5				// エラー時のインデックスコード "・"
#define SPR_FONT_MASK_WHITE			0x5555
#define SPR_FONT_MASK_GRAY			0x3333


//---------------------------------------------------------------------------

typedef struct {
	u8 count;
	u8 reserved[3];
} __PACKED ST_XCCTENT;


typedef struct {
	u8  start;
	u8  end;
	u16 offset;
} __PACKED ST_XCCT;


typedef struct {
	u16 d0;
	u16 d1;
	u16 d2;
	u16 d3;
} __PACKED ST_SPR_ATTR;

typedef struct {
	bool isDrawChr;
	bool isDrawDat;

	u8*  pCct;			// フォントシート
	u16* pImg;			// フォントデータ
	u16  mask;			// フォントマスク

	u8 dat[SPR_MAX_DAT_SIZE] ALIGN(4);
	ST_SPR_ATTR attr[SPR_MAX_ATTR_CNT] ALIGN(4);

} ST_SPR;


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void);
EWRAM_CODE void SprExec(void);

EWRAM_CODE void SprSetDatItem(void);
EWRAM_CODE void SprSetChrItem(void);
EWRAM_CODE void SprSetFontItem(void);
EWRAM_CODE void SprSetDat(u16* pTile, u32 tileSize, u16* pPal, u32 palSize);
EWRAM_CODE void SprSetChr(u32 no, u32 x, u32 y, u16 tile, u16 shape, u16 size);
EWRAM_CODE void SprShow(u32 no);
EWRAM_CODE void SprHide(u32 no);
EWRAM_CODE void SprMove(u32 no, u32 x, u32 y);
EWRAM_CODE void SprClearDat(void);
IWRAM_CODE void SprDrawDatChr(u32 x, u32 y, u16 code);
IWRAM_CODE void SprDrawDatChrSub1(u32 x, u32 y, u16 code);
IWRAM_CODE void SprDrawDatChrSub2(u32 x, u32 y, u16 code);
IWRAM_CODE void SprDrawDatChrSub3(u32 x, u32 y, u16 code);
IWRAM_CODE void SprDrawDatChrSub4(u32 x, u32 y, u16 code);

IWRAM_CODE u16  SprGetSjisIdx(u16 code);
EWRAM_CODE void SprSetImgWhite(void);
EWRAM_CODE void SprSetImgGray(void);
EWRAM_CODE bool SprIsImgWhite(void);

EWRAM_CODE void SprShowCursor(void);
EWRAM_CODE void SprHideCursor(void);
EWRAM_CODE void SprMoveCursor(u32 x, u32 y);

EWRAM_CODE void SprShowWindow(void);
EWRAM_CODE void SprHideWindow(void);

#ifdef __cplusplus
}
#endif
#endif
