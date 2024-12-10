#include "mem.h"
#include "../libbios/bios.h"


//---------------------------------------------------------------------------
ST_MEM Mem;


//---------------------------------------------------------------------------
EWRAM_CODE void MemInit(void)
{
	_Memset(&Mem, 0x00, sizeof(ST_MEM));
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemInc(void* src, void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

//	CpuSet(src, dst, (size / 4) | CPUSET_32BIT);
	swi_CpuSet(src, dst, (size / 4) | CPUSET_32BIT);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemFix(void* src, void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

//	CpuSet(src, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
	swi_CpuSet(src, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemClear(void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

	MemFix(&Mem.dummy, dst, size);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemIncFast(void* src, void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

//	CpuFastSet(src, dst, (size / 4));
	swi_CpuFastSet(src, dst, (size / 4));
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemFixFast(void* src, void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

//	CpuFastSet(src, dst, (size / 4) | CPUSET_SRC_FIX);
	swi_CpuFastSet(src, dst, (size / 4) | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemClearFast(void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

//	CpuFastSet(&Mem.dummy, dst, (size / 4) | CPUSET_SRC_FIX);
	swi_CpuFastSet(&Mem.dummy, dst, (size / 4) | CPUSET_SRC_FIX);
}
