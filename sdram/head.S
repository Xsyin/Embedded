@******************************************************************************
@ File：head.S
@ date: 2017.9.16 by xsyin
@******************************************************************************       

.equ MEM_CTL_BASE, 0x48000000
.equ SDRAM_BASE, 0x30000000

.text
.global _start
_start:
	bl disable_watch_dog
	bl memsetup
	bl copy_steppingstone_to_sdram
	ldr pc,=on_sdram
on_sdram:
	ldr sp,=0x34000000
	bl main
halt_loop:
	b halt_loop

disable_watch_dog:
	mov r1,#0x53000000       @WATCHDOG regisiter
	mov r2,#0x0 
	str r2,[r1]
	mov pc,lr 

copy_steppingstone_to_sdram:
	mov r1,#0
	ldr r2,=SDRAM_BASE
	mov r3,#1024*4
1:
	ldr r4,[r1],#4      @read 4 byte, then r1 += 4
	str r4,[r2],#4      @store 4 byte, then r2 += 4
	cmp r1,r3
	bne 1b              @'b': find the 1 before
	mov pc,lr          @return

memsetup:
	mov r1, #MEM_CTL_BASE
	adrl r2, mem_cfg_val
	add r3, r1, #13*4
1:
	ldr r4,[r2],#4
	str r4,[r1],#4
	cmp r1,r3
	bne 1b
	mov pc,lr

.align 4
mem_cfg_val:
	.long 0x22011110    @BWSCON
	.long 0x00000700    @BANKCON0
	.long 0x00000700    @BANKCON1
	.long 0x00000700    @BANKCON2
	.long 0x00000700    @BANKCON3
	.long 0x00000700    @BANKCON4
	.long 0x00000700    @BANKCON5
	.long 0x00018005    @BANKCON6
	.long 0x00018005    @BANKCON7
	.long 0x008C07A3    @REFRESH
	.long 0x000000B1    @BANKSIZE
	.long 0x00000030    @MRSRB6
	.long 0x00000030    @MRSRB7




