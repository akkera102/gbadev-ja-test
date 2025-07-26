/**************************************/
#include "AsmMacros.h"
/**************************************/
#include "ulc_Specs.h"
/**************************************/

ASM_DATA_GLOBAL(Fourier_CosSin)
ASM_DATA_BEG   (Fourier_CosSin, ASM_SECTION_RODATA;ASM_ALIGN(4))

Fourier_CosSin:
.if ULC_USE_QUADRATURE_OSC
	@ Quadrature oscillator terms (.16fxp)
	@ struct { u32 cos:20, sin:12; } = {.cos=Floor[2^16*Cos[(0+0.5)*Pi/2/N]], .sin=Floor[2^16*Sin[(0+0.5)*Pi/2/N]]}
	@ The oscillator frequency's value is constant up to
	@ scaling and is ommitted here; it is instead hardcoded.
	@ The value is Tan[Pi/2/N] ~= Pi/2/N (for large N)
	@ We use two approximations in the code:
	@  Tan[Pi/2/N] ~= (1+2^-4)(1-2^-2)/(N/2)
	@  Tan[Pi/2/N] ~= (1+2^-1)(1+2^-4)/N
	@ These values are mathematically equivalent, but differ
	@ in their rounding behaviour, allowing us to fine-tune
	@ the response of the oscillator.
	.word 0xC8F0FFB1 @ N=16
	.word 0x6480FFEC @ N=32
	.word 0x3240FFFB @ N=64
	.word 0x1920FFFE @ N=128
	.word 0x0C90FFFF @ N=256
	.word 0x0640FFFF @ N=512
	.word 0x0320FFFF @ N=1024
	.word 0x0190FFFF @ N=2048
.else
	@ Quarter sine table, shifted by a half sample, and interleaved as {Cos,Sin}
	@  CosSinTable[N_] := Table[{Cos[(n+0.5)*Pi/2 / N], Sin[(n+0.5)*Pi/2 / N]}, {n,0,N/2-1}]
	@  Table[CosSinTable[2^k], {k,4,11}]
	@ Used for IMDCT window and DCT-IV routines
	@ Note that this always includes windows for up to N=2048.
	.incbin "source/ulc/Fourier_CosSin16.bin" @ 16bit coefficients
.endif

ASM_DATA_END(Fourier_CosSin)

/**************************************/
//! EOF
/**************************************/
