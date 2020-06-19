#include <stdint.h>
#include <stdbool.h>
#include "bsp.h"
#include "config.h"
#include "i2c_driver.h"
#include "serial_multiplexer.h"
#include "string.h"
#include "xtx.h"

#include "ltc2992.h"

#define TEXT_ENDPOINT 0
#define BOARD_ENDPOINT 2

int main (void)
{
    // System Initialization
    sysclk_init();
    wdt_disable(WDT);

    BSP_vInit();
    SERMUX_vInit();
    //BSP_vUsbReset();
    CONFIG_vInit();

    // Register the board configuration endpoint
    SERMUX_vRegisterEndpoint(BOARD_ENDPOINT, &CONFIG_bConfigEndpoint);

    // Immediately register the board for XTX development, this will be changed later
    XTX_vConfig();
    delay_ms(100);

    // Power on the XTX
    /*
    BSP_vSetPowerEn(EN_VBATALT_BUS, true);
    BSP_vSetPowerEn(EN_5V_BUS, true);
    BSP_vSetPowerEn(EN_3V3_BUS, true);*/

    delay_ms(100);

    // Enable lines
    XTX_vSetEnable(true);
    XTX_SetNReset(true);
    
    BSP_vTelemetrySetCTS(false);

    /*
    All messages from the USART are handled by an endpoint. When the board 
    starts up only the BOARD_ENPOINT is enabled. This endpoint tells the 
    control software which board are supported. The control software then 
    sends a message to select a board, and the rest of the endpoints are 
    configured appropriately.

    Additionally, TEXT_ENDPOINT is used to send printf messages back to the 
    control software.
    */
    struct i2c_driver sI2cDriver;
    sI2cDriver.p_twihs = I2C_BOARD_DEVICE;
    while(1){
        SERMUX_vProcess();

    }

}


/*
void send_can_message(uint8_t message_type, uint8_t register_address, uint8_t xtx_address);

void send_can_message(uint8_t message_type, uint8_t register_address, uint8_t xtx_address) {
    struct mcan_tx_element tx_element;
    mcan_get_tx_buffer_element_defaults(&tx_element);
    tx_element.T0.reg |= MCAN_TX_ELEMENT_T0_EXTENDED_ID(message_type<< 24 | register_address << 16 | xtx_address << 8 | OBC_CAN_ADRESS) | MCAN_TX_ELEMENT_T0_XTD;
    tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID(OBC_CAN_ADRESS);
    uint8_t data_length = 2;
    tx_element.T1.bit.DLC = data_length;

    for (uint8_t i = 0; i < data_length; i++) {
        tx_element.data[i] = i;
    }

    mcan_set_tx_buffer_element(BSP_psGetCanDriver(), &tx_element, 0);
    mcan_tx_transfer_request(BSP_psGetCanDriver(), 1 );
}

*/