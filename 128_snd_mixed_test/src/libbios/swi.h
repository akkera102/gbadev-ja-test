#ifndef __SWI_H__
#define __SWI_H__
#ifdef __cplusplus
extern "C" {
#endif

/*
CULT-GBA and fixed Lorenzooone ver(MIT)

https://github.com/Cult-of-GBA/BIOS
https://github.com/Lorenzooone/Pokemon-Gen3-to-Gen-X/blob/main/source/decompress.s
*/


IWRAM_CODE void SwiCpuSet(void* src, void* dst, u32 mode);
IWRAM_CODE void SwiCpuFastSet(void* src, void* dst, u32 mode);
IWRAM_CODE void SwiLZ77UnCompWrite16bit(void* src, void* dst);
IWRAM_CODE s32  SwiDiv(s32 a, s32 b);
IWRAM_CODE s32  SwiDivMod(s32 a, s32 b);


#ifdef __cplusplus
}
#endif
#endif
