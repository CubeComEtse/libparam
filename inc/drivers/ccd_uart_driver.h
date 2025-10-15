/*
 * ccd_uart_driver.h
 *
 * Created: 2024/10/04 11:30:26
 *  Author: Kolijn
 */ 


#ifndef CCD_UART_DRIVER_H_
#define CCD_UART_DRIVER_H_

#include "asf.h"
#include "ioport.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stream_buffer.h"
#include "message_buffer.h"

#define UART_HOLDING_BUFFER_SIZE 32

#define UART_RX_HB_OVERFLOW  (0x01<<0)
#define UART_RX_SB_OVERFLOW  (0x01<<1)
#define UART_TX_SB_OVERFLOW  (0x01<<2)

typedef enum uart_comm_mode_e
{
	UART = 0,
	RS485,
	RS422,
} uart_comm_mode_t;

typedef enum uart_parity_enabled_e
{
	Disabled = 0,
	Enabled,
} uart_parity_enabled_t;

typedef enum
{
	Odd = 0,
	Even,
} uart_parity_mode_t;

typedef enum uart_baud_rates_e
{
	baud_115200 = 0,
	baud_230400,
	baud_460800,
	baud_921600,
} uart_baud_rates_t;

typedef struct ccd_uart_s
{
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
	
	TaskHandle_t rx_task_handle;
	TaskHandle_t tx_task_handle;
	
	MessageBufferHandle_t receiveMessageBuffer;
	
	// Usart details
	uart_comm_mode_t uart_comm_mode;
	uart_parity_enabled_t uart_parity_enabled;
	uart_parity_mode_t uart_parity_mode;
	uint32_t baudrate;
	
	// Error flags
	bool rx_holding_buffer_overflow;
	bool rx_streaming_buffer_overflow;
	bool tx_holding_buffer_overflow;
	
	void (*set_gpio_pin) (uint32_t pin, bool value);
	uint32_t sout_de_pin;
	uint32_t sout_nre_pin;
	uint32_t sin_de_pin;
	uint32_t sin_nre_pin;
	uint32_t uart_tx_pin;
	uint32_t uart_rx_pin;
	
} ccd_uart_t;

void ccd_uart_Init(ccd_uart_t * driver, Usart * base_usart, uint8_t priority);
void ccd_uart_ReInit(ccd_uart_t * driver);

void ccd_uart_setCommMode(void * vHandle, uart_comm_mode_t uart_comm_mode);
void ccd_uart_setParityEnabled(void * vHandle, uart_parity_enabled_t ParityEnabled);
void ccd_uart_setParityMode(void * vHandle, uart_parity_mode_t ParityMode);
void ccd_uart_setBaudRate(void * vHandle, uart_baud_rates_t BaudRate);

void ccd_uart_EnableTXInterrupt(ccd_uart_t * driver);
void ccd_uart_InterruptHandler(ccd_uart_t * driver);
void ccd_usart_RXProcessingTask(void * parameters);
void ccd_usart_TXProcessingTask(void * parameters);

void ccd_uart_StartFlowControl(void * driver);
void ccd_uart_StopFlowControl(void * driver);

uint32_t ccd_uart_get_error_status(void * vHandle);
void ccd_uart_clear_error_status(void * vHandle);

void ccd_b_uart_Send_message(void * vHandle, uint8_t * data, size_t data_len);
size_t ccd_b_uart_Receive_message(void * vHandle, uint8_t * data, size_t data_len);

#endif /* CCD_UART_DRIVER_H_ */