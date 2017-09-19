.text
.global _start
_start:
	LDR R0,=0x56000050        @R0 = GPBCON
	MOV R1, #0x00000100       @R1 = 1 << (4 * 2)
	STR R1,[R0]               @GPB6 = OUTPUT
	LDR R0,=0x56000054        @R0 = GPBDAT
	MOV R1, #0x00000000         @
	STR R1,[R0]               @GPB6_OUT = 0, LED2 on
MAIN_LOOP:
	B MAIN_LOOP