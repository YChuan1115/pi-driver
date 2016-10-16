#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pthread.h>
#include<my_debug.h>

#include<bcm2835.h>
#include<bme280.h>

#define BME280_ADDR 0x76

int main()
{
	struct bme280_t *bme;
	int count = 100;

	//-- init the bcm2835 library
    bcm2835_init();
    i2c_start();


	//-- new a bme280 device module with i2c_addr
	bme = bme280_new(BME280_ADDR);     if(bme == 0) return -1;
	bme280_init(bme);
	while(count--){
		usleep(500000);
		bme280_force_read_measurement(bme);
		bme280_show(bme);
		printf("count:%d\n",count);
	};


	// -- END
	bme280_write_mode(bme,BME280_MODE_SLEEP);
	bme280_free(bme);
	bcm2835_close();
    return 0;
}
