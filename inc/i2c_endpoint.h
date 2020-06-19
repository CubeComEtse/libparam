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

void i2c_endpoint_init(void);
bool i2c_endpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

#endif /* I2C_ENDPOINT_H_ */