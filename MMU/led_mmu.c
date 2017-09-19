//******************************************************************************
// File：init.c
// date: 2017.9.18 by xsyin
//******************************************************************************       

#define GPFCON (*(volatile unsigned long *)0xA0000050)
#define GPFDAT (*(volatile unsigned long *)0xA0000054)

#define GPF4_out (1<<(4*2))
#define GPF5_out (1<<(5*2))
#define GPF6_out (1<<(6*2))

static inline void wait(unsigned long dely)
{
	for(; dely > 0; dely--);
}

int main(void)
{
	unsigned long i = 0;
	GPFCON = GPF4_out | GPF5_out | GPF6_out;
	while(1)
	{
		wait(30000);
		GPFDAT = ~(i<<4);
		if(++i==8)
			i = 0;
	}
	return 0;
}
