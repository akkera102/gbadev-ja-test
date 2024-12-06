#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				39
#define NV_MAX_VAR_CNT					256
#define NV_MAX_CALL_CNT					5


enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_SEL,
	NV_ACT_LOAD,
};

//---------------------------------------------------------------------------

typedef struct {
	char* pStr;
	void  (*pFunc)(void);

} ST_NV_PARSE_TABLE;


typedef struct {
	s32   reg;			// �o�^��
	s32   ret;			// �I����̕ԋp��ϐ�
	s32   cnt;			// ���݂̑I����
	char* p[3];			// �I�����̕�����

} ST_NV_SEL;


typedef struct {
	s32   act;
	s32   step;
	s32   sleep;

	char* pStr;						// �X�N���v�g�t�@�C����
	u8*   pScn;						// �X�N���v�g�擪
	char* pCur;						// �J�[�\��
	u32*  pLbl;						// �W�����v�e�[�u���擪
	s32   lblMax;					// �W�����v�e�[�u���̌�
	bool  isLoop;


	// �`�抮���E�F�C�g�L��
	bool  isBuf;
	s32   bNo;

	// �X�N���[�������E�F�C�g�L��
	bool  isScr;
	s32   sNo;

	// �L�[���͎���PCM�Đ������E�F�C�g�L��
	bool  isPcm;
	s32   pcmWait;

	// �L�[���͂̃X�N���[������ƕ\���L��
	bool  isKeyScr;


	s32   callCnt;
	char* call[NV_MAX_CALL_CNT];

	u16   lastVar;
	u16   var[NV_MAX_VAR_CNT];

	ST_NV_SEL sel;

} ST_NV;


//---------------------------------------------------------------------------
EWRAM_CODE void  NvInit(void);
EWRAM_CODE void  NvExec(void);
EWRAM_CODE void  NvExecKey(void);
EWRAM_CODE void  NvExecSel(void);
EWRAM_CODE void  NvExecLoad(void);

EWRAM_CODE void  NvSetAct(s32 act);
EWRAM_CODE void  NvSetScn(char* pStr);
EWRAM_CODE void  NvSetScn2(s32 no);
EWRAM_CODE void  NvSetScn3(s32 no);
EWRAM_CODE void  NvSetLbl(s32 no);
EWRAM_CODE void  NvSetVar(s32 no, s32 num);

EWRAM_CODE s32   NvGetVar(s32 no);
EWRAM_CODE s32   NvGetSelReg(void);
EWRAM_CODE s32   NvGetSelCnt(void);
EWRAM_CODE char* NvGetSelStr(s32 no);
EWRAM_CODE char* NvGetStr(void);
EWRAM_CODE void  NvPopAct(void);

EWRAM_CODE void  NvPushCall(s32 no);
EWRAM_CODE void  NvPopCall(void);

EWRAM_CODE bool  NvIsActSel(void);

EWRAM_CODE s32   NvNextCurNum(void);
EWRAM_CODE char* NvNextCurStr(void);


#ifdef __cplusplus
}
#endif
#endif

