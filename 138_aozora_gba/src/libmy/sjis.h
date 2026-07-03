#ifndef __SJIS_H__
#define __SJIS_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define SJIS_CCT_HEAD_SIZE			16
#define SJIS_INVALID_INDEX			5			// エラー時のインデックスコード "・"
#define SJIS_FONT_CX				12
#define SJIS_FONT_CY				10

//---------------------------------------------------------------------------

typedef struct {
	u8 count;
	u8 reserved[3];
} __PACKED ST_SJIS_XCCTENT;


typedef struct {
	u8  start;
	u8  end;
	u16 offset;
} __PACKED ST_SJIS_XCCT;



typedef struct {
	u8*  pCct;			// フォントシート
	u16* pImg;			// フォントデータ

} ST_SJIS;


//---------------------------------------------------------------------------
void SjisInit(void);

IWRAM_CODE u16  SjisGetIdx(u16 code);
IWRAM_CODE u16* SjisGetImgPointer(u16 code);


#ifdef __cplusplus
}
#endif
#endif
