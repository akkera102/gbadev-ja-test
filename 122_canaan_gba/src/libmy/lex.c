#include "lex.h"


//---------------------------------------------------------------------------
ST_LEX Lex;


//---------------------------------------------------------------------------
EWRAM_CODE void LexInit(void)
{
	_Memset(&Lex, 0x00, sizeof(ST_LEX));
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexSetCur(char* pCur)
{
	Lex.pCur = pCur;
	Lex.pOld = pCur;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* LexGetCur(void)
{
	return Lex.pCur;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 LexGetNum(void)
{
	LexGetToken(false);

	if(Lex.type != LEX_TOKEN_NUM)
	{
		SystemError("[Err] LexGetNum -1");
	}

	return Lex.num;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* LexGetStr(void)
{
	LexGetToken(false);

	if(Lex.type != LEX_TOKEN_STR)
	{
		SystemError("[Err] LexGetStr NULL");
	}

	return Lex.str;
}
//---------------------------------------------------------------------------
EWRAM_CODE char LexGetChr(void)
{
	LexGetToken(true);

	if(Lex.type != LEX_TOKEN_STR)
	{
		SystemError("[Err] LexGetChr \\0");
	}

	return Lex.str[0];
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexGetToken(bool isChr)
{
	s32  num, cnt;

	ST_LEX* p = &Lex;
	p->pOld = p->pCur;

st: ;

	u32 type = LexGetType(*p->pCur);

	switch(type)
	{
	// 空白、タブ
	case LEX_TOKEN_SPACE:
		p->pCur++;
		goto st;

	// コンマ
	case LEX_TOKEN_CUM:
		p->pCur++;
		goto st;

	// CR
	case LEX_TOKEN_CR:
		p->pCur += 2;
		goto st;

	// LF
	case LEX_TOKEN_LF:
		p->pCur++;
		goto st;

	// コメント
	case LEX_TOKEN_COMMENT:
		LexSkipLine();
		goto st;

	// 終端
	case LEX_TOKEN_END:
		p->type = type;
		break;

	// 数字
	case LEX_TOKEN_NUM:
		num = 0;
		cnt = 0;

		do {
			num = (num * 10) + (*p->pCur++ - '0');
			cnt++;

		} while((LexGetType(*p->pCur) == LEX_TOKEN_NUM) && (cnt <= 8));

		p->type = type;
		p->num  = num;
		break;

	// ダブルクォート付き文字列
	case LEX_TOKEN_DQUOTE:
		cnt = 0;
		p->pCur++;

		do {
			p->buf[cnt++] = *p->pCur++;

		} while((LexGetType(*p->pCur) != LEX_TOKEN_DQUOTE) && (cnt < LEX_MAX_STR_CNT-1) && (isChr == false));

		p->buf[cnt] = '\0';
		p->pCur++;

		p->type = LEX_TOKEN_STR;
		p->num  = cnt;
		_Strncpy(p->str, p->buf, cnt+1);
		break;

	// 文字列
	case LEX_TOKEN_STR:
		cnt = 0;

		do {
			p->buf[cnt++] = *p->pCur++;

		} while((LexGetType(*p->pCur) != LEX_TOKEN_SPACE) && (LexGetType(*p->pCur) != LEX_TOKEN_CR) && (LexGetType(*p->pCur) != LEX_TOKEN_LF) && (cnt < LEX_MAX_STR_CNT-1) && (isChr == false));

		p->buf[cnt] = '\0';

		p->type = type;
		p->num  = cnt;
		_Strncpy(p->str, p->buf, cnt+1);
		break;
	}

	LexSkipLf();
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 LexGetType(char chr)
{
	if(chr == ' ' || chr == '\t')
	{
		return LEX_TOKEN_SPACE;
	}
	else if(chr == CR)
	{
		return LEX_TOKEN_CR;
	}
	else if(chr == LF)
	{
		return LEX_TOKEN_LF;
	}
	else if(chr == ',')
	{
		return LEX_TOKEN_CUM;
	}
	else if(chr == '#')
	{
		return LEX_TOKEN_COMMENT;
	}
	else if(chr == '\"')
	{
		return LEX_TOKEN_DQUOTE;
	}
	else if(chr == '\0')
	{
		return LEX_TOKEN_END;
	}
	else if(_IsDigit(chr) == true)
	{
		return LEX_TOKEN_NUM;
	}

	return LEX_TOKEN_STR;
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexSkipStr(char* pStr)
{
	char* p;

	do
	{
		LexSkipLine();
		p = LexGetStr();

	} 	while(_Strncmp(p, pStr, LEX_MAX_STR_CNT) != 0);
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexSkipLine(void)
{
	ST_LEX* p = &Lex;

	while(*p->pCur != '\0')
	{
		if(*p->pCur == CR)
		{
			p->pCur += 2;
			return;
		}

		if(*p->pCur == LF)
		{
			p->pCur += 1;
			return;
		}

		p->pCur++;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexSkipLf(void)
{
	ST_LEX* p = &Lex;

	if(*p->pCur == LF)
	{
		p->pCur++;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexUnGet(void)
{
	Lex.pOld = Lex.pCur;
}
//---------------------------------------------------------------------------
EWRAM_CODE bool LexIsEnd(void)
{
	return (*Lex.pCur == '\0') ? true : false;
}
