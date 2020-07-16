/*
 * i2c_driver.h
 *
 * Created: 2020/04/22 14:09:18
 *  Author: Kolijn
 */ 


#ifndef I2C_DRIVER_H_
#define I2C_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>
#include "twihs.h"

struct i2c_driver_data {
    Twihs *p_twihs;
};

void I2C_DRIVER_vInitPC104(struct i2c_driver_data* drv);
bool I2C_DRIVER_bWriteToChecksum(struct i2c_driver_data* drv, const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length);
bool I2C_DRIVER_bReadFromChecksum(struct i2c_driver_data* drv, const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, uint16_t length);
bool I2C_DRIVER_bWriteTo(struct i2c_driver_data* drv, const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length);
bool I2C_DRIVER_bReadFrom(struct i2c_driver_data* drv, const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, const uint16_t length);

#endif /* I2C_DRIVER_H_ */