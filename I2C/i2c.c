#include <stdio.h>
#include "i2c.h"
#include "s3c2440.h"

#define WRDATA   (1)
#define RDDATA   (2)

void delay(int time);

typedef struct tI2C{
	unsigned char *pData;      /* data buffer */
	volatile int dataCount;    /* pending data length */
	volatile int status;   
	volatile int mode;         /* read or write  */
	volatile int pt;           /* pending data position */
}t_S3C2440_I2C, *ptS3C2440_I2C;

static t_S3C2440_I2C g_tS3C2440_I2C;

void i2c_init(void)
{
	GPEUP |= 0xc000;
	GPECON |= 0xa0000000;

	INTMSK &= ~(BIT_IIC);

	/* bit[7] = 1, 使能ACK
     * bit[6] = 0, IICCLK = PCLK/16
     * bit[5] = 1, 使能中断
     * bit[3:0] = 0xf, Tx clock = IICCLK/16
     * PCLK = 50MHz, IICCLK = 3.125MHz, Tx Clock = 0.195MHz
     */
    IICCON = (1<<7) | (0<<6) | (1<<5) | (0xf);  // 0xaf

    IICADD = 0x10;
    IICSTAT = 0x10;

}

void i2c_write(unsigned int slvAddr, unsigned char *buf, int len)
{
	g_tS3C2440_I2C.mode = WRDATA;
	g_tS3C2440_I2C.pt = 0;
	g_tS3C2440_I2C.pData = buf;
	g_tS3C2440_I2C.dataCount = len;

	IICDS = slvAddr;
	IICSTAT = 0xf0;

	while(g_tS3C2440_I2C.dataCount != -1);
}

void i2c_read(unsigned int slvAddr, unsigned char *buf, int len)
{
	g_tS3C2440_I2C.mode = RDDATA;
	g_tS3C2440_I2C.pt = -1;
	g_tS3C2440_I2C.pData = buf;
	g_tS3C2440_I2C.dataCount = len;

	IICDS = slvAddr;
	IICSTAT = 0xb0;

	while(g_tS3C2440_I2C.dataCount != -1);
}

void I2CIntHandle(void)
{
	unsigned int iicSt, i;

	SRCPND = BIT_IIC;
	INTPND = BIT_IIC;

	iicSt = IICSTAT;

	if(iicSt & 0x8){printf("Bus arbitration failed\n\r");}

	switch(g_tS3C2440_I2C.mode)
	{
		case WRDATA:
		{
			if((g_tS3C2440_I2C.dataCount--) == 0)
			{
				IICSTAT = 0xd0;
				IICCON = 0xaf;
				delay(10000);
				break;
			}

			IICDS = g_tS3C2440_I2C.pData[g_tS3C2440_I2C.pt++];

			for(i = 0; i < 10; i++);

			IICCON = 0xaf;
			break;
		}

		case RDDATA:
		{
			if(g_tS3C2440_I2C.pt == -1)
			{
				g_tS3C2440_I2C.pt = 0;
				if(g_tS3C2440_I2C.dataCount == 1)
					IICCON = 0x2f;
				else
					IICCON = 0xaf;
				break;
			}

			g_tS3C2440_I2C.pData[g_tS3C2440_I2C.pt++] = IICDS;

			if(g_tS3C2440_I2C.dataCount == 0)
				IICCON = 0x2f;
			else
				IICCON = 0xaf;
			break;
		}
		default:
			break;
	}
}

void delay(int time)
{
	for(; time > 0; time--);
}
