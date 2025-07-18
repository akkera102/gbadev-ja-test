#ifndef __MEM_H__
#define __MEM_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "../libgba/gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
typedef struct {
	u32 dummy ALIGN(4);

} ST_MEM;


//---------------------------------------------------------------------------
void MemInit(void);

void MemInc(void* src, void* dst, u32 size);
void MemFix(void* src, void* dst, u32 size);
void MemClear(void* dst, u32 size);

void MemIncFast(void* src, void* dst, u32 size);
void MemFixFast(void* src, void* dst, u32 size);
void MemClearFast(void* dst, u32 size);


#ifdef __cplusplus
}
#endif
#endif
