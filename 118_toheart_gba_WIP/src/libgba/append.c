#include "append.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
IWRAM_CODE void CpuSet(const void* source,  void* dest, u32 mode)
{
	SystemCall(11);
}
//---------------------------------------------------------------------------
IWRAM_CODE void CpuFastSet(const void* source,  void* dest, u32 mode)
{
	SystemCall(12);
}
//---------------------------------------------------------------------------
IWRAM_CODE void LZ77UnCompWram(void* source, void* dest)
{
	SystemCall(17);
}
//---------------------------------------------------------------------------
IWRAM_CODE void LZ77UnCompVram(void* source, void* dest)
{
	SystemCall(18);
}
