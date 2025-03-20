#include "mem.h"
#include "../libbios/swi.h"


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
	SwiCpuSet(src, dst, (size / 4) | CPUSET_32BIT);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemFix(void* src, void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

//	CpuSet(src, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
	SwiCpuSet(src, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemClear(void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

	SwiCpuSet(&Mem.dummy, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemIncFast(void* src, void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

//	CpuFastSet(src, dst, (size / 4));
	SwiCpuFastSet(src, dst, (size / 4));
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemFixFast(void* src, void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

//	CpuFastSet(src, dst, (size / 4) | CPUSET_SRC_FIX);
	SwiCpuFastSet(src, dst, (size / 4) | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
IWRAM_CODE void MemClearFast(void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

//	CpuFastSet(&Mem.dummy, dst, (size / 4) | CPUSET_SRC_FIX);
	SwiCpuFastSet(&Mem.dummy, dst, (size / 4) | CPUSET_SRC_FIX);
}
