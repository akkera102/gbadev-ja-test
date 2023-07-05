#include "log.h"
#include "libmy/key.h"
#include "libmy/mem.h"
#include "manage.h"
#include "menu.h"


//---------------------------------------------------------------------------
ST_LOG Log EWRAM_BSS;


//---------------------------------------------------------------------------
EWRAM_CODE void LogInit(void)
{
	_Memset(&Log, 0x00, sizeof(ST_LOG));
}
//---------------------------------------------------------------------------
EWRAM_CODE void LogExec(void)
{
	u16 trg = KeyGetTrg();
	u16 rep = KeyGetRep();

	if(trg & KEY_B)
	{
End:
		// 戻り先：ノベル or システムメニュー
		if(Log.ret == LOG_RET_NOVEL)
		{
			TxtSetChr();
			TxtSetRes();

			ManageSetNovel();
		}
		else
		{
			TxtClearDat();
			TxtSetChr();

			MenuSetSystem(MENU_SYSTEM_SEL_LOG);

			ManageSetMenu();
		}

		return;
	}

	if(rep & KEY_LEFT)
	{
		if((Log.sel+1) < Log.cnt)
		{
			Log.sel++;
			Log.isDraw = true;
		}
	}

	if(rep & KEY_RIGHT)
	{
		if(Log.sel != 0)
		{
			Log.sel--;
			Log.isDraw = true;
		}

		goto End;
	}

	if(Log.isDraw == true)
	{
		Log.isDraw = false;

		TxtSetCur(false);
		TxtSetChr();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void LogSetInit(u32 ret)
{
	Log.isDraw = true;

	Log.sel = 0;
	Log.ret = ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE u16* LogGetBuf(void)
{
	s32 num = (Log.reg - Log.sel - 1) & (LOG_MAX_CNT - 1);

	return Log.buf[num];
}
//---------------------------------------------------------------------------
EWRAM_CODE void LogAddBuf(u16* p)
{
	MemInc(p, &Log.buf[Log.reg][0], TXT_SCREEN_CX * TXT_SCREEN_CY * 2);

	if(Log.cnt < LOG_MAX_CNT)
	{
		Log.cnt++;
	}

	Log.reg++;
	Log.reg &= (LOG_MAX_CNT - 1);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool LogIsEmpty(void)
{
	return (Log.cnt == 0) ? true : false;
}
