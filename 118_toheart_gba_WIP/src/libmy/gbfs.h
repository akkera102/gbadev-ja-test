#ifndef __GBFS_H__
#define __GBFS_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// �w�b�_�i32�o�C�g�j
typedef struct {
	char sig[16];				// �V�O�l�`�� "PinEightGBFS" + 0x0d + 0x0a + 0x1a + 0x0a
	u32  size;					// �A�[�J�C�u�̑傫��
	u16  dirOff;				// �t�@�C���ꗗ�̃I�t�Z�b�g(ROM�I�[����̑���)
	u16  fileCnt;				// �t�@�C���̓o�^��
	u8   noUse[8];				// �󂫗̈�
} __PACKED ST_GBFS_HEADER;


// �t�@�C�����X�g�i32�o�C�g�j
typedef struct {
	char fname[24];				// �t�@�C����
	u32  size;					// �T�C�Y
	u32  dataOff;				// �t�@�C���̃I�t�Z�b�g(ROM�I�[����̑���)
} __PACKED ST_GBFS_LIST;


typedef struct {
	ST_GBFS_HEADER* pHeader;
	ST_GBFS_LIST*   pList;
	u32             pos;
} ST_GBFS;

//---------------------------------------------------------------------------
EWRAM_CODE void  GbfsInit(void);

IWRAM_CODE void* GbfsGetPointer(char* fname);
IWRAM_CODE void* GbfsGetPointer2(u32 cnt);
IWRAM_CODE void* GbfsGetSafePointer(char* fname);
IWRAM_CODE void* GbfsGetSafePointer2(u32 cnt);

EWRAM_CODE char* GbfsGetFileName(void);
EWRAM_CODE u32   GbfsGetFileSize(void);
EWRAM_CODE u32   GbfsGetArcSize(void);
EWRAM_CODE u32   GbfsGetArcCnt(void);


#ifdef __cplusplus
}
#endif
#endif
