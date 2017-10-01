@******************************************************************************
@ File：head.S
@ date: 2017.9.24 by xsyin
@******************************************************************************

.text
.global _start
_start:
	ldr sp, =4096           @4 k SRAM
	bl disable_watchdog
	bl memsetup
	bl nand_init

	ldr r0, =0x30000000
	mov r1, #4096           @the start address of main.o
	mov r2, #2048           @the length to read
	bl nand_read

	ldr sp, =0x34000000     @the stack top
	ldr lr, =halt_loop      @return address
	ldr pc, =main           @'b' and 'bl' only can jump 32M, so use 'ldr'

halt_loop:
	b halt_loop

