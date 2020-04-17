
#include <asf.h>

#include "bsp.h"
#include "serial_multiplexer.h"


int main (void)
{
    // System Initialization
    sysclk_init();
    wdt_disable(WDT);

    BSP_vInit();

    while(1){
        SERMUX_vProcess();
    }
}


