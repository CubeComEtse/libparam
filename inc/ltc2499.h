/*
 * ltc2499.h
 *
 * Created: 2023/10/11 11:44:58
 *  Author: Kolijn
 */ 


#ifndef LTC2499_H_
#define LTC2499_H_

#include <stdint.h>

typedef struct{
	// The 7-bit i2c address. This is set using the vInit Function
	uint8_t i2c_bus_addres;
	
	// These function pointer have to be set before the device is initialized.
	void (*i2c_write_function)(const uint8_t chip_addr, const uint8_t * mem_address, const uint8_t mem_address_length, uint8_t* tx_buffer, const uint16_t length);
	void (*i2c_read_function)(const uint8_t chip_addr, const uint8_t * mem_address, const uint8_t mem_address_length, uint8_t* rx_buffer, const uint16_t length);
	
	uint8_t channel;
} ltc2499_device;

void LTC2499_vInit(ltc2499_device* dev);
void LTC2499_getSample(ltc2499_device *dev);

#endif /* LTC2499_H_ */