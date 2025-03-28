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
	s32  type;							// メニュー種類
	s32  ret;							// メニュー終了先
	s32  cnt;							// 選択中の項目
	s32  msg;							// メッセージ番号の先頭
	s32  reg;							// メッセージ番号の登録数
	s32  idx;							// 場面ジャンプ用インデックス
	s32  idxCur;						// 場面ジャンプ用インデックスカーソル

	void (*pFunc)(u16 trg, u16 rep);	// キー入力時の動作用関数
	char buf[MENU_BUF_SIZE];			// 項目文字編集用バッファ

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
