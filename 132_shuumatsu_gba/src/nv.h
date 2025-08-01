#ifndef __NV_H__
#define __NV_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------
#define NV_MAX_PARSE_CNT				20
#define NV_MAX_VAR_CNT					40				// �X�N���v�g�ϐ��F�ő� 33�i�����ρj
#define NV_MAX_READ_CNT					180				// ���ǃt���O�@�@�F�ő�177�i�����ρj(256*5+136) / 8
#define NV_MAX_EXPR_CNT					10

enum {
	NV_ACT_PARSE,
	NV_ACT_KEY,
	NV_ACT_SEL,
	NV_ACT_LOAD,
};

//---------------------------------------------------------------------------

typedef struct {
	bool isUse[NV_MAX_EXPR_CNT];
	s32  cnt;
} ST_NV_EXPR;

typedef struct {
	bool  isUse;
	s32   no;
	char* pCur;
} ST_NV_CALL;

typedef struct {
	s32   reg;			// �o�^��
	s32   cnt;			// ���݂̑I����
	char* p[4];			// �e�L�X�g
	u16   ofs[4];		// �W�����v�I�t�Z�b�g
} ST_NV_SEL;


typedef struct {
	s32   act;
	s32   prev;			// �O��act���
	s32   step;
	s32   wait;

	bool  isLoop;
	bool  isSkip;		// ���b�Z�[�W�X�L�b�v
	bool  isOmit;		// ���b�Z�[�W�X�L�b�v�����t���O
	bool  isPage;		// ���y�[�W
	bool  isEffect;		// �G�t�F�N�g���s

	s32   no;
	char* pScn;
	char* pCur;

	// ���ǃt���O
	u8    read[NV_MAX_READ_CNT];
	s32   idx;
	s32   bit;

	// �X�N���v�g�ϐ�
	u8    var[NV_MAX_VAR_CNT];

	ST_NV_EXPR expr;
	ST_NV_CALL call;
	ST_NV_SEL  sel;

} ST_NV;


//---------------------------------------------------------------------------
void  NvInit(void);
void  NvInitVar(void);
void  NvExec(void);
void  NvExecKey(void);
void  NvExecSel(void);
void  NvExecLoad(void);

void  NvSetAct(s32 act);
void  NvSetScn(s32 no);
void  NvSetScn2(s32 no);
void  NvSetSkip(void);
void  NvSetOmit(bool is);
void  NvSetRead(s32 i, s32 b);
void  NvSetVar(s32 no, s32 num);

s32   NvGetSelReg(void);
s32   NvGetSelCnt(void);
char* NvGetSelStr(s32 no);
s32   NvGetVar(s32 no);

s32   NvCurNum(void);
s32   NvCurHex(void);
char* NvCurStr(void);
char  NvCurChr(void);
void  NvCurSkip(s32 cnt);

bool  NvIsSkip(void);
bool  NvIsOmit(void);
bool  NvIsRead(s32 i, s32 b);
bool  NvIsReadValid(void);
bool  NvIsAct(s32 act);


#ifdef __cplusplus
}
#endif
#endif
