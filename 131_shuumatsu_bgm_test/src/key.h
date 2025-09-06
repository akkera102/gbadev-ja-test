#ifndef KEY_H
#define KEY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define KEY_REPEAT_CNT		10


//---------------------------------------------------------------------------
typedef struct {
	u16 cnt;					// ���݂̃L�[
	u16 trg;					// �����ꂽ�L�[
	u16 off;					// �����ꂽ�L�[
	u16 rep;					// ���s�[�g�L�[
	s16 repCnt;				// ���s�[�g�J�E���g
	u8  hld_i;
	u16 hld[0x8];			// 8�t���[�������ꑱ���Ă���L�[
} ST_KEY;


//---------------------------------------------------------------------------
void KeyInit(void);
IWRAM_CODE void KeyExec(void);

IWRAM_CODE u32  KeyGetCnt(void);
IWRAM_CODE u32  KeyGetTrg(void);
IWRAM_CODE u32  KeyGetOff(void);
IWRAM_CODE u32  KeyGetRep(void);
IWRAM_CODE u32  KeyGetHld(void);


#ifdef __cplusplus
}
#endif
#endif
