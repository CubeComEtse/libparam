
#include <asf.h>

#include "bsp.h"
#include "parser.h"
#include "usart_driver.h"

// Local variables
static struct usart_driver* telemetryUsartDriver;

int main (void)
{
    // System Initialization
    sysclk_init();
    BOARD_vInit();

    telemetryUsartDriver = BOARD_psGetTelemetryDriver();
    USART_setEndChar(telemetryUsartDriver, '\n');

    while(1) {
        // Wait for a command to come in

        if (USART_hasMessage(telemetryUsartDriver)){
            uint8_t* buf = USART_getRxBuffer(telemetryUsartDriver);
            parse_commands((char*) buf);
            USART_clearMessage(telemetryUsartDriver);
        }
    }
}

