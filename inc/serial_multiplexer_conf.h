/*
 * This file configures the serial multiplexer. The user should edit this file
 * to configure behavior
 */ 

#ifndef SERIAL_MULTIPLEXER_CONF_H_
#define SERIAL_MULTIPLEXER_CONF_H_

#include "usart_buffer.h"
#include "bsp.h"

/*
 * The HEADERBYTES array configure the series of bytes to look for that defines a new packet 
*/
const uint8_t HEADERBYTES[] = {0xF0, 0x55, 0xAA, 0x0F};

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