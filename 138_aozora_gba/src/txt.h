#ifndef __TXT_H__
#define __TXT_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "libmy/spr.h"

//---------------------------------------------------------------------------
#define TXT_MAX_SIORI_LEN				(15*2+1)


//---------------------------------------------------------------------------

typedef struct {

	bool  isExec;
	s32   x;
	s32   y;
	s32   baseNo;		// í èÌêFÇÃî‘çÜ
	s32   readNo;		// ä˘ì«êFÇÃî‘çÜ

	char  siori[TXT_MAX_SIORI_LEN] ALIGN(4);
	u16   buf[SPR_MAX_TXT_CX * SPR_MAX_TXT_CY] ALIGN(4);

} ST_TXT;


//---------------------------------------------------------------------------
void TxtInit(void);

void TxtExecNv(void);
void TxtExecSel(void);
void TxtExecLog(void);
void TxtExecMenu(void);

void TxtDrawStr(s32 x, s32 y, char* p);

void TxtClrBuf(void);
void TxtClrSpr(void);
void TxtAddBuf(char* p);
void TxtAddLog(void);
void TxtAddLog2(char* p);

void TxtSetSiori(char* p);
void TxtSetExec(void);
void TxtSetBaseNo(s32 no);
void TxtSetReadNo(s32 no);
s32  TxtGetBaseNo(void);
s32  TxtGetReadNo(void);
s32  TxtGetX(void);
s32  TxtGetY(void);

void TxtShow(void);
void TxtHide(void);
void TxtLoad(void);

bool TxtIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
