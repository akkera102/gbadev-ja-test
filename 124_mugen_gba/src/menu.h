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
	MENU_ACT_DRAW,
	MENU_ACT_SELECT,
};

enum {
	MENU_TYPE_TITLE,
	MENU_TYPE_SYSTEM,
	MENU_TYPE_OPTION,
	MENU_TYPE_SAVE,
	MENU_TYPE_LOAD,
	MENU_TYPE_NONE,
	NEMU_TYPE_ENDING1,
	NEMU_TYPE_ENDING2,
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
};

enum {
	MENU_TITLE_SEL_START,
	MENU_TITLE_SEL_LOAD,
	MENU_TITLE_SEL_ENDING,
};

enum {
	MENU_OPTION_SEL_WINDOW,
	MENU_OPTION_SEL_COLOR,
};


//---------------------------------------------------------------------------

typedef struct {
	s32  type;					// メニュー種類
	s32  ret;					// メニュー終了先
	s32  sel;					// 選択中の項目
	s32  msg;					// メッセージ番号の先頭
	s32  reg;					// メッセージ番号の登録数

	void (*pFunc)(u16 trg);		// キー入力時の動作用関数
	char buf[MENU_BUF_SIZE];	// 項目文字編集用バッファ

	s32  chap;					// 章ジャンプ（デバッグ用）

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
EWRAM_CODE void  MenuExecEnding1(u16 trg);
EWRAM_CODE void  MenuExecending2(u16 trg);

EWRAM_CODE void  MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, void* pFunc, bool isDraw);
EWRAM_CODE void  MenuSetSystem(s32 sel);
EWRAM_CODE void  MenuSetOption(s32 sel);
EWRAM_CODE void  MenuSetSave(s32 ret);
EWRAM_CODE void  MenuSetLoad(s32 ret);
EWRAM_CODE void  MenuSetNone(s32 ret);
EWRAM_CODE void  MenuSetTitle(s32 sel);
EWRAM_CODE void  MenuSetEnding1(s32 ret);
EWRAM_CODE void  MenuSetEnding2(s32 ret);
EWRAM_CODE void  MenuSetChap(s32 num);

EWRAM_CODE char* MenuGetStrTitle(void);
EWRAM_CODE char* MenuGetStrSelect(s32 sel);
EWRAM_CODE s32   MenuGetSel(void);
EWRAM_CODE s32   MenuGetReg(void);
EWRAM_CODE s32   MenuGetType(void);

#ifdef __cplusplus
}
#endif
#endif
