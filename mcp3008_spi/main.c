#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdint.h>
#include<mcp3008.h>


#define SPI_CS 1

int channel_n=0;

int main(int argc, char **argv)
{
    int i;
    	
	if(argc!=2) {
   	fprintf(stderr,"Usage: %s channel_num\n\n",argv[0]);
	exit(-1);
	} 
	
	channel_n=atoi(argv[1]);
	
	
	
	bcm2835_init();
    bcm2835_spi_begin();
	
	
	
    
	while(i<300) {
    printf("%d\n", MCP3008_analog_read( SPI_CS ,channel_n));
     usleep(10000);
	 i++;
    }

    bcm2835_spi_end();
    bcm2835_close();
    return 0;
}



