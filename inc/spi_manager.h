/*
 * spi_manager.h
 *
 * Created: 2020/03/27 13:38:28
 *  Author: Kolijn
 */ 


#ifndef SPI_MANAGER_H_
#define SPI_MANAGER_H_

enum SPI_SELECT {
    USB_SPI = 0,
    MCU_SPI = 1
};

enum SPI_CS_SELECT {
    SS_0 = 0,
    SS_1,
    SS_2,
    SS_3,
    SS_4,
    SS_5,
    SS_6,
    SS_7
};

void SPI_MANAGER_vSelectDevice(enum SPI_SELECT newSpiDevice);
void SPI_MANAGER_vSetCSLine(enum SPI_CS_SELECT newSpiSelect);
void SPI_MANGER_vSelect(void);
void SPI_MANAGER_vDeselect(void);
void SPI_MANAGER_vSetSpeed(uint32_t newSpeed);
void SPI_MANAGER_vSetMode(uint8_t newMode);
void SPI_MANAGER_vExchangeBuffers(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t bufLen);
#endif /* SPI_MANAGER_H_ */