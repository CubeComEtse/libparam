#include <stdint.h>
#include <stdbool.h>
#include "string.h"

#include "bsp.h"
#include "can_endpoint.h"
#include "config.h"
#include "endpoints.h"
#include "i2c_endpoint.h"
#include "Multitester.h"
#include "serial_multiplexer.h"
#include "spi_endpoint.h"
#include "register_handler.h"
#include "xtx.h"
#include "tmr.h"

// This was only for CAN testing
#include "std_message.h"
#include "can_driver.h"

int main (void)
{
    // System Initialization
    sysclk_init();
    wdt_disable(WDT);

    // Board initialization
    BSP_vInit();
    SERMUX_vInit();
    REG_vInit();

    // Init the endpoint
    CONFIG_vInit(BOARD_ENDPOINT);

    // Register the board configuration endpoint
    SERMUX_vRegisterEndpoint(BOARD_ENDPOINT, &CONFIG_bConfigEndpoint);

    BSP_vTelemetrySetCTS(false);
	I2C_SetEndpointSpeed(100000);

    // Always register all the Endpoints.
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT_CHKSM, &I2C_bEndpoint);
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT_PLAIN, &I2C_bEndpointNoChecksum);

    
    SERMUX_vRegisterEndpoint(CAN_ENDPOINT, &CAN_bEndpoint);

    /*
    All messages from the USART are handled by an endpoint. When the board 
    starts up only the BOARD_ENPOINT is enabled. This endpoint tells the 
    control software which board are supported. The control software then 
    sends a message to select a board, and the rest of the endpoints are 
    configured appropriately.

    Additionally, TEXT_ENDPOINT is used to send printf messages back to the 
    control software.
    */

    tmr_t uptimeTimer;
    uint32_t uptime = 0;
    TMR_vInit(&uptimeTimer, BSP_u16TmrGetTick, 1);
    TMR_vStart(&uptimeTimer, 1000);


    //CAN_vInitEndpoint(CAN_ENDPOINT, OBC_CAN_ADRESS, XTX_CAN_ADRESS);
    uint8_t rx_buffer[8];
    rx_buffer[ADDR_idx] = 0x02;
    rx_buffer[DIR_idx] = READ;
    rx_buffer[LEN_idx] = 3;
    rx_buffer[DATA_idx] = 0;
    uint16_t tx_len = 3;

    uint8_t tx_buffer[8];
    uint16_t tx_length = 0;

    


    while(1){
        SERMUX_vProcess();

        // Process the endpoints that require it
        I2C_vProcess();
        CAN_vProcess();
        CONFIG_vProcess();
        SPI_vProcess();
		
		MULTI_vProcess();

        REG_vProcessMessages();

        // XTX_vProcess();
        if (TMR_bExpired(&uptimeTimer)){
            // Increase 
            uptime += 1;
            REG_vSetUptime(uptime);
            TMR_vStart(&uptimeTimer, 1000);
        }
    }
}
