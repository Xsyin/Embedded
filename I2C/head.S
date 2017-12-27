
.extern main
.text
.global _start
_start:
	b Reset

@ 0x04
HandleUndef:
	b HandleUndef
@ 0x08
HandleSWI:
	b HandleSWI
@ 0x0c
HandlePrefetchAbort:
	b HandlePrefetchAbort
@ 0x10
HandleDataAbort:
	b HandleDataAbort
@ 0x14
HandleNotUsed:
	b HandleNotUsed
@ 0x18
	b HandleIRQ
@ 0x1c
HandleFIQ:
	b HandleFIQ

Reset:
	ldr sp, =4096
	bl disable_watch_dog
	bl clock_init
	bl memsetup
	bl nand_init

	ldr r0, =0x30000000
	mov r1, #4096
	mov r2, #16*1024
	bl copy_code_to_sdram

	bl clean_bss

/* CPSR:   
*     |N|Z|C|V|...|I|F|T|M|M|M|M|M|
*    I--- 1:IRQ disable   0: IRQ enable
*    F--- 1: FIQ disable  0: FIQ enable
*    T--- 1:Thumb         0: ARM
*    M[4:0]  : 0b10000    user mode
*            : 0b10001    FIQ mode 
*            : 0b10010    IRQ mode
*            : 0b10011    SVC mode
*            : 0b10111    Abort mode
*            : 0b11011    Undefined mode
*            : 0b11111    System mode
*/
	msr cpsr_c, #0xd2   @ IRQ mode
	ldr sp, =0x31000000

	msr cpsr_c, #0xdf   @ System mode
	ldr sp, =0x34000000

	ldr lr, =ret_initirq
	ldr pc, =init_irq
ret_initirq:
	msr cpsr_c, #0x5f   @enable IRQ
	ldr lr, =halt_loop
	ldr pc, =main
halt_loop:
	b halt_loop

HandleIRQ:
	sub lr, lr, #4
	stmdb sp!, {r0-r12,lr}

	ldr lr, =int_return
	ldr pc, =IRQ_Handle
int_return:
	ldmia sp!, {r0-r12,pc}^
