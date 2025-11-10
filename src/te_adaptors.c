/*
 * te_adaptors.c
 *
 * Created: 2025/02/17 15:49:58
 *  Author: Kolijn
 */ 

#include "te_adaptors.h"

#include "FreeRTOS.h"
#include "task.h"

#include "register_map.h"

void TE_Adaptors_Setup(te_scanner_t * pHandle)
{
	assert(pHandle);
	assert(pHandle->i2c_write_function);
	assert(pHandle->i2c_read_function);
	
	pHandle->adaptors[0].i2c_address = PCA9555_TE0_ADDR;
	pHandle->adaptors[1].i2c_address = PCA9555_TE1_ADDR;
	pHandle->adaptors[2].i2c_address = PCA9555_TE2_ADDR;
	pHandle->adaptors[3].i2c_address = PCA9555_TE3_ADDR;
	
	for (int i = 0; i < 4; i++)
	{
		pHandle->adaptors[i].scan_enabled = 1;
		pHandle->adaptors[i].state = UNINITIALIZED;
		pHandle->adaptors[i].new_portbits = 0x00;
		pHandle->adaptors[i].previous_portbits = 0x00;
		
	}
}

void TE_Adaptors_Task(void * vHandle)
{
	assert(vHandle);
	uint8_t buffer[] = {0x00, 0x00, 0x00};
	bool result = false;
	
	te_scanner_t * pHandle = (te_scanner_t *) vHandle;
	
	while(1)
	{
		for (int a_index = 0; a_index< 4; a_index++)
        {
			te_adaptor_t * curr = & (pHandle->adaptors[a_index]);
		
			switch (curr->state)
            {
				case UNINITIALIZED:
                {
					if (curr->scan_enabled)
					{
						if (TMR_bIsExpired(&curr->update_timer))
						{
							TMR_vStart(&curr->update_timer, 100);
						
							// Try to read the OUT registers as a test.
							uint8_t register_address = PCA9555_CMD_OUT_PORT0;
							result = pHandle->i2c_read_function(pHandle->i2c_handle, curr->i2c_address, &register_address, 1, buffer, 2);
							if (result)
                            {
								curr->state = INITIALIZING;
								curr->previous_portbits = 0x00;
								curr->new_portbits = 0x00;
							}
						}
					}
				    break;
                }                
				case INITIALIZING:
                {
					// There is a possibility we just re-detected a board that was already configured.
					// In this case, set the output values again, then set the port directions.
				
					buffer[0] = PCA9555_CMD_OUT_PORT0;
					buffer[1] = curr->previous_portbits & 0xFF;
					buffer[2] = (curr->previous_portbits >> 8) & 0xFF;
					pHandle->i2c_write_function(pHandle->i2c_handle, curr->i2c_address, buffer, 3);
				
					// Write output ports
				
					// 0 is output, 1 is input
					buffer[0] = PCA9555_CMD_CFG_PORT0;
					buffer[1] = 0x00;
					buffer[2] = 0xF8;
					pHandle->i2c_write_function(pHandle->i2c_handle, curr->i2c_address, buffer, 3);
				
					// Read the answer back in
					buffer[0] = PCA9555_CMD_CFG_PORT0;
					buffer[1] = 0x00;
					buffer[2] = 0x00;
					result = pHandle->i2c_read_function(pHandle->i2c_handle, curr->i2c_address, buffer, 1, &buffer[1], 2);
							
					if ((result) && (buffer[1] == 0x00) && (buffer[2] == 0xF8))
                    {
						// Seems configured, check what adapter this is.
						buffer[0] = PCA9555_CMD_IN_PORT0;
						buffer[1] = 0x00;
						buffer[2] = 0x00;
						result = pHandle->i2c_read_function(pHandle->i2c_handle, curr->i2c_address, buffer, 1, &buffer[1], 2);
						
						uint8_t type = (buffer[2] & 0xF0) >> 4;
						
						if (a_index == 0)
						{
							mm_setTE_Addr_0_Detected(true);
							mm_setTE_Addr_0_Type(type);
						}
						if (a_index == 1)
						{
							mm_setTE_Addr_1_Detected(true);
							mm_setTE_Addr_1_Type(type);
						}
						if (a_index == 2)
						{
							mm_setTE_Addr_2_Detected(true);
							mm_setTE_Addr_2_Type(type);
						}
						if (a_index == 3)
						{
							mm_setTE_Addr_3_Detected(true);
							mm_setTE_Addr_3_Type(type);
						}
						
						curr->state = IDLE;
					}
					else
                    {
						// TODO: More elegant error here
						if (a_index == 0)
						{
							mm_setTE_Addr_0_Detected(false);
						}
						if (a_index == 1)
						{
							mm_setTE_Addr_1_Detected(false);
						}
						if (a_index == 2)
						{
							mm_setTE_Addr_2_Detected(false);
						}
						if (a_index == 3)
						{
							mm_setTE_Addr_3_Detected(false);
						}
						curr->state = UNINITIALIZED;
					}
				    break;
                }                
				case IDLE:
                {
					if (curr->new_portbits != curr->previous_portbits)
					{
						buffer[0] = PCA9555_CMD_OUT_PORT0;
						buffer[1] = curr->new_portbits & 0xFF;
						buffer[2] = (curr->new_portbits >> 8) & 0xFF;
						pHandle->i2c_write_function(pHandle->i2c_handle, curr->i2c_address, buffer, 3);
				
						curr->previous_portbits = curr->new_portbits;
						
						uint32_t existing = 0;
						//This calculation really shouldn't be here.
						if (a_index == 0)
                        {
							existing = 0;
							mm_getTE_Addr_0(&existing);
							existing = (existing & 0x0000000F) | (curr->new_portbits << 16);
							mm_setTE_Addr_0(existing);
						}
						if (a_index == 1)
                        {
							existing = 0;
							mm_getTE_Addr_1(&existing);
							existing = (existing & 0x0000000F) | (curr->new_portbits << 16);
							mm_setTE_Addr_1(existing);
						}
						if (a_index == 2)
                        {
							existing = 0;
							mm_getTE_Addr_2(&existing);
							existing = (existing & 0x0000000F) | (curr->new_portbits << 16);
							mm_setTE_Addr_2(existing);
						}
						if (a_index == 3)
                        {
							existing = 0;
							mm_getTE_Addr_3(&existing);
							existing = (existing & 0x0000000F) | (curr->new_portbits << 16);
							mm_setTE_Addr_3(existing);
						}
					}
			
					if (TMR_bIsExpired(&curr->update_timer) && curr->scan_enabled)
					{
						// Check if the adapter is still connected.
						TMR_vStart(&curr->update_timer, 1000);
				
						buffer[0] = PCA9555_CMD_OUT_PORT0;
						buffer[1] = 0x00;
						buffer[2] = 0x00;
						result = pHandle->i2c_read_function(pHandle->i2c_handle, curr->i2c_address, buffer, 1, &buffer[1], 2);
				
						if (!result){
							// Todo: EVENT!
							if (a_index == 0)
                            {
								mm_setTE_Addr_0_Detected(false);
								curr->state = UNINITIALIZED;
							}
							if (a_index == 1)
                            {
								mm_setTE_Addr_1_Detected(false);
								curr->state = UNINITIALIZED;
							}
							if (a_index == 2)
                            {
								mm_setTE_Addr_2_Detected(false);
								curr->state = UNINITIALIZED;
							}
							if (a_index == 3)
                            {
								mm_setTE_Addr_3_Detected(false);
								curr->state = UNINITIALIZED;
							}
						}
					}
				    break;
                }
			}
		}
		vTaskDelay(pdMS_TO_TICKS(20));
	}
}

void TE_Adaptor_SetScanEnabled(te_scanner_t * pHandle, uint8_t index)
{
    assert(pHandle);
    assert(index < 4);
    
    pHandle->adaptors[index].scan_enabled = true;
}

void TE_Adaptor_ClearScanEnabled(te_scanner_t * pHandle, uint8_t index)
{
    assert(pHandle);
    assert(index < 4);
    
    pHandle->adaptors[index].scan_enabled = false;
}

void TE_Adaptor_SetTeBits(te_scanner_t * pHandle, uint8_t index, uint16_t bits)
{
    assert(pHandle);
    assert(index < 4);
    
    pHandle->adaptors[index].new_portbits |= bits;
}

void TE_Adaptor_ClearTeBits(te_scanner_t * pHandle, uint8_t index, uint16_t bits){
    assert(pHandle);
    assert(index < 4);
	
    pHandle->adaptors[index].new_portbits &= ~bits;
}
