#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "gsm.h"

int sendATCommandToUart( serial_port sp, uint8_t *cmdStr )
{
    uint8_t TxString[STRSIZE];
    uint8_t RxString[STRSIZE];
    struct timeval uart_timeout;

    uart_timeout.tv_sec = 1;
    uart_timeout.tv_usec = 0;

    memset( TxString, 0, sizeof( TxString ) );
    sprintf( TxString, "%s\r", cmdStr );
    DEBUG( "TxString={%s}\n", TxString );

    if ( uart_send( sp, TxString, strlen( TxString ), &uart_timeout ) )
    {
        DEBUG( "uart_send error\n" );
        return AT_ERROR;
    }

    do
    {
        memset( RxString, 0, sizeof( RxString ) );
        uart_receive_non_fix_size( sp, RxString, sizeof( RxString ), 0, &uart_timeout, TRUE );
        DEBUG( "RxString={%s}\n", RxString );

    }
    while ( !( strstr( RxString, "OK" ) || strstr( RxString, ">" ) || strstr( RxString, "ERROR" ) || strstr( RxString, "CONNECT" ) || strstr( RxString, "NO CARRIER" ) ) );

    DEBUG( "RxString={%s}\n", RxString );

    if ( strstr( RxString, "OK" ) )
    {
        return AT_OK;
    }

    if ( strstr( RxString, "CONNECT" ) )
    {
        return AT_CONNECT;
    }

    if ( strstr( RxString, "ERROR" ) )
    {
        return AT_ERROR;
    }

    if ( strstr( RxString, "NO CARRIER" ) )
    {
        return AT_NO_CARRIER;
    }
    if ( strstr( RxString, ">" ) )
    {
        return AT_OK;
    }

}

int checkOperatorSelection( serial_port sp )
{
    uint8_t TxString[STRSIZE];
    uint8_t RxString[STRSIZE];
    struct timeval uart_timeout;

    uart_timeout.tv_sec = 1;
    uart_timeout.tv_usec = 0;

    memset( TxString, 0, sizeof( TxString ) );
    sprintf( TxString, "AT+COPS?\r" );  // AT command: check the currently GSM operator selection
    DEBUG( "TxString={%s}\n", TxString );
    //send cops!!
    if ( uart_send( sp, TxString, strlen( TxString ), &uart_timeout ) )
    {
        DEBUG( "uart_send error\n" );
        return AT_ERROR;
    }

    memset( RxString, 0, sizeof( RxString ) );
    uart_receive_non_fix_size( sp, RxString, sizeof( RxString ), 0, &uart_timeout, FALSE );
    DEBUG( "RxString={%s}\n", RxString );

    if ( strstr( RxString, "Chunghwa Telecom" ) || strstr( RxString, "Pacific" ) || strstr( RxString, "Far EasTone" ) )
    {
	printf("%s\n ",RxString);        
	return GSM_VALID;
    }

    return GSM_INVALID;
}

int sendStreamToUart( serial_port sp, uint8_t *filePathStr )
{

    uint32_t file_fd;
    uint8_t RxString[STRSIZE];
    struct timeval uart_timeout;
    struct stat fileStatBuf;
    uint32_t fileSize;

    file_fd = open ( filePathStr, O_RDONLY | O_NOCTTY | O_NONBLOCK );

    if ( file_fd < 0 )
    {
        perror( "open file error !\n" );
        return AT_ERROR;
    }

    stat( filePathStr, &fileStatBuf );

    fileSize = fileStatBuf.st_size;
    uint8_t *fileBuf = malloc ( fileSize );
    read( file_fd, fileBuf, fileSize );

    uart_timeout.tv_sec = 1;
    uart_timeout.tv_usec = 0;

    if ( uart_send_new( sp, fileBuf, fileSize, &uart_timeout ) )
    {
        DEBUG( "uart_send error\n" );
        free( fileBuf );
        return AT_ERROR;
    }

    do
    {
        memset( RxString, 0, sizeof( RxString ) );
        uart_receive_non_fix_size( sp, RxString, sizeof( RxString ), 0, &uart_timeout, TRUE );
        DEBUG( "RxString={%s}\n", RxString );

    }
    while ( !( strstr( RxString, "OK" ) || strstr( RxString, "ERROR" ) || strstr(RxString,">")) );

    free( fileBuf );

    if ( strstr( RxString, "OK" ) )
    {
        return AT_OK;
    }

    if ( strstr( RxString, "ERROR" ) )
    {
        return AT_ERROR;
    }

    if(strstr(RxString,">"))
    {
	return AT_OK;
    }
}
