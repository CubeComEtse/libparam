/*
 * This module knows how to configure the board for the XTX, and how to parse
 * messages intended for it.
 */
#include <stdint.h>
#include <stdbool.h>

#include "obc_controller_rev_A.h"
#include "bsp.h"
#include "can_endpoint.h"
#include "endpoints.h"
#include "std_message.h"
#include "i2c_endpoint.h"
#include "serial_multiplexer.h"
#include "spi_endpoint.h"
#include "xtx.h"
#include "ioport.h"
#include "register_handler.h"
#include "tmr.h"

// Local functions
bool XTX_vConEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

// Struct to keep track of the timer
static tmr_t sUpdateTimer;
// Set the interval to check the pin
static uint16_t u16PinReadycheckInterval = 100;
// The previous state of the pin, should we send or not
static bool prevReadyPin = false;

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
    ioport_enable_pin(XTX_RDY_PIN);
    ioport_set_pin_dir(XTX_RDY_PIN, IOPORT_DIR_INPUT);
    ioport_set_pin_mode(XTX_RDY_PIN, IOPORT_MODE_PULLDOWN);

    // Configure endpoints
    I2C_vInitEndpoint(I2C_ENDPOINT, XTX_CAN_ADRESS, REG_GetI2CSpeed());
    CAN_vInitEndpoint(CAN_ENDPOINT, OBC_CAN_ADRESS, XTX_CAN_ADRESS);

    // Register them with the sermux
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT, &I2C_bEndpoint);
    SERMUX_vRegisterEndpoint(CAN_ENDPOINT, &CAN_bEndpoint);
    SERMUX_vRegisterEndpoint(SPI_ENDPOINT, &SPI_bEndpoint);
    SERMUX_vRegisterEndpoint(XTX_ENDPOINT, &XTX_vConEndpoint);

    // Enable lines
    TMR_vInit(&sUpdateTimer, BSP_u16TmrGetTick, 1);
    TMR_vStart(&sUpdateTimer, u16PinReadycheckInterval);
}

void XTX_vDeConfig(void)
{
    // De-register endpoints
    SERMUX_vDeRegisterEndpoint(I2C_ENDPOINT);
    SERMUX_vDeRegisterEndpoint(CAN_ENDPOINT);
    SERMUX_vDeRegisterEndpoint(SPI_ENDPOINT);
}


void XTX_vSetEnable(bool enabled) {
     ioport_set_pin_level(XTX_EN_PIN, enabled);
}

bool XTX_bGetEnable(void){
    return ioport_get_pin_level(XTX_EN_PIN);
}

void XTX_SetNReset(bool reset) {
     ioport_set_pin_level(XTX_nRST_PIN, reset);
}

bool XTX_bGetNReset(void){
    return ioport_get_pin_level(XTX_nRST_PIN);
}

bool XTX_bGetReady(void){
     return ioport_get_pin_level(XTX_RDY_PIN);
}

bool XTX_vConEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {
    if (rx_buffer[DIR_idx] == WRITE) {
        switch(rx_buffer[ADDR_idx]) {
            case XTX_ENABLED:
            XTX_vSetEnable(rx_buffer[DATA_idx]);
            break;
            case XTX_NRESET:
            XTX_SetNReset(rx_buffer[DATA_idx]);
            break;
        }
    }
    else {
        switch(rx_buffer[ADDR_idx]) {
            case XTX_ENABLED:
            tx_buffer[DATA_idx] = XTX_bGetEnable();
            break;
            case XTX_NRESET:
            tx_buffer[DATA_idx] = XTX_bGetNReset();
            break;
            case XTX_RDY:
            XTX_vProcess();
            tx_buffer[DATA_idx] = XTX_bGetReady();
            break;
            default:
            // Return before message is constructed
            return false;
        }
        tx_buffer[ADDR_idx] = rx_buffer[ADDR_idx];
        tx_buffer[DIR_idx] = rx_buffer[DIR_idx];
        tx_buffer[LEN_idx] = 1;
        *tx_length = 4;
        return true;
    }
    return false;
}

void XTX_vProcess(void) {
    //if (TMR_bExpired(&sUpdateTimer)) {

        bool newValue = XTX_bGetReady();
        if (prevReadyPin != newValue) {
            prevReadyPin = newValue;

            uint8_t message_data[4];
            message_data[ADDR_idx] = XTX_RDY;
            message_data[DIR_idx] = READ;
            message_data[LEN_idx] = 1;
            message_data[DATA_idx] = prevReadyPin;

            SERMUX_vTransmit(XTX_ENDPOINT, message_data, 4);
        }
        //TMR_vStart(&sUpdateTimer, u16PinReadycheckInterval);
    //}
 }