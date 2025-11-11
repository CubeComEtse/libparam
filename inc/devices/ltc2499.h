/*
 * ltc2499.h
 *
 * Created: 2023/10/11 11:44:58
 *  Author: Kolijn
 */ 


#ifndef LTC2499_H_
#define LTC2499_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct{
	// The 7-bit i2c address. This is set using the vInit Function
	uint8_t i2c_bus_addres;
	
	// These function pointer have to be set before the device is initialized.
    bool (*i2c_write_function)(void * handle, const uint8_t dev_addr, const uint8_t * data, const size_t data_len);
    bool (*i2c_read_function)(void * handle, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len);
    void * i2c_handle;
	
	bool read_or_write;
	
	uint8_t channel;
} ltc2499_device_t;

void LTC2499_vInit(ltc2499_device_t* dev);
void LTC2499_getSample(ltc2499_device_t *dev);

#endif /* LTC2499_H_ */