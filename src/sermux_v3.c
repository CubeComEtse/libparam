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

#include <string.h>
#include <assert.h>

#include "FreeRTOS.h"
#include "task.h"

#include "csp/interfaces/csp_if_kiss.h"

#include "csp_usart_cc.h"
#include "led_indicator.h"
#include "ccd_uart_driver.h"
#include "register_map.h"

extern csp_usart_cc_context_t csp_usart_cc_ctx_tel;

// TODO: What happens when a stream somewhere is full?
// TODO: What happens with message to target that doesn't exist?

/*
 * Initialize the SerMux.
 *
 * Before calling this function set the in and out streams of the struct to 
 * the UART's streams.
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
	
	CRC8_Initialize(&handle->crc_checker, 0x07);
}

/*
 * Registers a new target.
 * 
 * After calling this, messages for target *number* will be sent to the 
 * destination stream. 
 */
void SERMUX_V3_AddTarget(sermux_v3_t * handle, const uint8_t number, MessageBufferHandle_t in, MessageBufferHandle_t out, set_overflow_flag_t overflow_flag_function)
{
	assert (handle->num_targets < MAX_NUMBER_OF_TARGETS);
	
	handle->targets[handle->num_targets].number = number;
	handle->targets[handle->num_targets].in = in;
	handle->targets[handle->num_targets].out = out;
	handle->targets[handle->num_targets].set_overflow_flag = overflow_flag_function;
	
	handle->num_targets += 1;
}

/*
 * PC->GSE 
 */
void SERMUX_V3_ReceiveTask(void * params)
{
	sermux_v3_t* pHandle = (sermux_v3_t *) params;
	
	uint8_t rx_buffer[16];
	
	while(1)
	{
		// Try receiving data from the UART - Wait up to 500ms before updating state
		size_t rx_length = xStreamBufferReceive(pHandle->in_stream, rx_buffer, 16, pdMS_TO_TICKS(500));
	
        // No need to continue of no data was received
		if (rx_length == 0)
        {
			LEDIndicator_SetNextState(LED_POWER_ON);
			continue;
		}
        
        // Update indication LED and continue processing data
		LEDIndicator_SetNextState(LED_UART_COMMS);
        
        // TODO: [ADRIAAN] Consider doing this differently, currently overriding default parser.
        int xTaskWoken = pdFALSE;
        csp_kiss_rx(&csp_usart_cc_ctx_tel.iface, rx_buffer, rx_length, (void *)xTaskWoken);
        continue;
        
		// Check if bytes were dropped by the UART.
		// If it was, reset and wait for next message
		uint32_t uart_status = ccd_uart_get_error_status(pHandle->uart_handle);
		if (uart_status & UART_RX_HB_OVERFLOW)
		{
			mm_setRTOS_Status0_uartRxHBOverflow(true);
			pHandle->state = V2_WAITING_2;
			rx_length = 0;
		}
		if (uart_status & UART_RX_HB_OVERFLOW) // TODO: Why are we checking the same condition here twice???
		{
			mm_setRTOS_Status0_uartRxSBOverflow(true);
			pHandle->state = V2_WAITING_2;
			rx_length = 0;
		}
        
		// This flag isn't really relevant here, but check and clear it anyway.
		if (uart_status & UART_TX_SB_OVERFLOW)
		{
			mm_setRTOS_Status0_uartTxHBOverflow(true);
		}
		ccd_uart_clear_error_status(pHandle->uart_handle);
		
		for (uint32_t i = 0; i < rx_length; i++)
		{
			uint8_t rx_byte = rx_buffer[i];
		
			switch (pHandle->state)
			{
				case V2_WAITING_1:
                {
					if (rx_byte == 0xC3)
                    {
						pHandle->state = V2_WAITING_2;
					}
					break;
                }                    
					
				case V2_WAITING_2:
				{
					if (rx_byte == 0xA9)
                    {
						pHandle->state = V2_STORE_VERSION;
					}
					else {
						pHandle->state = V2_WAITING_1;
					}
					break;
	            }
			
				case V2_STORE_VERSION:
				{
					pHandle->rx_block.version = rx_byte;
					pHandle->state = V2_STORE_LENGTH;
					break;
	            }
			
				case V2_STORE_LENGTH:
				{
					pHandle->rx_block.length = rx_byte;
					pHandle->rx_block.rx_count = 0;
					pHandle->state = V2_STORE_DATA;
					break;
	            }
			
				case V2_STORE_DATA:
				{
					pHandle->rx_block.buffer[pHandle->rx_block.rx_count] = rx_byte;
					pHandle->rx_block.rx_count+= 1;
					if (pHandle->rx_block.rx_count == pHandle->rx_block.length)
                    {
						pHandle->state = V2_STORE_CRC;
					}
					break;
	            }
				
                case V2_STORE_CRC:
				{
					// Store CRC
					pHandle->rx_block.crc = rx_byte;
					
					// TOTO: Verify the CRC. We don't enable this immediately, wait until the OBC Software generates and 
					// checks it as well.
					uint8_t calculated_crc = CRC8_Calculate(&pHandle->crc_checker, pHandle->rx_block.buffer, pHandle->rx_block.length);
					
					if (pHandle->rx_block.crc != calculated_crc)
					{
						mm_setRTOS_Status0_SERMUX_CRC_Error(true);	
					}
					
					// Process all the messages in this block
					// This can be a uint8_t, but there was a bug where we lost a single byte, and messages 
					// would be misread in an endless loop. Using a large size stops this error, but still 
					// misreads messages.
					uint32_t curr_msg_index = 0;
					while (curr_msg_index < pHandle->rx_block.length)
					{
						uint8_t msg_len = pHandle->rx_block.buffer[curr_msg_index];
						uint8_t msg_target = pHandle->rx_block.buffer[curr_msg_index + 1] & 0x7F;
						
						// This is a safety check. If this is true, the index will never be
						// incremented, and we'll be stuck. So just abandon the block.
						// If this is true, it probably means previous messages  were malformed.
						if (msg_len == 0)
                        {
							curr_msg_index = pHandle->rx_block.length;
							continue;
						}
						if (msg_len > 32)
                        {
							curr_msg_index = pHandle->rx_block.length;
							continue;
						}
					
						for (uint32_t j = 0; j < pHandle->num_targets; j++)
                        {
							if (pHandle->targets[j].number == msg_target)
                            {
								size_t sent_size = xMessageBufferSend(pHandle->targets[j].in, &(pHandle->rx_block.buffer[curr_msg_index]), msg_len, 0);
								if (sent_size == 0 && pHandle->targets[i].set_overflow_flag != NULL)
								{
									pHandle->targets[i].set_overflow_flag(true);
								}
							}
						}
						
						// Increment by the message count
						curr_msg_index += msg_len;
					}
					pHandle->state = V2_WAITING_1;
					break;
                }                
					
				default:
                {
					pHandle->state = V2_WAITING_1;
					break;
                }                
			}
		}
	}
}

