/*
 * Receives characters from a UART stream, processes them into messages and
 * sends them to the correct target.
 *
 * Targets were previously called endpoints, were renamed in the V1 -> V2 message
 * change.
 *
 * Created: 2024/10/03 17:00:54
 *  Author: Kolijn
 */ 

#include "sermux_v3.h"

#include "FreeRTOS.h"
#include "task.h"
#include "led_indicator.h"

#include <string.h>
#include <assert.h>

// Todo:
// * What happens when a stream somewhere is full?
// * What happens with message to target that doesn't exist?

/*
 * Initialize the SerMux.
 *
 * Before calling this function set the in and out streams of the struct to 
 * the uart's streams.
*/
void SERMUX_V3_Init(sermux_v3_t * handle)
{
	// The streams have to be set before calling init.
	assert(handle->in_stream);
	assert(handle->out_stream);
	
	handle->rx_block.rx_count = 0;
	handle->tx_block.rx_count = 0;
	handle->num_targets = 0;
	handle->state = V2_WAITING_1;
}

/*
 * Registers a new target.
 * 
 * After calling this, messages for target *number* will be sent to the 
 * destination stream. 
*/
void SERMUX_V3_AddTarget(sermux_v3_t * handle, const uint8_t number, MessageBufferHandle_t in, MessageBufferHandle_t out)
{
	assert (handle->num_targets < MAX_NUMBER_OF_TARGETS);
	
	handle->targets[handle->num_targets].number = number;
	handle->targets[handle->num_targets].in = in;
	handle->targets[handle->num_targets].out = out;
	
	handle->num_targets += 1;
}

// PC->GSE
void SERMUX_V3_ReceiveTask(void * handle)
{
	sermux_v3_t* hnd = (sermux_v3_t *) handle;
	
	uint8_t rx_buffer[16];
	
	while(1)
	{
		// Try receiving data from the UART - Wait up to 500ms before updating state
		size_t rx_length = xStreamBufferReceive(hnd->in_stream, rx_buffer, 16, pdMS_TO_TICKS(500));
	
		if (rx_length == 0){
			LEDIndicator_SetNextState(LED_POWER_ON);
			continue;
		}
		else{
			LEDIndicator_SetNextState(LED_UART_COMMS);
		}
		
		for (uint32_t i = 0; i< rx_length; i++)
		{
			uint8_t rx_byte = rx_buffer[i];
		
			switch (hnd->state)
			{
				case V2_WAITING_1:
					if (rx_byte == 0xC3) {
						hnd->state = V2_WAITING_2;
					}
					break;
					
				case V2_WAITING_2:
					if (rx_byte == 0xA9) {
						hnd->state = V2_STORE_VERSION;
					}
					else {
						hnd->state = V2_WAITING_1;
					}
					break;
			
				case V2_STORE_VERSION:
					hnd->rx_block.version = rx_byte;
					hnd->state = V2_STORE_LENGTH;
					break;
			
				case V2_STORE_LENGTH:
					hnd->rx_block.length = rx_byte;
					hnd->rx_block.rx_count = 0;
					hnd->state = V2_STORE_DATA;
					break;
			
				case V2_STORE_DATA:
					hnd->rx_block.buffer[hnd->rx_block.rx_count] = rx_byte;
					hnd->rx_block.rx_count+= 1;
					if (hnd->rx_block.rx_count == hnd->rx_block.length){
						hnd->state = V2_STORE_CRC;
					}
					break;
				case V2_STORE_CRC:
					// Store CRC
					hnd->rx_block.crc = rx_byte;
					
					// Todo: Verify the CRC
					
					// Process all the messages in this block
					uint8_t curr_msg_index = 0;
					while (curr_msg_index < hnd->rx_block.length)
					{
						uint8_t msg_len = hnd->rx_block.buffer[curr_msg_index];
						uint8_t msg_target = hnd->rx_block.buffer[curr_msg_index +1];
						uint8_t msg_id = hnd->rx_block.buffer[curr_msg_index + 2];
						// bool dirBit = ((msg_target & 0x80) > 0);
						msg_target = msg_target & 0x7F;
						
						
						// This is a safety check. If this is true, the index will never be
						// incremented, and we'll be stuck. So just abandon the block.
						// If this is true, it probably means previous messages  were malformed.
						if (msg_len == 0){
							curr_msg_index = hnd->rx_block.length;
							continue;
						}
					
						for (uint32_t j = 0; j < hnd->num_targets; j++){
							if (hnd->targets[j].number == msg_target){
								//Todo: Ticks to Wait is a guess
								xMessageBufferSend(hnd->targets[j].in, &(hnd->rx_block.buffer[curr_msg_index]), msg_len, 0);
							}
						}
						
						// Todo: Should we raise an event if no targets were found?
						
						// Increment by the message count
						curr_msg_index += msg_len;
					}
					hnd->state = V2_WAITING_1;
					break;
					
				default:
					hnd->state = V2_WAITING_1;
					break;
			}
		}
	}
}

		
void SERMUX_V3_TransmitTask(void * handle)
{
	sermux_v3_t* hnd = (sermux_v3_t *) handle;
	
	// This buffer hold messages as we construct them.
	uint8_t tx_buffer[128];
	size_t tx_buffer_pos = 0;
	
	while(1)
	{
		tx_buffer[0] = 0xC3;
		tx_buffer[1] = 0xA9;
		tx_buffer[2] = 2; //Version 2
		tx_buffer_pos = 4;
		
		uint32_t j =0;
		while ((j < hnd->num_targets) && (tx_buffer_pos < 120))
		{
			size_t rx_size = 0;
			do {
				rx_size = xMessageBufferReceive (hnd->targets[j].out, &tx_buffer[tx_buffer_pos], 120-tx_buffer_pos,0);
				tx_buffer_pos += rx_size;
			}
			while(rx_size > 0);
			
			j+=1;
		}
		
		if (tx_buffer_pos > 4)
		{
			//Todo: CRC
			tx_buffer[tx_buffer_pos] = 0x00;
			tx_buffer[3] = tx_buffer_pos - 4;
			tx_buffer_pos += 1;
			
			//Todo: This timeout should be set?
			xStreamBufferSend(hnd->out_stream, tx_buffer, tx_buffer_pos, 0);
		}
		
		vTaskDelay(pdMS_TO_TICKS(1));
	}
}