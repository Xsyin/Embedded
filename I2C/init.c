#include "s3c2440.h"

#define S3C2440_MPLL_200MHZ ((0x5c<<12)|(0x01<<4)|(0x02))


void disable_watch_dog(void);
void clock_init(void);
void memsetup(void);
int copy_code_to_sdram(unsigned char *buf, unsigned long start_addr, int size);
void clean_bss(void)

void disable_watch_dog(void)
{
	WTCON = 0;
}

void clock_init(void)
{
	//LOCKTIME = 0x00ffffff
	CLKDIVN = 0x03;         // FCLK:HCLK:PCLK=1:2:4, HDIVN=1,PDIVN=1

	__asm__(
		"mrc p15, 0, r1, c1, c0, 0\n "
		"orr r1, r1, #0xc0000000\n"
		"mcr p15, 0, r1, c1, c0, 0\n"
		);

	/*
	 * 对于MPLLCON寄存器，[19:12]为MDIV，[9:4]为PDIV，[1:0]为SDIV
	 * 有如下计算公式：
	 *  S3C2410: MPLL(FCLK) = (m * Fin)/(p * 2^s)
	 *  S3C2410: MPLL(FCLK) = (2 * m * Fin)/(p * 2^s)
	 *  其中: m = MDIV + 8, p = PDIV + 2, s = SDIV
	 * 对于本开发板，Fin = 12MHz
	 * 设置CLKDIVN，令分频比为：FCLK:HCLK:PCLK=1:2:4，
	 * FCLK=200MHz,HCLK=100MHz,PCLK=50MHz
	 */
	MPLLCON = S3C2440_MPLL_200MHZ;
}

void memsetup(void)
{
	volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;
	p[0] = 0x22011110;     //BWSCON
    p[1] = 0x00000700;     //BANKCON0
    p[2] = 0x00000700;     //BANKCON1
    p[3] = 0x00000700;     //BANKCON2
    p[4] = 0x00000700;     //BANKCON3  
    p[5] = 0x00000700;     //BANKCON4
    p[6] = 0x00000700;     //BANKCON5
    p[7] = 0x00018005;     //BANKCON6
    p[8] = 0x00018005;     //BANKCON7
    
                                            /* REFRESH,
                                             * HCLK=12MHz:  0x008C07A3,
                                             * HCLK=100MHz: 0x008C04F4
                                             */ 
    p[9]  = 0x008C04F4;
    p[10] = 0x000000B1;     //BANKSIZE
    p[11] = 0x00000030;     //MRSRB6
    p[12] = 0x00000030;     //MRSRB7
}

void clean_bss(void)
{
	extern int __bss_start, __bss_end;
	int *p = &__bss_start;
	for(; p < &__bss_end; p++)
		*p = 0;
}
int copy_code_to_sdram(unsigned char *buf, unsigned long start_addr, int size)
{
	extern nand_write(unsigned char *buf, unsigned long start_addr, int size);
	nand_write(buf, start_addr, size);
	return 0;
}
