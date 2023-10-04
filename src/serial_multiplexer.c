#include "serial_multiplexer.h"
#include "serial_multiplexer_conf.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Sermux_v2.h"

/*
 * The HEADERBYTES array configure the series of bytes to look for that defines a new packet 
*/
const uint8_t HEADERBYTES[] = {0xF0, 0x55, 0xAA, 0x0F};

#ifndef TEST
struct sermux_message {
    uint16_t length;
    uint16_t endpoint;
    uint8_t message[MAX_MESSAGE_LENGTH];
    uint16_t message_index;
};
#endif

enum SERMUX_STATES {
    POSSIBLE_HEADER,
    LENGTH,
    ENDPOINT,
    DATA,
};
static enum SERMUX_STATES state;
static uint16_t stateCounter;
static struct sermux_message currentMessage;
static endpoint_callback_t endpointFunctions[MAX_ENDPOINTS];


// Local functions
#ifndef TEST
void SERMUX_vReceiveByte(void);
void SERMUX_vProcessMessage(void);
void SERMUX_vTxMessage(struct sermux_message* message);
void SERMUX_vTxMessageDirect(uint16_t endpoint, uint8_t* buffer, uint16_t length);
bool SERMUX_vEmptyEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);
struct sermux_message* SERMUX_spGetCurrentMessage(void);
#endif

// Check that the correct callback functions are specified
#ifndef SERMUX_u8GetByte
#warning Must configure SERMUX_u8GetByte function
#define SERMUX_u8GetByte() 0
#endif

#ifndef SERMUX_bByteAvailable
#warning: Must configure SERMUX_bByteAvailable function
#define SERMUX_bByteAvailable() true
#endif

// API Functions
void SERMUX_vInit(){
    state = POSSIBLE_HEADER;
    stateCounter = 0;
    currentMessage.length = 0;
    currentMessage.endpoint = 0;
    currentMessage.message_index = 0;

    for (uint8_t i = 0; i < MAX_ENDPOINTS; i++) {
        SERMUX_vRegisterEndpoint(i, SERMUX_vEmptyEndpoint);
    }
}

void SERMUX_vDeRegisterEndpoint(uint16_t endpoint) {
    SERMUX_vRegisterEndpoint(endpoint, SERMUX_vEmptyEndpoint);
}

void SERMUX_vProcess(void)
{
    SERMUX_vReceiveByte();
}

bool SERMUX_vRegisterEndpoint(const uint16_t endpoint, endpoint_callback_t func) {
    if (endpoint >= MAX_ENDPOINTS) {
        return false;
    }

    endpointFunctions[endpoint] = func;

    return true;
}

void SERMUX_vTransmit(uint16_t endpoint, uint8_t* buffer, uint16_t length) {
    
    struct sermux_message message;
    message.endpoint = endpoint;
    message.length = length;
    memcpy(message.message, buffer, length);

    SERMUX_vTxMessage(&message);
}

/*
Write without copying to a buffer
*/
void SERMUX_vTransmitDirect(uint16_t endpoint, uint8_t* buffer, uint16_t length) {
    SERMUX_vTxMessageDirect(endpoint, buffer, length);
}


