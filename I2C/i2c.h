#ifndef __2410IIC_H
#define __2410IIC_H 

void i2c_init(void);
void i2c_write(unsigned int slvAddr, unsigned char *buf, int len);
void i2c_read(unsigned int slvAddr, unsigned char *buf, int len);
void I2CIntHandle(void);

#endif
