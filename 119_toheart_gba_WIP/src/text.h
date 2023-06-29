#ifndef __TEXT_H__
#define __TEXT_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define TEXT_SCREEN_CX					17
#define TEXT_SCREEN_CY					10
#define TEXT_CURSOR_WAIT_CNT			30
#define TEXT_SIORI_SIZE					(22+1)


//---------------------------------------------------------------------------
typedef struct {

	// �\���L��
	bool isShow;

	// ���y�[�W�L��
	bool isPage;

	// �e�L�X�g���A
	bool isRes;

	// �����\��
	u8   x;
	u8   y;

	// �����\��
	bool isChr;
	u8   drawCnt;
	u8   waitCnt;
	u8   waitMax;

	// �J�[�\��
	bool isCur;
	bool isCurBlink;
	u8   curCnt;

	// �֑������������[�N�G���A
	u16  work[TEXT_SCREEN_CX * TEXT_SCREEN_CY] ALIGN(4);
	u8   workCnt;

	// ���b�Z�[�W�ޔ�p�o�b�t�@
	u16  buf[TEXT_SCREEN_CX * TEXT_SCREEN_CY] ALIGN(4);
	bool isBuf;

	// ������p�o�b�t�@
	char siori[TEXT_SIORI_SIZE];

} ST_TEXT;


//---------------------------------------------------------------------------
EWRAM_CODE void TextInit(void);
EWRAM_CODE void TextExecChr(void);
EWRAM_CODE void TextExecCur(void);
EWRAM_CODE void TextExecLog(void);
EWRAM_CODE void TextExecMenu(void);

EWRAM_CODE void TextDrawChr(u16 code);
EWRAM_CODE void TextDrawStr(char* p);
EWRAM_CODE void TextDrawStrXy(u32 x, u32 y, char* p);
EWRAM_CODE void TextDrawWork(void);
EWRAM_CODE void TextDrawLog(void);
EWRAM_CODE void TextDrawMenu(void);
EWRAM_CODE void TextDrawFull(u16* pStr);

EWRAM_CODE void TextSetChr(void);
EWRAM_CODE void TextSetCur(bool is);
EWRAM_CODE void TextSetRes(void);
EWRAM_CODE void TextSetPage(void);
EWRAM_CODE void TextSetDraw(char* p);
IWRAM_CODE bool TextCalcStr(char* p);
IWRAM_CODE bool TextIsChrFront(u16 code);
IWRAM_CODE bool TextIsChrBack(u16 code);

EWRAM_CODE void TextClear(void);
EWRAM_CODE void TextClearBuf(void);
EWRAM_CODE void TextClearDat(void);
EWRAM_CODE void TextClearXY(void);

EWRAM_CODE void TextShowWindow(void);
EWRAM_CODE void TextShowMsg(void);
EWRAM_CODE void TextHideWindow(void);
EWRAM_CODE void TextHideMsg(void);

EWRAM_CODE bool TextIsChr(void);
EWRAM_CODE bool TextIsCur(void);

EWRAM_CODE void TextSetSiori(char* p);

EWRAM_CODE void TextSetWaitMax(u32 num);
EWRAM_CODE u32  TextGetWaitMax(void);

EWRAM_CODE void TextRestart(void);

EWRAM_CODE void TextSetLf(void);


#ifdef __cplusplus
}
#endif
#endif
