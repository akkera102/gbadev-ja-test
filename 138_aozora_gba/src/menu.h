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
	MENU_TYPE_NONE,
	MENU_TYPE_SAVE,
	MENU_TYPE_LOAD,
	MENU_TYPE_TITLE,
	MENU_TYPE_NAVI,
	MENU_TYPE_SYSTEM,
	MENU_TYPE_OPTION,
	MENU_TYPE_DEBUG,
};

enum {
	MENU_TITLE_SEL_START,
	MENU_TITLE_SEL_LOAD,
	MENU_TITLE_SEL_OMAKE,
};

enum {
	MENU_NAVI_SEL_NONE,
	MENU_NAVI_SEL_ITEM,
};

enum {
	MENU_SYSTEM_SEL_SAVE,
	MENU_SYSTEM_SEL_LOAD,
	MENU_SYSTEM_SEL_OPTION,
	MENU_SYSTEM_SEL_DEBUG,
	MENU_SYSTEM_SEL_TITLE,
};

enum {
	MENU_OPTION_SEL_FADE,
	MENU_OPTION_SEL_BASE_COL,
	MENU_OPTION_SEL_READ_COL,
	MENU_OPTION_SEL_READ,
	MENU_OPTION_SEL_NAVI,
};

enum {
	MENU_DEBUG_SEL_BG,
	MENU_DEBUG_SEL_CHR,
	MENU_DEBUG_SEL_BGM,
	MENU_DEBUG_SEL_FMX,
	MENU_DEBUG_SEL_TXT,
};

//---------------------------------------------------------------------------

typedef struct {
	s32  type;							// メニュー種類
	s32  reg;							// メッセージ番号の登録数
	s32  msg;							// メッセージ番号の先頭
	s32  sel;							// 選択中の項目
	s32  var;							// 作業用変数

	void (*pFunc)(u16 rep, u16 trg);	// キー入力時の動作用関数
	char buf[MENU_BUF_SIZE];			// 項目文字編集用バッファ

	s32  page;							// セーブロードページ
	s32  no;							// セーブロードセレクト
	s32  dbg;
	s32  opt;
	s32  sys;

	s32  bg;
	s32  chr;
	s32  mus;
	s32  snd;
	s32  txt;

} ST_MENU;


//---------------------------------------------------------------------------
void  MenuInit(void);
void  MenuExec(void);

void  MenuExecNone(u16 trg, u16 rep);
void  MenuExecSave(u16 trg, u16 rep);
void  MenuExecLoad(u16 trg, u16 rep);
void  MenuExecTitle(u16 trg, u16 rep);
void  MenuExecNavi(u16 trg, u16 rep);
void  MenuExecSystem(u16 trg, u16 rep);
void  MenuExecOption(u16 trg, u16 rep);
void  MenuExecDebug(u16 trg, u16 rep);

void  MenuSetInit(s32 type, s32 ret, s32 sel, s32 msg, s32 reg, s32 var, void* pFunc, bool isShow);
void  MenuSetNone(void);
void  MenuSetSave(void);
void  MenuSetLoad(s32 ret);
void  MenuSetTitle(s32 sel);
void  MenuSetNavi(void);
void  MenuSetSystem(s32 sel);
void  MenuSetSystem2(void);
void  MenuSetOption(void);
void  MenuSetDebug(void);

char* MenuGetStrTitle(void);
char* MenuGetStrSel(s32 sel);
char* MenuGetStrSelOpt(s32 sel);
char* MenuGetStrSelDbg(s32 sel);
char* MenuGetStrSelNavi(s32 sel);
s32   MenuGetReg(void);
s32   MenuGetSel(void);


#ifdef __cplusplus
}
#endif
#endif
