/*
 * uart_target.c
 *
 * Created: 2025/01/24
 *  Author: Tené
 */ 

#include "uart_target.h"
#include <string.h>
#include <assert.h>
#include "pc_messages.h"


/*
 * Initialize the instance. 
 *
 * Before calling this function the following should be set
*/
void UARTTARGET_Init(uart_target_t * handle)
{
	//assert(handle->uart_send);
	// Do not assert the handle, it might be void. 
	
	// This buffer size is an initial guess. Feel free to update it later.
	handle->incoming_messages = xMessageBufferCreate(256);
	handle->outgoing_messages = xMessageBufferCreate(256);
	
}

void UARTTARGET_TxTask(void * handle) 
{
	//assert(handle);
	uart_target_t * hnd = (uart_target_t *) handle;
	
	uint8_t rx_buffer[32];
	v2_msg_t in_message;
	v2_msg_t out_message;
	
	bool decode_successfull;
	
	while(1) {
		// Wait indefinitely to receive a message
		size_t rx_length = xMessageBufferReceive(hnd->incoming_messages, rx_buffer, 16, portMAX_DELAY);
		
		if (rx_length == 0){
			continue;
		}
		
		
		decode_successfull = decode_v2_message(&in_message, rx_buffer, rx_length);
		
		if (!decode_successfull){
			continue;
		}
		
		// UART Message Structure:
		// Byte 0   - Message Type
		// Byte 1   - Message ID
		// Byte 2   - Destination Address
		// Byte 3   - Source Address
		// Byte 4-5 - Register Address (2 bytes, MSB first)
		// Byte 6-9 - Optional Data (If it is a write)

		if (in_message.target == EP_V2_UART_CC_2)
		{
			if (in_message.is_read) 
			{
				uint8_t * address = &in_message.data[0];
				uint8_t read_length = in_message.data[2];
			}
		}
		
	}
}