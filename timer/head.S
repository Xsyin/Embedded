@******************************************************************************
@ File：head.S
@ date: 2017.10.5 by xsyin
@******************************************************************************

.extern main
.text
.global _start
_start:
	b Reset
@0x4
HandleUndef:
	b HandleUndef
@0x8
HandleSWI:
	b HandleSWI
@0xC
HandlePrefetchAbort:
	b HandlePrefetchAbort
@0x10
HandleDataAbort:
	b HandleDataAbort
@0x14
HandleReserved:
	b HandleReserved
@0x18
	b HandleIRQ
@0x1c
HandleFIQ:
	b HandleFIQ

Reset:
	ldr sp, =4096
	bl disable_watchdog
	bl clock_init
	bl memsetup
	bl copy_steppingstone_to_sdram
	ldr pc, =on_sdram
on_sdram:
	msr cpsr_c, #0xd2           @set into IRQ mode
	ldr sp, =4096               @set sp_irq

	msr cpsr_c, #0xdf           @set into SYS mode
	ldr sp, =0x34000000         @set sp_sys

	bl init_led
	bl timer0_init
	bl init_irq
	msr cpsr_c, #0x5f           @set I-bit = 0, start interrupt

	ldr lr, =halt_loop
	ldr pc, =main

halt_loop:
	b halt_loop

HandleIRQ:
	sub lr, lr, #4
	stmdb sp!, {r0-r12,lr}
	ldr lr, =int_return
	ldr pc, =timer0_handle
int_return:
	ldmia sp!, {r0-r12, pc}^
