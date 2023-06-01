#ifndef __SYS_ARM_H__
#define __SYS_ARM_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"


IWRAM_CODE void CpuSet( const void *source, void *dest, u32 mode);
IWRAM_CODE void CpuFastSet( const void *source, void *dest, u32 mode);
IWRAM_CODE void LZ77UnCompWram(void *source, void *dest);
IWRAM_CODE void LZ77UnCompVram(void *source, void *dest);


#ifdef __cplusplus
}
#endif
#endif
