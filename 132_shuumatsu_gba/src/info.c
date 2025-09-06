#include "info.h"

//---------------------------------------------------------------------------
ROM_DATA s32 InfoImg[] = {
	8,		// BACK1
	46,		// BACK2
	36,		// BACK3
	29,		// BACK4
	37,		// BACK5
	47,		// BACK6
	28,		// BACK7
	7,		// BACK8
	39,		// BACK9
	138,	// BADIRH
//	2,		// BLACK
	59,		// CBAFTER
	56,		// CBBEFORE
	90,		// CHIEH1
	91,		// CHIEH2
	92,		// CHIEH3
	93,		// CHIEH4
	125,	// CHIEKAKO
	94,		// CHIEKISS
	67,		// CHIEMOGU
	69,		// DOMKANA
//	135,	// END
//	95,		// FRI
	48,		// FURIIRO
	127,	// FURIKOR
	14,		// GROCHIE
	15,		// GROSHIGE
	145,	// HAPPYIRH
	143,	// HAPPYKOR
	144,	// HAPPYMDR
	107,	// HIZAKAO
	16,		// HOKERUKI
	84,		// IRHHOSSA
	113,	// IROH1
	114,	// IROH2
	115,	// IROH3
	116,	// IROH4
	117,	// IROKISS
	9,		// JUGYOCHI
	10,		// JUGYOKAO
	98,		// KAGIIRO
	118,	// KANAH1
	119,	// KANAH2
	120,	// KANAH3
	121,	// KANAH4
	61,		// KANAIRO
	122,	// KANAKISS
	101,	// KAOH1
	102,	// KAOH2
	103,	// KAOH3
	104,	// KAOH4
	105,	// KAOH4B
	106,	// KAOKISS
	146,	// KCYOZORA
	85,		// KMIOROSI
	54,		// KOKERUKI
	89,		// KOUEN
	139,	// KURAKANA
	137,	// KURAKOR
	142,	// KURARKTH
//	0,		// LOGO1
//	1,		// LOGO2
	68,		// MADOKAO
	83,		// MADOMI1
	82,		// MADOMI2
	109,	// MIDOH1
	110,	// MIDOH2
	111,	// MIDOH3
	112,	// MIDOH4
	17,		// MIDOHON
	108,	// MIDOKISS
	97,		// MIDOMEGA
	128,	// MIDOMIO
//	6,		// MON
	62,		// MUSATWO
	12,		// OKUIRO
	13,		// OKUKANA
	100,	// ONBUCHIE
	124,	// RKHEIWA
	132,	// ROCKETKN
	74,		// RUKIGYU
	76,		// RUKIH1
	77,		// RUKIH2
	78,		// RUKIH3
	79,		// RUKIH4
	141,	// RUKIKISS
//	123,	// SAT
	126,	// SCCHIE
	99,		// SCKAIWA
	58,		// SEITOH1
	87,		// SEITOH2
	11,		// SORA
	81,		// TEREKAO
//	80,		// THU
//	990,	// TITLEX
//	18,		// TOPFONT
//	55,		// TUE
//	66,		// WED
	75,		// YUBIIRO
//	991,	// TITLE3
};

// 昇順（アーカイブ順でなく）
ROM_DATA s32 InfoBgm[] = {
	1,		// SILENCE
	0,		// 01_OP03
	5,		// 02_OP06
	10,		// 03_OP08
	8,		// 04_OP11
	14,		// 05_OP12
	12,		// 06_OP13
	13,		// 07_OP14
	6,		// 08_OP16
	9,		// 09_OP17
	7,		// 10_OP18
	4,		// 12_OP20_
	16,		// 13_OP21
	17,		// 14_OP22
	2,		// 15_OP23
	15,		// 16_OP28
	18,		// 17_OP29
	20,		// 18_OP30
//	3,		// RADIO
//	11,		// RADIONZ
};

ROM_DATA s32 InfoFmx[] = {
	0,		// TIMEBELL
	1,		// OD_M
	2,		// OD_P
	3,		// PAPER
	4,		// SD_M
	5,		// SD_P
	6,		// IDO
	7,		// DOM
	8,		// OD_WO
	9,		// OD_WC
	10,		// PAPERBAG
	11,		// OD_MO
};

//---------------------------------------------------------------------------
void InfoInit(void)
{
	// EMPTY
}
//---------------------------------------------------------------------------
s32 InfoGetImg(s32 idx)
{
	_ASSERT(idx < INFO_MAX_IMG_CNT);

	return InfoImg[idx];
}
//---------------------------------------------------------------------------
s32 InfoGetBgm(s32 idx)
{
	_ASSERT(idx < INFO_MAX_BGM_CNT);

	return InfoBgm[idx];
}
//---------------------------------------------------------------------------
s32 InfoGetFmx(s32 idx)
{
	_ASSERT(idx < INFO_MAX_FMX_CNT);

	return InfoFmx[idx];
}
//---------------------------------------------------------------------------
// キャラクタ番号からマスク番号を取得します
s32 InfoGetMskNo(s32 no)
{
	// chieko
	if(no == 41 || no == 43 || no == 44 || no == 45 || no == 63 || no == 96)
	{
		return 0;
	}

	// chihiro
	if(no == 24 || no == 26 || no == 27)
	{
		return 1;
	}

	// iroha
	if(no == 49 || no == 50 || no == 51)
	{
		return 2;
	}

	// kana
	if(no == 52 || no == 53 || no == 86 || no == 130 || no == 131)
	{
		return 3;
	}

	// kaori
	if(no == 19 || no == 20 || no == 21 || no == 57)
	{
		return 4;
	}

	// midori
	if(no == 22 || no == 23 || no == 25 || no == 38 || no == 60 || no == 129)
	{
		return 5;
	}

	// ruki
	if(no == 30 || no == 33 || no == 34 || no == 72 || no == 73)
	{
		return 6;
	}

	// shige
	if(no == 40 || no == 42 || no == 64 || no == 65 || no == 88)
	{
		return 7;
	}

	// tahiro
	if(no == 31 || no == 32 || no == 35 || no == 70 || no == 71)
	{
		return 8;
	}


	SystemError("[Err] InfoGetMsk no=%x\n", no);

	return 0;
}
