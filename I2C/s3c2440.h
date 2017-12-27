//******************************************************************************
// File：s3c2440.h
// date: 2017.10.7 by xsyin
//******************************************************************************

//WATCH DOG register
#define WTCON              (*(volatile unsigned long *)0x53000000)

//SDRAM register
#define MEM_CTL_BASE       0x48000000
#define SDRAM_BASE         0x30000000

//NAND Flash register
#define NFCONF             (*(volatile unsigned long *)0x4E000000)
#define NFCONT             (*(volatile unsigned long *)0x4E000004)
#define NFCMD              (*(volatile unsigned long *)0x4E000008)
#define NFADDR             (*(volatile unsigned long *)0x4E00000C)
#define NFDATA             (*(volatile unsigned long *)0x4E000010)
#define NFSTAT             (*(volatile unsigned long *)0x4E000020)

//GPIO register
#define GPACON              (*(volatile unsigned long *)0x56000000)
#define GPADAT              (*(volatile unsigned long *)0x56000004)

#define GPBCON              (*(volatile unsigned long *)0x56000010)
#define GPBDAT              (*(volatile unsigned long *)0x56000014)
#define GPBUP               (*(volatile unsigned long *)0x56000018)

#define GPCCON              (*(volatile unsigned long *)0x56000020)
#define GPCDAT              (*(volatile unsigned long *)0x56000024)
#define GPCUP               (*(volatile unsigned long *)0x56000028)

#define GPDCON              (*(volatile unsigned long *)0x56000030)
#define GPDDAT              (*(volatile unsigned long *)0x56000034)
#define GPDUP               (*(volatile unsigned long *)0x56000038)

#define GPECON    			(*(volatile unsigned long *)0x56000040)
#define GPEDAT    		    (*(volatile unsigned long *)0x56000044)
#define GPEUP     			(*(volatile unsigned long *)0x56000048)

#define GPFCON             (*(volatile unsigned long *)0x56000050)
#define GPFDAT             (*(volatile unsigned long *)0x56000054)
#define GPFUP              (*(volatile unsigned long *)0x56000058)

#define GPGCON             (*(volatile unsigned long *)0x56000060)
#define GPGDAT             (*(volatile unsigned long *)0x56000064)
#define GPGUP              (*(volatile unsigned long *)0x56000068)

#define GPHCON             (*(volatile unsigned long *)0x56000070)
#define GPHDAT             (*(volatile unsigned long *)0x56000074)
#define GPHUP              (*(volatile unsigned long *)0x56000078)

//interrupt register
#define SRCPND             (*(volatile unsigned long *)0x4A000000)
#define INTMOD             (*(volatile unsigned long *)0x4A000004)
#define INTMSK             (*(volatile unsigned long *)0x4A000008)
#define PRIORITY           (*(volatile unsigned long *)0x4A00000C)
#define INTPND             (*(volatile unsigned long *)0x4A000010)
#define INTOFFSET          (*(volatile unsigned long *)0x4A000014)
#define SUBSRCPND          (*(volatile unsigned long *)0x4A000018)
#define INTSUBMSK          (*(volatile unsigned long *)0x4A00001C)

//external interrupt register
#define EINTMASK           (*(volatile unsigned long *)0x560000A4)
#define EINTPEND           (*(volatile unsigned long *)0x560000A8)

//Clock & Power Management
#define LOCKTIME           (*(volatile unsigned long *)0x4C000000)
#define MPLLCON            (*(volatile unsigned long *)0x4C000004)
#define UPLLCON            (*(volatile unsigned long *)0x4C000008)
#define CLKCON             (*(volatile unsigned long *)0x4C00000C)
#define CLKSLOW            (*(volatile unsigned long *)0x4C000010)
#define CLKDIVN            (*(volatile unsigned long *)0x4C000014)

//PWM timer
#define TCFG0              (*(volatile unsigned long *)0x51000000)
#define TCFG1              (*(volatile unsigned long *)0x51000004)
#define TCON               (*(volatile unsigned long *)0x51000008)
#define TCNTB0             (*(volatile unsigned long *)0x5100000C)
#define TCMPB0             (*(volatile unsigned long *)0x51000010)
#define TCNTO0             (*(volatile unsigned long *)0x51000014)

//UART register
#define ULCON0             (*(volatile unsigned long *)0x50000000)
#define UCON0              (*(volatile unsigned long *)0x50000004)
#define UFCON0             (*(volatile unsigned long *)0x50000008)
#define UMCON0             (*(volatile unsigned long *)0x5000000C)
#define UTRSTAT0           (*(volatile unsigned long *)0x50000010)
#define UERSTAT0           (*(volatile unsigned long *)0x50000014)
#define UFSTAT0            (*(volatile unsigned long *)0x50000018)
#define UMSTAT0            (*(volatile unsigned long *)0x5000001C)
#define UTXH0              (*(volatile unsigned long *)0x50000020)
#define URXH0              (*(volatile unsigned long *)0x50000024)
#define UBRDIV0            (*(volatile unsigned long *)0x50000028)

