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
#include "std_message.h"

enum XTX_CAN_MESSAGE_TYPES {
    telecommand_request = 0x01,
    telecommand_response = 0x02,
    telecommand_not_ack = 0x03,
    telemetry_request = 0x04,
    telemetry_response = 0x05,
    telemetry_not_ack = 0x06
};

static uint8_t u8CanEndpoint;
static uint8_t u8CanAddress;
static uint8_t u8CanTarget;

/**
 * \brief Initialize the CAN Endpoint
 * 
 * \param endpoint The endpoint number 
 */
void CAN_vInitEndpoint(uint8_t endpoint, uint8_t can_address, uint8_t can_target) {
    u8CanEndpoint = endpoint;
    u8CanAddress = can_address;
    u8CanTarget = can_target;
}

/**
 * \brief Process a message from the UART.
 *
 * This function mirrors the I2C_bEndpoint and CONFIG_bEndpoint functions
 *
 * First byte (ADDR_idx) is the Address of the register to read/write to. 
 * Second byte (DIR_idx) is the direction, as specified by enum RWDirection
 * Third byte is the length of the data. (LEN_idx) The CAN endpoint does not 
 * use this, since the device knows how many bytes to send and this is encoded
 * in the CAN message.
 * 
 * \param rx_buffer Buffer of received data
 * \param rx_length Length of the data
 * \param tx_buffer Buffer to retransmit. Unused
 * \param tx_length Length to retransmit. Unused
 * 
 * \return bool True to retransmit the buffers. Always returns False
 */
bool CAN_bEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length)
{
    struct xtxCanMessage message;

    // Setup struct according to buffer values
    switch (rx_buffer[DIR_idx] ) {
        case READ:
			message.messageType = telemetry_request;
			message.dataLen = rx_buffer[LEN_idx];
			memset(message.data, 0, min(CAN_STRUCT_MAX_MESSAGE_LENGTH, message.dataLen));
			break;
        case WRITE:
			message.messageType = telecommand_request;
			message.dataLen = rx_buffer[LEN_idx];
			memcpy(message.data, &rx_buffer[DATA_idx], min(CAN_STRUCT_MAX_MESSAGE_LENGTH, message.dataLen));
			break;
        default:
			message.messageType = telemetry_request;
			message.dataLen = 0;
			break;
    }
    message.registerAddres = rx_buffer[ADDR_idx];
    
    message.address = u8CanAddress;
    message.targetAddres = u8CanTarget;

    CAN_DRIVER_vSendMessage(message);

    return false;
}

/**
 * \brief Process incoming CAN messages. Since this happens independently from
 *  transmit this function should be called regularly.
 * 
 * \param 
 * 
 * \return void
 */
void CAN_vProcess(void) {
    struct xtxCanMessage* currentMessage;
    uint8_t txBuffer[32];

    while (CAN_DRIVER_bHasMessage()) {
        // Get the latest message
        currentMessage = CAN_DRIVER_sGetMessage();

        txBuffer[ADDR_idx] = currentMessage->registerAddres;

        // We only get data to return if it is a telemetry response
        if (currentMessage->messageType == telemetry_response) {
            txBuffer[DIR_idx] = READ;
            txBuffer[LEN_idx] = currentMessage->dataLen;
            memcpy(&txBuffer[DATA_idx], currentMessage->data, currentMessage->dataLen);

            SERMUX_vTransmit(u8CanEndpoint, txBuffer, currentMessage->dataLen + 3);
        }
        CAN_DRIVER_vClearMessage();
    }
}
