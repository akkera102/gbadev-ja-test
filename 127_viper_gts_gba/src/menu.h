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
	MENU_TITLE_SEL_START,
	MENU_TITLE_SEL_LOAD,
};

//---------------------------------------------------------------------------

typedef struct {
	s32  type;							// ���j���[���
	s32  ret;							// ���j���[�I����
	s32  cnt;							// �I�𒆂̍���
	s32  msg;							// ���b�Z�[�W�ԍ��̐擪
	s32  reg;							// ���b�Z�[�W�ԍ��̓o�^��
	s32  sys;							// �V�X�e�����j���[�̃J�[�\���ʒu
	s32  jmp;							// ��ʃW�����v�p
	s32  jmpCur;						// ��ʃW�����v�J�[�\��

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

EWRAM_CODE void  MenuSetInit(s32 type, s32 ret, s32 cnt, s32 msg, s32 reg, void* pFunc, bool isDraw);
EWRAM_CODE void  MenuSetSystem(s32 cnt);
EWRAM_CODE void  MenuSetSystem2(void);
EWRAM_CODE void  MenuSetSave(s32 ret);
EWRAM_CODE void  MenuSetLoad(s32 ret);
EWRAM_CODE void  MenuSetNone(s32 ret);

EWRAM_CODE void  MenuSetJmp(s32 jmp);

EWRAM_CODE char* MenuGetStr(s32 sel);
EWRAM_CODE s32   MenuGetCnt(void);
EWRAM_CODE s32   MenuGetReg(void);
EWRAM_CODE s32   MenuGetType(void);


#ifdef __cplusplus
}
#endif
#endif
