#include "log.h"
#include "libmy/key.h"
#include "libmy/mem.h"
#include "manage.h"
#include "menu.h"
#include "txt.h"
#include "cur.h"


//---------------------------------------------------------------------------
ST_LOG Log;


//---------------------------------------------------------------------------
void LogInit(void)
{
	_Memset(&Log, 0x00, sizeof(ST_LOG));
}
//---------------------------------------------------------------------------
void LogExec(void)
{
	u16 trg = KeyGetTrg();
	u16 rep = KeyGetRep();

	if(trg & KEY_B)
	{
End:
		// 戻り先：ノベル or 選択肢 or システムメニュー
		if(ManageIsPrv(MANAGE_ACT_NV) == true)
		{
			ManageSetAct(MANAGE_ACT_RES);
		}
		else if(ManageIsPrv(MANAGE_ACT_SEL) == true)
		{
			ManageSetAct(MANAGE_ACT_SEL);
		}
		else
		{
			MenuSetSystem(MENU_SYSTEM_SEL_LOG);

			ManageSetAct(MANAGE_ACT_MENU);
		}

		return;
	}

	if(rep & KEY_LEFT)
	{
		if((Log.sel+1) < Log.cnt)
		{
			Log.sel++;

			TxtSetExec();
		}

		return;
	}

	if(rep & KEY_RIGHT)
	{
		if(Log.sel == 0)
		{
			goto End;
		}

		Log.sel--;

		TxtSetExec();

		return;
	}
}
//---------------------------------------------------------------------------
void LogSetInit(void)
{
	Log.sel = 0;

	CurHide();
	TxtSetExec();
}
//---------------------------------------------------------------------------
u16* LogGetBuf(void)
{
	s32 num = (Log.reg - Log.sel - 1) & (LOG_MAX_CNT - 1);

	return Log.buf[num];
}
//---------------------------------------------------------------------------
void LogAddBuf(u16* p)
{
	MemInc(p, &Log.buf[Log.reg][0], SPR_MAX_TXT_CX * SPR_MAX_TXT_CY * 2);

	if(Log.cnt < LOG_MAX_CNT)
	{
		Log.cnt++;
	}

	Log.reg++;
	Log.reg &= (LOG_MAX_CNT - 1);
}
//---------------------------------------------------------------------------
bool LogIsEmpty(void)
{
	return (Log.cnt == 0) ? true : false;
}
