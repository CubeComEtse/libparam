/*
 * spi_endpoint.h
 *
 * Created: 2020/04/21 20:54:28
 *  Author: Kolijn
 */ 


#ifndef SPI_ENDPOINT_H_
#define SPI_ENDPOINT_H_
#include <stdbool.h>
#include <stdint.h>

bool spi_endpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

#endif /* SPI_ENDPOINT_H_ */