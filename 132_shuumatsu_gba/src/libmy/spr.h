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
#define SPR_MAX_TXT_CX				17
#define SPR_MAX_TXT_CY				10

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

	// スプライトバッファ領域に文字を書き込む為のテーブル
	u16 tbl[SPR_MAX_TBL_SIZE/2] ALIGN(4);
	// テキストの色マスク
	u16 msk;

	bool isMsg;
	bool isCur;

} ST_SPR;


//---------------------------------------------------------------------------
void SprInit(void);

IWRAM_CODE void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size);
IWRAM_CODE void SprSetTile(s32 no, s32 tile);
IWRAM_CODE void SprShow(s32 no);
IWRAM_CODE void SprHide(s32 no);
IWRAM_CODE void SprMove(s32 no, s32 x, s32 y);
IWRAM_CODE void SprClearDat(void);
IWRAM_CODE void SprDrawDatChr(s32 x, s32 y, u16 code);

IWRAM_CODE void SprSetWhite(void);
IWRAM_CODE void SprSetGray(void);
IWRAM_CODE void SprSetSelect(void);
IWRAM_CODE void SprSetSelectCol(u16 col);

IWRAM_CODE void SprShowMsg(void);
IWRAM_CODE void SprShowCur(s32 no);
IWRAM_CODE void SprHideMsg(void);
IWRAM_CODE void SprHideCur(void);

IWRAM_CODE void SprMoveCur(s32 x, s32 y);


#ifdef __cplusplus
}
#endif
#endif
