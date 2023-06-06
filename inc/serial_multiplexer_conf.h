/*
 * This file configures the serial multiplexer. The user should edit this file
 * to configure behavior
 */ 

#ifndef SERIAL_MULTIPLEXER_CONF_H
#define SERIAL_MULTIPLEXER_CONF_H

#include "usart_buffer.h"
#include "bsp.h"


/*
 * The max number of callbacks, from 0 to MAX_ENDPOINTS
*/
#define MAX_ENDPOINTS  32


#define MAX_MESSAGE_LENGTH 64

/*
 * The SERMUX_bByteAvailable should call a function that returns true if there
 * is a new byte to process, false otherwise
*/
#define SERMUX_bByteAvailable()     (!(USART_RXBuffer_IsEmpty(BSP_psGetTelemetryDriver())))

/*
 * The SERMUX_u8GetByte should return an available byte
*/
#define SERMUX_u8GetByte()          USART_RXBuffer_GetByte(BSP_psGetTelemetryDriver())

/*
 * Put a new value in the buffer
*/
#define SERMUX_vPutByte(x)           USART_TXBuffer_PutByte(BSP_psGetTelemetryDriver(), x)


#define SERMUX_vGetSpaceAvailable()	USART_RXBuffer_GetFreeSpace(BSP_psGetTelemetryDriver())

#endif /* SERIAL_MULTIPLEXER_CONF_H_ */