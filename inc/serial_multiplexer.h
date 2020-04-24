/**
 * 
*/
#ifndef SERIAL_MULTIPLEXER_H_
#define SERIAL_MULTIPLEXER_H_

#include <stdint.h>
#include <stdbool.h>

/*
 * Any endpoint function should have this format. It will receive the rx_buffer
 * and rx_length, should exchange buffers, then put the response in tx_buffer, 
 * and tx_length. If the message is successfully handled, return true. Else 
 * return false. Note the rx_length and tx_length don't have to match. 0 length
 * return is possible
*/
typedef bool (*endpoint_callback_t)(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);

/**
 * \brief Initialize all settings involved with the Sermux
 */
void SERMUX_vInit(void);

/**
 * \brief Process incoming bytes and check for messages, and execute their callbacks
 *
 * This function should be called regularly, and will check all the bytes 
 * available at that point.
 * \return void
 */
void SERMUX_vProcess(void);

/**
 * \brief Adds a callback function to the array, to call if a message is received on that endpoint
 * 
 * \param endpoint
 * \param func
 * 
 * \return bool   True if successful
 */
bool SERMUX_vRegisterEndpoint(uint16_t endpoint, endpoint_callback_t func);

/**
 * \brief Send a complete message to the PC. Used by async endpoints such as USART
 * 
 * \param endpoint  The endpoint at the PC to send to. Typically this will match the source
 * \param buffer    The buffer to send. Max length of MAX_MESSAGE_LENGTH
 * \param length    The number of bytes to send
 * 
 * \return void
 */
void SERMUX_vTransmit(uint16_t endpoint, uint8_t* buffer, uint16_t length);

#ifdef TEST
struct sermux_message {
    uint16_t length;
    uint16_t endpoint;
    uint8_t message[16];
    uint16_t message_index;
};
void SERMUX_vReceiveByte(void);
void SERMUX_vProcessMessage(void);
void SERMUX_vTxMessage(struct sermux_message* message);
bool SERMUX_vEmptyEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);
#endif

#endif /* SERIAL_MULTIPLEXER_H_ */