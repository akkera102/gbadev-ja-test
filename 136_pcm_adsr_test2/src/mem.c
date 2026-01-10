#include "mem.h"
#include "libbios/swi.h"


//---------------------------------------------------------------------------
ST_MEM Mem;


//---------------------------------------------------------------------------
void MemInit(void)
{
	_Memset(&Mem, 0x00, sizeof(ST_MEM));
}
//---------------------------------------------------------------------------
void MemInc(void* src, void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

	SwiCpuSet(src, dst, (size / 4) | CPUSET_32BIT);
}
//---------------------------------------------------------------------------
void MemFix(void* src, void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

	SwiCpuSet(src, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
void MemClear(void* dst, u32 size)
{
	_ASSERT((size & 0x3) == 0);

	SwiCpuSet(&Mem.dummy, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
void MemIncFast(void* src, void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

	SwiCpuFastSet(src, dst, (size / 4));
}
//---------------------------------------------------------------------------
void MemFixFast(void* src, void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

	SwiCpuFastSet(src, dst, (size / 4) | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
void MemClearFast(void* dst, u32 size)
{
	_ASSERT((size & 31) == 0);

	SwiCpuFastSet(&Mem.dummy, dst, (size / 4) | CPUSET_SRC_FIX);
}
