#ifndef _I2C_H
#define _I2C_H
#include<i2c_platform.h>


void i2c_init(uint8_t sda_p, uint8_t scl_p);
void i2c_end();
int  i2c_read_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len );
int  i2c_write_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len );
int  i2c_read_data_block_2(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len );
int  i2c_read_reg(uint8_t i2c_addr, uint8_t reg, uint8_t * value_ptr);
int  i2c_write_reg(uint8_t i2c_addr, uint8_t reg, uint8_t value);

uint8_t i2c_probe(uint8_t i2c_addr);

#endif 
