/*
 * i2cendpoint.c
 *
 * Created: 2020/04/21 20:33:38
 *  Author: Kolijn
 */ 

#include "i2c_endpoint.h"
#include "i2c_driver.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

bool i2c_endpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {

    // Copy due to const reasons
    uint8_t rx_buffer_no_const[rx_length];
    memcpy(rx_buffer_no_const, rx_buffer, rx_length);
    uint16_t rx_length_no_const = rx_length;

    //I2C_DRIVER_vSendI2cBuffer(0xF5, rx_buffer_no_const, rx_length_no_const);
    
    return true;
}