/**************************************/
.section .iwram, "ax", %progbits
.balign 4
/**************************************/

@ r0: Num
@ r1: Den

.arm
__aeabi_uidivmod:
__aeabi_uidiv:
	MOVS	r2, r1 @ Div==0 check (Den -> r2)
	MOVEQ	r0, #0xFFFFFFFF
	MOVNES	r1, r0 @ Num==0 check (Num -> r1)
	@MOVEQ	r1, #0x00
	BXEQ	lr
1:	ADR	r3, 4f              @ Get highest shift such that (Den<<n) < Rem [3 opcodes, 32bit opcodes]
	MOV	r0, r1, lsr #0x04   @ Only goes down to 4 as a tradeoff to save cycles
	CMP	r2, r0, lsr #0x0C   @ Because the Rem >= (Den<<n) check might overflow,
	SUBLS	r3, r3, #0x10 * 3*4 @ we instead use Den <= (Rem>>n) for the comparison
	MOVLS	r0, r0, lsr #0x10
	CMP	r2, r0, lsr #0x04
	SUBLS	r3, r3, #0x08 * 3*4
	MOVLS	r0, r0, lsr #0x08
	CMP	r2, r0, lsr #0x00
	SUBLS	r3, r3, #0x04 * 3*4
	@MOVLS	r0, r0, lsr #0x04
	MOV	r0, #0x00 @ Quot=0
	MOV	pc, r3
.irp x, 31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
\x:	CMP	r2, r1, lsr #\x
	SUBLS	r1, r1, r2, lsl #\x
	ADDLS	r0, r0, #0x01 << \x
.endr
	BX	lr

/**************************************/
.size   __aeabi_uidivmod, .-__aeabi_uidivmod
.global __aeabi_uidivmod, __aeabi_uidiv
/**************************************/
/* EOF                                */
/**************************************/
