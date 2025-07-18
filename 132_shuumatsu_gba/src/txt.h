#ifndef __TXT_H__
#define __TXT_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "libmy/spr.h"

//---------------------------------------------------------------------------
#define TXT_MAX_REG_CNT					10
#define TXT_MAX_TITLE_LEN				(11*2+1)


//---------------------------------------------------------------------------

enum {
	TXT_CMD_MSG,
	TXT_CMD_CLS,
	TXT_CMD_LF,

};

typedef struct {
	s32   c;			// cmd
	char* p;			// msg

} ST_TXT_CMD_TBL;

typedef struct {

	bool  isExec;
	s32   x;
	s32   y;

	char  title[TXT_MAX_TITLE_LEN];

	bool  isBuf;
	u16   buf[SPR_MAX_TXT_CX * SPR_MAX_TXT_CY] ALIGN(4);

	s32   reg;
	ST_TXT_CMD_TBL tbl[TXT_MAX_REG_CNT];

} ST_TXT;


//---------------------------------------------------------------------------
void TxtInit(void);

void TxtExecNv(void);
void TxtExecSel(void);
void TxtExecRes(void);
void TxtExecLog(void);
void TxtExecMenu(void);

void TxtDrawChr(u16 code);
void TxtDrawStr(char* p);
void TxtDrawStrXy(s32 x, s32 y, char* p);

void TxtSetMsg(char* p);
void TxtSetCls(void);
void TxtSetLf(void);
void TxtSetTitle(char* p);
void TxtSetExec(void);

s32  TxtGetX(void);
s32  TxtGetY(void);

void TxtWriteBuf(void);
void TxtWriteSel(char* p);

void TxtClearBuf(void);
void TxtClearSel(void);

void TxtShow(void);
void TxtHide(void);

bool TxtIsExec(void);


#ifdef __cplusplus
}
#endif
#endif
