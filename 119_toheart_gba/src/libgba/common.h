#ifndef __COMMON_H__
#define __COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"


//---------------------------------------------------------------------------
typedef char* va_list;

#define _Max(a,b)				(((a)>(b))?(a):(b))
#define _Min(a,b)				(((a)>(b))?(b):(a))
#define _Toupper(c)				((c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c)
#define _IsAlpha(c)				((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? true : false)
#define _IsDigit(c)				((c >= '0') && (c <= '9') ? true : false)
#define _IsXDigit(c)			((_IsDigit(c) == true) || (c >= 'a' && c <= 'f') ? true : false)
#define _IsSpace(c)				((c == ' ') ? true : false)
#define _IsSJIS(c)				(((c)>=0x81 && (c)<=0x9f) || ((c)>=0xe0 && (c)<=0xef))

#define __vasz(x)				((sizeof(x)+sizeof(int)-1) & ~(sizeof(int) -1))
#define va_start(ap, n)			((ap) = (va_list)&n + __vasz(n))
#define va_arg(ap, type)		(*((type *)((va_list)((ap) = (void *)((va_list)(ap) + __vasz(type))) - __vasz(type))))
#define va_end(ap)				

#define CR						0x0d
#define LF						0x0a


//---------------------------------------------------------------------------
EWRAM_CODE u16   _Strlen(char* s1);
EWRAM_CODE char* _Strncpy(char* ret, char* s2, u16 size);
EWRAM_CODE s16   _Strncmp(char* s1, char* s2, u16 size);
EWRAM_CODE char* _Strcat(char* ret, char* s2);
EWRAM_CODE char* _Strchr(char* str, char chr);
EWRAM_CODE u16   _Atoi(char* s);

EWRAM_CODE char* _Memcpy(void* s1, void* s2, u32 size);
EWRAM_CODE s16   _Memcmp(void* s1, void* s2, u32 size);
EWRAM_CODE char* _Memset(void* s, u8 c, u32 size);

IWRAM_CODE void  _Printf(char* format, ...);
IWRAM_CODE char* _Sprintf(char* buf, char* format, ...);
IWRAM_CODE void  _DoSprintf(char* str, char* fmt, char* ap);
IWRAM_CODE char* _SprintfNum(s32 val, s32 base, char* s);
IWRAM_CODE char* _SprintfNumCol(s32 val, s32 base, char* s, s32 col, char colChr, bool isTop);
IWRAM_CODE char* _SprintfHex(u32 val, char* s, char hex);
IWRAM_CODE char* _SprintfHexCol(u32 val, char* s, s32 col, char colChr, bool isTop, char hex);
IWRAM_CODE char* _SprintfString(char* val, char* s);

IWRAM_CODE void MappyLog(char* buf);
EWRAM_CODE void SystemError(char* format, ...);

#ifdef __cplusplus
}
#endif
#endif

