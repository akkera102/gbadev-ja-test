#ifndef __MENU_H__
#define __MENU_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "txt.h"

//---------------------------------------------------------------------------
#define MENU_BUF_SIZE			(TXT_SCREEN_CX*2)

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
};

enum {
	MENU_RET_NONE,
	MENU_RET_TITLE,
	MENU_RET_SYSTEM,
};

enum {
	MENU_SYSTEM_SEL_SKIP = 0,
	MENU_SYSTEM_SEL_NONE,
	MENU_SYSTEM_SEL_LOG,
	MENU_SYSTEM_SEL_SAVE,
	MENU_SYSTEM_SEL_LOAD,
	MENU_SYSTEM_SEL_OPTION,
};
//---------------------------------------------------------------------------

typedef struct {
	bool isDraw;				// 描画フラグ
	s32  type;					// メニュー種類
	s32  ret;					// メニュー終了先
	s32  sel;					// 選択中の項目
	s32  msg;					// メッセージ番号の先頭
	s32  reg;					// メッセージ番号の登録数

	void (*pFunc)(u16 trg);		// キー入力時の動作用関数
	char buf[MENU_BUF_SIZE+1];	// 項目文字編集用バッファ
} ST_MENU;


//---------------------------------------------------------------------------
EWRAM_CODE void  MenuInit(void);
EWRAM_CODE void  MenuExec(void);

EWRAM_CODE void  MenuExecSystem(u16 trg);
EWRAM_CODE void  MenuExecOption(u16 trg);
EWRAM_CODE void  MenuExecSave(u16 trg);
EWRAM_CODE void  MenuExecLoad(u16 trg);
EWRAM_CODE void  MenuExecNone(u16 trg);

EWRAM_CODE void  MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, void* pFunc, bool isDraw);
EWRAM_CODE void  MenuSetSystem(s32 sel);
EWRAM_CODE void  MenuSetOption(void);
EWRAM_CODE void  MenuSetSave(s32 ret);
EWRAM_CODE void  MenuSetLoad(s32 ret);
EWRAM_CODE void  MenuSetNone(void);

EWRAM_CODE char* MenuGetSelStr(s32 sel);
EWRAM_CODE u8    MenuGetSel(void);
EWRAM_CODE u8    MenuGetReg(void);

#ifdef __cplusplus
}
#endif
#endif
