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

typedef void (*uart_send_message_t)(void * handle, uint8_t * data, size_t data_len);
typedef size_t (*uart_receive_message_t)(void * handle, uint8_t * data, size_t data_len);

typedef struct {
	uart_send_message_t uart_send;
	uart_receive_message_t uart_receive;
	
	void * uart_handle;
	
	uint8_t radio_uart_address;
	uint8_t gse_uart_address;
	
	MessageBufferHandle_t incoming_messages;
	MessageBufferHandle_t outgoing_messages;
	
}uart_target_t;


void UARTTARGET_Init(uart_target_t * handle);
void UARTTARGET_TxTask(void * handle);
void UARTTARGET_RxTask(void * handle);

#endif /* UART_TARGET_H_ */