
#include <asf.h>

#include "bsp.h"
#include "parser.h"


int main (void)
{
    // System Initialization
    sysclk_init();
    BSP_vInit();
    PARSER_vInit();

    while(1) {
        // Wait for a command to come in
        PARSER_vProcess();

        if (PARSER_bHasMessage()) {
            PARSER_vParseCommands();
            PARSER_vClearMessage();
        }
    }
}

