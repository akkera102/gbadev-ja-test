#include "bios_arm.h"


//---------------------------------------------------------------------------
ST_BIOS Bios;


//---------------------------------------------------------------------------
EWRAM_CODE void BiosInit(void)
{
	_Memset(&Bios, 0x00, sizeof(ST_BIOS));
}
//---------------------------------------------------------------------------
IWRAM_CODE void BiosCpuSet(void* src, void* dst, u32 size)
{
	if((size & 0x3) == 0)
	{
		CpuSet(src, dst, (size / 4) | CPUSET_32BIT);
	}
	else
	{
		CpuSet(src, dst, (size / 2));
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void BiosCpuSetFix(void* src, void* dst, u32 size)
{
	if((size & 0x3) == 0)
	{
		CpuSet(src, dst, (size / 4) | CPUSET_32BIT | CPUSET_SRC_FIX);
	}
	else
	{
		CpuSet(src, dst, (size / 2) | CPUSET_SRC_FIX);
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void BiosCpuSetFixClear(void* dst, u32 size)
{
	BiosCpuSetFix(&Bios.dummy, dst, size);
}
//---------------------------------------------------------------------------
IWRAM_CODE void BiosCpuSetFast(void* src, void* dst, u32 size)
{
	CpuFastSet(src, dst, size / 4);
}
//---------------------------------------------------------------------------
IWRAM_CODE void BiosCpuSetFastFix(void* src, void* dst, u32 size)
{
	CpuFastSet(src, dst, size / 4 | CPUSET_SRC_FIX);
}
//---------------------------------------------------------------------------
IWRAM_CODE void BiosCpuSetFastFixClear(void* dst, u32 size)
{
	BiosCpuSetFastFix(&Bios.dummy, dst, size);
}
