/*
 * Multitester.c
 *
 * Created: 2022/08/15 11:40:55
 *  Author: Kolijn
 */ 

#include "Multitester.h"

#include <assert.h>

#include "FreeRTOS.h"
#include "event.h"
#include "task.h"

#include "register_map.h"
#include "pca9555.h"

// The I2C Expander has two ports, with 8 outputs each. Outputs 0-3 are for Position1, 4-7
// are the same but for port2. The pins are repeated in the same order, so we can use an offset
#define ENA_PIN			(1 << 0)
#define POWER_PIN		(1 << 1)
#define nRESET_PIN		(1 << 2)
#define FAN_PIN			(1 << 3)

#define MULTITESTER_INVERT_MASK 0x2222


// Static Functions
static bool MULTI_vSetRfSwitchChannel(rf_relay_config_t * handle);

void RFRelay_Init(rf_relay_config_t * handle, const uint32_t relay_number)
{	
	assert(handle->i2c_read_function);
	assert(handle->i2c_write_function);
	
	handle->state = UNINITIALIZED;
	handle->set_channel = 0;
	handle->desired_channel = 0;
	handle->channel_num = relay_number;
	handle->scan_enabled = true;
	TMR_vCreate(&handle->update_timer, TMR_SOURCE_SYSTICK);
	if (relay_number == 1)
    {
		handle->i2c_address = PCA9555_RFSWITCH1_ADDR;
	}
	if (relay_number == 2)
    {
		handle->i2c_address = PCA9555_RFSWITCH2_ADDR;
	}
}

void RFRelay_Process(rf_relay_config_t * pHandle)
{
	uint8_t buffer[] = {0x00, 0x00, 0x00};
	bool result = false;
		
	switch (pHandle->state)
	{
		case UNINITIALIZED:
			if (TMR_bIsExpired(&pHandle->update_timer))
            {
				TMR_vStart(& pHandle->update_timer, 100);
				
				if (pHandle->scan_enabled)
                {
					uint8_t register_address = PCA9555_CMD_OUT_PORT0;
					result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, &register_address, 1, buffer, 2);
					
					if (result)
                    {
						pHandle->state = INITIALIZING;
					}
					if (pHandle->channel_num == 1)
                    {
						mm_setRFRelaysConf_RFSW1_Detected(result);
					}
					if (pHandle->channel_num == 2)
                    {
						mm_setRFRelaysConf_RFSW2_Detected(result);
					}
				}
			}
		break;
		
		
		case INITIALIZING:
			// First write the output channel, so that we don't double tick the relay
			MULTI_vSetRfSwitchChannel(pHandle);
						
			// Then make all pins outputs
			buffer[0] = PCA9555_CMD_CFG_PORT0;
			buffer[1] = 0xF0;
			buffer[2] = 0xFF;
			pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 3);
						
			// Read the answer back in
			buffer[0] = PCA9555_CMD_CFG_PORT0;
			buffer[1] = 0x00;
			buffer[2] = 0x00;
			result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 1, &buffer[1], 2);
			
			if ((result) && (buffer[1] == 0xF0) && (buffer[2] == 0xFF))
            {
				pHandle->state = IDLE;
			}
			else
            {
				// TODO: More elegant error here
				pHandle->state = UNINITIALIZED;
			}
		break;
		
		case IDLE:
			if (pHandle->desired_channel != pHandle->set_channel)
            {
				if (MULTI_vSetRfSwitchChannel(pHandle))
                {
					// If successful, update register map
					pHandle->set_channel = pHandle->desired_channel;
					if (pHandle->channel_num == 1)
                    {
						mm_setRFRelaysConf_RfSw1Chan(pHandle->desired_channel);
					}
					if (pHandle->channel_num == 2)
                    {
						mm_setRFRelaysConf_RfSw2Chan(pHandle->desired_channel);
					}
				}
				else
				{
					// Todo: Respond more intelligently to failure
					pHandle->state = UNINITIALIZED;	
				}
			}
			
			if (TMR_bIsExpired(&pHandle->update_timer))
			{
				TMR_vStart(&pHandle->update_timer, 1000);
					
				if (pHandle->scan_enabled)
				{
					buffer[0] = PCA9555_CMD_OUT_PORT0;
					buffer[1] = 0x00;
					buffer[2] = 0x00;
					result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 1, &buffer[1], 2);
					
					if (!result)
                    {
						pHandle->state = UNINITIALIZED;
					}
				}
			}
		
		break;
	}
}

