/*
 * ltc2499.c
 *
 * Created: 2023/10/11 09:11:49
 *  Author: Kolijn
 */ 

#include "ltc2499.h"

#include <assert.h>
#include <math.h>

#include "OBC.h"

void LTC2499_vInit(ltc2499_device_t * dev) {
	assert(dev->i2c_read_function);
	assert(dev->i2c_write_function);
	
	dev->i2c_bus_addres = 0x76;
	dev->read_or_write = true;
}

void LTC2499_getSample(ltc2499_device_t *dev)
{
	assert(dev);
	
	if (dev->read_or_write)
	{
		// Send the instruction to read the data
		uint8_t rx_buffer[4] = {0};
		dev->i2c_read_function(dev->i2c_handle, dev->i2c_bus_addres, NULL, 0, rx_buffer, 4);
		
		uint32_t rx_value = ((uint32_t)rx_buffer[0]) << 24 | ((uint32_t)rx_buffer[1]) << 16 | ((uint32_t) rx_buffer[2]) << 8 | (uint32_t)rx_buffer[3];
		
		// Ignore the first 2 bits (sign, and a bit the datasheet calls MSB)
		bool sig = rx_buffer[0] & 0x80;
		bool msb = rx_buffer[0] & 0x40;
		rx_value = rx_value & 0x3FFFFFFF;
		
		if (sig != msb)
		{
			// Bitshift down, ignoring the bottom 6 bits (2 bit sign, 24 bits value, 6 bits padding
			rx_value = rx_value >> 6;
			
			// Convert to a signed number
			int32_t signed_voltage = (int32_t) rx_value;
			if (msb){
				signed_voltage = - 16777215 + signed_voltage;
			}
			
			double voltage_ratio = ((double) signed_voltage)/ (16777216.0) / 2.0;
			// This is a Wheatstone bridge calculation, with all other resistor equal to 10k.
			double r_temperature = 3300 * (1 - 2 * voltage_ratio )/(1 + 2* voltage_ratio);
		
			// This part comes from the calculation for Beta of a RTC
			// T = Beta / (ln(R / (R0 . e ^(-B/T0)) )
			// The whole e ^(-B/T0)^is constant
			double temperature = 3500 / log(r_temperature/ 0.079291363) - 273.25;
			int32_t temp_int = (int32_t)(temperature * 100);
		
			switch (dev->channel){
				case 0:
				mm_setCSBoard_T0(temp_int);
				break;
				case 1:
				mm_setCSBoard_T1(temp_int);
				break;
				case 2:
				mm_setCSBoard_T2(temp_int);
				break;
				case 3:
				mm_setCSBoard_T3(temp_int);
				break;
				case 4:
				mm_setCSBoard_T4(temp_int);
				break;
				case 5:
				mm_setCSBoard_T5(temp_int);
				break;
				case 6:
				mm_setCSBoard_T6(temp_int);
				break;
				case 7:
				mm_setCSBoard_T7(temp_int);
				break;
			}
		}
		
		// Increment the channel that we will configure next time
		dev->channel += 1;
		if (dev->channel >= 8)
		{
			dev->channel = 0;
		}
	}
	else
	{	
		// Send an instruction to sample a channel
		uint8_t tx_buffer[2];
		// Set the ADC to sample from the channel using IN+, IN- as the inputs,
		tx_buffer[0] = 0xA0 | dev->channel;
		// 2nd byte sets frequency rejection and loads a new config.
		tx_buffer[1] = 0b10010000;
		dev->i2c_write_function(dev->i2c_handle, dev->i2c_bus_addres, tx_buffer, 1);
	}
	dev->read_or_write = !dev->read_or_write;
	
}