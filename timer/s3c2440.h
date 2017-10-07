//******************************************************************************
// File：s3c2440.h
// date: 2017.10.5 by xsyin
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
#define GPFCON             (*(volatile unsigned long *)0x56000050)
#define GPFDAT             (*(volatile unsigned long *)0x56000054)
#define GPFUP              (*(volatile unsigned long *)0x56000058)

#define GPGCON             (*(volatile unsigned long *)0x56000060)
#define GPGDAT             (*(volatile unsigned long *)0x56000064)
#define GPGUP              (*(volatile unsigned long *)0x56000068)

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

