/*
 * spi_endpoint.c
 *
 * Created: 2020/04/21 20:54:41
 *  Author: Kolijn
 */ 
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "spi_endpoint.h"
#include "spi_driver.h"

static uint8_t u8SpiEndpoint;

/**
 * \brief Initialize the SPI Endpoint
 * 
 * \param endpoint The endpoint number
 */
void SPI_vInitEndpoint(uint8_t endpoint) {
    u8SpiEndpoint = endpoint;
}

/**
 * \brief Process a message from the UART.
 *
 * This function mirrors the CAN_bEndpoint, CONFIG_bEndpoint I2C_bEndpoint
 * functions
 * 
 * \param rx_buffer Buffer of received data
 * \param rx_length Length of the data
 * \param tx_buffer Buffer to retransmit. Unused
 * \param tx_length Length to retransmit. Unused
 * 
 * \return bool True to retransmit the buffers. Always returns False
 */
bool SPI_bEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {

    // Copy due to const reasons
    uint8_t rx_buffer_no_const[rx_length];
    memcpy(rx_buffer_no_const, rx_buffer, rx_length);
    uint16_t rx_length_no_const = rx_length;

    SPI_DRIVER_vSelectDevice();
    SPI_DRIVER_vExchangeBuffers(rx_buffer_no_const, tx_buffer, rx_length_no_const);
    SPI_DRIVER_vDeselctDevice();

    *tx_length = rx_length;

    // Message handled successfully
    return true;
}

/**
 * \brief Match the CAN_vProcess pattern
 */
void SPI_vProcess(void) {

}