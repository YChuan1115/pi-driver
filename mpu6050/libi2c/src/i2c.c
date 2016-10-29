// use
#include<i2c_platform.h>

// implement
#include<i2c.h>




void i2c_init(uint8_t sda_p, uint8_t scl_p)
{
	// global variable : sda_pin and scl_pin defined in the i2c_platform.h
	I2C_START();
	SET_SDA_PIN(sda_p);
	SET_SCL_PIN(scl_p);
	//sda_pin = sda_p;
	//scl_pin = scl_p;
	SDA_AS_OUT();
	SCL_AS_OUT();
	SDA_UP();
	SCL_UP();
	usleep(10);
}


void i2c_end()
{
	I2C_STOP();
//#ifdef BCM2835_H
//	printf("S");
//	if((sda_pin == RPI_BPLUS_GPIO_J8_03) ||(scl_pin == RPI_BPLUS_GPIO_J8_03)  ){
//		printf("set back up \n");
//		bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_03, BCM2835_GPIO_FSEL_ALT0);
//	}
//
//	if((sda_pin == RPI_BPLUS_GPIO_J8_05) ||(scl_pin == RPI_BPLUS_GPIO_J8_05)  )
//		bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_05, BCM2835_GPIO_FSEL_ALT0);
//#endif 
}


int i2c_read_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len )
{
	uint8_t i;
	SDA_AS_OUT();
	SCL_AS_OUT();

	S_bit();
	send_byte( (i2c_addr << 1) | W_BIT );
	if(is_ACK() == 0) return -1;

	send_byte( reg );
	if(is_ACK() == 0) return -2;

	P_bit();
	usleep(10);
	S_bit();

	send_byte( (i2c_addr << 1) | R_BIT );
	if(is_ACK() == 0) return -3;

	len--;
	for(i = 0; i < len ; i++){
		buff[i] = read_byte();
		send_ACK();
	}

	buff[len] = read_byte();

	usleep(1);
	send_NACK();
	usleep(1);
	P_bit();
	usleep(100);
	return 0;
}




int i2c_read_data_block_with_delay(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len, int delay_us)
{
	uint8_t i;
	SDA_AS_OUT();
	SCL_AS_OUT();

	S_bit();
	send_byte( (i2c_addr << 1) | W_BIT );
	if(is_ACK() == 0) return -1;

	send_byte( reg );
	if(is_ACK() == 0) return -2;

	//P_bit();
	//usleep(100000);
	usleep(delay_us);
	S_bit();

	send_byte( (i2c_addr << 1) | R_BIT );
	if(is_ACK() == 0) return -3;

	len--;
	
	for(i = 0; i < len ; i++){
		buff[i] = read_byte();
		send_ACK();
	}

	buff[len] = read_byte();

	usleep(1);
	send_NACK();
	usleep(1);
	P_bit();
	usleep(100);
	return 0;
}




int i2c_write_data_block(uint8_t i2c_addr,uint8_t reg, uint8_t * buff, uint8_t len )
{
	uint8_t i;
	SDA_AS_OUT();
	SCL_AS_OUT();
	S_bit();

	send_byte( (i2c_addr << 1) | W_BIT );
	if(is_ACK() == 0) return -1;

	send_byte( reg );
	if(is_ACK() == 0) return -2;

	for(i = 0; i < len ; i++){
		send_byte( buff[i] );
		if(is_ACK() == 0) return -3;
	}

	usleep(1);
	P_bit();
	usleep(100);
	return 0;
}




int i2c_read_reg(uint8_t i2c_addr, uint8_t reg, uint8_t * value_ptr)
{
	return i2c_read_data_block(i2c_addr, reg, value_ptr, 1);
}




int i2c_write_reg(uint8_t i2c_addr, uint8_t reg, uint8_t value)
{
	return i2c_write_data_block(i2c_addr, reg, &value, 1);
}




// look up if the device at address of "i2c_addr" 
// return 1:  if device exist
// return 0: if device not exist
uint8_t i2c_probe(uint8_t i2c_addr)
{
	uint8_t res;
	SDA_AS_OUT();
	SCL_AS_OUT();
	S_bit();
	send_byte( (i2c_addr << 1) | R_BIT);
	res = is_ACK();
	P_bit();

	return res;
}
