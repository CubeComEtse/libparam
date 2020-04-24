/*
 * i2c_driver.c
 *
 * Created: 2020/04/22 14:09:04
 *  Author: Kolijn
 */ 
#include "i2c_driver.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "twihs.h"


bool I2C_DRIVER_bWriteTo(struct i2c_driver* drv, const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length) {
    uint8_t tx_buffer_no_const[length];
    memcpy(tx_buffer_no_const, tx_buffer, length);

    twihs_packet_t write_packet;
    write_packet.chip = chip_addr;
    write_packet.addr[0] = mem_address;
    write_packet.addr_length = 1;
    write_packet.buffer = tx_buffer_no_const;
    write_packet.length = (uint32_t) length;

    // ToDo: Determine which driver to use
    uint32_t result = twihs_master_write(drv->p_twihs, &write_packet);
    return result == TWIHS_SUCCESS;
}

bool I2C_DRIVER_bReadFrom(struct i2c_driver* drv, const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, uint16_t length) {

    twihs_packet_t read_packet;
    read_packet.chip = chip_addr;
    read_packet.addr[0] = mem_address;
    read_packet.addr_length = 1;
    read_packet.buffer = rx_buffer;
    read_packet.length = (uint32_t) length;

    // ToDo: Determine which driver to use
    uint32_t result = twihs_master_read(drv->p_twihs, &read_packet);
    return result == TWIHS_SUCCESS;
}