/*
 * Tries to set the relay to the channel, returns true if set, false otherwise.
*/
static bool MULTI_vSetRfSwitchChannel(rf_relay_config_t * handle)
{
	uint8_t tx_buffer[] = {0x00, 0x00, 0x00};
	if (handle->desired_channel != 0)
    {
		tx_buffer[1] = 0x1 << (handle->desired_channel-1);
	}
	
	tx_buffer[0] = PCA9555_CMD_OUT_PORT0;
	bool result = handle->i2c_write_function(handle->i2c_handle, handle->i2c_address, tx_buffer, 3);
	
	// Todo: Probably read this value back
	
	return result;
}

void RFRelay_SetScanEnabled(rf_relay_config_t * pHandle, bool value)
{
	pHandle->scan_enabled = value;
}

/*
 * This function can be called from external sources to set the desired channel
*/
void RFRelay_SetDesiredChannel(rf_relay_config_t * handle, uint8_t channel)
{
	handle->desired_channel = channel;
}

// void MULTI_Init(multitester_t * handle)
// {
// 	assert(handle->i2c_write_function);
// 	assert(handle->i2c_read_function);
// 	
// 	handle->state = UNINITIALIZED;
// 	TMR_vCreate(&handle->update_timer, TMR_SOURCE_SYSTICK);
// 	handle->i2c_address = PCA9555_MULTITESTER_ADDR;
// 	
// 	handle->scan_enabled = true;
// 	handle->new_portbits = 0x00;
// 	handle->previous_portbits = 0x00;
// 	handle->auto_clear = true;
// }
// 
// 
// void MULTI_Process(multitester_t * pHandle)
// {
// 	uint8_t buffer[] = {0, 0, 0};
// 	switch (pHandle->state)
// 	{
// 		case UNINITIALIZED:
// 			// IF we exceeded the countdown, check if the multi_tester is there.
// 			if (TMR_bIsExpired(&pHandle->update_timer))
// 			{
// 				TMR_vStart(&pHandle->update_timer, 100);
// 				
// 				if (pHandle->scan_enabled){
// 					uint8_t register_address = PCA9555_CMD_OUT_PORT0;
// 					bool result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, &register_address, 1, buffer, 2);
// 					
// 					if (result){
// 						pHandle->state = INITIALIZING;
// 					}
// 					mm_setMultiConf0_Detected(result);
// 				}
// 			}
// 		break;
// 		case INITIALIZING:
// 		{
// 				// Write the desired state
// 				uint16_t inverted_bits = pHandle->new_portbits ^ MULTITESTER_INVERT_MASK;
// 				buffer[0] = PCA9555_CMD_OUT_PORT0;
// 				buffer[1] = inverted_bits & 0xFF;
// 				buffer[2] = (inverted_bits >> 8) & 0xFF;
// 				pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 3);
// 				
// 			
// 				// Make all pins outputs
// 				buffer[0] = PCA9555_CMD_CFG_PORT0;
// 				buffer[1] = 0x00;
// 				buffer[2] = 0x00;
// 				pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 3);
// 				
// 				pHandle->state = IDLE;
// 		}
// 		break;
// 		case IDLE:
// 			if (pHandle->new_portbits != pHandle->previous_portbits)
// 			{
// 				// The Power bits need to be inverted, because they go through a transistor on
// 				// the multitester
// 				uint16_t inverted_bits = pHandle->new_portbits ^ MULTITESTER_INVERT_MASK;
// 				
// 				buffer[0] = PCA9555_CMD_OUT_PORT0;
// 				buffer[1] = inverted_bits & 0xFF;
// 				buffer[2] = (inverted_bits >> 8) & 0xFF;
// 				pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 3);
// 						
// 				mm_setMultiConf1_Status(pHandle->new_portbits);
// 				pHandle->previous_portbits = pHandle->new_portbits;
// 			}
// 			
// 			if (TMR_bIsExpired(&pHandle->update_timer) && pHandle->scan_enabled)
// 			{
// 				// Check if the multiTester is still connected.
// 				TMR_vStart(&pHandle->update_timer, 1000);
// 				
// 				buffer[0] = PCA9555_CMD_OUT_PORT0;
// 				buffer[1] = 0x00;
// 				buffer[2] = 0x00;
// 				bool result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 1, &buffer[1], 2);
// 				
// 				if (!result){
// 					// Todo: EVENT!
// 					pHandle->state = UNINITIALIZED;
// 				}
// 			}
// 		break;
// 	}
// 	
// }
// 
// void MULTI_SetBitsFrom(multitester_t * pHandle, uint16_t set_bits)
// {
// 	uint32_t new_bits = (pHandle->new_portbits | set_bits);
// 	
// 	if (pHandle->auto_clear){
// 		if (set_bits & (POWER_PIN << 0))
// 		{
// 			// Clear all the other pins (except fans)
// 			new_bits = (new_bits & ~0x7770);
// 		}
// 		if (set_bits & (POWER_PIN << 4))
// 		{
// 			// Clear all the other pins (except fans)
// 			new_bits = (new_bits & ~0x7707);
// 		}
// 		if (set_bits & (POWER_PIN << 8))
// 		{
// 			// Clear all the other pins (except fans)
// 			new_bits = (new_bits & ~0x7077);
// 		}
// 		if (set_bits & (POWER_PIN << 12))
// 		{
// 			// Clear all the other pins (except fans)
// 			new_bits = (new_bits & ~0x0777);
// 		}
// 	}
// 	
// 	pHandle->new_portbits = new_bits;
// }
// 
// void MULTI_ClearBitsFrom(multitester_t * pHandle, uint16_t clear_bits)
// {
// 	pHandle->new_portbits = pHandle->new_portbits & ~clear_bits;
// }
// 
// void MULTI_SetAutoClear(multitester_t * pHandle, bool value)
// {
// 	pHandle->auto_clear = value;
// }
// 
// void MULTI_SetScanEnabled(multitester_t * pHandle, bool value){
// 	pHandle->scan_enabled = value;
// }


