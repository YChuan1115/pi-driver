#include <stdio.h>
#include "gsm.h"

int main( int argc, char *argv[] )
{
    serial_port sp;
    uint32_t uart_speed;
    struct timeval uart_timeout;
    uint8_t TxString[STRSIZE];
    uint8_t RxString[STRSIZE];
    uint8_t stdinBuf[STRSIZE];
    uint8_t *phoneNumberStr;

    DEBUG( "phone number='%s'\n", argv[1] );

    phoneNumberStr = argv[1];


    sp = uart_open( GSMDEVICE );

    if ( sp == INVALID_SERIAL_PORT )
    {
        perror( "Cannot Open Serial Port !\n" );
        return AT_ERROR;
    }

    //uart_set_speed( sp, 115200 );
						
    uart_set_speed( sp, 9600 );
    //test
    //uart_speed =  uart_get_speed(sp);
    //DEBUG("new uart_speed=%d\n", uart_speed);
    //test

    if ( checkOperatorSelection( sp ) )
    {
        uart_close( sp );
        perror( "No GSM operator, or SIM card is not exist !\n" );
        return AT_ERROR;
    }

    printf( "Dial to %s ...\n", phoneNumberStr );
    memset( TxString, 0, sizeof( TxString ) );
    sprintf( TxString, "ATD%s;\r", phoneNumberStr );

    if ( sendATCommandToUart( sp, TxString ) )
    {
        uart_close( sp );
        perror( "atd error\n" );
        return AT_ERROR;
    }

    printf( "Connectting...\n");

    do
    {
        memset( stdinBuf, 0, sizeof( stdinBuf ) );
        fgets( stdinBuf, 4, stdin );

        if ( strstr( stdinBuf, "ath" ) )
        {
            if ( sendATCommandToUart( sp, "ath" ) )
            {
                uart_close( sp );
                perror( "ath error\n" );
                return AT_ERROR;
            }

            printf( "Hang on !\n" );
            uart_close( sp );
            return AT_OK;
        }

        memset( RxString, 0, sizeof( RxString ) );
        uart_receive_non_fix_size( sp, RxString, sizeof( RxString ), 0, &uart_timeout, TRUE );
        DEBUG( "RxString={%s}\n", RxString );
    }
    while ( !( strstr( RxString, "NO CARRIER" ) || strstr( RxString, "ERROR" ) ) );

    if ( strstr( RxString, "NO CARRIER" ) )
    {
        uart_close( sp );
        printf( "NO CARRIER, hang on !\n" );
        return AT_NO_CARRIER;
    }

    if ( strstr( RxString, "ERROR" ) )
    {
        uart_close( sp );
        return AT_ERROR;
    }

    uart_close( sp );
    return AT_OK;
}
