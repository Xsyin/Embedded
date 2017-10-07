//******************************************************************************
// File：serial.h
// date: 2017.10.7 by xsyin
//******************************************************************************

void uart0_init(void);
void putc(unsigned char c);
unsigned char getc(void);
int isDigit(unsigned char c);
int isLetter(unsigned char c);
