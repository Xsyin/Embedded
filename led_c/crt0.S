.text
.global _start
_start:
	ldr r0,=0x53000000      @WATCHDOG rigister
	mov r1,#0x0            
	str r1,[r0]             @write 0,no WATCHDOG
	ldr sp,=1024*4          @stack ptr
	bl main                 @call c 
halt_loop:
	b halt_loop
