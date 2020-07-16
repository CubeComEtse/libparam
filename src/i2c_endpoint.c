/*
 * i2cendpoint.c
 *
 * Created: 2020/04/21 20:33:38
 *  Author: Kolijn
 */ 

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "i2c_endpoint.h"
#include "i2c_driver.h"
#include "std_message.h"

static struct i2c_driver_data sI2cDriver;
static uint8_t u8I2CEndpoint;
static uint8_t u8I2CAddress;

/**
 * \brief Initialize the I2C Endpoint
 * 
 * \param endpoint The endpoint number
 * \param dev_addr The i2c address of the device to talk to
 */
void I2C_vInitEndpoint(uint8_t endpoint, uint8_t dev_addr) {
    I2C_DRIVER_vInitPC104(&sI2cDriver);
    u8I2CEndpoint = endpoint;
    u8I2CAddress = dev_addr;
}

/**
 * \brief Process a message from the UART.
 *
 * This function mirrors the CAN_bEndpoint and CONFIG_bEndpoint functions
 *
 * First byte (ADDR_idx) is the address of the register to read/write to. 
 * Second byte (DIR_idx) is the direction, as specified by enum RWDirection
 * Third byte is the length of the data. (LEN_idx).
 * Data is located at (DATA_idx), if there is any
 *
 * If data is read the function returns true to re-transmit the data
 * 
 * \param rx_buffer Buffer of received data
 * \param rx_length Length of the data
 * \param tx_buffer Buffer to retransmit. Unused
 * \param tx_length Length to retransmit. Unused
 * 
 * \return bool True to retransmit the buffers. Always returns False
 */
bool I2C_bEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {
    
    // If it is a read packet, it should have length 3
    if (rx_buffer[DIR_idx] == READ) {
        
        // Update the TX buffer with values
        tx_buffer[ADDR_idx] = rx_buffer[ADDR_idx];
        tx_buffer[DIR_idx] = rx_buffer[DIR_idx];
        tx_buffer[LEN_idx] = rx_buffer[LEN_idx];
        // The length is the 3 bytes + the length we're reading
        *tx_length = 3 + rx_buffer[LEN_idx];

        return I2C_DRIVER_bReadFromChecksum(&sI2cDriver, u8I2CAddress, rx_buffer[ADDR_idx], &tx_buffer[DATA_idx], rx_buffer[LEN_idx]);
    }
    else
    {
        I2C_DRIVER_bWriteToChecksum(&sI2cDriver, u8I2CAddress, rx_buffer[ADDR_idx], &rx_buffer[DATA_idx], rx_buffer[LEN_idx]);
        // Always return false, writes don't send data back
        return false;
    }
}

/**
 * \brief Match the CAN_vProcess pattern
 */
void I2C_vProcess(void) {

}
