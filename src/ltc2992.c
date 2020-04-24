/*
 * ltc2992.c
 *
 * Created: 2020/04/23 09:21:36
 *  Author: Kolijn
 */ 

#include "ltc2992.h"
#include <stdint.h>
#include <stdbool.h>


void LTC2992_vNormalSetup(struct ltc2992_device* dev, uint8_t bus_address) {
    dev->i2c_bus_addres = bus_address;

    /*
    LTC2992_vSetRegister(dev, LTC2992_CTRLA, \
        CTRLA_CALIBRATE_EVERY_CONV | \
        CTRLA_MEASUREMENT_MODE_CONTINUOUS | \
        CTRLA_V_CONT_MODE_SENSE);
        */
}

uint8_t LTC2992_u8GenAddr(uint8_t adr0, uint8_t adr1) {

    //Validate input, could probably assert here?
    if ((adr0 > 2) || (adr1 > 2)) {
        return 0;
    }

    // adr0 is low
    if (adr0 == 0) {
        switch (adr1) {
            case 0: return 0x6F; break;
            case 1: return 0x6C; break;
            case 2: return 0x6E; break;
        }
    }

    // adr0 is high
    if (adr0 == 1) {
        switch (adr1) {
            case 0: return 0x67; break;
            case 1: return 0x69; break;
            case 2: return 0x6D; break;
        }
    }

    // adr0 is Not connected
    if (adr0 == 2) {
        switch (adr1) {
            case 0: return 0x6B; break;
            case 1: return 0x68; break;
            case 2: return 0x6A; break;
        }
    }

    return 0;
}

void LTC2992_vSetRegister(struct ltc2992_device* dev, uint8_t register_address, uint8_t flags) {

}

void LTC2992_vReadPower(struct ltc2992_device* dev, uint16_t* power_1, uint16_t* power_2) {
    // Check that the functions are set
    if (dev->i2c_read_function == 0) {
        return;
    }

    uint8_t rx_buffer[] = {0, 0, 0};

    dev->i2c_read_function(dev->i2c_bus_addres, (uint16_t) LTC2992_P1, rx_buffer, 3);

    // Convert the value to power
    *power_1 = (uint16_t) (rx_buffer[1] << 8| rx_buffer[0]);
}
