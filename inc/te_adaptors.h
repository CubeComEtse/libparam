/*
 * te_adaptors.h
 *
 * Created: 2025/02/18 07:55:58
 *  Author: Kolijn
 */ 


#ifndef TE_ADAPTORS_H_
#define TE_ADAPTORS_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "pca9555.h"
#include "tmr.h"

/*
	This struct stores details for each possible TE Adapter.
	Each of them are processed separately, but common things like
	the i2c functions are kept separately.
*/

typedef struct {	
	bool scan_enabled;
	enum pca_device_state state;
	tmr_t update_timer;
	
	uint16_t new_portbits;
	uint16_t previous_portbits;
	
	uint8_t i2c_address;
}te_adaptor_t;


typedef struct {
	bool (*i2c_write_function)(void * handle, const uint8_t dev_addr, const uint8_t * data, const size_t data_len);
	bool (*i2c_read_function)(void * handle, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len);
	void * i2c_handle;
	
	te_adaptor_t adaptors[4];
} te_scanner_t;

void TE_Adaptors_Setup(te_scanner_t * pHandle);
void TE_Adaptors_Task(void * vHandle);

void TE_Adaptor_SetScanEnabled(te_scanner_t * pHandle, uint8_t index);
void TE_Adaptor_ClearScanEnabled(te_scanner_t * pHandle, uint8_t index);

void TE_Adaptor_SetTeBits(te_scanner_t * pHandle, uint8_t index, uint16_t bits);
void TE_Adaptor_ClearTeBits(te_scanner_t * pHandle, uint8_t index, uint16_t bits);

#endif /* TE_ADAPTORS_H_ */