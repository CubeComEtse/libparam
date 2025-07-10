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
#include "message_buffer.h"

#define UART_HOLDING_BUFFER_SIZE 32

#include <asf.h>

typedef enum {
	UART = 1,
	RS485,
	RS422,
}uart_comm_mode_t;

typedef struct {
	// Buffers containing the incoming and outgoing data.
	StreamBufferHandle_t uart_rx_buffer;
	StreamBufferHandle_t uart_tx_buffer;
	
	uint8_t tx_holding_buffer[UART_HOLDING_BUFFER_SIZE];
	volatile size_t tx_buffer_read;
	volatile size_t tx_buffer_write;
	
	uint8_t rx_holding_buffer[UART_HOLDING_BUFFER_SIZE];
	volatile size_t rx_buffer_read;
	volatile size_t rx_buffer_write;
	
	Usart * base_usart;
	
	bool doFlowControl;
	uint32_t cts_pin; // (clear to send)
	
	TaskHandle_t task_reference;
	
	MessageBufferHandle_t receiveMessageBuffer;
	
	// Usart details
	uart_comm_mode_t uart_comm_mode;
	uint32_t baudrate;
	
	void (*set_gpio_pin) (uint32_t pin, bool value);
	void (*disable_pin) (uint32_t pin);
	uint32_t rs422_nre_pin;
	uint32_t rs422_de_pin;
	uint32_t rs485_de_pin;
	uint32_t uart_tx_pin;
	uint32_t uart_rx_pin;
}ccd_uart_t;

void ccd_uart_Init(ccd_uart_t * driver, Usart * base_usart);

void ccd_uart_setCommMode(void * vHandle, uart_comm_mode_t uart_comm_mode);

void ccd_uart_EnableTXInterrupt(ccd_uart_t * driver);
void ccd_uart_InterruptHandler(ccd_uart_t * driver);
void ccd_usart_RXProcessingTask(void * parameters);
void ccd_usart_TXProcessingTask(void * parameters);

void ccd_uart_StartFlowControl(void * driver);
void ccd_uart_StopFlowControl(void * driver);

void ccd_b_uart_Send_message(void * vHandle, uint8_t * data, size_t data_len);
size_t ccd_b_uart_Receive_message(void * vHandle, uint8_t * data, size_t data_len);

#endif /* CCD_UART_DRIVER_H_ */