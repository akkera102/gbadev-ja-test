#ifndef __MENU_H__
#define __MENU_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "txt.h"

//---------------------------------------------------------------------------
#define MENU_BUF_SIZE			(TXT_SCREEN_CX*2+1)

enum {
	MENU_TYPE_SYSTEM,
	MENU_TYPE_SAVE,
	MENU_TYPE_LOAD,
	MENU_TYPE_NONE,
	MENU_TYPE_DEBUG,
	MENU_TYPE_BATTLE,
};

enum {
	MENU_RET_NONE,
	MENU_RET_SYSTEM,
	MENU_RET_NOVEL,
};

enum {
	MENU_SYSTEM_SEL_SAVE,
	MENU_SYSTEM_SEL_LOAD,
	MENU_SYSTEM_SEL_JUMP,
};

enum {
	MENU_DEBUG_SEL_FLAG1,
	MENU_DEBUG_SEL_FLAG2,
	MENU_DEBUG_SEL_MMODE,
};

enum {
	MENU_BATTLE_SEL_WIN,
	MENU_BATTLE_SEL_LOSE,
};

//---------------------------------------------------------------------------

typedef struct {
	s32  type;							// ���j���[���
	s32  ret;							// ���j���[�I����
	s32  cnt;							// �I�𒆂̍���
	s32  msg;							// ���b�Z�[�W�ԍ��̐擪
	s32  reg;							// ���b�Z�[�W�ԍ��̓o�^��
	s32  idx;							// ��ʃW�����v�p�C���f�b�N�X
	s32  idxCur;						// ��ʃW�����v�p�C���f�b�N�X�J�[�\��

	void (*pFunc)(u16 trg, u16 rep);	// �L�[���͎��̓���p�֐�
	char buf[MENU_BUF_SIZE];			// ���ڕ����ҏW�p�o�b�t�@

} ST_MENU;


//---------------------------------------------------------------------------
EWRAM_CODE void  MenuInit(void);
EWRAM_CODE void  MenuExec(void);

EWRAM_CODE void  MenuExecSystem(u16 trg, u16 rep);
EWRAM_CODE void  MenuExecSave(u16 trg, u16 rep);
EWRAM_CODE void  MenuExecLoad(u16 trg, u16 rep);
EWRAM_CODE void  MenuExecNone(u16 trg, u16 rep);
EWRAM_CODE void  MenuExecDebug(u16 trg, u16 rep);
EWRAM_CODE void  MenuExecBattle(u16 trg, u16 rep);

EWRAM_CODE void  MenuSetInit(s32 type, s32 ret, s32 cnt, s32 msg, s32 reg, void* pFunc, bool isDraw);
EWRAM_CODE void  MenuSetSystem(s32 cnt);
EWRAM_CODE void  MenuSetSystem2(void);
EWRAM_CODE void  MenuSetSave(s32 ret);
EWRAM_CODE void  MenuSetLoad(s32 ret);
EWRAM_CODE void  MenuSetNone(s32 ret);
EWRAM_CODE void  MenuSetDebug(void);
EWRAM_CODE void  MenuSetBattle(void);

EWRAM_CODE char* MenuGetStr(s32 sel);
EWRAM_CODE s32   MenuGetCnt(void);
EWRAM_CODE s32   MenuGetReg(void);
EWRAM_CODE s32   MenuGetType(void);
EWRAM_CODE s32   MenuGetIdx(void);


#ifdef __cplusplus
}
#endif
#endif
