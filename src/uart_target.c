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

#include "FreeRTOS.h"
#include "task.h"

// Special characters:
#define FEND	0xC0
#define FESC    0xDB
#define TFEND   0xDC
#define TFESC   0xDD


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
		
		// UART Message Structure - KISS (GSE & Radio): uart_msg_kiss_packet
		// Byte 0   - Message Type
		// Byte 1   - Message ID
		// Byte 2   - Destination Address
		// Byte 3   - Source Address
		// Byte 4-5 - Register Address (2 bytes, MSB first)
		// Byte 6-9 - Optional Data (If it is a write)
		
		// UART Message Structure (PC & Gse): in_message
		// Head 0	- Total Length
		// Head 1	- Endpoint & Direction bit
		// Head 2	- Message ID
		// Byte 0	- Message Type
		// Byte 1	- Payload length (including address)
		// Byte 2...- Data (2&3 is address)
		
		// After decode_v2_message: in_message:
		// in_message.data points to msg_type (Byte 0)
		// in_message.data_len includes address
	
		if (in_message.target == EP_V2_UART_CC_2)
		{	
			uint8_t uart_msg_kiss_packet[32] = {0}; 
				
			uart_msg_kiss_packet[0] = FEND;
				
			//uart_msg_kiss_packet[1] = in_message.msg_id;
			uart_msg_kiss_packet[1] = in_message.msg_type;
			uart_msg_kiss_packet[2] = in_message.msg_id;
			uart_msg_kiss_packet[3] = hnd->gse_uart_address;
			uart_msg_kiss_packet[4] = hnd->radio_uart_address;
			uart_msg_kiss_packet[5] = in_message.data[2]; 
			uart_msg_kiss_packet[6] = in_message.data[3];
			
			// Loop through data and replace special characters
			uint8_t processed_data[4];
			uint8_t processed_index = 0;
			for (uint8_t i = 0; i < 4; i++) {
				if (in_message.data[4 + i] == FEND) {
					processed_data[processed_index++] = FESC;
					processed_data[processed_index++] = TFEND;
					} else if (in_message.data[4 + i] == FESC) {
					processed_data[processed_index++] = FESC;
					processed_data[processed_index++] = TFESC;
					} else {
					processed_data[processed_index++] = in_message.data[4 + i];
				}
			}
			
			memcpy(&uart_msg_kiss_packet[7], processed_data, processed_index);
			uart_msg_kiss_packet[7 + processed_index] = FEND;

			
			hnd->uart_send(hnd->uart_handle, uart_msg_kiss_packet, 8 + processed_index);
			//hnd->uart_send(hnd->uart_handle, &in_message.data[2], in_message.data[1]);	
		}
		
	}
}


void UARTTARGET_RxTask(void * handle) 
{
	uart_target_t * hnd = (uart_target_t *) handle;
	
	uint8_t rx_buffer[32] = {0};
	v2_msg_t out_message;
	size_t rx_length;
	
	while(1){
		vTaskDelay(pdMS_TO_TICKS(200));
		
		
		//if (!hnd->uart_receive(hnd->uart_handle, rx_buffer, sizeof(rx_buffer))) {
			//continue;
		//}
		//
		//if (rx_length == 0)
		//{
			//continue;
		//}
		//
		//if (rx_buffer[0] != FEND || rx_buffer[rx_length - 1] != FEND) {
			//continue; // Invalid frame
		//}
		//
		//// Process the packet
		//uint8_t processed_data[32] = {0};
		//uint8_t processed_index = 0;
		//
		//for (size_t i = 1; i < rx_length - 1; i++) {
			//if (rx_buffer[i] == FESC) {
				//if (rx_buffer[i + 1] == TFEND) {
					//processed_data[processed_index++] = FEND;
					//} else if (rx_buffer[i + 1] == TFESC) {
					//processed_data[processed_index++] = FESC;
				//}
				//i++; // Skip next byte since it's part of escape sequence
				//} else {
				//processed_data[processed_index++] = rx_buffer[i];
			//}
		//}
		//
		//// Populate v2_msg_t structure
		//out_message.msg_type = processed_data[0];
		//out_message.msg_id = processed_data[1];
		//out_message.target = EP_V2_UART_CC_2; 
		//out_message.is_read = (processed_data[5] == 0); // Determine read/write
		//out_message.data = &processed_data[5];
		//out_message.data_len = processed_index - 5;
		//
		//// Encode and send to message buffer
		//uint8_t encoded_message[32];
		//size_t encoded_length = encode_v2_message(encoded_message, &out_message);
		//
		//if (encoded_length > 0) {
			//xMessageBufferSend(hnd->incoming_messages, encoded_message, encoded_length, portMAX_DELAY);
		//}
		

		
	}

}