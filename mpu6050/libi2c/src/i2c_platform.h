#ifndef I2C_PLATFORM_H
#define I2C_PLATFORM_H
#include<stdint.h>
//#include<bcm2835.h>
/*
 * i2c_platform.h
 * description: 
 *     i2c_platform.h define the depending gpio actions.
 * */


#ifndef I2C_PLATFORM_C
	uint8_t sda_pin;
	uint8_t scl_pin;
#else 
	extern uint8_t sda_pin;
	extern uint8_t scl_pin;
#endif 


//#ifdef BCM2835_H
//	#define I2C_START()        bcm2835_init()
//	#define SDA_UP()           bcm2835_gpio_write(sda_pin,HIGH)
//	#define SDA_DOWN()         bcm2835_gpio_write(sda_pin,LOW)
//	#define SCL_UP()           bcm2835_gpio_write(scl_pin,HIGH)
//	#define SCL_DOWN()         bcm2835_gpio_write(scl_pin,LOW)
//	#define SDA_AS_OUT()       bcm2835_gpio_fsel(sda_pin,BCM2835_GPIO_FSEL_OUTP)
//	#define SCL_AS_OUT()       bcm2835_gpio_fsel(scl_pin,BCM2835_GPIO_FSEL_OUTP)
//	#define SDA_AS_IN()        bcm2835_gpio_fsel(sda_pin,BCM2835_GPIO_FSEL_INPT)
//	#define SCL_AS_IN()        bcm2835_gpio_fsel(scl_pin,BCM2835_GPIO_FSEL_INPT)
//	#define SDA_IN_PULL_HIGH() bcm2835_gpio_set_pud(sda_pin, BCM2835_GPIO_PUD_UP)
//	#define SDA_IN_PULL_DOWN() bcm2835_gpio_set_pud(sda_pin, BCM2835_GPIO_PUD_DOWN)
//	#define SCL_IN_PULL_HIGH() bcm2835_gpio_set_pud(scl_pin, BCM2835_GPIO_PUD_UP)
//	#define SCL_IN_PULL_DOWN() bcm2835_gpio_set_pud(scl_pin, BCM2835_GPIO_PUD_DOWN)
//	#define SDA_READ_IN()      bcm2835_gpio_lev(sda_pin)
//	#define SCL_READ_IN()      bcm2835_gpio_lev(scl_pin)
//
//	#define PIN_3 RPI_BPLUS_GPIO_J8_03
//	#define PIN_5 RPI_BPLUS_GPIO_J8_05
//#else 
//#endif 



#define W_BIT 0x00
#define R_BIT 0x01



struct B8{
	unsigned b0:1;
	unsigned b1:1;
	unsigned b2:1;
	unsigned b3:1;
	unsigned b4:1;
	unsigned b5:1;
	unsigned b6:1;
	unsigned b7:1;
};

void    S_bit();
void    P_bit();
int     is_ACK();
int     send_ACK();
int     send_NACK();
uint8_t read_bit();

void    send_byte(uint8_t byte);
uint8_t read_byte();

void SET_SDA_PIN(uint8_t pin );
void SET_SCL_PIN(uint8_t pin );

void I2C_START();
void I2C_STOP();
void SDA_UP();
void SDA_DOWN();         
void SCL_UP();
void SCL_DOWN();
void SDA_AS_OUT();
void SCL_AS_OUT();
void SDA_AS_IN();
void SCL_AS_IN();
void SDA_IN_PULL_HIGH();
void SDA_IN_PULL_DOWN();
void SCL_IN_PULL_HIGH();
void SCL_IN_PULL_DOWN();
uint8_t SDA_READ_IN();
uint8_t SCL_READ_IN();

#endif 