/* I2C registers */
#define IICCON  	(*(volatile unsigned *)0x54000000) // IIC control
#define IICSTAT 	(*(volatile unsigned *)0x54000004) // IIC status
#define IICADD  	(*(volatile unsigned *)0x54000008) // IIC address
#define IICDS   	(*(volatile unsigned *)0x5400000c) // IIC data shift
#define IICLC		(*(volatile unsigned *)0x54000010)	 //IIC multi-master line control

// INTOFFSET register
#define ISR_EINT0_OFT     0
#define ISR_EINT1_OFT     1
#define ISR_EINT2_OFT     2
#define ISR_EINT3_OFT     3
#define ISR_EINT4_7_OFT   4
#define ISR_EINT8_23_OFT  5
#define ISR_NOTUSED6_OFT  6
#define ISR_BAT_FLT_OFT   7
#define ISR_TICK_OFT      8
#define ISR_WDT_OFT       9
#define ISR_TIMER0_OFT    10
#define ISR_TIMER1_OFT    11
#define ISR_TIMER2_OFT    12
#define ISR_TIMER3_OFT    13
#define ISR_TIMER4_OFT    14
#define ISR_UART2_OFT     15
#define ISR_LCD_OFT       16
#define ISR_DMA0_OFT      17
#define ISR_DMA1_OFT      18
#define ISR_DMA2_OFT      19
#define ISR_DMA3_OFT      20
#define ISR_SDI_OFT       21
#define ISR_SPI0_OFT      22
#define ISR_UART1_OFT     23
#define ISR_NOTUSED24_OFT 24
#define ISR_USBD_OFT      25
#define ISR_USBH_OFT      26
#define ISR_IIC_OFT       27
#define ISR_UART0_OFT     28
#define ISR_SPI1_OFT      29
#define ISR_RTC_OFT       30
#define ISR_ADC_OFT       31


// PENDING BIT
#define BIT_EINT0		(0x1)
#define BIT_EINT1		(0x1<<1)
#define BIT_EINT2		(0x1<<2)
#define BIT_EINT3		(0x1<<3)
#define BIT_EINT4_7		(0x1<<4)
#define BIT_EINT8_23	(0x1<<5)
#define BIT_CAM			(0x1<<6)		
#define BIT_BAT_FLT		(0x1<<7)
#define BIT_TICK		(0x1<<8)
#define BIT_WDT_AC97	(0x1<<9)
#define BIT_TIMER0		(0x1<<10)
#define BIT_TIMER1		(0x1<<11)
#define BIT_TIMER2		(0x1<<12)
#define BIT_TIMER3		(0x1<<13)
#define BIT_TIMER4		(0x1<<14)
#define BIT_UART2		(0x1<<15)
#define BIT_LCD			(0x1<<16)
#define BIT_DMA0		(0x1<<17)
#define BIT_DMA1		(0x1<<18)
#define BIT_DMA2		(0x1<<19)
#define BIT_DMA3		(0x1<<20)
#define BIT_SDI			(0x1<<21)
#define BIT_SPI0		(0x1<<22)
#define BIT_UART1		(0x1<<23)
#define BIT_NFCON		(0x1<<24)		
#define BIT_USBD		(0x1<<25)
#define BIT_USBH		(0x1<<26)
#define BIT_IIC			(0x1<<27)
#define BIT_UART0		(0x1<<28)
#define BIT_SPI1		(0x1<<29)
#define BIT_RTC			(0x1<<30)
#define BIT_ADC			(0x1<<31)
#define BIT_ALLMSK		(0xffffffff)

#define BIT_SUB_ALLMSK	(0x7fff)
#define BIT_SUB_AC97 	(0x1<<14)
#define BIT_SUB_WDT 	(0x1<<13)
#define BIT_SUB_CAM_S	(0x1<<12)		
#define BIT_SUB_CAM_C	(0x1<<11)		
#define BIT_SUB_ADC		(0x1<<10)
#define BIT_SUB_TC		(0x1<<9)
#define BIT_SUB_ERR2	(0x1<<8)
#define BIT_SUB_TXD2	(0x1<<7)
#define BIT_SUB_RXD2	(0x1<<6)
#define BIT_SUB_ERR1	(0x1<<5)
#define BIT_SUB_TXD1	(0x1<<4)
#define BIT_SUB_RXD1	(0x1<<3)
#define BIT_SUB_ERR0	(0x1<<2)
#define BIT_SUB_TXD0	(0x1<<1)
#define BIT_SUB_RXD0	(0x1<<0)
