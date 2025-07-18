#include "txt.h"
#include "libmy/spr.h"
#include "libmy/mem.h"
#include "img.h"
#include "log.h"
#include "menu.h"
#include "nv.h"


//---------------------------------------------------------------------------
ST_TXT Txt;


//---------------------------------------------------------------------------
void TxtInit(void)
{
	_Memset(&Txt, 0x00, sizeof(ST_TXT));

	TxtClearBuf();
}
//---------------------------------------------------------------------------
void TxtExecNv(void)
{
	Txt.isBuf = true;

	// ���ǃ`�F�b�N
	if(NvIsRead2() == false)
	{
		SprSetWhite();
	}
	else
	{
		SprSetSelect();
	}

	SprShowMsg();


	s32 i;

	for(i=0; i<Txt.reg; i++)
	{
		s32 cmd = Txt.tbl[i].c;

		if(cmd == TXT_CMD_MSG)
		{
			TxtDrawStr(Txt.tbl[i].p);

			continue;
		}

		if(cmd == TXT_CMD_CLS)
		{
			TxtClearBuf();

			continue;
		}

		if(cmd == TXT_CMD_LF)
		{
			Txt.x = 0;
			Txt.y++;

			continue;
		}

		SystemError("[Err] TxtExecNv %x %x\n", i, cmd);
	}

	Txt.reg = 0;
	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtExecSel(void)
{
	Txt.isBuf = false;

	SprClearDat();
	SprShowMsg();

	s32 reg = NvGetSelReg();
	s32 cnt = NvGetSelCnt();
	s32 i;

	Txt.x = 0;
	Txt.y = 0;

	for(i=0; i<reg; i++)
	{
		if(i == cnt)
		{
			SprSetWhite();
		}
		else
		{
			SprSetGray();
		}

		TxtDrawStr(NvGetSelStr(i));

		if(Txt.x != 0)
		{
			Txt.x = 0;
			Txt.y++;
		}
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtExecRes(void)
{
	// ���ǃ`�F�b�N
	if(NvIsRead2() == false)
	{
		SprSetWhite();
	}
	else
	{
		SprSetSelect();
	}

	SprShowMsg();


	s32 x, y, c = 0;

	for(y=0; y<SPR_MAX_TXT_CY; y++)
	{
		for(x=0; x<SPR_MAX_TXT_CX; x++)
		{
			SprDrawDatChr(x, y, Txt.buf[c++]);
		}
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtExecLog(void)
{
	u16* p = LogGetBuf();

	SprSetGray();
	SprShowMsg();

	s32 x, y;

	for(y=0; y<SPR_MAX_TXT_CY; y++)
	{
		for(x=0; x<SPR_MAX_TXT_CX; x++)
		{
			SprDrawDatChr(x, y, *p++);
		}
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtExecMenu(void)
{
	Txt.isBuf = false;

	SprClearDat();
	SprSetWhite();
	SprShowMsg();

	s32 type = MenuGetType();
	s32 reg  = MenuGetReg();
	s32 sel  = MenuGetSel();
	s32 i, x, y;

	// �^�C�g��
	char* p;

	if(type == MENU_TYPE_SYSTEM)
	{
		p = Txt.title;

		if( _Strlen(p) <= 12)
		{
			x = 4;
			y = 0;
		}
		else
		{
			x = 3;
			y = 0;
		}
	}
	else
	{
		p = MenuGetStrTitle();
		x = 4;
		y = 0;
	}

	TxtDrawStrXy(x, y, p);

	// �I����
	if(type == MENU_TYPE_TITLE)
	{
		x = 5;
		y = 7;
	}
	else if(type == MENU_TYPE_DEBUG)
	{
		x = 2;
		y = 2;
	}
	else
	{
		x = 3;
		y = 2;
	}

	for(i=0; i<reg; i++)
	{
		if(i == sel)
		{
			SprSetWhite();
		}
		else
		{
			SprSetGray();
		}

		TxtDrawStrXy(x, y+i, MenuGetStrSel(i));
	}

	Txt.isExec = false;
}
//---------------------------------------------------------------------------
void TxtDrawChr(u16 code)
{
	if(Txt.x >= SPR_MAX_TXT_CX)
	{
		Txt.x = 0;
		Txt.y++;
	}

	_ASSERT(Txt.x < SPR_MAX_TXT_CX && Txt.y < SPR_MAX_TXT_CY);

	SprDrawDatChr(Txt.x, Txt.y, code);


	if(Txt.isBuf == true)
	{
		Txt.buf[(Txt.y * SPR_MAX_TXT_CX) + Txt.x] = code;
	}

	Txt.x++;
}
//---------------------------------------------------------------------------
void TxtDrawStr(char* p)
{
	u16 code;

	while(*p != '\0')
	{
		code  = *p++ << 8;
		code += *p++;

		TxtDrawChr(code);
	}
}
//---------------------------------------------------------------------------
void TxtDrawStrXy(s32 x, s32 y, char* p)
{
	s32 tx = Txt.x;
	s32 ty = Txt.y;

	Txt.x = x;
	Txt.y = y;

	TxtDrawStr(p);

	Txt.x = tx;
	Txt.y = ty;
}
//---------------------------------------------------------------------------
void TxtSetMsg(char* p)
{
	_ASSERT(Txt.reg < TXT_MAX_REG_CNT);

	Txt.tbl[Txt.reg].c = TXT_CMD_MSG;
	Txt.tbl[Txt.reg].p = p;

	Txt.reg++;
}
//---------------------------------------------------------------------------
void TxtSetCls(void)
{
	_ASSERT(Txt.reg < TXT_MAX_REG_CNT);

	Txt.tbl[Txt.reg].c = TXT_CMD_CLS;

	Txt.reg++;
}
//---------------------------------------------------------------------------
void TxtSetLf(void)
{
	_ASSERT(Txt.reg < TXT_MAX_REG_CNT);

	Txt.tbl[Txt.reg].c = TXT_CMD_LF;

	Txt.reg++;
}
//---------------------------------------------------------------------------
void TxtSetTitle(char* p)
{
	_Strncpy(Txt.title, p, TXT_MAX_TITLE_LEN-1);

	Txt.title[TXT_MAX_TITLE_LEN-1] = '\0';
}
//---------------------------------------------------------------------------
void TxtSetExec(void)
{
	Txt.isExec = true;
}
//---------------------------------------------------------------------------
s32 TxtGetX(void)
{
	return Txt.x;
}
//---------------------------------------------------------------------------
s32 TxtGetY(void)
{
	return Txt.y;
}
//---------------------------------------------------------------------------
// �e�L�X�g�o�b�t�@�����O�ɒǉ�
void TxtWriteBuf(void)
{
	if(Txt.x == 0 && Txt.y == 4)
	{
		return;
	}

	LogAddBuf(Txt.buf);
}
//---------------------------------------------------------------------------
// �I���������O�ɒǉ�
void TxtWriteSel(char* p)
{
	MemClear(Txt.buf, sizeof(Txt.buf));

	u16 code;
	s32 i;

	for(i=0; *p != '\0'; i++)
	{
		code  = *p++ << 8;
		code += *p++;

		_ASSERT(i < SPR_MAX_TXT_CX * SPR_MAX_TXT_CY);

		Txt.buf[i] = code;
	}

	LogAddBuf(Txt.buf);
}
//---------------------------------------------------------------------------
void TxtClearBuf(void)
{
//	TRACE("[TxtClearBuf]\n");

	Txt.x = 0;
	Txt.y = 4;

	SprClearDat();
	MemClear(Txt.buf, sizeof(Txt.buf));
}
//---------------------------------------------------------------------------
void TxtClearSel(void)
{
//	TRACE("[TxtClearSel]\n");

	Txt.x = 0;
	Txt.y = 4;

	SprClearDat();
}
//---------------------------------------------------------------------------
void TxtShow(void)
{
	SprShowMsg();
}
//---------------------------------------------------------------------------
void TxtHide(void)
{
	SprHideMsg();
}
//---------------------------------------------------------------------------
bool TxtIsExec(void)
{
	return Txt.isExec;
}
