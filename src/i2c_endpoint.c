/*
 * i2cendpoint.c
 *
 * Created: 2020/04/21 20:33:38
 *  Author: Kolijn
 */ 

#include "i2c_endpoint.h"
#include "i2c_driver.h"
#include "obc_controller_rev_A.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

static struct i2c_driver sI2cDriver;

#define XTX_ADDR                0x26

// This has to match the VS studio program
enum RWDirection
{
    I2C_READ = 0,
    I2C_WRITE = 1
};

// Has to match the VS studio struct definition
#define ADDR_idx 0
#define DIR_idx 1
#define LEN_idx 2
#define DATA_idx 3

void i2c_endpoint_init(void) {
    sI2cDriver.p_twihs = I2C_PC104_DEVICE;
}

bool i2c_endpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {
    
    // If it is a read packet, it should have length 3
    if (rx_buffer[DIR_idx] == I2C_READ) {
        
        // Update the TX buffer with values
        tx_buffer[ADDR_idx] = rx_buffer[ADDR_idx];
        tx_buffer[DIR_idx] = rx_buffer[DIR_idx];
        tx_buffer[LEN_idx] = rx_buffer[LEN_idx];
        // The length is the 3 bytes + the length we're reading
        *tx_length = 3 + rx_buffer[LEN_idx];

        return I2C_DRIVER_bReadFromChecksum(&sI2cDriver, XTX_ADDR, rx_buffer[ADDR_idx], &tx_buffer[DATA_idx], rx_buffer[LEN_idx]);
    }
    else
    {
        I2C_DRIVER_bWriteToChecksum(&sI2cDriver, XTX_ADDR, rx_buffer[ADDR_idx], &rx_buffer[DATA_idx], rx_buffer[LEN_idx]);

        // Always return false, writes don't send data back
        return false;
    }
}