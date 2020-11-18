/*
 * usart_driver.h
 *
 * Created: 2020/02/26 09:11:05
 *  Author: Kolijn
 */ 


#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>

#define USART_RX_BUFFER_SIZE 800
#define USART_TX_BUFFER_SIZE 800

// USART transmit and receive circular buffer.
typedef struct USART_Buffer
{
    volatile uint8_t RX[USART_RX_BUFFER_SIZE];
    volatile uint8_t TX[USART_TX_BUFFER_SIZE];
    volatile uint16_t RX_Head;
    volatile uint16_t RX_Tail;
    volatile uint16_t TX_Head;
    volatile uint16_t TX_Tail;
} USART_Buffer_t;


/*! \brief Struct used when interrupt driven driver is used.
*
*  Struct containing pointer to a usart, a buffer and a location to store Data
*  register interrupt level temporary.
*/
typedef struct Usart_and_buffer
{
    USART_Buffer_t buffer;
} USART_data_t;

void USART_BUFFER_vInitialize(USART_data_t * usart_data);

// TX Buffer Status
bool USART_TXBuffer_IsEmpty(USART_data_t * usart_data);
uint16_t USART_TXBuffer_GetFreeSpace(USART_data_t * usart_data);
uint16_t USART_TXBuffer_GetUsedSpace(USART_data_t * usart_data);
//TX buffer interaction
bool USART_TXBuffer_PutByte(USART_data_t * usart_data, uint8_t data);

// RX Buffer Status
bool USART_RXBuffer_IsEmpty(USART_data_t * usart_data);
uint16_t USART_RXBuffer_GetFreeSpace(USART_data_t * usart_data);
uint16_t USART_RXBuffer_GetUsedSpace(USART_data_t * usart_data); 
// RX Buffer Interaction
uint8_t USART_RXBuffer_GetByte(USART_data_t * usart_data);

// Called in the interrupt to add/remove bytes
bool USART_BUFFER_Receive(USART_data_t* usart_data, uint8_t rx_byte);
bool USART_BUFFER_Transmit(USART_data_t* usart_data, uint8_t* tx_byte);

#endif /* USART_DRIVER_H_ */