/*
 * This module knows how to configure the board for the XTX, and how to parse
 * messages intended for it.
 */
#include <stdint.h>
#include <stdbool.h>

#include "obc_controller_rev_A.h"
#include "can_endpoint.h"
#include "endpoints.h"
#include "i2c_endpoint.h"
#include "serial_multiplexer.h"
#include "spi_endpoint.h"
#include "xtx.h"
#include "ioport.h"

// Local functions
bool XTX_vConEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

/**
* \brief Configure for the XTX board
* 
* \param data 
* 
* \return void
*/
void XTX_vConfig(void) {
    // Setup control pins

    // Setup XTXEn pin
    ioport_enable_pin(XTX_EN_PIN);
    ioport_set_pin_level(XTX_EN_PIN, 0);
    ioport_set_pin_dir(XTX_EN_PIN, IOPORT_DIR_OUTPUT);
    
    // Setup nReset
    ioport_enable_pin(XTX_nRST_PIN);
    ioport_set_pin_level(XTX_nRST_PIN, 0);
    ioport_set_pin_dir(XTX_nRST_PIN, IOPORT_DIR_OUTPUT);

    // Setup ready pin
    // ioport_enable_pin(XTX_RDY_PIN);
    ioport_set_pin_dir(XTX_RDY_PIN, IOPORT_DIR_INPUT);
    ioport_set_pin_mode(XTX_RDY_PIN, IOPORT_MODE_PULLDOWN);

    // Configure endpoints
    I2C_vInitEndpoint(I2C_ENDPOINT, XTX_CAN_ADRESS);
    CAN_vInitEndpoint(CAN_ENDPOINT, OBC_CAN_ADRESS, XTX_CAN_ADRESS);

    // Register them with the sermux
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT, &I2C_bEndpoint);
    SERMUX_vRegisterEndpoint(CAN_ENDPOINT, &CAN_bEndpoint);
    SERMUX_vRegisterEndpoint(SPI_ENDPOINT, &SPI_bEndpoint);

}

 void XTX_vDeConfig(void) {
    // De-register endpoints
    SERMUX_vDeRegisterEndpoint(I2C_ENDPOINT);
    SERMUX_vDeRegisterEndpoint(CAN_ENDPOINT);
    SERMUX_vDeRegisterEndpoint(SPI_ENDPOINT);
 }


 void XTX_vSetEnable(bool enabled) {
     ioport_set_pin_level(XTX_EN_PIN, enabled);
 }

 void XTX_SetNReset(bool reset) {
     ioport_set_pin_level(XTX_nRST_PIN, reset);
 }

 bool XTX_bGetEnable(void){
     return ioport_get_pin_level(XTX_RDY_PIN);
 }

 bool XTX_vConEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {
    switch (rx_buffer[0]) {

    }
    return true;
 }