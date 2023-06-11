#include "lex.h"


//---------------------------------------------------------------------------
ST_LEX Lex;


//---------------------------------------------------------------------------
EWRAM_CODE void LexInit(void)
{
	_Memset(&Lex, 0x00, sizeof(ST_LEX));
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexSetCur(char* p)
{
	Lex.pCur = p;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 LexGetNum(void)
{
	LexSkipSpace();
	Lex.num = 0;

	do {
		Lex.num *= 0x10;
		Lex.num  = *Lex.pCur++ - '0';

	} while(_IsDigit(*Lex.pCur) == TRUE);

	return Lex.num;
}
//---------------------------------------------------------------------------
EWRAM_CODE s32 LexGetHex(void)
{
	LexSkipSpace();
	Lex.num = 0;

	do {

		Lex.num *= 0x10;

		if(*Lex.pCur >= 'a' && *Lex.pCur <= 'f')
		{
			Lex.num += *Lex.pCur++ - 'a' + 10;
		}
		else
		{
			Lex.num += *Lex.pCur++ - '0';
		}

	} while(_IsXDigit(*Lex.pCur) == TRUE);


	return Lex.num;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* LexGetStr(void)
{
	LexSkipSpace();
	Lex.num = 0;

	do
	{
		Lex.str[Lex.num++] = *Lex.pCur++;

	} while(*Lex.pCur != ' ' && *Lex.pCur != LF);

	Lex.str[Lex.num++] = '\0';


	_ASSERT(Lex.num < LEX_MAX_STR_SIZE);

	return Lex.str;
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexSkipLine(void)
{
	do
	{
		if(*Lex.pCur == '\0')
		{
			return;
		}

	} while(*Lex.pCur++ != LF);
}
//---------------------------------------------------------------------------
EWRAM_CODE void LexSkipSpace(void)
{
	for(;;)
	{
		if(*Lex.pCur == '\0')
		{
			return;
		}

		if(*Lex.pCur == ' ')
		{
			Lex.pCur++;
			continue;
		}

		return;
	}
}
