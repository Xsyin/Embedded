//******************************************************************************
// File：interrupt.c
// date: 2017.10.6 by xsyin
//******************************************************************************

#include "s3c2440.h"

void timer0_handle()
{
	if(INTOFFSET == 10)
		GPFDAT = ~(GPFDAT & (0x07<<4));

	//clear interrupt
	SRCPND = 1 << INTOFFSET;
	INTPND = INTPND;
}
