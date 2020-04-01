
#include <asf.h>

#include "bsp.h"
#include "obc_controller_rev_A.h"

int main (void)
{
    // ASF system Initialization
    sysclk_init();

    // Custom board Initizlization
    BOARD_vInit();

    while(1) {
        usart_putchar(TELEMETRY_USART, 'a');
        while(!usart_is_tx_empty(TELEMETRY_USART));
        
        delay_ms(500);
    }
}
