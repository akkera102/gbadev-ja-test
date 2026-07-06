#include "seen.h"
#include "siori.h"

/*
	FW005 EX_SC 0-3 隠しシナリオ 3全開放
	FW008 H1ED  0-2 雨音   2ハッピー 1バッド
	FW009 H2ED  0-2 悠夏   2ハッピー 1バッド
	FW010 H3ED  0-2 藍     2ハッピー 1バッド
	FW011 H4ED  0-2 明日菜 2ハッピー 1バッド
	FW012 H5ED  0-2 文乃   2ハッピー 1バッド
	FW013 H6ED  0-2 ハッピー時シナリオ追加 2エキスパート 1ハッピー 0無し
*/

//---------------------------------------------------------------------------
ST_SEEN Seen EWRAM_BSS;


//---------------------------------------------------------------------------
void SeenInit(void)
{
	_Memset(&Seen, 0x00, sizeof(ST_SEEN));

	SioriLoadLast();
	SioriLoadRead();

	// おまけシナリオ開放
	Seen.fw[ 5] = 3;
	Seen.fw[13] = 2;
}
//---------------------------------------------------------------------------
void SeenSetFl(s32 i, s8 n)
{
	_ASSERT(i < SEEN_MAX_FL_CNT);
	_ASSERT(n < 2);

	Seen.fl[i] = n;
}
//---------------------------------------------------------------------------
void SeenSetFw(s32 i, s8 n)
{
	_ASSERT(i < SEEN_MAX_FW_CNT);

	// ハッピー、バッドはOR計算
	if(i >= 8 && i <= 12)
	{
		Seen.fw[i] |= n;

		return;
	}

	Seen.fw[i] = n;
}
//---------------------------------------------------------------------------
void SeenSetRead(s32 i, u8 b)
{
	_ASSERT(i < SEEN_MAX_READ_SIZE);
	_ASSERT(b < 8);

	Seen.read[i] |= 1 << b;
}
//---------------------------------------------------------------------------
s8 SeenGetFl(s32 i)
{
	_ASSERT(i < SEEN_MAX_FL_CNT);

	return Seen.fl[i];
}
//---------------------------------------------------------------------------
s8 SeenGetFw(s32 i)
{
	_ASSERT(i < SEEN_MAX_FW_CNT);

	// バット判定回避
	if(i >= 8 && i <= 12)
	{
		return Seen.fw[i] & 0x2;
	}

	return Seen.fw[i];
}
//---------------------------------------------------------------------------
bool SeenIsRead(s32 i, u8 b)
{
	_ASSERT(i < SEEN_MAX_READ_SIZE);
	_ASSERT(b < 8);

	return (Seen.read[i] & 1 << b) ? true : false;

}
//---------------------------------------------------------------------------
// アイコン描画用フラグ
u32 SeenGetIcoBit(void)
{
	u32 ret = 0;

	// ハッピー
	ret |= ((Seen.fw[ 8] & 2) ? 1 : 0) << 0;	// 雨音
	ret |= ((Seen.fw[ 9] & 2) ? 1 : 0) << 1;	// 悠夏
	ret |= ((Seen.fw[10] & 2) ? 1 : 0) << 2;	// 藍
	ret |= ((Seen.fw[11] & 2) ? 1 : 0) << 3;	// 明日菜
	ret |= ((Seen.fw[12] & 2) ? 1 : 0) << 4;	// 文乃

	// バッド
	ret |= ((Seen.fw[ 8] & 1) ? 1 : 0) << 5;
	ret |= ((Seen.fw[ 9] & 1) ? 1 : 0) << 6;
	ret |= ((Seen.fw[10] & 1) ? 1 : 0) << 7;
	ret |= ((Seen.fw[11] & 1) ? 1 : 0) << 8;
	ret |= ((Seen.fw[12] & 1) ? 1 : 0) << 9;

	return ret;
}
