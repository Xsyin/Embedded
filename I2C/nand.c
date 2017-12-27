//******************************************************************************
// File：nand.c
// date: 2017.9.24 by xsyin
//******************************************************************************
#define LARGER_NAND_PAGE

#define BUSY 1
#define NAND_SECTOR_SIZE 512
#define NAND_BLOCK_MASK  (NAND_SECTOR_SIZE - 1)

#define NAND_SECTOR_SIZE_LP 2048
#define NAND_BLOCK_MASK_LP  (NAND_SECTOR_SIZE_LP - 1)

typedef unsigned int S3C2440_REG32;

typedef struct {
	S3C2440_REG32 NFCONF;
	S3C2440_REG32 NFCONT;
	S3C2440_REG32 NFCMD;
	S3C2440_REG32 NFADDR;
	S3C2440_REG32 NFDATA;
	S3C2440_REG32 NFMECCD0;
	S3C2440_REG32 NFMECCD1;
	S3C2440_REG32 NFSECCD;
	S3C2440_REG32 NFSTAT;
	S3C2440_REG32 NFESTAT0;
	S3C2440_REG32 NFESTAT1;
	S3C2440_REG32 NFMECC0;
	S3C2440_REG32 NFMECC1;
	S3C2440_REG32 NFSECC;
	S3C2440_REG32 NFSBLK;
	S3C2440_REG32 NFEBLK;
}S3C2440_NAND;

// typedef struct {
// 	void (*nand_reset)(void);
// 	void (*wait_idle)(void);
// 	void (*nand_select_chip)(void);
// 	void (*nand_deselect_chip)(void);
// 	void (*write_cmd)(int cmd);
// 	void (*write_addr)(unsigned int addr);
// 	unsigned char (*read_data)(void);
// }t_nand_chip;

static S3C2440_NAND *s3c2440nand = (S3C2440_NAND *)0x4e000000;

//static t_nand_chip nand_chip;

void nand_init(void);
void nand_read(unsigned char *buf, unsigned long start_addr, int size);

static void s3c2440_reset(void);
static void s3c2440_wait_idle(void);
static void s3c2440_select_chip(void);
static void s3c2440_deselect_chip(void);
static void s3c2440_write_cmd(int cmd);
static void s3c2440_write_addr(unsigned int addr);
static unsigned char s3c2440_read_data(void);

static void s3c2440_reset(void)
{
	s3c2440_select_chip();
	s3c2440_write_cmd(0xff);
	s3c2440_wait_idle();
	s3c2440_deselect_chip();
}

static void s3c2440_wait_idle(void)
{
	int i;
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFSTAT;
	while(!(*p & BUSY))
		for(i=0;i<10;i++);
}

static void s3c2440_select_chip(void)
{
	int i;
	s3c2440nand->NFCONT &= ~(1<<1);
	for(i=0;i<10;i++);
}

static void s3c2440_deselect_chip(void)
{
	s3c2440nand->NFCONT |= (1<<1); 
}

static void s3c2440_write_cmd(int cmd)
{
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFCMD;
	*p = cmd;
}

static void s3c2440_write_addr(unsigned int addr)
{
	int i;
	volatile unsigned char *p= (volatile unsigned char *)&s3c2440nand->NFADDR;

	*p = addr & 0xff;
	for(i=0;i<10;i++);
	*p = (addr >> 9) & 0xff;
	for(i=0;i<10;i++);
	*p = (addr >> 17) & 0xff;
	for(i=0;i<10;i++);
	*p = (addr >> 25) & 0xff;
	for(i=0;i<10;i++);
	
}

static void s3c2440_write_addr_lp(unsigned int addr)
{
	int i;
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;
	int col, row;

	col = addr & NAND_BLOCK_MASK_LP;
	row = addr / NAND_SECTOR_SIZE_LP;

	*p = col & 0xff;       /* col addr A0~A7 */
	for(i=0;i<10;i++);
	*p = (col >> 8) & 0x0f;
	for(i=0;i<10;i++);
	*p = row & 0xff;
	for(i=0;i<10;i++);
	*p = (row >> 8) & 0xff;
	for(i=0;i<10;i++);
	*p = (row >> 16) & 0x03;
	for(i=0;i<10;i++);
}

static unsigned char s3c2440_read_data(void)
{
	volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFDATA;
	return *p;
}


void nand_init(void)
{
#define TACLS 0
#define TWRPH0 3
#define TWRPH1 0
// 	nand_chip.nand_reset = s3c2440_reset;          //implement the hook
// 	nand_chip.wait_idle  = s3c2440_wait_idle;
// 	nand_chip.nand_select_chip = s3c2440_select_chip;
// 	nand_chip.nand_deselect_chip = s3c2440_deselect_chip;
// 	nand_chip.write_cmd = s3c2440_write_cmd;
// #ifdef LARGER_NAND_PAGE
// 	nand_chip.write_addr = s3c2440_write_addr_lp;
// #else
// 	nand_chip.write_addr = s3c2440_write_addr;
// #endif
// 	nand_chip.read_data = s3c2440_read_data;
	//set the time line
	s3c2440nand->NFCONF = (TACLS << 12)|(TWRPH0 << 8)|(TWRPH1 << 4);
	//enable the nandflash controll, init ECC, deselct
	s3c2440nand->NFCONT = (1 << 4)|(1 << 1)|(1 << 0);

	//nand_chip.nand_reset();
	s3c2440_reset();

}

void nand_read(unsigned char *buf, unsigned long start_addr, int size)
{
	int i, j;
#ifdef LARGER_NAND_PAGE
	if((start_addr & NAND_BLOCK_MASK_LP)||(size & NAND_BLOCK_MASK_LP))
		return;
#else
	if((start_addr & NAND_BLOCK_MASK)||(size & NAND_BLOCK_MASK))
		return;
#endif
	//nand_chip.nand_select_chip();
	s3c2440_select_chip();
	for(i=0; i<10; i++);

	for(i=start_addr; i<(start_addr + size);)
	{
		//nand_chip.write_cmd(0);
		s3c2440_write_cmd(0);
		//nand_chip.write_addr(i);
#ifdef LARGER_NAND_PAGE
		s3c2440_write_addr_lp(i);
		//nand_chip.write_cmd(0x30);
		s3c2440_write_cmd(0x30);
#else
		s3c2440_write_addr(i);
#endif
		//nand_chip.wait_idle();
		s3c2440_wait_idle();
#ifdef LARGER_NAND_PAGE
		for(j=0; j < NAND_SECTOR_SIZE_LP; j++, i++){
#else
		for(j=0; j < NAND_SECTOR_SIZE; j++, i++){
#endif
			//*buf = nand_chip.read_data();
			*buf = s3c2440_read_data();
			buf++;
		}
	}
	//nand_chip.nand_deselect_chip();
	s3c2440_deselect_chip();

	return;
}
