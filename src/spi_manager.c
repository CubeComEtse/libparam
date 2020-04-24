/*
 * spi_manager.c
 *
 * This module implements all the functions that can be called from the
 * computer program
 */

#include "asf.h"
#include "obc_controller_rev_A.h"
#include "spi_manager.h"
#include <stdint.h>
#include "bsp.h"


static uint32_t SPI_MANAGER_u32CsPin = SPI_CS_PIN_0;
static uint32_t SPI_MANAGER_u32Speed = 400000;
static uint8_t SPI_MANAGER_u8Mode = 0;
// The polarity setting is equal to the selected level
static bool SPI_MANAGER_bCsPolarity = 0;

/**
 * \brief   Set the micro controller or the USB in charge of the SPI communications.
 *          This is effective immediately
 *
 * \param newSpiDevice      Either USB_SPI or USB_SPI
 */
void SPI_MANAGER_vSelectDevice(enum SPI_SELECT newSpiDevice)
{
    if (newSpiDevice == USB_SPI) {
        ioport_set_pin_level(SPI_SELECT_PIN, 0);
    }
    if (newSpiDevice == MCU_SPI) {
        ioport_set_pin_level(SPI_SELECT_PIN, 1);
    }
}

/**
 * \brief Sets the CS pin to use when transmitting
 *
 * \param newSpiSelect Any of (SPI_CS_0 .. SPI_CS_7)
 */
void SPI_MANAGER_vSetCSLine(enum SPI_CS_SELECT newSpiSelect)
{
    // Setup new directions
    ioport_set_pin_dir(SPI_MANAGER_u32CsPin, IOPORT_DIR_INPUT);
    ioport_set_pin_dir(SPI_MANAGER_u32CsPin, IOPORT_DIR_OUTPUT);

    // Store pin value
    SPI_MANAGER_u32CsPin = newSpiSelect;
}


/**
 * \brief Select the SPI device
 */
void SPI_MANGER_vSelect(void)
{
    ioport_set_pin_level(SPI_CS_PIN_7, SPI_MANAGER_bCsPolarity);
}

/**
 * \brief Deselect the SPI device
 *
 * Depending on the CS polarity setting, this may mean high or low on the line
 */
void SPI_MANAGER_vDeselect(void)
{
    ioport_set_pin_level(SPI_CS_PIN_7, !SPI_MANAGER_bCsPolarity);
}

/**
 * \brief Re-configures the SPI device to a new speed
 *
 * \param newSpeed a integer indicating the Hz - eg 4000000
 */
void SPI_MANAGER_vSetSpeed(uint32_t newSpeed)
{
    SPI_MANAGER_u32Speed = newSpeed;
   spi_master_setup_device(SPI_DEVICE, BSP_psGetSpiDriver(), SPI_MANAGER_u8Mode, SPI_MANAGER_u32Speed, 0);
}

/**
 * \brief Sets the Clock and data edge mode
 * 
 * \param newMode The mode, 0,1,2, or 3
 * 
 */
void SPI_MANAGER_vSetMode(uint8_t newMode)
{
    SPI_MANAGER_u8Mode = newMode;
    spi_master_setup_device(SPI_DEVICE, BSP_psGetSpiDriver(), SPI_MANAGER_u8Mode, SPI_MANAGER_u32Speed, 0);
}

/**
 * \brief Send data. This function is blocking
 * 
 * \param txBuffer
 * \param rxBuffer
 * \param bufLen
 * 
 * \return void
 */
void SPI_MANAGER_vExchangeBuffers(uint8_t* txBuffer, uint8_t* rxBuffer, uint16_t bufLen) {
    spi_transceive_packet(SPI_DEVICE, txBuffer, rxBuffer, bufLen);
}