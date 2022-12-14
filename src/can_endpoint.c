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
static uint8_t u8Mode;

static uint8_t prevDFACanAddress;

/**
* \brief Initialize the CAN Endpoint
*
* \param endpoint The endpoint number
*/
void CAN_vInitEndpoint(uint8_t endpoint, uint8_t can_address, uint8_t can_target, uint8_t mode) {
	u8CanEndpoint = endpoint;
	u8CanAddress = can_address;
	u8CanTarget = can_target;
	u8Mode = mode;
	
	CAN_DRIVER_vSetCanMode(u8Mode);
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
	can_message_t message;
	message.fullheader= 0;

	// Setup struct according to buffer values
	if (u8Mode == CC_CAN_MODE){
		
		switch (rx_buffer[DIR_idx] ) {
		case READ:
			message.fullheader |= telemetry_request << 24;
			message.length = rx_buffer[LEN_idx];
			memset(message.data, 0, min(CAN_STRUCT_MAX_MESSAGE_LENGTH, message.length));
			break;
		case WRITE:
			message.fullheader = telecommand_request;
			message.length = rx_buffer[LEN_idx];
			memcpy(message.data, &rx_buffer[DATA_idx], min(CAN_STRUCT_MAX_MESSAGE_LENGTH, message.length));
			break;
		default:
			message.fullheader = telemetry_request;
			message.length = 0;
			break;
		}
		message.fullheader |= rx_buffer[ADDR_idx] << 16;
		
		message.fullheader |= u8CanAddress << 8;
		message.fullheader |= u8CanTarget;
		

		CAN_DRIVER_vSendMessage(message);
	}
	
	// Setup struct according to buffer values
	if (u8Mode == DFA_CAN_MODE){
		
		message.fullheader |= rx_buffer[DIR_idx] << 24;
		message.fullheader |= rx_buffer[CAN_EXTRA] << 16;
		message.fullheader |= u8CanTarget << 8;
		message.fullheader |= u8CanAddress; 
		
		// Set the register address
		message.data[0] = rx_buffer[ADDR_idx];
		prevDFACanAddress = rx_buffer[ADDR_idx];
		
		// Copy data. If it is a read, length should be 0.
		memcpy(&message.data[1], &rx_buffer[DATA_idx+1], rx_buffer[LEN_idx]);
		
		// Copy the length
		message.length = rx_buffer[LEN_idx];
		
		CAN_DRIVER_vSendMessage(message);
	
	}

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
	can_message_t* currentMessage;
	uint8_t txBuffer[32];

	while (CAN_DRIVER_bHasMessage())
	{
		// Get the latest message
		currentMessage = CAN_DRIVER_sGetMessage();

		if (u8Mode == CC_CAN_MODE){
				
			txBuffer[ADDR_idx] = currentMessage->registerAddres;

			// We only get data to return if it is a telemetry response
			if (currentMessage->messageType == telemetry_response) {
				txBuffer[DIR_idx] = READ;
				txBuffer[LEN_idx] = currentMessage->dataLen;
				memcpy(&txBuffer[DATA_idx], currentMessage->data, currentMessage->dataLen);

				SERMUX_vTransmit(u8CanEndpoint, txBuffer, currentMessage->dataLen + 3);
			}
		}
		
		if (u8Mode == DFA_CAN_MODE)
		{	
			 
			// message.fullheader |= rx_buffer[DIR_idx] << 24;
			// message.fullheader |= rx_buffer[CAN_EXTRA] << 16;
			
			// The DFA protocol doesn't send the address back to us. So just
			// Remember what the address was, and send it back.
			txBuffer[ADDR_idx] = prevDFACanAddress;
			txBuffer[DIR_idx] = (currentMessage->fullheader >> 24) & 0xFF;
			txBuffer[LEN_idx] = 1;
			// Message ID is extracted from the header,
			txBuffer[CAN_EXTRA] = (currentMessage->fullheader >> 16) & 0xFF;
						
			memcpy(&txBuffer[DATA_idx+1], currentMessage->data, currentMessage->length);
			txBuffer[LEN_idx] += currentMessage->length;
			
			
		}
		CAN_DRIVER_vClearMessage();
	}
}
