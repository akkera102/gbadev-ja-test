/**************************************/
#include "AsmMacros.h"
/**************************************/
#include "ulc_Specs.h"
/**************************************/

ASM_DATA_GLOBAL(ulc_Log2Table)
ASM_DATA_BEG   (ulc_Log2Table, ASM_SECTION_RODATA;ASM_ALIGN(1))

@ Integer Log2[x], for x=2^n
@ Use as: ulc_Log2Table[0x077CB531 * x >> (32-5)]

ulc_Log2Table:
	.byte  0, 1,28, 2,29,14,24,3
	.byte 30,22,20,15,25,17, 4,8
	.byte 31,27,13,23,21,19,16,7
	.byte 26,12,18, 6,11, 5,10,9

ASM_DATA_END(ulc_Log2Table)

/**************************************/
//! EOF
/**************************************/
