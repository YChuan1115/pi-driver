#define I2C_PLATFORM_C

// use
#include<unistd.h>
#include<stdint.h>

// use: platform depending 
#include<bcm2835.h>

// implement 
#include<i2c_platform.h>


void write_bit(uint8_t bit)
{
	if(bit)
		SDA_UP();
	else
		SDA_DOWN();
	usleep(1);
	SCL_UP();
	usleep(1);
	SCL_DOWN();
	usleep(1);
	
}




uint8_t read_bit()
{
	uint8_t res;

	usleep(1);
	SCL_UP();
	usleep(1);
	res = SDA_READ_IN();
	SCL_DOWN();
	//SDA_AS_OUT();
	
	return res;
}




void send_byte(uint8_t byte)
{
	SCL_AS_OUT();
	SDA_AS_OUT();

	//SCL_DOWN();

	//SDA_UP();
	usleep(1);
	write_bit( ((struct B8*)(&byte))->b7 );
	write_bit( ((struct B8*)(&byte))->b6 );
	write_bit( ((struct B8*)(&byte))->b5 );
	write_bit( ((struct B8*)(&byte))->b4 );
	write_bit( ((struct B8*)(&byte))->b3 );
	write_bit( ((struct B8*)(&byte))->b2 );
	write_bit( ((struct B8*)(&byte))->b1 );
	write_bit( ((struct B8*)(&byte))->b0 );
	SDA_UP();

}




uint8_t read_byte()
{
	uint8_t byte;
	SCL_DOWN();
	SDA_UP();
	SDA_AS_IN();
	SDA_IN_PULL_HIGH();
	((struct B8 *)(&byte))->b7 = read_bit();
	((struct B8 *)(&byte))->b6 = read_bit();
	((struct B8 *)(&byte))->b5 = read_bit();
	((struct B8 *)(&byte))->b4 = read_bit();
	((struct B8 *)(&byte))->b3 = read_bit();
	((struct B8 *)(&byte))->b2 = read_bit();
	((struct B8 *)(&byte))->b1 = read_bit();
	((struct B8 *)(&byte))->b0 = read_bit();
	SDA_AS_OUT();
	return byte;
}




void S_bit()
{
	SDA_UP();
	SCL_UP();
	usleep(10);
	SDA_DOWN();
	usleep(1);
	SCL_DOWN();
	usleep(1);
}




void P_bit()
{
	SDA_AS_OUT();
	SDA_DOWN();
	SCL_DOWN();
	usleep(1);
	SCL_UP();
	usleep(1);
	SDA_UP();
	usleep(1);
}




int is_ACK()
{
	int res;
	SDA_UP();
	SDA_AS_IN();
	SDA_IN_PULL_HIGH();
	usleep(10);
	SCL_UP();
	usleep(10);
	res = SDA_READ_IN();
	SCL_DOWN();
	usleep(1);
	SDA_AS_OUT();
	SDA_UP();
	if(res == 0) 
		return 1;
	return 0;
}



int send_ACK()
{
	SDA_AS_OUT();
	SDA_DOWN();
	usleep(1);
	SCL_UP();
	usleep(1);
	SCL_DOWN();
	SDA_UP();
	SDA_AS_IN();
	usleep(1);
	return 0;
}




send_NACK()
{
	SDA_AS_OUT();
	SDA_UP();
	SCL_UP();
	usleep(1);
	SCL_DOWN();
	usleep(1);
	SDA_UP();
	usleep(1);
	SDA_AS_IN();

	return 0;
}


void SET_SDA_PIN(uint8_t pin)
{
	switch (pin) {
		case 3:  pin = RPI_BPLUS_GPIO_J8_03;break;
		case 5:  pin = RPI_BPLUS_GPIO_J8_05;break;
		case 7:  pin = RPI_BPLUS_GPIO_J8_07;break;
		case 8:  pin = RPI_BPLUS_GPIO_J8_08;break;
		case 10: pin = RPI_BPLUS_GPIO_J8_10;break;
		case 11: pin = RPI_BPLUS_GPIO_J8_11;break;
		case 12: pin = RPI_BPLUS_GPIO_J8_12;break;
		case 13: pin = RPI_BPLUS_GPIO_J8_13;break;
		case 15: pin = RPI_BPLUS_GPIO_J8_15;break;
		case 16: pin = RPI_BPLUS_GPIO_J8_16;break;
		case 18: pin = RPI_BPLUS_GPIO_J8_18;break;
		case 19: pin = RPI_BPLUS_GPIO_J8_19;break;
		case 21: pin = RPI_BPLUS_GPIO_J8_21;break;
		case 22: pin = RPI_BPLUS_GPIO_J8_22;break;
		case 23: pin = RPI_BPLUS_GPIO_J8_23;break;
		case 24: pin = RPI_BPLUS_GPIO_J8_24;break;
		case 26: pin = RPI_BPLUS_GPIO_J8_26;break;
		case 29: pin = RPI_BPLUS_GPIO_J8_29;break;
		case 31: pin = RPI_BPLUS_GPIO_J8_31;break;
		case 32: pin = RPI_BPLUS_GPIO_J8_32;break;
		case 33: pin = RPI_BPLUS_GPIO_J8_33;break;
		case 35: pin = RPI_BPLUS_GPIO_J8_35;break;
		case 36: pin = RPI_BPLUS_GPIO_J8_36;break;
		case 37: pin = RPI_BPLUS_GPIO_J8_37;break;
		case 38: pin = RPI_BPLUS_GPIO_J8_38;break;
		case 40: pin = RPI_BPLUS_GPIO_J8_40;break;
		default: pin = 0;break;
	}
	sda_pin = pin;
}

