#include "nv.h"
#include "nv2.h"
#include "nv3.h"
#include "libmy/gbfs.h"
#include "libmy/key.h"
#include "libmy/spr.h"
#include "log.h"
#include "img.h"
#include "menu.h"
#include "siori.h"
#include "file.h"
#include "manage.h"
#include "bgm.h"
#include "se.h"
#include "sakura.h"
#include "rein.h"

//---------------------------------------------------------------------------
ST_NV Nv;


//---------------------------------------------------------------------------
EWRAM_CODE void NvInit(void)
{
	_Memset(&Nv, 0x00, sizeof(ST_NV));

	// 共通フラグの上書き
	SioriLoadFlag();
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExec(void)
{
	Nv.vblankCnt++;

	if(Nv.wait != 0)
	{
		Nv.wait--;
		return;
	}

	if(Nv.isWaitSe == true)
	{
		if(SeIsEnd2() == false)
		{
			return;
		}

		Nv.isWaitSe = false;
	}

	switch(Nv.act)
	{
	case NV_ACT_PARSE:
		NvExecParse();
		break;

	case NV_ACT_KEY:
		NvExecKey();
		break;

	case NV_ACT_SELECT:
		NvExecSel();
		break;

	case NV_ACT_RESTART:
		NvExecRestart();
		break;

	default:
		SystemError("[Err] NvExec Nv.act = %d\n", Nv.act);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecKey(void)
{
	u16 cnt = KeyGetCnt();
	u16 trg = KeyGetTrg();

	// 次の選択肢までスキップ
	if(Nv.isSkip == true)
	{
		if(cnt & KEY_B)
		{
			Nv.isSkip = false;
		}
		else
		{
			goto KeyOn;
		}
	}


	switch(Nv.step)
	{
	case 0:
		TxtShowMsg();
		TxtSetCur(true);

		Nv.step++;
		break;

	case 1:
		if(cnt & KEY_R || trg & KEY_A || trg & KEY_DOWN)
		{
KeyOn:
			// 選択肢メッセージ表示後かチェック
			if(Nv.isSelKey == false)
			{
				TxtSetCur(false);
				NvSetAct(NV_ACT_PARSE);
			}
			else
			{
				TxtSetPageNew();
				Nv.isSelKey = false;
				NvSetAct(NV_ACT_SELECT);
			}
		}
		else if((trg & KEY_LEFT) && (LogIsEmpty() == false))
		{
			LogSetInit(LOG_RET_NOVEL);
			ManageSetLog();

			Nv.step--;
		}
		else if(trg & KEY_B)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_SKIP);
			ManageSetMenu();

			Nv.step--;
		}
		else if(trg & KEY_L)
		{
			TxtHideWindow();
			MenuSetNone(MENU_RET_NOVEL);
			ManageSetMenu();

			Nv.step--;
		}
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecSel(void)
{
	switch(Nv.step)
	{
	// 項目の表示
	case 0:
		TxtClearXY();
		TxtShowMsg();
		TxtSetBuf(false);
		TxtSetCur(false);
		Nv.isSkip = false;

		s32 i;

		for(i=0; i<Nv.sel.cnt; i++)
		{
			if(i == Nv.sel.num)
			{
				SprSetImgWhite();
			}
			else
			{
				SprSetImgGray();
			}

			NvSetSelStr(i);

			TxtDrawStr(Nv.sel.str);
			TxtSetLf();
		}

		SprSetImgWhite();
		NvSetEffectAfter(IMG_EFFECT_TXT_ON);

		Nv.step++;
		break;

	// 選択中
	case 1: ;
		u16 trg = KeyGetTrg();

		if((trg & KEY_A) && Nv.sel.num != -1)
		{
			Nv.step++;
		}
		else if((trg & KEY_LEFT) && (LogIsEmpty() == false))
		{
			LogSetInit(LOG_RET_NOVEL);
			ManageSetLog();

			Nv.step--;
		}
		else if(trg & KEY_B)
		{
			MenuSetSystem(MENU_SYSTEM_SEL_SKIP);
			ManageSetMenu();

			Nv.step--;
		}
		else if(trg & KEY_L)
		{
			TxtHideWindow();
			MenuSetNone(MENU_RET_NOVEL);
			ManageSetMenu();

			Nv.step--;
		}
		else if((trg & KEY_UP) && Nv.sel.num > 0)
		{
			Nv.sel.num--;

			Nv.step--;
		}
		else if((trg & KEY_DOWN) && (Nv.sel.num + 1) < Nv.sel.cnt)
		{
			Nv.sel.num++;

			Nv.step--;
		}
		break;

	// 選択終了
	case 2:
		// 履歴に選択肢を保存
		TxtClearXY();
		TxtSetBuf(true);

		NvSetSelStr(Nv.sel.num);
		TxtDrawStr(Nv.sel.str);
		TxtSetPageNew();

		// 選択肢のアドレスへジャンプ
		Nv.pCur = Nv.sel.pSrc;
		Nv.curAdr = Nv.sel.srcAdr;

		// 選択肢 or 可変選択肢
		if(Nv.isSelOpt == false)
		{
			// TRACE("[selJump: %x]\n", Nv.curAdr + 3 + 2 * Nv.sel.cnt + Nv.sel.jump[Nv.sel.num]);
			NvJumpCurAdr(Nv.curAdr + 3 + 2 * Nv.sel.cnt + Nv.sel.jump[Nv.sel.num]);
		}
		else
		{
			// TRACE("[selJump: %x]\n", Nv.curAdr + 3 + Nv.sel.jump[Nv.sel.num] * Nv.sel.offset);
			NvJumpCurAdr(Nv.curAdr + 3 + Nv.sel.jump[Nv.sel.num] * Nv.sel.offset);
		}

		NvSetAct(NV_ACT_PARSE);
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvExecRestart(void)
{
	switch(Nv.step)
	{
	case 0:
		LogInit();
		TxtHideMsg();
		SakuraStop();
		Nv.step++;
		break;

	case 1:
		ImgSetEffectBefore(IMG_EFFECT_WIPE_TTOB);
		Nv.step++;
		break;

	case 2:
		ImgSetEffectAfter(IMG_EFFECT_FADE_PALETTE);
		BgmRestart();
		SeStop();
		Nv.step++;
		break;

	case 3:
		TxtRestart();
		ImgRestart();
		NvPopAct();

		if(Nv.isSakura == true)
		{
			TRACE("[sakura seed = %x]\n", Nv.vblankCnt);
			SakuraSeed(Nv.vblankCnt);
			SakuraStart(false);
		}

		// 選択肢の場合のリセット
		Nv.sel.num = -1;
		break;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectBefore(u8 no)
{
	if(Nv.isSkip == true)
	{
		return;
	}

	ImgSetEffectBefore(no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectAfter(u8 no)
{
	if(Nv.isSakura == true)
	{
		u8 bg = ImgGetBgS();

		// 校門と校内背景のみ、そのまま降らす
		if(bg != 0x0b && bg != 0x14)
		{
			SakuraStop();
			Nv.isSakura = false;
		}
	}

	if(Nv.isRein == true)
	{
		if(ImgIsBgS() == false)
		{
			ReinStop();
			Nv.isRein = false;
		}
		else
		{
			u8 bg = ImgGetBgS();

			// 公園（雨雲）、公園（夜）、商店街
			if(bg != 0x1a && bg != 0xb0 && bg != 0x17)
			{
				ReinStop();
				Nv.isRein = false;
			}
		}
	}


	if(Nv.isSkip == true)
	{
		if(no == IMG_EFFECT_TXT_ON)
		{
			return;
		}

		no = IMG_EFFECT_NORMAL;
	}

	ImgSetEffectAfter(no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectTime(u8 num)
{
	if(Nv.isSkip == true)
	{
		return;
	}

	ImgSetEffectTime(num);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEffectCal(u8 num)
{
	if(Nv.isSkip == true)
	{
		return;
	}

	u8 m = NvGetCalMonth(num);
	u8 d = NvGetCalDay(num);
	u8 w = NvGetCalWeek(num);

	ImgSetEffectCal(m, d, w);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetScn(u32 no)
{
	u8* p = FileGetScn(no);

	Nv.size   = FileGetSize();
	Nv.pTxt   = p;
	Nv.pCur   = p;

	NvSkipCurChr('E');
	Nv.maxEvt = NvGetCurHex();
	Nv.pEvt   = Nv.pCur + 1;

	NvSkipCurChr('M');
	Nv.maxMsg = NvGetCurHex();
	Nv.pMsg   = Nv.pCur + 1;

	Nv.scnNo  = no;
	Nv.evtNo  = 0;
	Nv.msgNo  = 0;

	TRACE("\n[NvSetScn %04x.txt E%02x M%02x]\n", no, Nv.maxEvt, Nv.maxMsg);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetEvt(u32 no)
{
	_ASSERT(no < Nv.maxEvt);

	// アドレス取得
	Nv.pCur = Nv.pEvt + no * 5;
	u32 adr = NvGetCurHex();

	// アドレスへジャンプ
	Nv.pCur = Nv.pEvt + Nv.maxEvt * 5 + 1;
	NvJumpCurAdr(adr);

	Nv.evtNo = no;
	TRACE("[NvSetEvt %x %x]\n", no, adr);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetMsg(u32 no)
{
	_ASSERT(no < Nv.maxMsg);

	Nv.pRet = Nv.pCur;

	// アドレス取得
	Nv.pCur = Nv.pMsg + no * 5;
	u32 adr = NvGetCurHex();

	// アドレスへジャンプ
	Nv.pCur = Nv.pMsg + Nv.maxMsg * 5 + 1;
	NvJumpCurAdr(adr);

	Nv.msgNo = no;
	TRACE("[NvSetMsg %x %x]\n", no, adr);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetSkip(void)
{
	Nv.isSkip = true;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetAct(s32 act)
{
	Nv.act  = act;
	Nv.step = 0;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvPushAct(s32 act)
{
	Nv.act2 = Nv.act;
	NvSetAct(act);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvPopAct(void)
{
	NvSetAct(Nv.act2);
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSetFlag(u8 no, s8 val)
{
	Nv.flag[no] = val;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvAddFlag(u8 no, s8 val)
{
	Nv.flag[no] += val;
}
//---------------------------------------------------------------------------
EWRAM_CODE void NvSubFlag(u8 no, s8 val)
{
	Nv.flag[no] -= val;
}
//---------------------------------------------------------------------------
EWRAM_CODE s8 NvGetFlag(u8 no)
{
	return Nv.flag[no];
}
//---------------------------------------------------------------------------
EWRAM_CODE u16 NvGetChrNo(u16 no)
{
	// あかりの髪型
	if((no >> 8) == 0)
	{
		if(Nv.flag[NV_FLAG_AKARI] & 0x01)
		{
			no |= 0x80;
		}

		no |= 0x100;
	}

	return no;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 NvGetBgVNo(u8 no)
{
	// あかりの髪型
	if(no == 0x11 || no == 0x13)
	{
		if(Nv.flag[NV_FLAG_AKARI] & 0x01)
		{
			no = 0x12;
		}
	}

	// レミィパンツの色違い。V82は欠番
	if(no >= 0x81 && no <= 0x86)
	{
		no = 0x80;
	}

	return no;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 NvGetCalMonth(u8 num)
{
	if(num <= 31)
	{
		return 3;
	}

	if(num <= 61)
	{
		return 4;
	}

	return 5;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 NvGetCalDay(u8 num)
{
	if(num <= 31)
	{
		return num;
	}

	if(num <= 61)
	{
		num -= 31;
		return num;
	}

	num -= 61;
	return num;
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 NvGetCalWeek(u8 num)
{
	return DivMod(num + 5, 7);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool NvIsSkip(void)
{
	return Nv.isSkip;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool NvIsRestart(void)
{
	return (Nv.act == NV_ACT_RESTART) ? true : false;
}
