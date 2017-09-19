@******************************************************************************
@ File：crt0.S
@ date: 2017.9.16 by xsyin
@******************************************************************************       

.text
.global _start
_start:
	ldr r0,=0x53000000       @WATCHDOG register
	mov r1,#0x0  
	str r1,[r0]              @no WATCHDOG
	ldr sp,=1024*4
	bl main
halt_loop:
	b halt_loop
