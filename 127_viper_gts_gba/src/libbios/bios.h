#ifndef __FADE_H__
#define __FADE_H__
#ifdef __cplusplus
extern "C" {
#endif


IWRAM_CODE void swi_CpuSet(void* src, void* dst, u32 mode);
IWRAM_CODE void swi_CpuFastSet(void* src, void* dst, u32 mode);
IWRAM_CODE void swi_LZ77UnCompWrite16bit(void* src, void* dst);


#ifdef __cplusplus
}
#endif
#endif
