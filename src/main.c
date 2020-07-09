#include <stdint.h>
#include <stdbool.h>
#include "asf.h"
#include "bsp.h"
#include "can_endpoint.h"
#include "config.h"
#include "i2c_endpoint.h"
#include "serial_multiplexer.h"
#include "string.h"
#include "xtx.h"

#include "ltc2992.h"

#define TEXT_ENDPOINT 0
#define I2C_ENDPOINT 1
#define BOARD_ENDPOINT 2
#define CAN_ENDPOINT 3

int main (void)
{
    // System Initialization
    sysclk_init();
    wdt_disable(WDT);

    // Board initialization
    BSP_vInit();
    SERMUX_vInit();
    //BSP_vUsbReset();   
    CONFIG_vInit();

    // Init the endpoints
    i2c_endpoint_init();
    can_endpoint_init();

    // Register the board configuration endpoint
    SERMUX_vRegisterEndpoint(BOARD_ENDPOINT, &CONFIG_bConfigEndpoint);
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT, &i2c_endpoint);
    SERMUX_vRegisterEndpoint(CAN_ENDPOINT, &can_endpoint);

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
    while(1){
        SERMUX_vProcess();
        CONFIG_vUpdate();
        can_endpoint_process();
    }

}