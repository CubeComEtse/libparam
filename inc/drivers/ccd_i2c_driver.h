/*
 * cc_i2c_driver.h
 *
 * Created: 2024/10/04 21:42:57
 *  Author: Kolijn
 */ 


#ifndef CC_I2C_DRIVER_H_
#define CC_I2C_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <asf.h>

typedef struct {
	Twihs * base_twihs;
}ccd_i2c_t;

void ccd_i2c_driver_Init(ccd_i2c_t * driver, Twihs * instance);
void ccd_i2c_driver_SetBaud(ccd_i2c_t * driver, uint32_t new_baud);
bool ccd_i2c_driver_Write(void * driver, const uint8_t dev_addr, const uint8_t * data, const size_t data_len);
bool ccd_i2c_driver_Read(void * driver, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len);


#endif /* CC_I2C_DRIVER_H_ */