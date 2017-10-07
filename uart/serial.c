//******************************************************************************
// File：serial.c
// date: 2017.10.7 by xsyin
//******************************************************************************

#include "serial.h"
#include "s3c2440.h"

#define TXD0READY        (1<<2)
#define RXD0READY        (1)

#define PCLK             50000000         //PCLK = 50MHZ
#define UART_CLK         PCLK
#define UART_BAUD_RATE   11520            //baud_rate = 115200
#define UART_BRD         ((UART_CLK / (UART_BAUD_RATE * 16)) - 1)

void uart0_init(void)
{
	GPHCON |= 0xa0;    //GPHCON[7:6]=RXD[0] GPHCON[5:4]=TXD[0] GPHCON[3:2]=INPUT GPHCON[1:0]=INPUT
	GPFUP = 0x0C;

	ULCON0 = 0x03;      //8-bits, one stop bit, no parity
	UCON0 = 0x05;      //interrupt request or polling mode, select PCLK
	UFCON0 = 0x00;     //NOT USE FIFO
	UMCON0 = 0x00;     //NOT USE FLOW CTL
	UBRDIV0 = UART_BRD;
}

void putc(unsigned char c)
{
	//wait until all data is transmited
	while(!(UTRSTAT0 & TXD0READY));

	UTXH0 = c;
}

unsigned char getc(void)
{
	while(!(UTRSTAT0 & RXD0READY));

	return URXH0;
}

int isDigit(unsigned char c)
{
	if(c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int isLetter(unsigned char c)
{
	if(c >= 'a' && c <= 'z')
		return 1;
	else if(c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}
