#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<i2c.h>

int main(int argc,char *argv[]){
	int address ;
	uint8_t res = 0;
	i2c_init(3,5);

	printf("\n");
	printf("    ");
	printf("    ");
	printf("    ");
	for(address = 0x03 ;address < 0x77 ;address++ ){
		if((address % 16) == 0)printf("\n");
		res = i2c_probe(address);
		if(res)
			printf(" %02X ", address );
		else
			printf(" -- ");
	}
	printf("\n");
	i2c_end();
	return 0;
}
