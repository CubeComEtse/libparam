/*
 * ccd_uart_driver.h
 *
 * Created: 2024/10/04 11:30:26
 *  Author: Kolijn
 */ 


#ifndef CCD_UART_DRIVER_H_
#define CCD_UART_DRIVER_H_

#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"

#define UART_HOLDING_BUFFER_SIZE 50

#include <asf.h>

typedef struct {
	// Buffers containing the incoming and outgoing data.
	StreamBufferHandle_t uart_rx_buffer;
	StreamBufferHandle_t uart_tx_buffer;
	
	uint8_t tx_holding_buffer[UART_HOLDING_BUFFER_SIZE];
	size_t tx_buffer_read;
	size_t tx_buffer_write;
	
	uint8_t rx_holding_buffer[UART_HOLDING_BUFFER_SIZE];
	size_t rx_buffer_read;
	size_t rx_buffer_write;
	
	Usart * base_usart;
	
	uint32_t cts_pin;
	
	TaskHandle_t task_reference;
}ccd_uart_t;

void ccd_uart_Init(ccd_uart_t * driver, Usart * base_usart, const uint32_t baud);
void ccd_uart_SetCTS(ccd_uart_t * driver, bool dir);
void ccd_uart_EnableTXInterrupt(ccd_uart_t * driver);
void ccd_uart_InterruptHandler(ccd_uart_t * driver);
void ccd_usart_RXProcessingTask(void * parameters);
void ccd_usart_TXProcessingTask(void * parameters);

#endif /* CCD_UART_DRIVER_H_ */