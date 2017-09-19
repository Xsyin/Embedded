@******************************************************************************
@ File：head.S
@ date: 2017.9.17 by xsyin
@******************************************************************************       

.text
.global _start
_start:
	ldr sp,=4096        @the top of 4KB SRAM
	bl disable_watchdog
	bl memsetup
	bl copy_2th_to_sdram
	bl create_page_table
	bl mmu_init         @start mmu 
	ldr sp,=0xB4000000  @the top of SDRAM (use virtual addr)
	ldr pc,=0xB0004000  @the start of second part code
halt_loop:
	b halt_loop
	