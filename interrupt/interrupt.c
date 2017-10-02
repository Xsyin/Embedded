//******************************************************************************
// File：interrupt.c
// date: 2017.10.1 by xsyin
//******************************************************************************

#include "s3c2440.h"

void IRQ_ISR()
{
	unsigned long irq_num = INTOFFSET;

	switch(irq_num)
	{
		//K1 press down
		case 0:
		{
			GPFDAT |= (0x7<<4);    //all led off
			GPFDAT &= ~(1<<4);     //LIGHT LED1
			break;
		}

		//K2 press down
		case 2:
		{
			GPFDAT |= (0x7<<4);    //ALL LED OFF
			GPFDAT &= ~(1<<5);     //LIGHT LED2
			break;
		}

		//K3 press down
		case 5:
		{
			GPFDAT |= (0x7<<4);   //ALL LED OFF
			GPFDAT &= ~(1<<6);    //LIGHT LED3
			break;
		}

		default:
			break;
	}

	//clear interrupt
	if(irq_num == 5)
		EINTPEND = (1<<11);    //EINT8_23 = IRQ5
	SRCPND = 1 << irq_num;
	INTPND = 1 << irq_num;
}
