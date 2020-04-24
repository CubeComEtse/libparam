/*
 * spi_driver.h
 *
 * Created: 2020/04/21 21:36:23
 *  Author: Kolijn
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include "bsp.h"
#include "spi_manager.h"

#define SPI_DRIVER_vSelectDevice()                                  SPI_MANGER_vSelect()
#define SPI_DRIVER_vExchangeBuffers(buffer, rx_buffer, length)      SPI_MANAGER_vExchangeBuffers(buffer, rx_buffer, length)
#define SPI_DRIVER_vDeselctDevice()                                 SPI_MANAGER_vDeselect()

#endif /* SPI_DRIVER_H_ */
