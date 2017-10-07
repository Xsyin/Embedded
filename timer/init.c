//******************************************************************************
// File：init.c
// date: 2017.10.5 by xsyin
//******************************************************************************

#include "s3c2440.h"

#define S3C2440_MPLL_200MHZ    ((0x5c<<12)|(0x01<<4)|(0x02))
#define GPF4_out               (1<<(4*2))
#define GPF5_out               (1<<(5*2))
#define GPF6_out               (1<<(6*2))


void disable_watchdog();
void clock_init();
void memsetup();
void copy_steppingstone_to_sdram();
void init_led();
void timer0_init();
void init_irq();

void disable_watchdog()
{
	WTCON = 0;
}


void clock_init()
{
	CLKDIVN = 0x03;        //FCLK:HCLK:PCLK=1:2:4, HDIVN=1,PDIVN=1

	//HDIVN != 0, Change CPU bus mode from "fast bus mode" to "asynchronous bus mode"
__asm__(
	"mrc p15, 0, r1, c1, c0, 0\n"    //read controll register
	"orr r1, r1, #0xc0000000\n"      //set
	"mcr p15, 0, r1, c1, c0, 0\n"    //write
	);
	
	MPLLCON = S3C2440_MPLL_200MHZ;   //now, FCLK=200MHZ, HCLK=100MHZ, PCLK=50MHZ
}

void memsetup()
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
	//p[9] = 0x008C04F4;   //REFRESH   HCLK = 100MHZ
	p[9] = 0x008C07A3;     //HCLK = 12MHZ
	p[10] = 0x000000B1;  //BANKSIZE
	p[11] = 0x00000030;  //MRSRB6
	p[12] = 0x00000030;  //MRSRB7
}

void copy_steppingstone_to_sdram()
{
	unsigned int *pdwsrc = (unsigned int *)0;
	unsigned int *pdwdest = (unsigned int *)SDRAM_BASE;

	while(pdwsrc<(unsigned int *)4096)
	{
		*pdwdest = *pdwsrc;
		pdwsrc++;
		pdwdest++;
	}

}

void init_led()
{
	GPFCON = GPF4_out | GPF5_out | GPF6_out;
}

void timer0_init()
{
	TCFG0 = 99;       //Prescaler 0 = 99
	TCFG1 = 0x03;     //select 1/16 divider signal
	TCNTB0 = 31250;   //0.5S every interrupt
	TCON |=(1<<1);    //refersh
	TCON = 0x09;      //TCON[3] = auto reload TCON[0]= start timer0
}

void init_irq()
{
	INTMSK &= (~(1<<10));  //INTMSK[10]=INT_TIMER0, 0=service available
}
