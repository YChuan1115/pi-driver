#ifndef __GSMTYPE_H__
#define __GSMTYPE_H__

#include "uart.h"
#include "debug.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define GSMDEVICE "/dev/ttyUSB0"
//#define GSMDEVICE "/dev/ttyAMA0"

//#define GSMDEVICE "/dev/ttySAC1"
//#define GSMDEVICE "/dev/ttySAC1"
//#define GSMDEVICE "/dev/ttySAC1"
#define STRSIZE 1024

enum
{
    GSM_SUCCESS = 0,
    GSM_VALID = 0,
    GSM_ERROR,
    GSM_INVALID,
    GSM_OVER_SIZE
};

enum AT_RETURN_TYPE
{
    AT_OK,
    AT_CONNECT = 0 ,
    AT_ERROR,
    AT_RING,
    AT_NO_CARRIER,
    AT_ERROR_,
    AT_READY
};


int sendATCommandToUart( serial_port sp, uint8_t *cmdStr );
int checkOperatorSelection( serial_port sp );
int sendStreamToUart( serial_port sp, uint8_t *filePathStr );

#endif  //__GSM-TYPE_H__