void SET_SCL_PIN(uint8_t pin)
{
	switch (pin) {
		case 3:  pin = RPI_BPLUS_GPIO_J8_03;break;
		case 5:  pin = RPI_BPLUS_GPIO_J8_05;break;
		case 7:  pin = RPI_BPLUS_GPIO_J8_07;break;
		case 8:  pin = RPI_BPLUS_GPIO_J8_08;break;
		case 10: pin = RPI_BPLUS_GPIO_J8_10;break;
		case 11: pin = RPI_BPLUS_GPIO_J8_11;break;
		case 12: pin = RPI_BPLUS_GPIO_J8_12;break;
		case 13: pin = RPI_BPLUS_GPIO_J8_13;break;
		case 15: pin = RPI_BPLUS_GPIO_J8_15;break;
		case 16: pin = RPI_BPLUS_GPIO_J8_16;break;
		case 18: pin = RPI_BPLUS_GPIO_J8_18;break;
		case 19: pin = RPI_BPLUS_GPIO_J8_19;break;
		case 21: pin = RPI_BPLUS_GPIO_J8_21;break;
		case 22: pin = RPI_BPLUS_GPIO_J8_22;break;
		case 23: pin = RPI_BPLUS_GPIO_J8_23;break;
		case 24: pin = RPI_BPLUS_GPIO_J8_24;break;
		case 26: pin = RPI_BPLUS_GPIO_J8_26;break;
		case 29: pin = RPI_BPLUS_GPIO_J8_29;break;
		case 31: pin = RPI_BPLUS_GPIO_J8_31;break;
		case 32: pin = RPI_BPLUS_GPIO_J8_32;break;
		case 33: pin = RPI_BPLUS_GPIO_J8_33;break;
		case 35: pin = RPI_BPLUS_GPIO_J8_35;break;
		case 36: pin = RPI_BPLUS_GPIO_J8_36;break;
		case 37: pin = RPI_BPLUS_GPIO_J8_37;break;
		case 38: pin = RPI_BPLUS_GPIO_J8_38;break;
		case 40: pin = RPI_BPLUS_GPIO_J8_40;break;
		default: pin = 0;break;
	}
	scl_pin = pin;
}




// -- the GPIO actions used by the i2c-protocol //
//

void I2C_START()
{
	bcm2835_init();
}

void I2C_STOP()
{
	if((sda_pin == RPI_BPLUS_GPIO_J8_03) ||(scl_pin == RPI_BPLUS_GPIO_J8_03)  ){
		bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_03, BCM2835_GPIO_FSEL_ALT0);
	}
	
	if((sda_pin == RPI_BPLUS_GPIO_J8_05) ||(scl_pin == RPI_BPLUS_GPIO_J8_05)  )
		bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_05, BCM2835_GPIO_FSEL_ALT0);
}

void SDA_UP()
{
	bcm2835_gpio_write(sda_pin,HIGH);
}


void SDA_DOWN()
{
	bcm2835_gpio_write(sda_pin,LOW);
}




void SCL_UP()
{
	bcm2835_gpio_write(scl_pin,HIGH);
}


void SCL_DOWN()
{
	bcm2835_gpio_write(scl_pin,LOW);
}


void SDA_AS_OUT()
{
	bcm2835_gpio_fsel(sda_pin,BCM2835_GPIO_FSEL_OUTP);
}


void SCL_AS_OUT()
{
	bcm2835_gpio_fsel(scl_pin,BCM2835_GPIO_FSEL_OUTP);
}


void SDA_AS_IN()
{
	bcm2835_gpio_fsel(sda_pin,BCM2835_GPIO_FSEL_INPT);
}


void SCL_AS_IN()
{
	bcm2835_gpio_fsel(scl_pin,BCM2835_GPIO_FSEL_INPT);
}


void SDA_IN_PULL_HIGH()
{
	bcm2835_gpio_set_pud(sda_pin, BCM2835_GPIO_PUD_UP);
}


void SDA_IN_PULL_DOWN()
{
	bcm2835_gpio_set_pud(sda_pin, BCM2835_GPIO_PUD_DOWN);
}


void SCL_IN_PULL_HIGH()
{
	bcm2835_gpio_set_pud(scl_pin, BCM2835_GPIO_PUD_UP);
}


void SCL_IN_PULL_DOWN()
{
	bcm2835_gpio_set_pud(scl_pin, BCM2835_GPIO_PUD_DOWN);
}


uint8_t SDA_READ_IN()
{
	return bcm2835_gpio_lev(sda_pin);
}


uint8_t SCL_READ_IN()
{
	return bcm2835_gpio_lev(scl_pin);
}


