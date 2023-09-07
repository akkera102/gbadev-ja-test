#ifndef __TXT_H__
#define __TXT_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define TXT_SCREEN_CX					17
#define TXT_SCREEN_CY					10
#define TXT_CURSOR_WAIT_CNT				30
#define TXT_SIORI_SIZE					(22+1)


//---------------------------------------------------------------------------
typedef struct {

	// �\���L��
	bool isShow;

	// ���y�[�W�L��
	bool isPage;

	// �e�L�X�g���A
	bool isRes;

	// �����\��
	s32  x;
	s32  y;

	// �����\��
	bool isChr;
	s32  drawCnt;
	s32  waitCnt;
	s32  waitMax;

	// �J�[�\��
	bool isCur;
	bool isCurBlink;
	s32  curCnt;

	// �֑������������[�N�G���A
	u16  work[TXT_SCREEN_CX * TXT_SCREEN_CY] ALIGN(4);
	s32  workCnt;

	// ���b�Z�[�W�ޔ�p�o�b�t�@
	u16  buf[TXT_SCREEN_CX * TXT_SCREEN_CY] ALIGN(4);
	bool isBuf;

	// ������p�o�b�t�@
	char siori[TXT_SIORI_SIZE];

} ST_TXT;


//---------------------------------------------------------------------------
EWRAM_CODE void TxtInit(void);
EWRAM_CODE void TxtExecChr(void);
EWRAM_CODE void TxtExecCur(void);
EWRAM_CODE void TxtExecLog(void);
EWRAM_CODE void TxtExecMenu(void);

EWRAM_CODE void TxtDrawChr(u16 code);
EWRAM_CODE void TxtDrawStr(char* p);
EWRAM_CODE void TxtDrawStrXy(u32 x, u32 y, char* p);
EWRAM_CODE void TxtDrawWork(void);
EWRAM_CODE void TxtDrawFull(u16* pStr);

EWRAM_CODE void TxtSetChr(void);
EWRAM_CODE void TxtSetCur(bool is);
EWRAM_CODE void TxtSetRes(void);
EWRAM_CODE void TxtSetPage(void);
EWRAM_CODE void TxtSetPageNew(void);
EWRAM_CODE void TxtSetDraw(char* p);
IWRAM_CODE bool TxtCalcStr(char* p);
IWRAM_CODE bool TxtIsChrFront(u16 code);
IWRAM_CODE bool TxtIsChrBack(u16 code);

EWRAM_CODE void TxtClear(void);
EWRAM_CODE void TxtClearBuf(void);
EWRAM_CODE void TxtClearDat(void);
EWRAM_CODE void TxtClearXY(void);

EWRAM_CODE void TxtShowWindow(void);
EWRAM_CODE void TxtShowMsg(void);
EWRAM_CODE void TxtHideWindow(void);
EWRAM_CODE void TxtHideMsg(void);

EWRAM_CODE bool TxtIsChr(void);
EWRAM_CODE bool TxtIsCur(void);

EWRAM_CODE void TxtSetSiori(char* p);

EWRAM_CODE void TxtSetWaitMax(u32 num);
EWRAM_CODE u32  TxtGetWaitMax(void);

EWRAM_CODE void TxtRestart(void);

EWRAM_CODE void TxtSetLf(void);
EWRAM_CODE void TxtSetBuf(bool is);


#ifdef __cplusplus
}
#endif
#endif
