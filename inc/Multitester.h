/*
 * Both the MultiTester and RF Relays are external things we use a lot.
 * They are all always on the same addresses.
 * Depending on the setup, they may or may not be connected. The GSE
 * continuously scans for them, they configures them if they are connected.
 * 
 * We could use individual FreeRTOS tasks for them, but that clutters up the 
 * number of tasks we have. Instead, each instance just uses a timer and needs 
 * to be regularly called.
*/

#ifndef MULTITESTER_H_
#define MULTITESTER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "pca9555.h"
#include "tmr.h"

#define I2C_CMD_WRITE 0x01
#define I2C_CMD_READ 0x02

#define POSITION_1 0x51
#define POSITION_2 0x52
#define POSITION_3 0x53
#define POSITION_4 0x54

typedef struct {

	uint8_t i2c_address;
	enum pca_device_state state;
	tmr_t update_timer;
	uint32_t new_portbits;
	uint32_t previous_portbits;
	
} multitester_positions_t;


typedef struct {
	bool (*i2c_write_function)(void * handle, const uint8_t dev_addr, const uint8_t * data, const size_t data_len);
	bool (*i2c_read_function)(void * handle, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len);
	void * i2c_handle;
	
	//uint8_t i2c_address;
	
	// The multi-tester has similar state to the RF relays. 
	//enum pca_device_state state;
	//enum mtcv2_states mtcv2_state;
	
	// Timer tells us when to check for updates
	//tmr_t update_timer;
	
	// These values map 1:1 to the setting for the IO expander IC.
	//uint16_t new_portbits;
	//uint32_t new_portbits;
	//uint32_t previous_portbits;
	//bool auto_clear;
	//bool scan_enabled;
	
	multitester_positions_t multi_positions[4];
	
} multitester_t;



typedef enum channel{
	Position1 = 1,
	Position2 = 2,
	Position3 = 3,
	Position4 = 4
} channel_id_t;

typedef struct
{
	bool (*i2c_write_function)(void * handle, const uint8_t dev_addr, const uint8_t * data, const size_t data_len);
	bool (*i2c_read_function)(void * handle, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len);
	void * i2c_handle;
	
	// Track state. 0 - Disconnected. 1 - Connected and configured.
	enum pca_device_state state;
	
	// Set from the register handler. We update the register handler when a channel was set.
	uint8_t set_channel;
	uint8_t desired_channel;
	
	uint8_t i2c_address;
	
	uint8_t channel_num;
	
	tmr_t update_timer;
	bool scan_enabled;
} rf_relay_config_t;

void RFRelay_Init(rf_relay_config_t * handle, const uint32_t relay_number);
void RFRelay_Process(rf_relay_config_t * pHandle);
void RFRelay_SetScanEnabled(rf_relay_config_t * pHandle, bool value);
void RFRelay_SetDesiredChannel(rf_relay_config_t * handle, uint8_t channel);

void MULTI_Init(multitester_t * handle);
void MULTI_Process(multitester_t * pHandle);
void MULTI_SetBitsFrom(multitester_t * pHandle, uint16_t set_bits);
void MULTI_ClearBitsFrom(multitester_t * pHandle, uint16_t clear_bits);
void MULTI_SetAutoClear(multitester_t * pHandle, bool value);
void MULTI_SetScanEnabled(multitester_t * pHandle, bool value);

// Multitester Version 2
void MTCV2_Init(multitester_t * handle);
void MTCV2_SetBits(multitester_t * pHandle, uint8_t index, uint32_t bits);
void MTCV2_ClearBits(multitester_t * pHandle, uint8_t index, uint32_t bits);
void MTCV2_Task(void * vHandle);

#endif /* MULTITESTER_H_ */
