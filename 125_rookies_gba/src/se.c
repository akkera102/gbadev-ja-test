#include "se.h"
#include "libmy/vgm.arm.h"
#include "file.h"

//---------------------------------------------------------------------------
ST_SE Se;


//---------------------------------------------------------------------------
EWRAM_CODE void SeInit(void)
{
	_Memset(&Se, 0x00, sizeof(ST_SE));

	SeStop();
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlay(s32 no, bool isLoop)
{
//	u8* pDat = FileGetFmx(no);

	TRACE("[SePlay no:%d loop:%d]\n", no, isLoop);

//	VgmPlay(pDat, isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SePlay2(s32 no)
{
	Se.no = no;
	Se.isLoop = SeIsLoopNo(no);

	SePlay(Se.no, Se.isLoop);
}
//---------------------------------------------------------------------------
// セーブデータのロード時に使います（ループ再生の効果音のみ演奏）
EWRAM_CODE void SePlayLoad(void)
{
	if(Se.isLoop == false)
	{
		SeStop();

		return;
	}

	SePlay(Se.no, Se.isLoop);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SeStop(void)
{
	if(VgmIsPlay() == false)
	{
		return;
	}

	VgmStop2();
}
//---------------------------------------------------------------------------
EWRAM_CODE bool SeIsLoopNo(s32 no)
{
	switch(no)
	{
		case 2:		// 電話コール1
		case 13:	// 電話コール2
		case 14:	// 踏切
		case 26:	// 麻雀かき混ぜる
		case 31:	// 警報音
		case 42:	// 電話切った後
		case 47:	// 地震
		case 50:	// 宿直室燃える
		case 55:	// 電話コール3
		case 56:	// 電話コール4
		case 57:	// ガチャ、電話切った後

		// PMDファイルから効果音に変更
		case 66:	// 雨
		case 67:	// ジリリ
		case 68:	// 水（水道）
			return true;
	}

	return false;
}
