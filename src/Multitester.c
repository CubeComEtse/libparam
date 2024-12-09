/*
 * Multitester.c
 *
 * Created: 2022/08/15 11:40:55
 *  Author: Kolijn
 */ 

#include "Multitester.h"

#include <assert.h>
#include "register_map.h"

#include "event.h"

// The I2C Expander has two ports, with 8 outputs each. Outputs 0-3 are for Position1, 4-7
// are the same but for port2. The pins are repeated in the same order, so we can use an offset
#define ENA_PIN			(1 << 0)
#define POWER_PIN		(1 << 1)
#define nRESET_PIN		(1 << 2)
#define FAN_PIN			(1 << 3)

#define PCA9555_CMD_IN_PORT0	0
#define PCA9555_CMD_IN_PORT1	1
#define PCA9555_CMD_OUT_PORT0	2
#define PCA9555_CMD_OUT_PORT1	3
#define PCA9555_CMD_PI_PORT0	4
#define PCA9555_CMD_PI_PORT1	5
#define PCA9555_CMD_CFG_PORT0	6
#define PCA9555_CMD_CFG_PORT1	7

#define PCA9555_MULTITESTER_ADDR	0b0100000
#define PCA9555_RFSWITCH1_ADDR		0b0100001
#define PCA9555_RFSWITCH2_ADDR		0b0100010


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
	TMR_vCreate(&handle->update_timer, TMR_SOURCE_SYSTICK);
	if (relay_number == 1){
		handle->i2c_address = PCA9555_RFSWITCH1_ADDR;
	}
	if (relay_number == 2) {
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
			if (TMR_bIsExpired(&pHandle->update_timer)){
				TMR_vStart(& pHandle->update_timer, 100);
				uint8_t register_address = PCA9555_CMD_OUT_PORT0;
				result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, &register_address, 1, buffer, 2);
				
				if (result){
					pHandle->state = INITIALIZING;
				}
				if (pHandle->channel_num == 1){
					mm_setRFRelaysConf_RFSW1_Detected(result);
				}
				if (pHandle->channel_num == 2){
					mm_setRFRelaysConf_RFSW2_Detected(result);
				}
			}
				
			break;
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
			
			if ((result) && (buffer[1] == 0xF0) && (buffer[2] == 0xFF)){
				pHandle->state = IDLE;
			}
			else {
				// TODO: More elegant error here
				pHandle->state = UNINITIALIZED;
			}
		break;
		
		
		
		case IDLE:
			if (pHandle->desired_channel != pHandle->set_channel){
				
				if (MULTI_vSetRfSwitchChannel(pHandle)) {
					// If successful, update register map
					pHandle->set_channel = pHandle->desired_channel;
					if (pHandle->channel_num == 1){
						mm_setRFRelaysConf_RfSw1Chan(pHandle->desired_channel);
					}
					if (pHandle->channel_num == 2){
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
					
				buffer[0] = PCA9555_CMD_OUT_PORT0;
				buffer[1] = 0x00;
				buffer[2] = 0x00;
				result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 1, &buffer[1], 2);
					
				if (!result){
					pHandle->state = UNINITIALIZED;
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
	if (handle->desired_channel != 0){
		tx_buffer[1] = 0x1 << (handle->desired_channel-1);
	}
	
	tx_buffer[0] = PCA9555_CMD_OUT_PORT0;
	bool result = handle->i2c_write_function(handle->i2c_handle, handle->i2c_address, tx_buffer, 3);
	
	// Todo: Probably read this value back
	
	return result;
}

void RFRelay_SetScanEnabled(rf_relay_config_t * pHandle, bool value){
	pHandle->scan_enabled = value;
}

/*
 * This function can be called from external sources to set the desired channel
*/
void RFRelay_SetDesiredChannel(rf_relay_config_t * handle, uint8_t channel)
{
	handle->desired_channel = channel;
}





void MULTI_Init(multitester_t * handle)
{
	assert(handle->i2c_write_function);
	assert(handle->i2c_read_function);
	
	handle->state = UNINITIALIZED;
	TMR_vCreate(&handle->update_timer, TMR_SOURCE_SYSTICK);
	handle->i2c_address = PCA9555_MULTITESTER_ADDR;
	
	handle->scan_enabled = true;
	handle->new_portbits = 0x00;
	handle->previous_portbits = 0x00;
	handle->auto_clear = true;
}


void MULTI_Process(multitester_t * pHandle)
{
	uint8_t buffer[] = {0, 0, 0};
	switch (pHandle->state)
	{
		case UNINITIALIZED:
			// IF we exceeded the countdown, check if the multi_tester is there.
			if (TMR_bIsExpired(&pHandle->update_timer))
			{
				TMR_vStart(&pHandle->update_timer, 100);
				
				if (pHandle->scan_enabled){
					uint8_t register_address = PCA9555_CMD_OUT_PORT0;
					bool result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, &register_address, 1, buffer, 2);
					
					if (result){
						pHandle->state = INITIALIZING;
					}
					mm_setMultiConf0_Detected(result);
				}
			}
		break;
		case INITIALIZING:
		{
				// Write the desired state
				uint16_t inverted_bits = pHandle->new_portbits ^ MULTITESTER_INVERT_MASK;
				buffer[0] = PCA9555_CMD_OUT_PORT0;
				buffer[1] = inverted_bits & 0xFF;
				buffer[2] = (inverted_bits >> 8) & 0xFF;
				pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 3);
				
			
				// Make all pins outputs
				buffer[0] = PCA9555_CMD_CFG_PORT0;
				buffer[1] = 0x00;
				buffer[2] = 0x00;
				pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 3);
				
				pHandle->state = IDLE;
		}
		break;
		case IDLE:
			if (pHandle->new_portbits != pHandle->previous_portbits)
			{
				// The Power bits need to be inverted, because they go through a transistor on
				// the multitester
				uint16_t inverted_bits = pHandle->new_portbits ^ MULTITESTER_INVERT_MASK;
				
				buffer[0] = PCA9555_CMD_OUT_PORT0;
				buffer[1] = inverted_bits & 0xFF;
				buffer[2] = (inverted_bits >> 8) & 0xFF;
				pHandle->i2c_write_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 3);
						
				mm_setMultiConf1_Status(pHandle->new_portbits);
				pHandle->previous_portbits = pHandle->new_portbits;
			}
			
			if (TMR_bIsExpired(&pHandle->update_timer) && pHandle->scan_enabled)
			{
				// Check if the multiTester is still connected.
				TMR_vStart(&pHandle->update_timer, 1000);
				
				buffer[0] = PCA9555_CMD_OUT_PORT0;
				buffer[1] = 0x00;
				buffer[2] = 0x00;
				bool result = pHandle->i2c_read_function(pHandle->i2c_handle, pHandle->i2c_address, buffer, 1, &buffer[1], 2);
				
				if (!result){
					// Todo: EVENT!
					pHandle->state = UNINITIALIZED;
				}
			}
		break;
	}
	
}

