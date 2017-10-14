//******************************************************************************
// File：main.c
// date: 2017.10.7 by xsyin
//******************************************************************************

#include "serial.h"

int main()
{
	unsigned char c;

	uart0_init();

	while(1)
	{
		c = getc();
		if(isDigit(c) || isLetter(c))
		{
			switch(c){
				case '9':
					putc('0');
					break;
				case 'z':
					putc('a');
					break;
				case 'Z':
					putc('A');
					break;
				default:
					putc(c+1);
					break;
			}
		}
	}
	return 0;
}
