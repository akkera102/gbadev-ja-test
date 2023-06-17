#include "gbfs.h"


//---------------------------------------------------------------------------
// gba_cart.ld
extern u8 __rom_end__;


//---------------------------------------------------------------------------
ST_GBFS Gbfs;


//---------------------------------------------------------------------------
EWRAM_CODE void GbfsInit(void)
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
IWRAM_CODE void* GbfsGetPointer2(u32 cnt)
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
IWRAM_CODE void* GbfsGetSafePointer2(u32 cnt)
{
	void* p = GbfsGetPointer2(cnt);

	if(p == NULL)
	{
		SystemError("[Err][GBFSGetSafePointer2] .gbfs File Not Found: No.%d\n", cnt);
	}

	return p;
}
//---------------------------------------------------------------------------
EWRAM_CODE char* GbfsGetFileName(void)
{
	return Gbfs.pList[Gbfs.pos].fname;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 GbfsGetFileSize(void)
{
	return Gbfs.pList[Gbfs.pos].size;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 GbfsGetArcSize(void)
{
	return Gbfs.pHeader->size;
}
//---------------------------------------------------------------------------
EWRAM_CODE u32 GbfsGetArcCnt(void)
{
	return Gbfs.pHeader->fileCnt;
}
