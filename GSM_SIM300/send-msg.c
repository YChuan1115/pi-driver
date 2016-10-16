#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "gsm.h"

#define phoneNumberStr "0920065540"
serial_port sp;
char msg[20];
int main( int argc, char *argv[] )
{
    uint32_t uart_speed;
    //uint32_t picSize, titleSize, textBodySize;
    struct timeval uart_timeout;
    uint8_t TxString[STRSIZE];
    uint8_t RxString[STRSIZE];
   // uint8_t *phoneNumberStr, *picPathStr, *titlePathStr, *textBodyPathStr;
    uint8_t *meg;
    uint8_t val[]={0x1A};

    DEBUG( "phone number='%s'\n",phoneNumberStr);
    //DEBUG( "pic path='%s'\n", argv[2] );
    //DEBUG( "title path='%s'\n", argv[3] );
    //DEBUG( "text path='%s'\n", argv[4] );

    //phoneNumberStr = "0920065540";
    //picPathStr = argv[2];
    //titlePathStr = argv[3];
    //textBodyPathStr = argv[4];
     time_t t1 = time(NULL);
     struct tm *nPtr = localtime(&t1);
     int year = nPtr->tm_year + 1900;
     int month = nPtr->tm_mon + 1;
     int mday = nPtr->tm_mday;
     int wday = nPtr->tm_wday;
     int hour = nPtr->tm_hour;
     int min = nPtr->tm_min; 
     int sec = nPtr->tm_sec;
     sprintf(msg,"%4d %2d %2d %2d:%2d:%2d\n", year, month, mday,hour,min,sec);

    sp = uart_open( GSMDEVICE );

    if ( sp == INVALID_SERIAL_PORT )
    {
        perror( "Cannot Open Serial Port !\n" );
        return AT_ERROR;
    }

    uart_set_speed( sp, 9600 );

    
    if ( checkOperatorSelection( sp ) )
    {
        uart_close( sp );
        perror( "No GSM operator, or SIM card is not exist !\n" );
        return AT_ERROR;
    }

    printf( "Send message to %s ...\n", phoneNumberStr );
    //1 text mode
    if ( sendATCommandToUart( sp, "AT+CMGF=1\r" ) )
    {
        uart_close( sp );
        perror( "AT+CMGF error\n" );
        return AT_ERROR;
    }

    //2
    if ( sendATCommandToUart( sp, "AT+CMGS=\"+886920065540\"\r" ) )
    {
        uart_close( sp );
        perror( "AT+CMGS error\n" );
        return AT_ERROR;
    }
     
 
    //3  MESSAGE
    if ( sendATCommandToUart( sp, msg ) )
 //   if ( sendATCommandToUart( sp, "TEST ABC 123 YA SUCCESS" ) )
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







/*
int getFileSize( uint8_t *filePathStr )
{
    struct stat picStatBuf;
    uint32_t fileSize;

    stat( filePathStr, &picStatBuf );

    fileSize = picStatBuf.st_size;
    DEBUG( "file size=%d bytes\n", fileSize );
    return fileSize;
}

void StrUpperCase ( uint8_t *sPtr )
{
    while ( *sPtr != '\0' )
    {
        *sPtr = ( uint8_t ) toupper ( ( uint32_t ) * sPtr );
        ++sPtr;
    }
}*/
