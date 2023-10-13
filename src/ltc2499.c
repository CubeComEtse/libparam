/*
 * ltc2499.c
 *
 * Created: 2023/10/11 09:11:49
 *  Author: Kolijn
 */ 

#include <stddef.h>

#include "ltc2499.h"
#include "tmr.h"

void LTC2499_vInit(ltc2499_device* dev) {
	dev->i2c_bus_addres = 0x54;
}

void LTC2499_getSample(ltc2499_device *dev){
	// Send an instruction to sample a channel
	
	uint8_t tx_buffer[2];
	// Set the ADC to sample from the channel using IN+, IN- as the inputs,
	tx_buffer[0] = 0xA0 | dev->channel;
	// 2nd byte sets frequency rejection and loads a new config.
	tx_buffer[1] = 0b10010000;
	
	dev->i2c_write_function(dev->i2c_bus_addres, NULL, 0, tx_buffer, 2);
	
	
	// Send the instruction to read the data
	uint8_t rx_buffer[2] = {0};
	dev->i2c_read_function(dev->i2c_bus_addres, NULL, 0, rx_buffer, 2);
	
	dev->channel += 1;
	if (dev->channel >= 8)
	{
		dev->channel = 0;
	}
	
}