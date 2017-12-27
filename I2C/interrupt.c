#include <stdio.h>
#include "s3c2440.h"

extern void I2CIntHandle(void);

void (*isr_handle_array[50])(void);

void dummy_isr(void)
{
	printf("Dummy_isr\n\r");
	while(1);
}

void init_irq(void)
{
	int i = 0;
	for(i = 0; i < sizeof(isr_handle_array)/sizeof(isr_handle_array[0]); i++)
	{
		isr_handle_array[i] = dummy_isr;
	}

	INTMOD = 0x0;    //ALL IRQ mode
	INTMSK = BIT_ALLMSK;   

	isr_handle_array[ISR_IIC_OFT] = I2CIntHandle;
}

void IRQ_Handle(void)
{
	unsigned long oft = INTOFFSET;

	if(oft == 4)
		EINTPEND = 1<<7;
	SRCPND = 1<<oft;
	INTPND = 1<<oft;

	isr_handle_array[oft]();
}
