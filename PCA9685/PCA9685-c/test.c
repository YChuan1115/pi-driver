#include<stdio.h>
#include<stdlib.h>
#include<motor_dev.h>
#include<bcm2835.h>

int main(int argc,char *argv[]){
	bcm2835_init();
	bcm2835_i2c_begin();

	return 0;
}
