#ifndef __MENU_H__
#define __MENU_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"
#include "libmy/spr.h"

//---------------------------------------------------------------------------
#define MENU_BUF_SIZE			(SPR_MAX_TXT_CX*2+1)

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
	MENU_OPTION_SEL_FADE,
	MENU_OPTION_SEL_MVOL,
	MENU_OPTION_SEL_IMG,
	MENU_OPTION_SEL_BGM,
	MENU_OPTION_SEL_FMX,
	MENU_OPTION_SEL_BASE_COL,
	MENU_OPTION_SEL_READ_COL,
	MENU_OPTION_SEL_OMIT,
};

enum {
	MENU_DEBUG_VAR_1,
	MENU_DEBUG_VAR_2,
	MENU_DEBUG_VAR_3,
	MENU_DEBUG_VAR_4,
	MENU_DEBUG_VAR_5,
	MENU_DEBUG_VAR_6,
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

	s32  siori;					// セーブロード選択初期値

	s32  img;
	s32  bgm;
	s32  fmx;

} ST_MENU;


//---------------------------------------------------------------------------
void  MenuInit(void);
void  MenuExec(void);

void  MenuExecSystem(u16 trg);
void  MenuExecOption(u16 trg);
void  MenuExecSave(u16 trg);
void  MenuExecLoad(u16 trg);
void  MenuExecNone(u16 trg);
void  MenuExecTitle(u16 trg);
void  MenuExecDebug(u16 trg);

void  MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, void* pFunc, bool isDraw);
void  MenuSetSystem(s32 sel);
void  MenuSetOption(s32 sel);
void  MenuSetSave(s32 ret);
void  MenuSetLoad(s32 ret);
void  MenuSetNone(s32 ret);
void  MenuSetTitle(s32 sel);
void  MenuSetDebug(s32 sel);

char* MenuGetStrTitle(void);
char* MenuGetStrSel(s32 sel);
char* MenuGetStrSelOpt(s32 sel);
char* MenuGetStrSelDbg(s32 sel);
s32   MenuGetSel(void);
s32   MenuGetReg(void);
s32   MenuGetType(void);


#ifdef __cplusplus
}
#endif
#endif
