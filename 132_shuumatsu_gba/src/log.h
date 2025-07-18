#ifndef __LOG_H__
#define __LOG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "libmy/spr.h"

//---------------------------------------------------------------------------
#define LOG_MAX_CNT					16


//---------------------------------------------------------------------------

typedef struct {
	s32  reg;		// 登録数
	s32  cnt;		// 書き込み場所（リングバッファ用）
	s32  sel;		// 現在の表示位置

	u16  buf[LOG_MAX_CNT][SPR_MAX_TXT_CX * SPR_MAX_TXT_CY] ALIGN(4);

} ST_LOG;


//---------------------------------------------------------------------------
void LogInit(void);
void LogExec(void);

void LogSetInit(void);
u16* LogGetBuf(void);
void LogAddBuf(u16* p);

bool LogIsEmpty(void);


#ifdef __cplusplus
}
#endif
#endif

