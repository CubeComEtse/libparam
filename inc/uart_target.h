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

// UART Message Structure:
// Byte 0   - Message Type
// Byte 1   - Message ID
// Byte 2   - Destination Address
// Byte 3   - Source Address
// Byte 4-5 - Register Address (2 bytes, MSB first)
// Byte 6-9 - Optional Data (If it is a write)

//typedef void (*uart_send_message_t)(void * handle, uint32_t header, uint8_t * data, size_t data_len);
// set baud?

typedef struct {
	//uart_send_message_t uart_send;
	
	void * uart_handle;
	
	MessageBufferHandle_t incoming_messages;
	MessageBufferHandle_t outgoing_messages;
	
}uart_target_t;

void UARTTARGET_Init(uart_target_t * handle);
void UARTTARGET_TxTask(void * handle);

#endif /* UART_TARGET_H_ */