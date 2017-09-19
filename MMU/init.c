//******************************************************************************
// File：init.c
// date: 2017.9.17 by xsyin
//******************************************************************************       

#define WTCON (*(volatile unsigned long *)0x53000000)
#define MEM_CTL_BASE 0x48000000

void disable_watchdog(void)
{
	WTCON = 0;
}

void memsetup(void)
{
	unsigned long const mem_cfg_val[] = {
			0x22011110,    //BWSCON
			0x00000700,    //BANKCON0
			0x00000700,    //BANKCON1
			0x00000700,    //BANKCON2
			0x00000700,    //BANKCON3
			0x00000700,    //BANKCON4
			0x00000700,    //BANKCON5
			0x00018005,    //BANKCON6
			0x00018005,    //BANKCON7
			0x008C07A3,    //REFRESH
			0x000000B1,    //BANKSIZE
			0x00000030,    //MRSRB6
			0x00000030     //MRSRB7  
	};
	volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;
	int i = 0;
	for (; i < 13; ++i)
	{
		p[i] = mem_cfg_val[i];
	}

}

void copy_2th_to_sdram(void)
{
	unsigned long *srcPtr = (unsigned long *)2048;
	unsigned long *destPtr = (unsigned long *)0x30004000;
	while(srcPtr < (unsigned long *)4096)
	{
		*destPtr = *srcPtr;
		srcPtr++;
		destPtr++;
	}
}

void create_page_table(void)
{
	#define MMU_FULL_ACCESS (3<<10)   /*full access*/
	#define MMU_DOMAIN      (0<<5)
	#define MMU_SPECIAL     (1<<4)
	#define MMU_CACHEABLE   (1<<3)
	#define MMU_BUFFABLE    (1<<2)
	#define MMU_SECTION     (2)      /* it's a segment */
	#define MMU_SECDESC     (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL | MMU_SECTION)
	#define MMU_SECDESC_CB  (MMU_FULL_ACCESS | MMU_DOMAIN | MMU_SPECIAL |\
							 MMU_CACHEABLE | MMU_BUFFABLE | MMU_SECTION)
	#define MMU_SECTION_SIZE 0x00100000  //1 MB 

	unsigned long virtualaddr, physicaladdr ;
	unsigned long *tlb_base = (unsigned long *)0x30000000;

    //0~1M mapped to 4KB Steppingstone 
	virtualaddr = 0;
	physicaladdr = 0;
	*(tlb_base + (virtualaddr>>20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC_CB;

    //GPIO start at 0x56000000, GPFCON = 0x56000050, GPFDAT = 0x56000054
    //0xA0000000~0xA0100000 mapped to 0x56000000~0x56100000
    //0xA0000050 -> 0x56000050, 0xA0000054 -> 0x56000054
    virtualaddr = 0xA0000000;
    physicaladdr = 0x56000000;
    *(tlb_base + (virtualaddr>>20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC;

    //SDRAM: 0x30000000~0x33FFFFFF, 64M
    //0xB0000000~0xB3FFFFFF mapped
    virtualaddr = 0xB0000000;
    physicaladdr = 0x30000000;
    while(virtualaddr < 0xB4000000)
    {
	    *(tlb_base + (virtualaddr>>20)) = (physicaladdr & 0xFFF00000) | MMU_SECDESC_CB;
    	virtualaddr += 0x100000;
    	physicaladdr += 0x100000;
    }
}

void mmu_init(void)
{
	unsigned long ttb = 0x30000000;
	__asm__(
		"mov r0, #0\n"
		"mcr p15, 0, r0, c7, c7, 0\n"    //disable ICache and DCache
		"mcr p15, 0, r0, c7, c10,4\n"    //drain write buffer on v4
		"mcr p15, 0, r0, c8, c7,0\n"     //disable TLB

		"mov r4, %0\n"        //r4 = translation table base
		"mcr p15, 0, r4, c2, c0, 0\n"   //set translation table base register

		"mvn r0, #0\n"
		"mcr p15, 0, r0, c3, c0, 0\n"   //Domain access  control register

		"mrc p15, 0, r0, c1, c0, 0\n"   //read control register

		//clear bits
		"bic r0, r0, #0x3000\n"
		"bic r0, r0, #0x0300\n"
		"bic r0, r0, #0x0087\n"

		//set bits
		"orr r0, r0, #0x0002\n"
		"orr r0, r0, #0x0004\n"
		"orr r0, r0, #0x1000\n"
		"orr r0, r0, #0x0001\n"

		"mcr p15, 0, r0, c1, c0, 0\n"    //write to register
		:                                //no ouput
		: "r" (ttb)                    //input
	);
}
