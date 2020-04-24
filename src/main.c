
#include <asf.h>

#include "bsp.h"

#include "config.h"
#include "serial_multiplexer.h"
#include "i2c_endpoint.h"
#include "spi_endpoint.h"

#define TEXT_ENDPOINT 0
#define I2C_ENDPOINT 1
#define SPI_ENDPOINT 2
#define BOARD_ENDPOINT 3

int main (void)
{
    // System Initialization
    sysclk_init();
    wdt_disable(WDT);

    BSP_vInit();
    SERMUX_vInit();
    BSP_vUsbReset();

    // Setup endpoint functions
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT, &i2c_endpoint);
    SERMUX_vRegisterEndpoint(SPI_ENDPOINT, &spi_endpoint);
    SERMUX_vRegisterEndpoint(BOARD_ENDPOINT, &CONFIG_bConfigEndpoint);

    while(1){
        SERMUX_vProcess();
    }
}


