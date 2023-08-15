#ifndef __KEY_H__
#define __KEY_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "../libgba/gba.h"

//---------------------------------------------------------------------------
#define KEY_REPEAT_CNT		10


//---------------------------------------------------------------------------

typedef struct {
	u32 cnt;					// ���݂̃L�[
	u32 trg;					// �����ꂽ�L�[
	u32 off;					// �����ꂽ�L�[
	u32 rep;					// ���s�[�g�L�[
	s32 repCnt;					// ���s�[�g�J�E���g
} ST_KEY;


//---------------------------------------------------------------------------
EWRAM_CODE void KeyInit(void);
IWRAM_CODE void KeyExec(void);

EWRAM_CODE u32  KeyGetCnt(void);
EWRAM_CODE u32  KeyGetTrg(void);
EWRAM_CODE u32  KeyGetOff(void);
EWRAM_CODE u32  KeyGetRep(void);


#ifdef __cplusplus
}
#endif
#endif
