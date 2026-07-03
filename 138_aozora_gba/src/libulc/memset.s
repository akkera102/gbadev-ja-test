/************************************************/

@ r0: &Dst
@ r1:  Val (only lower 8bits used)
@ r2:  Cnt

.arm
.section .iwram, "ax", %progbits
.balign 4

memset:
	MOV	ip, r0             @ Dst -> ip (r0=Dst must be preserved)
	AND	r1, r1, #0xFF      @ Broadcast 8bit fill value
	ORR	r1, r1, r1, lsl #0x08
	ORR	r1, r1, r1, lsl #0x10

.LSetHead:
	TST	ip, #0x03          @ Word aligned?
	BEQ	.LSetBody
1:	MOVS	r3, ip, lsr #0x01  @ Check 2-byte align [C=1]
	CMPCS	r2, #0x01          @ Check count
	STRCSB	r1, [ip], #0x01    @  Align
	SUBCS	r2, r2, #0x01      @  Count down
2:	MOVS	r3, ip, lsr #0x02  @ Check 4-byte align [C=1]
	CMPCS	r2, #0x02          @ Check count
	STRCSH	r1, [ip], #0x02    @  Align
	SUBCS	r2, r2, #0x02      @  Count down
3:	CMP	r2, #0x01          @ Check count
	STREQB	r1, [ip]           @  Set tail
	BXLS	lr

.LSetBody:
	STMFD	sp!, {r4-r8,lr}
	MOV	r3, r1             @ Broadcast to all fill registers
	MOV	r4, r1
	MOV	r5, r1
	MOV	r6, r1
	MOV	r7, r1
	MOV	r8, r1
	MOV	lr, r1
1:	SUBS	r2, r2, #0x40
	STMCSIA	ip!, {r1,r3-r8,lr} @ Set 64-byte blocks
	STMCSIA	ip!, {r1,r3-r8,lr}
	BHI	1b
	BEQ	.LExit             @ Early exit when nothing left

.LSetTail:
	MOVS	r2, r2, lsl #0x1B  @ Set 32-byte, 16-byte
	STMCSIA	ip!, {r1,r3-r8,lr}
	STMMIIA	ip!, {r1,r3-r5}
	MOVS	r2, r2, lsl #0x02  @ Set 8-byte, 4-byte
	STMCSIA	ip!, {r1,r3}
	STRMI	r1, [ip], #0x04
	MOVS	r2, r2, lsl #0x02  @ Set 2-byte, 1-byte
	STRCSH	r1, [ip], #0x02
	STRMIB	r1, [ip], #0x01

.LExit:
	LDMFD	sp!, {r4-r8,lr}
	BX	lr

.type   memset, %function
.size   memset, .-memset
.global memset

/************************************************/
//! EOF
/************************************************/
