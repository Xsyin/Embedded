#include "s3c2440.h"
#include "serial.h"

#define TXD0READY     (1<<2)
#define RXD0READY     (1)

#define PCLK          50000000
#define UART_CLK      PCLK
#define UART_BAUD_RATE 115200
#define UART_BRD      ((UART_CLK / (UART_BAUD_RATE * 16)) - 1)

void uart0_init(void)
{
	GPHCON |= 0xa0;
	GPHUP  = 0x0c;

	ULCON0 = 0x03;
	UCON0  = 0x05;
	UFCON0 = 0x00;
	UMCON0 = 0x00;
	UBRDIV0 = UART_BRD;
}

void putc(unsigned char c)
{
	while(!(UTRSTAT0 & TXD0READY));

	UTXH0 = c;
}

unsigned char getc(void)
{
	while(!(UTRSTAT0 & RXD0READY));

	return URXH0;
}

int puts(const char *s)
{
	int i = 0;
	while(*s){
		putc(*s);
		s++;
		i++;
	}
	putc("\n");
	putc("\r");
	return i+2;
}

int putchar(int c)
{
	putc((unsigned char)c);
	return c;
}
