#ifndef __NV2_H__
#define __NV2_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "libgba/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	char* cmd;
	s32   argv;
	void  (*pFunc)(void);

} ST_NV_PARSE_TBL;

//---------------------------------------------------------------------------
void NvExecParse(void);
void NvExecParseSub(void);

void NvExecParse1G(void);
void NvExecParse1B(void);
void NvExecParse1E(void);
void NvExecParse1X(void);
void NvExecParse1J(void);
void NvExecParse1T(void);
void NvExecParse1S(void);
void NvExecParse2G(void);
void NvExecParse2R(void);
void NvExecParse2L(void);
void NvExecParse2N(void);
void NvExecParse2I(void);
void NvExecParse2W(void);
void NvExecParse2T(void);
void NvExecParse3R(void);
void NvExecParse3T(void);
void NvExecParse3M(void);
void NvExecParse3N(void);
void NvExecParseSel(void);
void NvExecParseCal(void);

bool NvIsExecParseCmd(char* p);


#ifdef __cplusplus
}
#endif
#endif
