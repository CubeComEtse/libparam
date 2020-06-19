/*
 * This module knows how to configure the board for the XTX, and how to parse
 * messages intended for it.
 */
#include <stdint.h>
#include <stdbool.h>
#include "serial_multiplexer.h"
#include "spi_endpoint.h"
#include "i2c_endpoint.h"
#include "xtx.h"
#include "obc_controller_rev_A.h"
#include "ioport.h"

#define XTX_I2C_ENDPOINT   1
#define XTX_SPI_ENDPOINT   4
#define XTX_CAN_ENDPOINT   6
#define XTX_CON_ENDPOINT   7

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

    // XTX control endpoint - used to toggle enable and reset lines
    SERMUX_vRegisterEndpoint(XTX_CON_ENDPOINT, &XTX_vConEndpoint);

    // Setup SPI
    // SPI endpoint - if a board needs a special endpoint it
    SERMUX_vRegisterEndpoint(XTX_SPI_ENDPOINT, &spi_endpoint);

    // Setup I2C
    // I2C Endpoint
    i2c_endpoint_init();
    SERMUX_vRegisterEndpoint(XTX_I2C_ENDPOINT, &i2c_endpoint);
 }

 void XTX_vDeConfig(void) {
    // De-assert all pins

    // De-register endpoints
    SERMUX_vDeRegisterEndpoint(XTX_CON_ENDPOINT);
    SERMUX_vDeRegisterEndpoint(XTX_SPI_ENDPOINT);
    SERMUX_vDeRegisterEndpoint(XTX_I2C_ENDPOINT);
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