void MTCV2_Init(multitester_t * handle) {
	assert(handle->i2c_write_function);
	assert(handle->i2c_read_function);
	
	handle->multi_positions[0].i2c_address = 0x51;
	handle->multi_positions[1].i2c_address = 0x52;
	handle->multi_positions[2].i2c_address = 0x53;
	handle->multi_positions[3].i2c_address = 0x54;
	
	for (int i = 0; i < 4; i++)
	{
		//handle->multi_positions[i].state = UNINITIALIZED;
		handle->multi_positions[i].state = STARTUP;
		handle->multi_positions[i].new_portbits = 0x00;
		handle->multi_positions[i].previous_portbits = 0x00;
		
	}
}

/**
 * @brief Sets specified bits in the new_portbits field of multitester handle.
 * 
 * This function performs a bitwise OR operation to add one or more bits to 
 * the new_portbits value, indicating pins to be set on the port.
 *
 * @param pHandle Pointer to multitester handle structure.
 * @param index 
 * @param bits Bitmask specifying which bits to set.
 */
void MTCV2_SetBits(multitester_t * pHandle, uint8_t index, uint32_t bits) {
	assert(pHandle);
	pHandle->multi_positions[index].new_portbits |= bits;
}

/**
 * @brief Clears specified bits in the new_portbits field of multitester handle.
 * 
 * This function performs a bitwise AND with the inverse of bits to clear 
 * specific bits in the new_portbits value, indicating pins to be cleared.
 *
 * @param pHandle Pointer to multitester handle structure.
 * @param index 
 * @param bits Bitmask specifying which bits to clear.
 */
