//******************************************************************************
// File：init.c
// date: 2017.10.1 by xsyin
//******************************************************************************

#include "s3c2440.h"

#define GPF0_eint  (0x2<<(0*2))
#define GPF2_eint  (0x2<<(2*2))
#define GPG3_eint  (0x2<<(3*2))

#define GPF0_mask  (3<<(0*2))
#define GPF2_mask  (3<<(2*2))
#define GPG3_mask  (3<<(3*2))

#define GPF4_out   (1<<(4*2))
#define GPF5_out   (1<<(5*2))
#define GPF6_out   (1<<(6*2))

#define GPF4_mask  (3<<(4*2))
#define GPF5_mask  (3<<(5*2))
#define GPF6_mask  (3<<(6*2))

void disable_watchdog()
{
	WTCON = 0;
}

void init_led()
{

	//LED1,LED2,LED3 out
	GPFCON &= ~(GPF4_mask | GPF5_mask | GPF6_mask);
	GPFCON |= (GPF4_out | GPF5_out | GPF6_out);

}

void init_irq()
{
	//K1,K2 in
	GPFCON &= ~(GPF0_mask | GPF2_mask);
	GPFCON |= (GPF0_eint | GPF2_eint);     //interrupt EINT0, EINT2

	GPGCON &= ~GPG3_mask;
	GPGCON |= GPG3_eint;                  //interrupt EINT11

	//set EINTMASK for EINT11
	EINTMASK &= ~(1<<11);

	/* PRIORITY[0] = ARB_MODE0=0, priority does not rotate
	   PRIORITY[8:7] = ARB_SEL0=0, REQ 1-2-3-4, EINT0 = REQ1, EINT2 = REQ3
	   EINT0 > EINT2 > EINT11
	*/
	PRIORITY = (PRIORITY &((~0x01) | (0x3<<7))) | (0x0 << 7);

	//enable EINT0, EINT2, EINT8_23
	INTMSK &= (~(1<<0))& (~(1<<2)) & (~(1<<5));
}
