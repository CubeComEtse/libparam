/**
 * 
*/
#ifndef SERIAL_MULTIPLEXER_H_
#define SERIAL_MULTIPLEXER_H_

#include <stdint.h>

/**
 * \brief Process incoming bytes and check for messages
 *
 * This function should be called regularly, and will check all the bytes 
 * available at that point.
 * \return void
 */
void SERMUX_vProcess(void);

#ifdef TEST
struct sermux_message {
    uint16_t length;
    uint16_t endpoint;
    uint8_t message[16];
    uint16_t message_index;
};
struct sermux_message* SERMUX_spGetCurrentMessage(void);
#endif

#endif /* SERIAL_MULTIPLEXER_H_ */