// Private Functions
void SERMUX_vReceiveByte(void)
{
	// This flag gets set if a message is processed. 
	// This releases the process so that other things can run as well.
	bool processedMessage = false;
    while (SERMUX_bByteAvailable() && !processedMessage && SERMUX_vV2CanReceive()) {
    
        uint8_t received_byte = SERMUX_u8GetByte();
		
		// Send the byte to the 2nd state machine as well.
		// Its messages are processed outside of this loop.
		
		SERMUX_vV2StateMachine(received_byte);
        
        switch (state) {
        case POSSIBLE_HEADER:

            if (received_byte == HEADERBYTES[stateCounter]) {
                stateCounter += 1;
                if (stateCounter == 4) {
                    currentMessage.length = 0;
                    currentMessage.endpoint = 0;
                    state = LENGTH;
                    stateCounter = 0;
                }
            } else {
                // If for any reason they don't match, just reset the counter
                stateCounter = 0;
            }
            break;
        case LENGTH:
            currentMessage.length |= received_byte << (8 * stateCounter);
            stateCounter += 1;

            if (stateCounter == 2) {
                // Validate length value
                if (currentMessage.length > MAX_MESSAGE_LENGTH) {
                    // Reject the message
                    state = POSSIBLE_HEADER;
                    stateCounter = 0;
                } else {
                    // Subtract 2 endpoint bytes
                    currentMessage.length -= 2;
                    state = ENDPOINT;
                    stateCounter = 0;
                }
            }
            break;

        case ENDPOINT:
            currentMessage.endpoint |= received_byte << (8 * stateCounter);
            stateCounter += 1;

            if (stateCounter == 2) {
                if (currentMessage.endpoint >= MAX_ENDPOINTS) {
                    // Reject the message
                    state = POSSIBLE_HEADER;
                    stateCounter = 0;
                } else {
                    state = DATA;
                    stateCounter = 0;
                }
            }
            break;

        case DATA:
            // Just store data to array
            currentMessage.message[stateCounter] = received_byte;
            stateCounter += 1;

            if (stateCounter >= currentMessage.length) {
                // Process message and reset
                SERMUX_vProcessMessage();
				processedMessage = true;
                
                currentMessage.endpoint = 0;
                currentMessage.length = 0;
                stateCounter = 0;

                state = POSSIBLE_HEADER;
            }
            break;
        default:
            state = POSSIBLE_HEADER;
            stateCounter = 0;
            break;
        }
    }
    
}



void SERMUX_vProcessMessage(void) {

    if (currentMessage.endpoint >= MAX_ENDPOINTS) {
        // Error in message
        return;
    }
    struct sermux_message responseMessage;

    // If the function returns true, echo values back
    endpoint_callback_t func = endpointFunctions[currentMessage.endpoint];
    if (func(currentMessage.message, currentMessage.length, responseMessage.message, &responseMessage.length)) {
        
        responseMessage.endpoint = currentMessage.endpoint;

        SERMUX_vTxMessage(&responseMessage);
        
    }
}

void SERMUX_vTxMessage(struct sermux_message* message) {
    // TODO: Check for full tX buffer

    if (message->length > 0) {
        // Send header bytes
        for (uint8_t i = 0; i < 4; i++) {
            SERMUX_vPutByte(HEADERBYTES[i]);
        }

        // Send length
        SERMUX_vPutByte((message->length+2) & 0xFF);
        SERMUX_vPutByte(((message->length+2) >> 8) & 0xFF);

        // Send endpoint
        SERMUX_vPutByte(message->endpoint & 0xFF);
        SERMUX_vPutByte((message->endpoint >> 8) & 0xFF);

        // Send data
        for (uint8_t i = 0; i < message->length; i++) {
            SERMUX_vPutByte(message->message[i]);
        }
    }
}

uint16_t SERMUX_vGetFreeSpace(void){
	return SERMUX_vGetSpaceAvailable();
}

void SERMUX_vTxMessageDirect(uint16_t endpoint, uint8_t* buffer, uint16_t length){
	if (length > 0) {
        // Send header bytes
        for (uint8_t i = 0; i < 4; i++) {
            SERMUX_vPutByte(HEADERBYTES[i]);
        }

        // Send length
        SERMUX_vPutByte((length+2) & 0xFF);
        SERMUX_vPutByte(((length+2) >> 8) & 0xFF);

        // Send endpoint
        SERMUX_vPutByte(endpoint & 0xFF);
        SERMUX_vPutByte((endpoint >> 8) & 0xFF);

        // Send data
        for (uint32_t i = 0; i < length; i++) {
            SERMUX_vPutByte(buffer[i]);
        }
    }
}

bool SERMUX_vEmptyEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length){
    *tx_length = 0;
    return true;
}

/*
For Testing - Get the current message
*/
struct sermux_message* SERMUX_spGetCurrentMessage(void) {
    return &currentMessage;
}