/*
 * GSE->PC 
 */
void SERMUX_V3_TransmitTask(void * params)
{
	sermux_v3_t* pHandle = (sermux_v3_t *) params;
	
	// This buffer hold messages as we construct them.
	uint8_t tx_buffer[256];
	size_t tx_buffer_pos = 0;
	size_t buffer_size_without_overhead = 245;
	
	while(1)
	{
		tx_buffer[0] = 0xC3;
		tx_buffer[1] = 0xA9;
		tx_buffer[2] = 2; //Version 2
		tx_buffer_pos = 4;
		
		uint32_t j = 0;
		while ((j < pHandle->num_targets) && (tx_buffer_pos < buffer_size_without_overhead))
		{
			size_t rx_size = 0xFF;
			while(rx_size > 0)
            {
				rx_size = xMessageBufferReceive (pHandle->targets[j].out, &tx_buffer[tx_buffer_pos], buffer_size_without_overhead-tx_buffer_pos, 0);
				tx_buffer_pos += rx_size;
			}
			j += 1;
		}
		
		if (tx_buffer_pos > 4)
		{
			tx_buffer[tx_buffer_pos] = CRC8_Calculate(&pHandle->crc_checker, &tx_buffer[4], tx_buffer_pos - 4);
			tx_buffer[3] = tx_buffer_pos - 4;
			tx_buffer_pos += 1;
			
			if (xStreamBufferSpacesAvailable(pHandle->out_stream) > tx_buffer_pos)
            {
				size_t send_size = xStreamBufferSend(pHandle->out_stream, tx_buffer, tx_buffer_pos, 0);
				if (send_size == 0)
                {
					mm_setRTOS_Status0_uartTxSBOverflow(true);
				}
			}
			else
            {
				// We could probably do something smarter than build a block, THEN check if it fits the buffer.
				mm_setRTOS_Status0_uartTxSBOverflow(true);
			}
		}
		
		// 8 seems fine?
		vTaskDelay(pdMS_TO_TICKS(8));
	}
}