void MTCV2_ClearBits(multitester_t * pHandle, uint8_t index, uint32_t bits) {
	assert(pHandle);
	//pHandle->multi_positions[index].new_portbits &= ~bits;
	if (bits == 0x00) {
		pHandle->multi_positions[index].new_portbits &= bits;
	} else {
		pHandle->multi_positions[index].new_portbits &= ~bits;
	}
}


/**
 * @brief Main task for managing multitester I2C communication and port state.
 * 
 * This function runs continuously, updating gpio pin values 
 * over I2C when changes occur.
 *
 * @param vHandle Pointer to multitester handle (void cast).
 */
void MTCV2_Task(void * vHandle) {
	
		assert(vHandle);
		multitester_t * pHandle = (multitester_t *) vHandle;
		bool result = false;
		uint8_t buffer[] = {0x00, 0x00, 0x00, 0x00, 0x00};
		
		
		while (1) {
			
			for (int m_index = 0; m_index < 4; m_index++) {
			
				multitester_positions_t * current_pos = &(pHandle->multi_positions[m_index]);
				uint32_t read_bits = 0;
			
				switch(current_pos->state) {
					case STARTUP:  
						// Read MTC memorymap
						
						switch (current_pos->i2c_address) {
							case 0x51:
								mm_getMTC_Addr_0(&read_bits);
								break;
							case 0x52:
								mm_getMTC_Addr_1(&read_bits);
								break;
							case 0x53:
								mm_getMTC_Addr_2(&read_bits);
								break;
							case 0x54:
								mm_getMTC_Addr_3(&read_bits);
								break;
						}
						
						buffer[0] = I2C_CMD_WRITE;
						buffer[1] = (read_bits >> 0) & 0xFF;
						buffer[2] = (read_bits >> 8) & 0xFF;
						buffer[3] = (read_bits >> 16) & 0xFF;
						buffer[4] = (read_bits >> 24) & 0xFF;
						pHandle->i2c_write_function(pHandle->i2c_handle, current_pos->i2c_address, buffer, 5);
						
						current_pos->state = UNINITIALIZED;
						
					break;
					case UNINITIALIZED:
						if (TMR_bIsExpired(&current_pos->update_timer))
						{
							TMR_vStart(&current_pos->update_timer, 100);
							current_pos->state = INITIALIZING;
						}
						break;
				
					case INITIALIZING:
						current_pos->state = IDLE;
						break;
					
					case IDLE:
						if (current_pos->new_portbits != current_pos->previous_portbits) {
						
							buffer[0] = I2C_CMD_WRITE;
							buffer[1] = (current_pos->new_portbits >> 0) & 0xFF;
							buffer[2] = (current_pos->new_portbits >> 8) & 0xFF;
							buffer[3] = (current_pos->new_portbits >> 16) & 0xFF;
							buffer[4] = (current_pos->new_portbits >> 24) & 0xFF;
							pHandle->i2c_write_function(pHandle->i2c_handle, current_pos->i2c_address, buffer, 5);
						
							// Update value in memorymap
							uint32_t existing = 0;
							switch (current_pos->i2c_address) {
								case 0x51:
									mm_setMTC_Addr_0(current_pos->new_portbits);
									break;
								case 0x52:
									mm_setMTC_Addr_1(current_pos->new_portbits);
									break;
								case 0x53:
									mm_setMTC_Addr_2(current_pos->new_portbits);
									break;
								case 0x54:
									mm_setMTC_Addr_3(current_pos->new_portbits);
									break;
							}

							current_pos->previous_portbits = current_pos->new_portbits;
						
						}
					
						if (TMR_bIsExpired(&current_pos->update_timer)) {
							buffer[0] = I2C_CMD_READ;
							pHandle->i2c_read_function(pHandle->i2c_handle, current_pos->i2c_address, buffer, 1, &buffer[1], 4);
							
							uint32_t read_bits = 0;
							switch (current_pos->i2c_address) {
								case 0x51:
									mm_getMTC_Addr_0(&read_bits);
									break;
								case 0x52:
									mm_getMTC_Addr_1(&read_bits);
									break;
								case 0x53:
									mm_getMTC_Addr_2(&read_bits);
									break;
								case 0x54:
									mm_getMTC_Addr_3(&read_bits);
									break;
							}
							
							current_pos->state = UNINITIALIZED;
						}
					
						break;
					
				
				}
			
			}

// 			switch (pHandle->mtcv2_state) {
// 			case STARTUP:
// 				if (TMR_bIsExpired(&pHandle->update_timer)) {
// 					TMR_vStart(&pHandle->update_timer, 100);
// 					// pHandle->state = INITIALIZING;
// 					pHandle->mtcv2_state = WAIT;
// 				}
// 				break;
// 				
// 			case WAIT:
// 				if (pHandle->new_portbits != pHandle->previous_portbits) {
// 					pHandle->mtcv2_state = WRITE;
// 				} else if (TMR_bIsExpired(&pHandle->update_timer)) {
// 					pHandle->mtcv2_state = READ;
// 				}
// /*				pHandle->mtcv2_state = WRITE;*/
// 				break;
// 				
// 			case WRITE:
// 			
// /*				if (pHandle->new_portbits != pHandle->previous_portbits) {*/
// 					
// 					buffer[0] = I2C_CMD_WRITE;
// 					buffer[1] = (pHandle->new_portbits >> 0) & 0xFF;
// 					buffer[2] = (pHandle->new_portbits >> 8) & 0xFF;
// 					buffer[3] = (pHandle->new_portbits >> 16) & 0xFF;
// 					buffer[4] = (pHandle->new_portbits >> 24) & 0xFF;
// 					result = pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 5);
// 					
// 					if (result) {
// 					
// 						// Update value in memorymap
// 						switch (pHandle->i2c_address) {
// 							case 0x51:
// 							mm_setMTC_Addr_0(pHandle->new_portbits);
// 							break;
// 							case 0x52:
// 							mm_setMTC_Addr_1(pHandle->new_portbits);
// 							break;
// 							case 0x53:
// 							mm_setMTC_Addr_2(pHandle->new_portbits);
// 							break;
// 							case 0x54:
// 							mm_setMTC_Addr_3(pHandle->new_portbits);
// 							break;
// 						}
// 
// 						pHandle->previous_portbits = pHandle->new_portbits;
// 						pHandle->mtcv2_state = READ;
// 						TMR_vStart(&pHandle->update_timer, 10); // small delay before read
// 						
// 					} else {
// 						pHandle->mtcv2_state = ERROR;
// 						TMR_vStart(&pHandle->update_timer, 100);
// 					}
// 						
// /*				}*/
// 
// 				
// // 				if (TMR_bIsExpired(&pHandle->update_timer)) {
// // 					// TMR_vStart(&pHandle->update_timer, 1000);
// // 					pHandle->mtcv2_state = READ;
// // 				}
// 				break;
// 				
// 			case READ:
// 				buffer[0] = I2C_CMD_READ;
// 				result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 1, &buffer[1], 4);
// /*				pHandle->mtcv2_state = STARTUP;*/
// 				if (result) {
// 					pHandle->mtcv2_state = WAIT;
// 					TMR_vStart(&pHandle->update_timer, 1000);
// 				} else {
// 					pHandle->mtcv2_state = ERROR;
// 					TMR_vStart(&pHandle->update_timer, 100);
// 				}
// 				break;
// 				
// 			case ERROR:
// 				
// 				if (TMR_bIsExpired(&pHandle->update_timer)) {
// 					pHandle->mtcv2_state = READ; // retry
// 				}
// 				break;
// 				
// 			}

			vTaskDelay(pdMS_TO_TICKS(20));
			
		}
}
