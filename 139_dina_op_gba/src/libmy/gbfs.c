#include "gbfs.h"

/* gbfs.h
   access object in a GBFS file

Copyright 2002 Damian Yerrick

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

//---------------------------------------------------------------------------
// gba_cart.ld
extern u8 __rom_end__;


//---------------------------------------------------------------------------
ST_GBFS Gbfs;


//---------------------------------------------------------------------------
void GbfsInit(void)
{
	_Memset(&Gbfs, 0x00, sizeof(ST_GBFS));


	char* pHeader = (char*)(((u32)&__rom_end__ + 0xff) & 0xffffff00);

	if(_Strncmp(pHeader, "PinEightGBFS", sizeof("PinEightGBFS")-1) == 0)
	{
		Gbfs.pHeader = (ST_GBFS_HEADER*)pHeader;
		Gbfs.pList   = (ST_GBFS_LIST*)(pHeader + Gbfs.pHeader->dirOff);
	}
	else
	{
		SystemError("[Err][GbfsInit] .gbfs File Not Found(pHeader = %x)", pHeader);
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void* GbfsGetPointer(char* fname)
{
	s32 left  = 0;
	s32 right = Gbfs.pHeader->fileCnt;
	s32 mid;
	s32 ret;

	while(left <= right)
	{
		mid = (left + right) / 2;
		ret = _Strncmp(fname, Gbfs.pList[mid].fname, 24);

		if(ret == 0)
		{
			Gbfs.pos = mid;
			return (u8*)Gbfs.pHeader + Gbfs.pList[mid].dataOff;
		}

		if(ret > 0)
		{
			left  = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}

	return NULL;
}
//---------------------------------------------------------------------------
IWRAM_CODE void* GbfsGetPointer2(s32 cnt)
{
	if(cnt >= Gbfs.pHeader->fileCnt)
	{
		return NULL;
	}

	Gbfs.pos = cnt;
	return (u8*)Gbfs.pHeader + Gbfs.pList[cnt].dataOff;
}
//---------------------------------------------------------------------------
IWRAM_CODE void* GbfsGetSafePointer(char* fname)
{
	void* p = GbfsGetPointer(fname);

	if(p == NULL)
	{
		SystemError("[Err][GBFSGetSafePointer] .gbfs File Not Found: %s\n", fname);
	}

	return p;
}
//---------------------------------------------------------------------------
IWRAM_CODE void* GbfsGetSafePointer2(s32 cnt)
{
	void* p = GbfsGetPointer2(cnt);

	if(p == NULL)
	{
		SystemError("[Err][GBFSGetSafePointer2] .gbfs File Not Found: No.%d\n", cnt);
	}

	return p;
}
//---------------------------------------------------------------------------
char* GbfsGetFileName(void)
{
	return Gbfs.pList[Gbfs.pos].fname;
}
//---------------------------------------------------------------------------
u32 GbfsGetFileSize(void)
{
	return Gbfs.pList[Gbfs.pos].size;
}
//---------------------------------------------------------------------------
u32 GbfsGetArcSize(void)
{
	return Gbfs.pHeader->size;
}
//---------------------------------------------------------------------------
u32 GbfsGetArcCnt(void)
{
	return Gbfs.pHeader->fileCnt;
}
