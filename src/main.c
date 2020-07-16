#include <stdint.h>
#include <stdbool.h>
#include "string.h"

#include "bsp.h"
#include "can_endpoint.h"
#include "config.h"
#include "endpoints.h"
#include "i2c_endpoint.h"
#include "serial_multiplexer.h"
#include "spi_endpoint.h"
#include "xtx.h"


int main (void)
{
    // System Initialization
    sysclk_init();
    wdt_disable(WDT);

    // Board initialization
    BSP_vInit();
    SERMUX_vInit();

    // Init the endpoint
    CONFIG_vInit(BOARD_ENDPOINT);

    // Register the board configuration endpoint
    SERMUX_vRegisterEndpoint(BOARD_ENDPOINT, &CONFIG_bConfigEndpoint);
    
    // Immediately register the board for XTX development, this will be changed later
    XTX_vConfig();

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

        // Process the endpoints that require it
        I2C_vProcess();
        CAN_vProcess();
        CONFIG_vProcess();
        SPI_vProcess();
    }
}
