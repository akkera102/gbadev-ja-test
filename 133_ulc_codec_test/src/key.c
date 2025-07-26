#include "key.h"

//---------------------------------------------------------------------------
ST_KEY Key;


//---------------------------------------------------------------------------
void KeyInit(void)
{
	_Memset(&Key, 0x00, sizeof(ST_KEY));
}
//---------------------------------------------------------------------------
// vblank����1�񂾂��Ăяo���܂��i�`���^�����O�h�~�j
IWRAM_CODE void KeyExec(void)
{
	u32 cnt = REG_KEYINPUT;

	cnt     = ~cnt & 0x3ff;
	Key.trg = (Key.trg ^ cnt) & ~Key.cnt;
	Key.off = Key.off ^ (~cnt & Key.cnt);
	Key.cnt = cnt;


	// �L�[���s�[�g
	if(Key.trg & DPAD || Key.repCnt == 0)
	{
		Key.rep = Key.cnt;
		Key.repCnt = KEY_REPEAT_CNT;
	}
	else
	{
		Key.rep = 0;
	}

	if(Key.cnt & DPAD)
	{
		if(Key.repCnt != 0) Key.repCnt--;
	}
	else
	{
		Key.repCnt = 0;
	}
}
//---------------------------------------------------------------------------
// ���݉�����Ă���{�^��
IWRAM_CODE u32 KeyGetCnt(void)
{
	return Key.cnt;
}
//---------------------------------------------------------------------------
// �����ꂽ���̃{�^��
IWRAM_CODE u32 KeyGetTrg(void)
{
	return Key.trg;
}
//---------------------------------------------------------------------------
// �����ꂽ���̃{�^��
IWRAM_CODE u32 KeyGetOff(void)
{
	return Key.off;
}
//---------------------------------------------------------------------------
// �L�[���s�[�g�̃{�^���B�\���L�[�̂ݑΉ�
IWRAM_CODE u32 KeyGetRep(void)
{
	return Key.rep;
}
