#include "mp.h"
#include "mp2.h"

//---------------------------------------------------------------------------

ROM_DATA ST_MP_WAVE testWave = {
	.type = 0,
	.stat = 0x4000,
	.freq = 68583572,
	.loop = 0,
	.size = 256,
	.data = {
		0, 3, 6, 9, 12, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 49, 51, 54, 57, 60, 63, 65, 68, 71, 73, 76, 78, 81, 83, 85, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 107, 109, 111, 112, 113, 115, 116, 117, 118, 120, 121, 122, 122, 123, 124, 125, 125, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 126, 126, 126, 125, 125, 124, 123, 122, 122, 121, 120, 118, 117, 116, 115, 113, 112, 111, 109, 107, 106, 104, 102, 100, 98, 96, 94, 92, 90, 88, 85, 83, 81, 78, 76, 73, 71, 68, 65, 63, 60, 57, 54, 51, 49, 46, 43, 40, 37, 34, 31, 28, 25, 22, 19, 16, 12, 9, 6, 3, 0, -3, -6, -9, -12, -16, -19, -22, -25, -28, -31, -34, -37, -40, -43, -46, -49, -51, -54, -57, -60, -63, -65, -68, -71, -73, -76, -78, -81, -83, -85, -88, -90, -92, -94, -96, -98, -100, -102, -104, -106, -107, -109, -111, -112, -113, -115, -116, -117, -118, -120, -121, -122, -122, -123, -124, -125, -125, -126, -126, -126, -127, -127, -127, -127, -127, -127, -127, -126, -126, -126, -125, -125, -124, -123, -122, -122, -121, -120, -118, -117, -116, -115, -113, -112, -111, -109, -107, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -85, -83, -81, -78, -76, -73, -71, -68, -65, -63, -60, -57, -54, -51, -49, -46, -43, -40, -37, -34, -31, -28, -25, -22, -19, -16, -12, -9, -6, -3, 0, 0, 0, 0
	},
};

ROM_DATA ST_MP_TONE testTone = {
	.ctl     = { 0, 60, 0, 0 },
	.wp      = &testWave,
	.Attack  = 127,
	.Decay   = 245,
	.Sustain = 180,
	.Release = 165,
};

ST_MP_AREA   MpArea;
ST_MP_PLAYER MpPlayer;
ST_MP_TRACK  MpTrack[MP_MAX_TRACK];

//---------------------------------------------------------------------------
void MpInit(void)
{
	MpExecSwi1A(&MpArea);
	MpExecSwi20(&MpPlayer, MpTrack, MP_MAX_TRACK);
	MpExecSwi21(&MpPlayer, &testSong);
}
//---------------------------------------------------------------------------
void MpPlayAdr(u32 adr)
{
	MpExecSwi21(&MpPlayer, (void*)adr);
}
//---------------------------------------------------------------------------
void MpPlayMus(void)
{
	MpExecSwi21(&MpPlayer, &testSong);
}
//---------------------------------------------------------------------------
void MpPlayKey(u32 ch, u32 key)
{
	if(ch >= MP_MAX_CH)
	{
		return;
	}

	ST_MP_TONE* t = &testTone;
	ST_MP_CH*   c = &MpArea.vchn[ch];

	c->LeftVol  = 64;
	c->RightVol = 64;

	c->Attack   = 255;
	c->Decay    = 240;
	c->Sustain  = 0;
	c->Release  = 200;
/*
	c->Attack   = t->Attack;
	c->Decay    = t->Decay;
	c->Sustain  = t->Sustain;
	c->Release  = t->Release;
*/
	c->wp       = t->wp;
	c->fr       = MpExecSwi1F(key, 0);

	// キーオン
	c->Status   = 0x80;
}
//---------------------------------------------------------------------------
void MpStopKey(u32 ch)
{
	if(ch >= MP_MAX_CH)
	{
		return;
	}

	ST_MP_CH* c = &MpArea.vchn[ch];

	// キーオフ
	// リリース状態（余韻）に移行
	c->Status |= 0x40;
}
//---------------------------------------------------------------------------
void MpStopAll(void)
{
	s32 i;

	for(i=0; i<MP_MAX_CH; i++)
	{
		MpArea.vchn[i].Status = 0;
	}
}
//---------------------------------------------------------------------------
u32 MpGetActiveCnt(void)
{
	u32 ret = 0;
	s32 i;

	for(i=0; i<MP_MAX_CH; i++)
	{
		if(MpArea.vchn[i].Status != 0)
		{
			ret++;
		}
	}
	
	return ret;
}
//---------------------------------------------------------------------------
// SoundDriverInit
void MpExecSwi1A(ST_MP_AREA* a)
{
	register u32 _r0 asm("r0") = (u32)a;

	asm volatile("swi #0x1a" : "+l" (_r0) :: "r1", "r2", "r3", "r12", "cc", "memory");
}
//---------------------------------------------------------------------------
// SoundDriverMode
void MpExecSwi1B(u32 mode)
{
	register u32 _r0 asm("r0") = mode;

	asm volatile("swi #0x1b" : "+l" (_r0) :: "r1", "r2", "r3", "r12", "cc", "memory");
}
//---------------------------------------------------------------------------
// SoundDriverMain
void MpExecSwi1C(void)
{
	asm volatile("swi #0x1c" ::: "r0", "r1", "r2", "r3", "r12", "cc", "memory");
}
//---------------------------------------------------------------------------
// SoundDriverVSync
void MpExecSwi1D(void)
{
	asm volatile("swi #0x1d" ::: "r0", "r1", "r2", "r3", "r12", "cc", "memory");
}
//---------------------------------------------------------------------------
// MidiKey2Freq
u32 MpExecSwi1F(u32 key, u32 tune)
{
	register u32 _r0 asm("r0") = (u32)&testWave;
	register u32 _r1 asm("r1") = key;
	register u32 _r2 asm("r2") = tune;

	asm volatile("swi #0x1f" : "+l" (_r0), "+l" (_r1), "+l" (_r2) :: "r3", "r12", "cc", "memory");

	return _r0;
}
//---------------------------------------------------------------------------
// SoundWhatever0
void MpExecSwi20(ST_MP_PLAYER* p, ST_MP_TRACK* t, u32 cnt)
{
	register u32 _r0 asm("r0") = (u32)p;
	register u32 _r1 asm("r1") = (u32)t;
	register u32 _r2 asm("r2") = cnt;

	asm volatile("swi #0x20" : "+l" (_r0), "+l" (_r1), "+l" (_r2) :: "r3", "r12", "cc", "memory");
}
//---------------------------------------------------------------------------
// SoundWhatever1
void MpExecSwi21(ST_MP_PLAYER* p, ST_MP_SONG* s)
{
	register u32 _r0 asm("r0") = (u32)p;
	register u32 _r1 asm("r1") = (u32)s;

	asm volatile("swi #0x21" : "+l" (_r0), "+l" (_r1) :: "r2", "r3", "r12", "cc", "memory");
}
