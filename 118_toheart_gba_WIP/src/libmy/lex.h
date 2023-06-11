#ifndef __LEX_H__
#define __LEX_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------
#define LEX_MAX_STR_SIZE				(255)


//---------------------------------------------------------------------------

typedef struct {
	char* pCur;

	s32   num;
	char  str[LEX_MAX_STR_SIZE+1] ALIGN(4);

} ST_LEX;


//---------------------------------------------------------------------------
EWRAM_CODE void  LexInit(void);
EWRAM_CODE void  LexSetCur(char* p);

EWRAM_CODE s32   LexGetNum(void);
EWRAM_CODE s32   LexGetHex(void);
EWRAM_CODE char* LexGetStr(void);

EWRAM_CODE void  LexSkipLine(void);
EWRAM_CODE void  LexSkipSpace(void);


#ifdef __cplusplus
}
#endif
#endif
