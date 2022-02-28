/*
 * i2c_endpoint.h
 *
 * Created: 2020/04/21 20:33:55
 *  Author: Kolijn
 */ 

#ifndef I2C_ENDPOINT_H_
#define I2C_ENDPOINT_H_

#include <stdbool.h>
#include <stdint.h>

void I2C_SetEndpointSpeed(uint32_t newSpeed);
void I2C_SetEndpointAddress(uint8_t address);
bool I2C_bEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);
bool I2C_bEndpointNoChecksum(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);
void I2C_vProcess(void);

#endif /* I2C_ENDPOINT_H_ */