//******************************************************************************
// File：init.c
// date: 2017.10.7 by xsyin
//******************************************************************************

#include "s3c2440.h"

#define S3C2440_MPLL_200MHZ  ((0X5C<<12)|(0x1<<4)|(0x2))

void disable_watchdog(void);
void clock_init(void);
void memsetup(void);
void copy_steppingstone_to_sdram(void);

void disable_watchdog(void)
{
	WTCON = 0;
}

void clock_init(void)
{
	CLKDIVN = 0x03;     //FCLK:PLCK:HCLK=1:2:4
	//SET BUS MODE
	__asm__(
		"mrc p15, 0, r1, c1, c0, 0\n"
		"orr r1, r1, #0xC0000000\n"
		"mcr p15, 0, r1, c1, c0, 0\n"
	);
	MPLLCON = S3C2440_MPLL_200MHZ;
}

void memsetup(void)
{
	volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;

	p[0] = 0x22011110;   //BWSCON
	p[1] = 0x00000700;   //BANKCON0
	p[2] = 0x00000700;   //BANKCON1
	p[3] = 0x00000700;   //BANKCON2
	p[4] = 0x00000700;   //BANKCON3
	p[5] = 0x00000700;   //BANKCON4
	p[6] = 0x00000700;   //BANKCON5
	p[7] = 0x00018005;   //BANKCON6
	p[8] = 0x00018005;   //BANKCON7
	p[9] = 0x008C04F4;   //REFRESH   HCLK = 100MHZ
	p[10] = 0x000000B1;  //BANKSIZE
	p[11] = 0x00000030;  //MRSRB6
	p[12] = 0x00000030;  //MRSRB7
}

void copy_steppingstone_to_sdram(void)
{
	unsigned int *pdwsrc = (unsigned int *)0;
	unsigned int *pdwdest = (unsigned int *)SDRAM_BASE;
	while(pdwsrc < (unsigned int *)4096)
	{
		*pdwdest = *pdwsrc;
		pdwsrc++;
		pdwdest++;
	}

}
