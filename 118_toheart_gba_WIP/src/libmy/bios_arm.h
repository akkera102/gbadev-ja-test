#ifndef __BIOS_H__
#define __BIOS_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
typedef struct {
	u32 dummy ALIGN(4);
} ST_BIOS;


//---------------------------------------------------------------------------
EWRAM_CODE void BiosInit(void);

IWRAM_CODE void BiosCpuSet(void* src, void* dst, u32 size);
IWRAM_CODE void BiosCpuSetFix(void* src, void* dst, u32 size);
IWRAM_CODE void BiosCpuSetFixClear(void* dst, u32 size);

IWRAM_CODE void BiosCpuSetFast(void* src, void* dst, u32 size);
IWRAM_CODE void BiosCpuSetFastFix(void* src, void* dst, u32 size);
IWRAM_CODE void BiosCpuSetFastFixClear(void* dst, u32 size);


#ifdef __cplusplus
}
#endif
#endif
