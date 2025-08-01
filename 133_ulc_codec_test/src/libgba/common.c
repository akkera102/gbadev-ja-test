#include "common.h"
#include "../libbios/swi.h"

//---------------------------------------------------------------------------
char sprintfBuf[COMMON_SPRINT_BUF_CNT] ALIGN(4);


//---------------------------------------------------------------------------
IWRAM_CODE s32 _Strlen(char* s1)
{
	volatile s32 i = 0;

	while(s1[i] != '\0')
	{
		i++;
	}

	return i;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _Strncpy(char* ret, char* s2, s32 size)
{
	volatile char* s1 = ret;

	if(size == 0)
	{
		goto End;
	}

	while((*s1++ = *s2++) && --size > 0)
	{
		// EMPTY
	}

	if((*--s2 == '\0') && --size > 0)
	{
		do
		{
			*s1++ = '\0';
		
		} while(--size > 0);
	}

End:
	return ret;
}
//---------------------------------------------------------------------------
IWRAM_CODE s32 _Strncmp(char* s1, char* s2, s32 size)
{
	if(size == 0)
	{
		goto End;
	}

	do {
		if(*s1 != *s2++)
		{
			break;
		}

		if(*s1++ == '\0')
		{
			return 0;
		}

	} while (--size > 0);

	if(size > 0)
	{
		if(*s1   == '\0') return -1;
		if(*--s2 == '\0') return  1;

		return *s1 - *s2;
	}

End:
	return 0;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _Strcat(char* ret, char* s2)
{
	char* s1 = ret;

	while (*s1++ != '\0')
	{
		// EMPTY
	}
	s1--;

	while( (*s1++ = *s2++) != '\0' )
	{
		// EMPTY
	}

	return ret;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _Strchr(char* str, char chr)
{
	while(chr != *str)
	{
		if(*str++ == '\0')
		{
			return NULL;
		}
	}

	return str;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _Memcpy(void* s1, void* s2, s32 size)
{
	char* p1 = (char*)s1;
	char* p2 = (char*)s2;

	if(size == 0)
	{
		goto End;
	}

	size++;
	while(--size > 0)
	{
		*p1++ = *p2++;
	}

End:
	return s1;
}
//---------------------------------------------------------------------------
IWRAM_CODE s32 _Memcmp(void* s1, void* s2, s32 size)
{
	char* p1 = (char*)s1;
	char* p2 = (char*)s2;

	if(size)
	{
		size++;
		while(--size > 0)
		{
			if(*p1++ == *p2++)
			{
				continue;
			}

			return (s32)*--p1 - (s32)*--p2;
		}
	}

	return 0;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _Memset(void* s, u8 c, s32 size)
{
	volatile char* s1 = (char*)s;

	if(size == 0)
	{
		goto End;
	}

	size++;
	while(--size > 0)
	{
		*s1++ = c;
	}

End:
	return s;
}
//---------------------------------------------------------------------------
IWRAM_CODE void _Printf(char* format, ...)
{
	char* ap;
	va_start(ap, format);
	_DoSprintf(sprintfBuf, format, ap);
	va_end(ap);

	MgbaLog(sprintfBuf);
	MappyLog(sprintfBuf);
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _Sprintf(char* buf, char* format, ...)
{
	char* ap;
	va_start(ap, format);
	_DoSprintf(buf, format, ap);
	va_end(ap);

	return buf;
}
//---------------------------------------------------------------------------
IWRAM_CODE void _DoSprintf(char* str, char* fmt, char* ap)
{
	s32   val;
	char* val2;
	char  val3;

	char* src = str;
	char  c;
	s32   col = 0;
	char  colChr = ' ';
	bool  isCol;

	for(;;)
	{
		c = *fmt++;

		if(c == '\0')
		{
			*str++ = '\0';
			_ASSERT(str - src < COMMON_SPRINT_BUF_CNT);

			return;
		}

		if(c != '%')
		{
			*str++ = c;
			continue;
		}

		c = *fmt++;
		if(c == '0')
		{
			colChr = '0';
			c = *fmt++;
		}

		if(_IsDigit(c) == true)
		{
			col   = c - '0';
			isCol = true;
			c = *fmt++;
		}
		else
		{
			isCol = false;
		}

		switch(c)
		{
		case 'd':
			val  = va_arg(ap, int);

			if(val < 0)
			{
				val *= -1;
				*str++ = '-';
			}

			str = (isCol == true) ? _SprintfNumCol(val, 10, str, col, colChr, true) : _SprintfNum(val, 10, str); 
			break;

		case 'x':
			val = va_arg(ap, int);
			str = (isCol == true) ? _SprintfHexCol((u32)val, str, col, colChr, true, 'a') : _SprintfHex((u32)val, str, 'a'); 
			break;

		case 'X':
			val = va_arg(ap, int);
			str = (isCol == true) ? _SprintfHexCol((u32)val, str, col, colChr, true, 'A') : _SprintfHex((u32)val, str, 'A'); 
			break;

		case 's':
			val2 = va_arg(ap, char*);
			str = _SprintfString(val2, str);
			break;

		case 'c':
			val3  = va_arg(ap, char);
			*str++ = val3;
			break;

		case '\0':
		default:
			*str++ = '\0';
			return;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _SprintfNum(s32 val, s32 base, char* s)
{
	s32 c = SwiDivMod(val, base);
	val = SwiDiv(val, base);

	if(val > 0)
	{
		s = _SprintfNum(val, base, s);
	}

	*s++ = c+'0';

	return s;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _SprintfNumCol(s32 val, s32 base, char* s, s32 col, char colChr, bool isTop)
{
	s32 c = SwiDivMod(val, base);
	val = SwiDiv(val, base);

	if(col > 1)
	{
		s = _SprintfNumCol(val, base, s, col-1, colChr, false);
	}

	if(c != 0 || val != 0 || isTop == true)
	{
		*s++ = c+'0';
	}
	else
	{
		*s++ = colChr;
	}

	return s;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _SprintfHexCol(u32 val, char* s, s32 col, char colChr, bool isTop, char hex)
{
	u32 c = val & 0xf;
	val = val >> 4;

	if(col > 1)
	{
		s = _SprintfHexCol(val, s, col-1, colChr, false, hex);
	}

	if(c != 0 || val != 0 || isTop == true)
	{
		*s++ = (c>9) ? c-10+hex : c+'0';
	}
	else
	{
		*s++ = colChr;
	}

	return s;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _SprintfHex(u32 val, char* s, char hex)
{
	if(val >= 0x10)
	{
		s = _SprintfHex(val >> 4, s, hex);
	}

	u32 c = val & 0xf;
	*s++ = (c>9) ? c-10+hex : c+'0';

	return s;
}
//---------------------------------------------------------------------------
IWRAM_CODE char* _SprintfString(char* val, char* s)
{
	while(*val != '\0')
	{
		*s++ = *val++;
	}

	return s;
}
//---------------------------------------------------------------------------
IWRAM_CODE void MgbaLog(char* buf)
{
	REG_DEBUG_ENABLE = 0xC0DE;

	u32 len = _Strlen(buf);

	while(len)
	{
		u32 write = _Min(len, 256);

		_Memcpy(REG_DEBUG_STR, buf, write);
		REG_DEBUG_FLAGS = 0x102;				// mGBA Warning

		buf += write;
		len -= write;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void MappyLog(char* buf)
{
	__asm volatile("mov r2, %0; ldr r0,=0xc0ded00d; and r0,r0" :: "r"(buf) : "r2", "r0");
}
//---------------------------------------------------------------------------
void SystemError(char* format, ...)
{
	char* ap;
	va_start(ap, format);
	_DoSprintf(sprintfBuf, format, ap);
	va_end(ap);

	MgbaLog(sprintfBuf);
	MappyLog(sprintfBuf);

	for(;;)
	{
		SystemCall(5);
	}
}
