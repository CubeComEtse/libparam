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


/**
 * \brief Write to a register on the device
 * 
 * \param drv           Pointer to the driver struct
 * \param chip_addr     I2C Chip address
 * \param mem_address   The register address to write to
 * \param tx_buffer     The data to write. This does not include the checksum
 * \param length        Length of the data
 * 
 * \return bool
 */
bool I2C_DRIVER_bWriteToChecksum(struct i2c_driver* drv, const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length) {
    // Create a new buffer to de-const the data and to add the checksum
    uint8_t tx_buffer_no_const[length + 2];
    memcpy(tx_buffer_no_const, tx_buffer, length);

    uint16_t calculated_checksum = 0;
    for (uint8_t i = 0 ; i < length; i ++) {
        calculated_checksum += (uint16_t) tx_buffer_no_const[i];
    }
    // Add the register address
    calculated_checksum += mem_address;

    tx_buffer_no_const[length] = calculated_checksum & 0xFF;
    tx_buffer_no_const[length+1] = (calculated_checksum >> 8) & 0xFF;

    twihs_packet_t write_packet;
    write_packet.chip = chip_addr;
    write_packet.addr[0] = mem_address;
    write_packet.addr_length = 1;
    write_packet.buffer = tx_buffer_no_const;
    write_packet.length = ((uint32_t) length) + 2;


    uint32_t result = twihs_master_write(drv->p_twihs, &write_packet);
    return result == TWIHS_SUCCESS;
}


/**
 * \brief 
 * 
 * \param drv           Pointer to the driver struct
 * \param chip_addr     I2C Chip address
 * \param mem_address   The register address to read from
 * \param rx_buffer     A buffer to receive data into. It should be big enough to receive the data + 2 checksum
 * \param length        Length of the data, not including checksum
 * 
 * \return bool         True if reception was successfull and the checksum matches
 */
bool I2C_DRIVER_bReadFromChecksum(struct i2c_driver* drv, const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, const uint16_t length) {
    twihs_packet_t read_packet;
    read_packet.chip = chip_addr;
    // Since we are only reading from s byte, the checksum is just that bute.
    read_packet.addr[0] = mem_address;
    read_packet.addr[1] = mem_address;
    read_packet.addr[2] = 0x00;
    read_packet.addr_length = 3;
    read_packet.buffer = rx_buffer;
    read_packet.length = ((uint32_t) length) + 2;

    uint32_t result = twihs_master_read(drv->p_twihs, &read_packet);
    // Clear buffer?
    twihs_read_byte(drv->p_twihs);
    uint16_t calculated_checksum = 0;

    // Checksum calculation
    for (uint8_t i = 0 ; i < length; i ++) {
        calculated_checksum += (uint16_t) rx_buffer[i];
    }
    bool res = (result == TWIHS_SUCCESS) && ((calculated_checksum & 0xFF) == rx_buffer[length]) && (((calculated_checksum >> 8) & 0xFF) == rx_buffer[length+1]);
    return res;
}


/**
 * \brief Write to an I2C device without calculating a checksum
 * 
 * \param drv           Pointer to the driver struct
 * \param chip_addr     I2C Chip address
 * \param mem_address   The register address to read from
 * \param rx_buffer     A buffer to receive data into.
 * \param length        Length of the data,
 * 
 * \return bool         True if reception was successful
 */
bool I2C_DRIVER_bWriteTo(struct i2c_driver* drv, const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length) {
    // Create a new buffer to de-const the data
    uint8_t tx_buffer_no_const[length];
    memcpy(tx_buffer_no_const, tx_buffer, length);

    twihs_packet_t write_packet;
    write_packet.chip = chip_addr;
    write_packet.addr[0] = mem_address;
    write_packet.addr_length = 1;
    write_packet.buffer = tx_buffer_no_const;
    write_packet.length = ((uint32_t) length);

    uint32_t result = twihs_master_write(drv->p_twihs, &write_packet);

    return result == TWIHS_SUCCESS;
}

bool I2C_DRIVER_bReadFrom(struct i2c_driver* drv, const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, const uint16_t length) {
    twihs_packet_t read_packet;
    read_packet.chip = chip_addr;
    read_packet.addr[0] = mem_address;
    read_packet.addr_length = 1;
    read_packet.buffer = rx_buffer;
    read_packet.length = ((uint32_t) length);

    uint32_t result = twihs_master_read(drv->p_twihs, &read_packet);

    return result == TWIHS_SUCCESS;
}
