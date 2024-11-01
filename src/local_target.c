/*
 * This instance handles local messages. It mostly interacts with the 
 * register_handler directly.
 *
 * Created: 2024/10/03 18:10:09
 *  Author: Kolijn
 */ 

/*
 * This is the I2C Target. All messages that should be sent over I2C are 
 * received and processed here.
 * 
 * This instance has a stream buffer which receives messages. A FreeRTOS 
 * task checks this buffer and sends messages if required. This instance
 * requires function pointers to I2C read and write functions.
 *
 * Created: 2024/10/03 17:08:40
 * Author: Kolijn
 */ 

#include "local_target.h"

#include <assert.h>

#include "FreeRTOS.h"
#include "message_buffer.h"

#include "pc_messages.h"
#include "register_handler.h"


/*
 * Initialize the instance. 
 *
 * Before calling this function the following should be set
*/
void LOCALTARGET_Init(local_target_t * handle)
{	
	// This buffer size is an initial guess. Feel free to update it later.
	handle->incoming_messages = xMessageBufferCreate(256);
	handle->outgoing_messages= xMessageBufferCreate(256);
	
}

#include "bsp.h"

void LOCALTARGET_Task(void *handle)
{
	assert(handle);
	local_target_t * pHandle = (local_target_t *) handle;
	
	uint8_t rx_buffer[32];
	v2_msg_t in_message;
	uint8_t out_message_data[8];
	uint8_t tx_buffer[32];
	v2_msg_t out_message;
	
	bool decode_successfull;
	
	while(1){
		// Wait indefinitely to receive a message
		size_t rx_length =  xMessageBufferReceive(pHandle->incoming_messages, rx_buffer, 16, pdMS_TO_TICKS(50));
		
		if (rx_length == 0){
			continue;
		}
		
		decode_successfull = decode_v2_message(&in_message, rx_buffer, rx_length);
		
		if (!decode_successfull){
			continue;
		}
		
		
		ioport_set_pin_level(PIN_DEBUG_0, 1);
		if (in_message.is_read){
			
			// Ensure there is enough data in this message to be a read
			if (in_message.data_len != 2)
			{
				// Todo: Create event for malformed messages
				continue;
			}
			
			// Get the register address we want to read
			uint32_t address = in_message.data[0] | (in_message.data[1] << 8);
			
			uint8_t size = 0;
			if (REG_vReadFromAddress(address, &out_message_data[2], &size)){
				//Copy address
				out_message_data[0] = in_message.data[0];
				out_message_data[1] = in_message.data[1];
				
				// Set data
				out_message.data = out_message_data;
				out_message.data_len = size + 2;
				
				// Copy header
				out_message.target = in_message.target;
				out_message.msg_id = in_message.msg_id;
				out_message.is_read = out_message.is_read;
				
				size_t tx_size = encode_v2_message(tx_buffer, &out_message);
				xMessageBufferSend(pHandle->outgoing_messages, tx_buffer, tx_size, pdMS_TO_TICKS(10));
			}
			
		}
		else{
			//Todo: This
			if (in_message.data_len != 6)
			{
				// Todo: Create event for malformed messages
				continue;
			}
			
			uint32_t address = in_message.data[0] | (in_message.data[1] << 8);
			REG_vWriteToAddress(address, &in_message.data[2], 4);
			// Todo: Register handler respond with a read/write result.
			// Our messages don't support that yet.
		}
		ioport_set_pin_level(PIN_DEBUG_0, 0);
		
	}
}