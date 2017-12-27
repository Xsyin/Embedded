#include "s3c2440.h"
#include "serial.h"

#define TXD0READY    (1 << 2)
#define RXD0READY 	 (1)

void init_uart(void)
{
	GPHCON |= 0xa0;
	GPHUP = 0x0c;

	ULCON0 = 0x03;
	UCON0 = 0x05;
	UFCON0 = 0x00;
	UMCON0 = 0x00;
	UBRDIV0 = 12;  
}

void putc(unsigned char c)
{
	while(!(UTRSTAT0 & TXD0READY));
	UTXH0 = c;
}

unsigned char getc(void)
{
#ifdef SERIAL_ECHO
	unsigned char ret;
#endif
	while(!(UTRSTAT0 & RXD0READY));
	ret = URXH0;
#ifdef SERIAL_ECHO
	if(ret == 0x0d || ret == 0x0a)
	{
		putc(0x0d);
		putc(0x0a);
	}else{
		putc(ret);
	}
#endif
	return ret;
}
