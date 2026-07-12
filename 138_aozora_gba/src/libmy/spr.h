#ifndef __SPR_H__
#define __SPR_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SPR_MAX_DAT_CNT				312							// テキストバッファタイル数
#define SPR_MAX_DAT_SIZE			(0x20 * SPR_MAX_DAT_CNT)
#define SPR_MAX_TBL_SIZE			9984
#define SPR_MAX_TXT_CX				17
#define SPR_MAX_TXT_CY				6

#define SPR_FONT_IMG_CX				12
#define SPR_FONT_IMG_CY				10
#define SPR_FONT_IMG_BLANK_CY		2
#define SPR_FONT_MASK_BASE			0x7777
#define SPR_FONT_MASK_GRAY			0x5555
#define SPR_FONT_MASK_READ			0x3333


//---------------------------------------------------------------------------

typedef struct {
	u16 d0;
	u16 d1;
	u16 d2;
	u16 d3;
} __PACKED ST_SPR_OAM;

typedef struct {

	u16 tbl[SPR_MAX_TBL_SIZE/2] ALIGN(4);
	u16 msk;

} ST_SPR;


//---------------------------------------------------------------------------
void SprInit(void);

void SprSetChr(s32 no, s32 x, s32 y, u16 tile, u16 shape, u16 size);

IWRAM_CODE void SprSetTile(s32 no, s32 tile);
IWRAM_CODE void SprShow(s32 no);
IWRAM_CODE void SprHide(s32 no);
IWRAM_CODE void SprMove(s32 no, s32 x, s32 y);
IWRAM_CODE void SprClrDat(void);
IWRAM_CODE void SprVramSjis(s32 x, s32 y, u16 code);

void SprSetBase(void);
void SprSetGray(void);
void SprSetRead(void);
void SprSetColBase(u16 no);
void SprSetColRead(u16 no);

void SprShowMsg(void);
void SprShowCur(s32 no);
void SprShowNavi(void);
void SprHideMsg(void);
void SprHideCur(void);
void SprHideNavi(void);

void SprMoveCur(s32 x, s32 y);
void SprMoveNavi(s32 y);


#ifdef __cplusplus
}
#endif
#endif
