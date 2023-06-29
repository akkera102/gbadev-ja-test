#include "log.h"
#include "libmy/key.h"
#include "libmy/bios.h"
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
			TextSetChr();
			TextSetCur(TRUE);
			TextSetRes();

			ManageSetNovel();
		}
		else
		{
			TextClearDat();
			TextSetChr();

			MenuSetSystem(MENU_SYSTEM_SEL_LOG);

			ManageSetMenu();
		}

		return;
	}

	if(rep & KEY_LEFT)
	{
		if((Log.sel+1) < Log.reg)
		{
			Log.sel++;
			Log.isDraw = TRUE;
		}
	}

	if(rep & KEY_RIGHT)
	{
		if(Log.sel != 0)
		{
			Log.sel--;
			Log.isDraw = TRUE;
		}

		goto End;
	}

	if(Log.isDraw == TRUE)
	{
		Log.isDraw = FALSE;

		TextSetCur(FALSE);
		TextSetChr();
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void LogSetInit(u32 ret)
{
	Log.isDraw = TRUE;

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
	BiosCpuSet(p, &Log.buf[Log.cnt][0], TEXT_SCREEN_CX * TEXT_SCREEN_CY * 2);

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
	return (Log.reg == 0) ? TRUE : FALSE;
}
