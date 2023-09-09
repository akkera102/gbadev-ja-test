#ifndef __LEX_H__
#define __LEX_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------
#define LEX_MAX_STR_CNT				64

enum {
	LEX_TOKEN_NUM,
	LEX_TOKEN_STR,
	LEX_TOKEN_CUM,
	LEX_TOKEN_SPACE,
	LEX_TOKEN_COMMENT,
	LEX_TOKEN_DQUOTE,
	LEX_TOKEN_CR,
	LEX_TOKEN_LF,
	LEX_TOKEN_END,
};


//---------------------------------------------------------------------------
typedef struct {
	char* pCur;								// カーソル
	char* pOld;								// UnGet用カーソル
	u32   type;								// トークンタイプ
	s32   num;								// 数字 or 文字列の長さ
	char  str[LEX_MAX_STR_CNT] ALIGN(4);	// 文字列
} ST_LEX;


//---------------------------------------------------------------------------
EWRAM_CODE void  LexInit(void);
EWRAM_CODE void  LexSetCur(char* pCur);
EWRAM_CODE char* LexGetCur(void);

EWRAM_CODE s32   LexGetNum(void);
EWRAM_CODE char* LexGetStr(void);
EWRAM_CODE char  LexGetChr(void);

EWRAM_CODE void  LexGetToken(bool isChr);
EWRAM_CODE u32   LexGetType(char chr);
EWRAM_CODE void  LexSkipStr(char* pStr);
EWRAM_CODE void  LexSkipLine(void);
EWRAM_CODE void  LexSkipLf(void);
EWRAM_CODE void  LexUnGet(void);

EWRAM_CODE bool  LexIsEnd(void);

#ifdef __cplusplus
}
#endif
#endif
