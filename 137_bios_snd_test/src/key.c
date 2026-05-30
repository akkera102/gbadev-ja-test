#include "key.h"

//---------------------------------------------------------------------------
ST_KEY Key;


//---------------------------------------------------------------------------
void KeyInit(void)
{
	_Memset(&Key, 0x00, sizeof(ST_KEY));
}
//---------------------------------------------------------------------------
// vblank中に1回だけ呼び出します（チャタリング防止）
IWRAM_CODE void KeyExec(void)
{
	u32 cnt = REG_KEYINPUT;

	cnt     = ~cnt & 0x3ff;
	Key.trg = (Key.trg ^ cnt) & ~Key.cnt;
	Key.off = Key.off ^ (~cnt & Key.cnt);
	Key.cnt = cnt;


	// キーリピート
	if(Key.trg & DPAD || Key.repCnt == 0)
	{
		Key.rep = Key.cnt;
		Key.repCnt = KEY_REPEAT_CNT;
	}
	else
	{
		Key.rep = 0;
	}

	if(Key.cnt & DPAD)
	{
		if(Key.repCnt != 0) Key.repCnt--;
	}
	else
	{
		Key.repCnt = 0;
	}
}
//---------------------------------------------------------------------------
// 現在押されているボタン
IWRAM_CODE u32 KeyGetCnt(void)
{
	return Key.cnt;
}
//---------------------------------------------------------------------------
// 押された時のボタン
IWRAM_CODE u32 KeyGetTrg(void)
{
	return Key.trg;
}
//---------------------------------------------------------------------------
// 離された時のボタン
IWRAM_CODE u32 KeyGetOff(void)
{
	return Key.off;
}
//---------------------------------------------------------------------------
// キーリピートのボタン。十字キーのみ対応
IWRAM_CODE u32 KeyGetRep(void)
{
	return Key.rep;
}