void MULTI_SetBitsFrom(multitester_t * pHandle, uint16_t set_bits)
{
	uint32_t new_bits = (pHandle->new_portbits | set_bits);
	
	if (pHandle->auto_clear){
		if (set_bits & (POWER_PIN << 0))
		{
			// Clear all the other pins (except fans)
			new_bits = (new_bits & ~0x7770);
		}
		if (set_bits & (POWER_PIN << 4))
		{
			// Clear all the other pins (except fans)
			new_bits = (new_bits & ~0x7707);
		}
		if (set_bits & (POWER_PIN << 8))
		{
			// Clear all the other pins (except fans)
			new_bits = (new_bits & ~0x7077);
		}
		if (set_bits & (POWER_PIN << 12))
		{
			// Clear all the other pins (except fans)
			new_bits = (new_bits & ~0x0777);
		}
	}
	
	pHandle->new_portbits = new_bits;
}

void MULTI_ClearBitsFrom(multitester_t * pHandle, uint16_t clear_bits)
{
	pHandle->new_portbits = pHandle->new_portbits & ~clear_bits;
}

void MULTI_SetAutoClear(multitester_t * pHandle, bool value)
{
	pHandle->auto_clear = value;
}

void MULTI_SetScanEnabled(multitester_t * pHandle, bool value){
	pHandle->scan_enabled = value;
}