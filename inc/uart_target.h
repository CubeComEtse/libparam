/*
 * uart_target.h
 *
 * Created: 2025/01/24
 *  Author: Tené
 */ 

#ifndef UART_TARGET_H_
#define UART_TARGET_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "FreeRTOS.h"
#include "message_buffer.h"
#include "stream_buffer.h"
#include "semphr.h"
#include "ccd_uart_driver.h"

typedef void (*uart_send_message_t)(void * handle, uint8_t * data, size_t data_len);
typedef size_t (*uart_receive_message_t)(void * handle, uint8_t * data, size_t data_len);

typedef struct {
	uart_send_message_t uart_send;
	uart_receive_message_t uart_receive;
	
	SemaphoreHandle_t uart_semaphore;
	
	void * uart_handle;
	uart_comm_mode_t uart_mode;
	
	uint8_t radio_uart_address;
	uint8_t gse_uart_address;
	
	MessageBufferHandle_t incoming_messages;
	MessageBufferHandle_t outgoing_messages;
	
}uart_target_t;


void UARTTARGET_Init(uart_target_t * handle);
void UARTTARGET_TxTask(void * handle);
void UARTTARGET_RxTask(void * handle);
bool UARTTARGET_SetCommMode(uart_target_t * pHandle, uart_comm_mode_t CommMode);
bool UARTTARGET_SetParityEnabled(uart_target_t * pHandle, uart_parity_enabled_t ParityEnabled);
bool UARTTARGET_SetParityMode(uart_target_t * pHandle, uart_parity_mode_t ParityMode);
bool UARTTARGET_SetBaudRate(uart_target_t * pHandle, uart_baud_rates_t BaudRate);

#endif /* UART_TARGET_H_ */