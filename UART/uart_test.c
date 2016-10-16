#include     <stdio.h>      
#include     <stdlib.h>    
#include 	<string.h>
#include     <unistd.h>     
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      
#include     <termios.h>    
#include     <errno.h>     
#include <stdlib.h>
static char *serial_name[]={"/dev/ttyAMA0","/dev/ttyUSB0","/dev/ttyS0","/dev/ttyS1"};
int main(void)
{
	int  n, len,  fd_max,i;
  fd_set  readfds;
  char buffer[256];
	static struct termios oldtio,newtio;

	printf(" *** 0:ttyAMA0 ***\r\n,*** 1:ttyUSB0 ***\r\n,*** 2:ttyS0 ***\r\n,*** 3:ttyS1 ***\r\n");
	printf("*** please input the open serial : ");
	scanf("%d",&i);

	int fd = open(serial_name[i],O_RDWR | O_NOCTTY | O_NDELAY);//270
	if(fd<0){
		perror("Cannot Open Serial Port !\n");
	}
	else 
		printf("open Serial Port success !\r\n");
	
	tcgetattr(fd,&oldtio);
	tcgetattr(fd,&newtio);
	

	cfsetispeed(&newtio,B9600);
	cfsetospeed(&newtio,B9600);

	newtio.c_lflag&= ~(ICANON | ECHO | ECHOE | ISIG);
	
	newtio.c_cflag &= ~PARENB;
	
	
	newtio.c_cflag &= ~CSTOPB;
	

	newtio.c_cflag &= ~CSIZE;
	newtio.c_cflag |= CS8;
	

	newtio.c_oflag &= ~OPOST;
	

	newtio.c_cflag |= (CLOCAL | CREAD);
	
	newtio.c_iflag = 0;
	

	newtio.c_cc[VTIME] = 4;
	newtio.c_cc[VMIN] = 4;
	

	if(tcsetattr(fd,TCSAFLUSH,&newtio)<0)
	{
		printf("tcsetattr fail !\n");
		exit(1);
	}

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    fd_max = fd + 1;
	
    /* Do the select */
    while(1) 
    {
  	
	   n = select(fd_max,&readfds,NULL,NULL,NULL);
	   memset(buffer, 0, sizeof(buffer));
	   if (n<=0)
     	      printf("select failed");
     else
        {
            if (FD_ISSET(fd, &readfds))
                 {	  	char buf[4];
	 		              len=read(fd, buffer, 4);
			      int t; 
                              float temp;
                              t=(buffer[1]<<8)+buffer[0];
                              temp=(float)t/100.0;
        	              fprintf(stderr, "Readed %d data:%6.2f  %#x %#x\n",len,temp,buffer[2],buffer[3]);  
        	            //  sprintf(buf, "got data:%s\n",buf);  
                  	      //for write....rs485 needs GPIO to control rx & tx
                              // write(fd,buf,strlen(buf));
                	}
	      }
    }
}	
