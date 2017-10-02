@******************************************************************************
@ File：head.S
@ date: 2017.10.1 by xsyin
@******************************************************************************

.extern main
.text 
.global _start
_start:
	b Reset
@0x04
HandleUndef:
	b HandleUndef
@0x08
HandleSWI:
	b HandleSWI
@0x0c
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

	msr cpsr_c, #0xd2      @IRQ mode
	ldr sp, =3072          @set stack ptr sp_irq

	msr cpsr_c, #0xd3      @system mode
	ldr sp, =4096          @set sp_sys

	bl init_led
	bl init_irq
	msr cpsr_c, #0x5f     @set I-bit=0, enable IRQ interrupt

	ldr lr, =halt_loop    @return address
	ldr pc, =main         @call main

halt_loop:
	b halt_loop

HandleIRQ:
	sub lr, lr, #4       @return address
	stmdb sp!, {r0-r12,lr}   @save the register used
	ldr lr, =int_return      @set IRQ ISR return address
	ldr pc, =IRQ_ISR         @call ISR in interrupt.c 
int_return:
	ldmia sp!, {r0-r12,pc}^
	



