#ifndef __BIOS_H__
#define __BIOS_H__
#ifdef __cplusplus
extern "C" {
#endif

/*
CULT-GBA and fixed Lorenzooone ver(MIT)

https://github.com/Cult-of-GBA/BIOS
https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X/blob/main/source/decompress.s
*/


IWRAM_CODE void swi_CpuSet(void* src, void* dst, u32 mode);
IWRAM_CODE void swi_CpuFastSet(void* src, void* dst, u32 mode);
IWRAM_CODE void swi_LZ77UnCompWrite16bit(void* src, void* dst);


#ifdef __cplusplus
}
#endif
#endif
