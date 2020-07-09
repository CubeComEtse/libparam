/*
 * can_endpoint.c
 *
 * Created: 2020/06/26 12:38:29
 *  Author: Kolijn
 */ 

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "can_endpoint.h"
#include "can_driver.h"
#include "serial_multiplexer.h"

// This has to match the VS studio program
enum RWDirection
{
    CAN_READ = 0,
    CAN_WRITE = 1
};

#define ADDR_idx 0
#define DIR_idx 1
#define LEN_idx 2
#define DATA_idx 3

enum XTX_CAN_MESSAGE_TYPES {
    telecommand_request = 0x01,
    telecommand_response = 0x02,
    telecommand_not_ack = 0x03,
    telemetry_request = 0x04,
    telemetry_response = 0x05,
    telemetry_not_ack = 0x06
};

void can_endpoint_init(void) {

}

void can_endpoint_process(void) {
    struct xtxCanMessage* currentMessage;
    uint8_t txBuffer[32];

    while (CAN_DRIVER_bHasMessage()) {
        currentMessage = CAN_DRIVER_sGetMessage();

        // Copy message details to sermux-capable message

        txBuffer[ADDR_idx] = currentMessage->registerAddres;

        // We only get data to return if it is a telemetry respons
        if (currentMessage->messageType == telemetry_response) {
            txBuffer[DIR_idx] = CAN_READ;
                    
            txBuffer[LEN_idx] = currentMessage->dataLen;
        
            // Copy the rest of the data here
            memcpy(&txBuffer[DATA_idx], currentMessage->data, currentMessage->dataLen);

            // TODO: This 3 needs to live elsewhere - should be CAN_ENDPOINT
            SERMUX_vTransmit(3, txBuffer, currentMessage->dataLen + 3);
        }

        CAN_DRIVER_vClearMessage();
    }
}


bool can_endpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length)
{
    // Copy the receives sermux message to a CAN message
    struct xtxCanMessage message;

    // Check what direction was asked for
    switch (rx_buffer[DIR_idx] ) {
        case CAN_READ:
        message.messageType = telemetry_request;
        break;
        case CAN_WRITE:
        message.messageType = telecommand_request;
        break;
        default:
        message.messageType = telemetry_request;
        break;
    }

    // Set Register
    message.registerAddres = rx_buffer[ADDR_idx];

    // Add data write here, when we do writes
    message.dataLen = rx_buffer[LEN_idx];
    memcpy(message.data, &rx_buffer[DATA_idx], min(CAN_STRUCT_MAX_MESSAGE_LENGTH, message.dataLen));


    CAN_DRIVER_vSendMessage(message);

    // Nothing to send back
    return false;
}

