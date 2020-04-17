#include "serial_multiplexer.h"
#include "serial_multiplexer_conf.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef TEST
struct sermux_message {
    uint16_t length;
    uint16_t endpoint;
    uint8_t message[16];
    uint16_t message_index;
};
#endif

enum SERMUX_STATES {
    POSSIBLE_HEADER,
    LENGTH,
    ENDPOINT,
    DATA
};
static enum SERMUX_STATES state = POSSIBLE_HEADER;
static uint16_t state_counter = 0;
static struct sermux_message currentMessage;


#ifndef SERMUX_u8GetByte
#warning Must configure SERMUX_u8GetByte function
#define SERMUX_u8GetByte() 0
#endif

#ifndef SERMUX_bByteAvailable
#warning: Must configure SERMUX_bByteAvailable function
#define SERMUX_bByteAvailable() true
#endif

#include <stdio.h>

void SERMUX_vProcess(void)
{
    while (SERMUX_bByteAvailable()) {
        uint8_t received_byte = SERMUX_u8GetByte();

        switch (state) {
        case POSSIBLE_HEADER:

            if (received_byte == HEADERBYTES[state_counter]) {
                state_counter += 1;
                if (state_counter == 4) {
                    state = LENGTH;
                    state_counter = 0;
                }
            } else {
                // If for any reason they don't match, just reset the counter
                state_counter = 0;
            }
            break;
        case LENGTH:
            currentMessage.length |= received_byte << (8 * state_counter);
            state_counter += 1;

            if (state_counter == 2) {
                state = ENDPOINT;
                state_counter = 0;
            }
            break;
        case ENDPOINT:
            currentMessage.endpoint |= received_byte << (8 * state_counter);
            state_counter += 1;

            if (state_counter == 2) {
                state = DATA;
                state_counter = 0;
            }
            break;

        case DATA:
            // Just store data to array
            currentMessage.message[currentMessage.message_index] = received_byte;
            currentMessage.message_index += 1;
            state_counter += 1;

            if (state_counter == currentMessage.length) {
                // Do something with the message
                state = POSSIBLE_HEADER;
                state_counter = 0;
            }
            break;
        default:
            state = POSSIBLE_HEADER;
            state_counter = 0;
            break;
        }
    }
}

/*
For Testing
*/
struct sermux_message* SERMUX_spGetCurrentMessage(void) {
    return &currentMessage;
}