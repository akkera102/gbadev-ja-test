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
	MENU_TYPE_OPTION,
	MENU_TYPE_SAVE,
	MENU_TYPE_LOAD,
	MENU_TYPE_NONE,
	MENU_TYPE_TITLE,
	MENU_TYPE_DEBUG,
};

enum {
	MENU_RET_NONE,
	MENU_RET_TITLE,
	MENU_RET_SYSTEM,
	MENU_RET_OPTION,
	MENU_RET_NOVEL,
};

enum {
	MENU_SYSTEM_SEL_SAVE,
	MENU_SYSTEM_SEL_LOAD,
	MENU_SYSTEM_SEL_SKIP,
	MENU_SYSTEM_SEL_NONE,
	MENU_SYSTEM_SEL_LOG,
	MENU_SYSTEM_SEL_OPTION,
	MENU_SYSTEM_SEL_DEBUG,
};

enum {
	MENU_TITLE_SEL_START,
	MENU_TITLE_SEL_LOAD,
};

enum {
	MENU_OPTION_SEL_TXT_FADE,
	MENU_OPTION_SEL_TXT_WAIT,
	MENU_OPTION_SEL_HOWTO,
};

enum {
	MENU_DEBUG_SEL_JUMP,
	MENU_DEBUG_VAR_1,
	MENU_DEBUG_VAR_2,
	MENU_DEBUG_VAR_3,
	MENU_DEBUG_VAR_4,
};

//---------------------------------------------------------------------------

typedef struct {
	s32  type;					// ���j���[���
	s32  ret;					// ���j���[�I����
	s32  sel;					// �I�𒆂̍���
	s32  msg;					// ���b�Z�[�W�ԍ��̐擪
	s32  reg;					// ���b�Z�[�W�ԍ��̓o�^��

	void (*pFunc)(u16 trg);		// �L�[���͎��̓���p�֐�
	char buf[MENU_BUF_SIZE];	// ���ڕ����ҏW�p�o�b�t�@

	bool isHowto;				// �U�����̕\���L��
	s32  siori;					// �Z�[�u���[�h�I�������l
	s32  day;					// �f�o�b�O�p���t

} ST_MENU;


//---------------------------------------------------------------------------
EWRAM_CODE void  MenuInit(void);
EWRAM_CODE void  MenuExec(void);

EWRAM_CODE void  MenuExecSystem(u16 trg);
EWRAM_CODE void  MenuExecOption(u16 trg);
EWRAM_CODE void  MenuExecSave(u16 trg);
EWRAM_CODE void  MenuExecLoad(u16 trg);
EWRAM_CODE void  MenuExecNone(u16 trg);
EWRAM_CODE void  MenuExecTitle(u16 trg);
EWRAM_CODE void  MenuExecDebug(u16 trg);

EWRAM_CODE void  MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, void* pFunc, bool isDraw);
EWRAM_CODE void  MenuSetSystem(s32 sel);
EWRAM_CODE void  MenuSetOption(s32 sel);
EWRAM_CODE void  MenuSetSave(s32 ret);
EWRAM_CODE void  MenuSetLoad(s32 ret);
EWRAM_CODE void  MenuSetNone(s32 ret);
EWRAM_CODE void  MenuSetTitle(s32 sel);
EWRAM_CODE void  MenuSetDebug(s32 sel);

EWRAM_CODE char* MenuGetStrTitle(void);
EWRAM_CODE char* MenuGetStrSelect(s32 sel);
EWRAM_CODE char* MenuGetStrSelectOption(s32 sel);
EWRAM_CODE char* MenuGetStrSelectDebug(s32 sel);
EWRAM_CODE s32   MenuGetSel(void);
EWRAM_CODE s32   MenuGetReg(void);
EWRAM_CODE s32   MenuGetType(void);

EWRAM_CODE bool  MenuIsHowto(void);

#ifdef __cplusplus
}
#endif
#endif
