#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "gsm.h"

#define phoneNumberStr "0920065540"
serial_port sp;
char msg_header[] ={"0011000C918896026055040008A0465730970798108B66000A"}; 
char msg_tail[] ={"7D1A57309707000A827E93575B78966295DC5FC360A80020767C58314EBA9EC35EF65B8F"}; 
int main( int argc, char *argv[] )
{
    uint32_t uart_speed;
    uint8_t TxString[STRSIZE];
    uint8_t RxString[STRSIZE];
    uint8_t val[]={0x1A};
    int i;
    
     printf( "SEND SMS %d\n", atoi(argv[1]) );
    //DEBUG( "phone number='%s'\n",phoneNumberStr);
    //DEBUG( "title path='%s'\n", argv[3] );
    //DEBUG( "text path='%s'\n", argv[4] );
    //picPathStr = argv[2];
    //titlePathStr = argv[3];
    //textBodyPathStr = argv[4];
    
    struct timeval uart_timeout;
     time_t t1 = time(NULL);
     struct tm *nPtr = localtime(&t1);
     int year = nPtr->tm_year + 1900;
     int month = nPtr->tm_mon + 1;
     int mday = nPtr->tm_mday;
     int wday = nPtr->tm_wday;
     int hour = nPtr->tm_hour;
     int min = nPtr->tm_min; 
     int sec = nPtr->tm_sec;
      char *msg_date;
      char msg_buf[512]={0};
      msg_date=msg_buf;
   
   memcpy(msg_date,msg_header,sizeof(msg_header)-1);
   msg_date+=sizeof(msg_header)-1; 
   msg_date+=sprintf(msg_date,"003%d003%d6642003%d003%d5206003%d003%d79d2",hour/10,hour%10,min/10,min%10,sec/10,sec%10); 
//	printf(msg_buf);
#if 1
    sp = uart_open( GSMDEVICE );

      printf("open port %s successfully \n",GSMDEVICE);
    if ( sp == INVALID_SERIAL_PORT )
    {
        perror( "Cannot Open Serial Port !\n" );
        return AT_ERROR;
    }

    uart_set_speed( sp, 9600 );
    sleep(1);
    
    if ( checkOperatorSelection( sp ) )
    {
        uart_close( sp );
        perror( "No GSM operator, or SIM card is not exist !\n" );
        return AT_ERROR;
    }
    // sleep(1);
    //printf( "Send message to %s ...\n", phoneNumberStr );
    //0 init
    if ( sendATCommandToUart( sp, "AT\r" ) )
    {
        uart_close( sp );
        perror( "AT error\n" );
        return AT_ERROR;
    }
    //1 PDU Mode CMGF=1
    if ( sendATCommandToUart( sp, "AT+CMGF=0\r" ) )
    {
        uart_close( sp );
        perror( "AT+CMGF error\n" );
        return AT_ERROR;
    }

    //2 (SEND LEN) PDU CMGS= LEN
    if ( sendATCommandToUart( sp, "AT+CMGS=84\r" ) )
    {
        uart_close( sp );
        perror( "AT+CMGS error\n" );
        return AT_ERROR;
    }
    usleep(500000);
  #endif  
    msg_date+=sprintf(msg_date,"767C751F003%d",atoi(argv[1]));
    
//    sendATCommandToUart( sp,msg_buf );
    memcpy(msg_date,msg_tail,sizeof(msg_tail)-1);


#if 1
    for(i=0;i<256;i++) {
     if (i%16==0)   printf("\n");
      printf("%c ", msg_buf[i]) ;
   }
#endif

    //3  MESSAGE
    if ( sendATCommandToUart( sp, msg_buf ) )
    {
        uart_close( sp );
        perror( "MESSAGE ERROR\n" );
        return AT_ERROR;
    }

    if ( sendATCommandToUart( sp, val) )
    {
        uart_close( sp );
        perror( "Send error\n" );
        return AT_ERROR;
    }

    uart_close( sp );
    printf( "Send message completely !\n" );
    return AT_OK;
}
