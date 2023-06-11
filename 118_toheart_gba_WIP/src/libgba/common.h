#ifndef COMMON_H
#define COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"


//---------------------------------------------------------------------------
#define _Max(a,b)				(((a)>(b))?(a):(b))
#define _Min(a,b)				(((a)>(b))?(b):(a))
#define _Toupper(c)				((c >= 'a' && c <= 'z') ? (c - ('a' - 'A')) : c)
#define _IsAlpha(c)				((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? TRUE : FALSE)
#define _IsDigit(c)				((c >= '0') && (c <= '9') ? TRUE : FALSE)
#define _IsXDigit(c)			((_IsDigit(c) == TRUE) || (c >= 'a' && c <= 'f') ? TRUE : FALSE)
#define _IsSpace(c)				((c == ' ') ? TRUE : FALSE)
#define _IsSJIS(c)				((((c)>=0x81 && (c)<=0x9f) || ((c)>=0xe0 && (c)<=0xef)) ? TRUE : FALSE)
#define _IsKana(c)				(((c)>=0xA6 && (c)<=0xDD) ? TRUE : FALSE)

#define __vasz(x)				((sizeof(x)+sizeof(int)-1) & ~(sizeof(int) -1))
#define va_start(ap, n)			((ap) = (char*)&n + __vasz(n))
#define va_arg(ap, type)		(*((type*)((char*)((ap) = (void*)((char*)(ap) + __vasz(type))) - __vasz(type))))
#define va_end(ap)				

#define CR						0x0d
#define LF						0x0a


//---------------------------------------------------------------------------
EWRAM_CODE s32   _Strlen(char* s1);
EWRAM_CODE char* _Strncpy(char* ret, char* s2, s32 size);
EWRAM_CODE s32   _Strncmp(char* s1, char* s2, s32 size);
EWRAM_CODE char* _Strcat(char* ret, char* s2);
EWRAM_CODE char* _Strchr(char* str, char chr);
EWRAM_CODE u32   _Atoi(char* s);

EWRAM_CODE char* _Memcpy(void* s1, void* s2, s32 size);
EWRAM_CODE s32   _Memcmp(void* s1, void* s2, s32 size);
IWRAM_CODE char* _Memset(void* s, u8 c, s32 size);

IWRAM_CODE void  _Printf(char* format, ...);
IWRAM_CODE char* _Sprintf(char* buf, char* format, ...);
IWRAM_CODE void  _DoSprintf(char* str, char* fmt, char* ap);
IWRAM_CODE char* _SprintfNum(s32 val, s32 base, char* s);
IWRAM_CODE char* _SprintfNumCol(s32 val, s32 base, char* s, s32 col, char colChr, bool isTop);
IWRAM_CODE char* _SprintfHex(u32 val, char* s, char hex);
IWRAM_CODE char* _SprintfHexCol(u32 val, char* s, s32 col, char colChr, bool isTop, char hex);
IWRAM_CODE char* _SprintfString(char* val, char* s);

IWRAM_CODE void SystemError(char* format, ...);
IWRAM_CODE void mappylog(char* buf);


#ifdef __cplusplus
}
#endif
#endif
