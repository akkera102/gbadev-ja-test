#ifndef __LOG_H__
#define __LOG_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "txt.h"

//---------------------------------------------------------------------------
#define LOG_MAX_CNT					4


enum {
	LOG_RET_NOVEL,
	LOG_RET_SYSTEM,
};

//---------------------------------------------------------------------------

typedef struct {
	bool isDraw;

	s32  reg;		// �o�^��
	s32  cnt;		// �������ݏꏊ�i�����O�o�b�t�@�p�j
	s32  sel;		// ���݂̃Z���N�g
	s32  ret;		// ���A��

	u16  buf[LOG_MAX_CNT][TXT_SCREEN_CX * TXT_SCREEN_CY] ALIGN(4);

} ST_LOG;


//---------------------------------------------------------------------------
EWRAM_CODE void LogInit(void);
EWRAM_CODE void LogExec(void);

EWRAM_CODE void LogSetInit(u32 ret);

EWRAM_CODE u16* LogGetBuf(void);
EWRAM_CODE void LogAddBuf(u16* p);
EWRAM_CODE void LogDrawBuf(s32 sel);

EWRAM_CODE bool LogIsEmpty(void);


#ifdef __cplusplus
}
#endif
#endif

