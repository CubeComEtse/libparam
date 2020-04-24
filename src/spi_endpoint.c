/*
 * spi_endpoint.c
 *
 * Created: 2020/04/21 20:54:41
 *  Author: Kolijn
 */ 

 #include "spi_endpoint.h"
 #include "spi_driver.h"
 #include <stdbool.h>
 #include <stdint.h>
 #include <string.h>

 
bool spi_endpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {

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