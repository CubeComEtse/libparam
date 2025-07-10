/*
 * uart_target.c
 *
 * Created: 2025/01/24
 *  Author: Tené
 */ 

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "uart_target.h"
#include "pc_messages.h"
#include "FreeRTOS.h"
#include "task.h"

// Special characters:
#define FEND	0xC0 // 192
#define FESC    0xDB // 219
#define TFEND   0xDC // 220 
#define TFESC   0xDD // 221


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
	
	handle->uart_semaphore = xSemaphoreCreateMutex();
	
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
			uart_msg_kiss_packet[1] = in_message.data[0]; // msg_type
			uart_msg_kiss_packet[2] = in_message.msg_id;
			uart_msg_kiss_packet[3] = hnd->gse_uart_address;
			uart_msg_kiss_packet[4] = hnd->radio_uart_address;
			uart_msg_kiss_packet[5] = in_message.data[2]; 
			uart_msg_kiss_packet[6] = in_message.data[3];
			
			// write
			if (!in_message.is_read)
			{
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
			} else {
				uart_msg_kiss_packet[7] = FEND;
				hnd->uart_send(hnd->uart_handle, uart_msg_kiss_packet, 8);
			}
				
		}
		
	}
}


void UARTTARGET_RxTask(void * handle) 
{
	uart_target_t * hnd = (uart_target_t *) handle;
	
	uint8_t rx_buffer[32];
	size_t rx_max_length = 32;
	uint8_t uart_msg_kiss_packet[32];
	uint8_t out_message_data[32];
	size_t packet_index = 0;
	bool receiving = false;
	bool escaped = false;

	
	while(1){
		vTaskDelay(pdMS_TO_TICKS(200));
		
		//1. call uart_receive to get bytes
		
		size_t received_bytes_length = hnd->uart_receive(hnd->uart_handle, rx_buffer, rx_max_length);
		
		if (received_bytes_length == 0){
			continue;
		}
		
		//3. disassemble kiss packet -> out_message
		for (size_t i = 0; i < received_bytes_length; i++)
		{
			uint8_t rx_byte = rx_buffer[i];
			
			//start receiving only when start byte (FEND) is received
			if (!receiving){
				if (rx_byte == FEND){
					receiving = true;
					packet_index = 0;
					continue;
				}
			} else {
				
				if (rx_byte == FEND){
					// End of packet received
					
					if (packet_index < 6){
						// Invalid length, expecting (excluding the start&end FEND):
						//[0] msg type
						//[1] msg id
						//[2] src address
						//[3] dest address
						//[4] reg. address msb
						//[5] reg. address lsb
						//[6-x] data

						// "throw away" message, restart receiving
						receiving = false;
						continue;
					}
					
					// Full packet received
					v2_msg_t out_message;
					out_message.msg_id = uart_msg_kiss_packet[1];
					out_message.target = EP_V2_UART_CC_2;
					out_message.data_len = packet_index - 2; // data length of entire msg (not only data+addresses)
					out_message.data = out_message_data;
					
					out_message.data[0] = uart_msg_kiss_packet[0]; // msg type
					out_message.data[1] = 6; // can this be hardcoded?
					out_message.data[2] = uart_msg_kiss_packet[4]; // address msb
					out_message.data[3] = uart_msg_kiss_packet[5]; // address lsb
					
					uint8_t index = 4;
					for (size_t j = 6; j < packet_index; j++) {
						out_message.data[index++] = uart_msg_kiss_packet[j];
					}
					
					uint8_t encoded[32];
					size_t encoded_len = encode_v2_message(encoded, &out_message);
					
					xMessageBufferSend(hnd->outgoing_messages, encoded, encoded_len, 0);
					
					//xMessageBufferSend(hnd->outgoing_messages, &out_message, sizeof(out_message), portMAX_DELAY);
					receiving = false;
					continue;
					
					
				}
				
				// Handle escaping
				if (rx_byte == FESC) {
					escaped = true;
					continue;
				}
				
				// fix
				if (escaped) {
					if (rx_byte == TFEND) {
						rx_byte = FEND;
						} else if (rx_byte == TFESC) {
						rx_byte = FESC;
					}
					escaped = false;
				}
				
				// Store received bytes
				if (packet_index < sizeof(uart_msg_kiss_packet)){
					uart_msg_kiss_packet[packet_index++] = rx_byte;
				}		
				
			}
			
		}

	}

}

bool UARTTARGET_SetCommMode(uart_target_t * pHandle, uart_comm_mode_t CommMode)
{
	// Should we wait for the buffer to be empty?
	if(xSemaphoreTake(pHandle->uart_semaphore, pdMS_TO_TICKS(200))) {
		ccd_uart_setCommMode(pHandle->uart_handle, CommMode);
		xSemaphoreGive(pHandle->uart_semaphore);
		return true;	
	}
	return false;
}