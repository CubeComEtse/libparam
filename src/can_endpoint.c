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
#include "endpoints.h"
#include "serial_multiplexer.h"
#include "std_message.h"
#include "Sermux_v2.h"
#include "delay.h"
#include "tmr.h"
#include "bsp.h"

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



typedef enum
{
	idle = 0,
	initialize_read,
	setup_for_page_read,
	send_read_command,
	wait_for_read_ack,
	send_read_segment_command,
	wait_for_data,
	
	timer_for_uart,
	wait_for_uart_empty,
	page_done,

} dfa_sw_states_t;

static dfa_sw_states_t dfa_sw_state;
static uint8_t dfa_fw_buffer[515];
static uint16_t startPage; // Also functions as current page
static uint16_t endPage;
static uint16_t currentSegment;
static uint16_t writePos;
static uint32_t remaining_bytes = 0;
// The first transfer in a segment has an address in it as well, this flag
// tracks when it needs to be removed.
static bool firstTransferDone = false;

static tmr_t can_timeout = {0};



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
		
		// This indicates the message is a read. In that case, send the 
		// address we want to read from as the first data byte
		if (rx_buffer[CAN_EXTRA] == 0xFF){
			message.fullheader |= rx_buffer[CAN_EXTRA] << 16;
			
			// Set the register address
			message.data[0] = rx_buffer[ADDR_idx];
			
			prevDFACanAddress = rx_buffer[ADDR_idx];
			
			// Copy data. If it is a read, length should be 0.
			memcpy(&message.data[1], &rx_buffer[DATA_idx+1], rx_buffer[LEN_idx]);
			
			// Copy the length
			message.length = rx_buffer[LEN_idx];
		}
		else{
			// This is a write.
			message.fullheader |= rx_buffer[ADDR_idx] << 16;
			
			memcpy(message.data, &rx_buffer[DATA_idx+1], rx_buffer[LEN_idx]);
			
			// Copy the length
			message.length = rx_buffer[LEN_idx]-1;
		}
		
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

	if (CAN_DRIVER_bHasMessage())
	{
		// Get the latest message
		currentMessage = CAN_DRIVER_sGetMessage();
		ioport_set_pin_level(TEST_PIN,1);
		
		if (dfa_sw_state != idle){
			CAN_vDFAFirmwareProcess(currentMessage);
		}
		else
		{
			if (u8Mode == CC_CAN_MODE)
			{
				txBuffer[ADDR_idx] = (currentMessage->fullheader >> 16 ) & 0xFF;

				// We only get data to return if it is a telemetry response
				if ((currentMessage->fullheader >> 24 ) & (0xFF == telemetry_response)) {
					txBuffer[DIR_idx] = READ;
					txBuffer[LEN_idx] = currentMessage->length;
					memcpy(&txBuffer[DATA_idx], currentMessage->data, currentMessage->length);

					SERMUX_vTransmit(u8CanEndpoint, txBuffer, currentMessage->length + 3);
				}
			}
		
			if (u8Mode == DFA_CAN_MODE)
			{	
			 
				// message.fullheader |= rx_buffer[DIR_idx] << 24;
				// message.fullheader |= rx_buffer[CAN_EXTRA] << 16;
			
				// The DFA protocol doesn't send the address back to us. So just
				// Remember what the address was, and send it back.
				txBuffer[ADDR_idx] = (currentMessage->fullheader >> 16) & 0xFF;
				txBuffer[DIR_idx] = (currentMessage->fullheader >> 24) & 0xFF;
				txBuffer[LEN_idx] = 1;
				// Message ID is extracted from the header,
				txBuffer[CAN_EXTRA] = (currentMessage->fullheader >> 16) & 0xFF;
						
				memcpy(&txBuffer[DATA_idx+1], currentMessage->data, currentMessage->length);
				txBuffer[LEN_idx] += currentMessage->length;
			
				// The added length here is 4. 3 for the normal header, 1 for the address
				SERMUX_vTransmit(u8CanEndpoint, txBuffer, currentMessage->length + 4);
			
			}
			if (u8Mode == CC_CAN_2_MODE){
				uint8_t id = (currentMessage->fullheader & 0xFF0000) >> 16;
				// MsgType
				txBuffer[0] = (currentMessage->fullheader & 0x1F000000) >> 24;
				txBuffer[1] = currentMessage->length;
				memcpy(&txBuffer[2], currentMessage->data, currentMessage->length);
				SERMUX_v2_vSendMessage(u8CanEndpoint, id, txBuffer, currentMessage->length + 2);
			}
		}
		CAN_DRIVER_vClearMessage();
		ioport_set_pin_level(TEST_PIN, 0);
	}
}

bool CAN_bDFAFirmwareEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length)
{
	if (rx_buffer[DIR_idx] == WRITE){
		if (rx_buffer[ADDR_idx] == 0x01 && dfa_sw_state == idle){
			startPage = ((int) rx_buffer[DATA_idx]) |  ((int) (rx_buffer[DATA_idx+1]<<8) & 0xFF);
			endPage = ((int) rx_buffer[DATA_idx+2]) |  ((int) (rx_buffer[DATA_idx+3]<<8) & 0xFF);
			dfa_sw_state = initialize_read;
		}
	}
	
	return false;
}

/*
 * This endpoint is special. It is used only for DFA firmware updates, to interface with their HDRTX software
 * 
 * Reading an image:
 *   This endpoint will receive the instruction to read an image from one 
 *   address, to another. It will then start at that address, reading each 
 *   FLASH_PAGE in between. It will automatically transfer all this data to the PC
 
 16 MB, 512 - sized pages. Addr 0 - 32768. From & To addresses will be a uint16.
*/

void CAN_vDFAFirmwareProcess(can_message_t* msg)
{
	can_message_t message;
	
	switch (dfa_sw_state){
		case idle:
		break;
		
		case initialize_read:
			dfa_sw_state = setup_for_page_read;
		break;
		
		case setup_for_page_read:
			currentSegment = 0;
			writePos = 3;
			remaining_bytes =0;
			dfa_sw_state = send_read_command;
		break;
		
		case send_read_command:
			// Build up a message to read the current page into the buff.
			message.fullheader = 0x0C << 24;
			message.fullheader |= 196 << 16; // Hard coded command for FlashPageToBuf
			message.fullheader |= u8CanTarget << 8;
			message.fullheader |= u8CanAddress;
			message.data[0] = startPage & 0xFF;
			message.data[1] = (startPage>>8) & 0xFF;
			message.length =2;
			CAN_DRIVER_vSendMessage(message);
			dfa_sw_state = wait_for_read_ack;
			
			TMR_vInit(&can_timeout, BSP_u16TmrGetTick, 1);
			TMR_vStart(&can_timeout, 100);
		break;
		
		case wait_for_read_ack:
			// Check for timeout
			if (TMR_bExpired(&can_timeout)) {
				dfa_sw_state = idle;
				break;
			}
			
			//Check if we received a message
			if (msg != NULL)
			{
				uint8_t id = (msg->fullheader >> 24) & 0x1F;
				uint8_t addr = (msg->fullheader >> 16) & 0xFF;
				// Single frame message, TC response, correct address & response == 0
				if ((id == 0x04) && (addr == 196) && (msg->data[0] == 0x00))
				{
					dfa_sw_state = send_read_segment_command;
				}
			}
		break;
		
		case send_read_segment_command:
			// Build up a message to read the current page into the buff.
			message.fullheader = 0x0C << 24;
			message.fullheader |= 203 << 16; // Hard coded command for GetPageBufData
			message.fullheader |= u8CanTarget << 8;
			message.fullheader |= u8CanAddress;
			message.data[0] = currentSegment;
			message.length =1;
			
			CAN_DRIVER_vSendMessage(message);
			dfa_sw_state = wait_for_data;
					
			TMR_vInit(&can_timeout, BSP_u16TmrGetTick, 1);
			TMR_vStart(&can_timeout, 100);
		break;
		
		case wait_for_data:
			// Check for timeout
			if (TMR_bExpired(&can_timeout)) {
				dfa_sw_state = idle;
				break;
			}
			
			if (msg != NULL)
			{
				uint8_t id = (msg->fullheader >> 24) & 0x1F;
				uint8_t addr = (msg->fullheader >> 16) & 0xFF;
				
				// MultiFrame Control message, TC response
				// This should be the first response we get
				if ((id == 0x06) && (addr == 203)){
					// Use data field to get the expected number of bytes
					remaining_bytes = (uint32_t) msg->data[3];
					
					firstTransferDone = false;
				}
				
				// MultiFrame Data message, TC response
				if ((id == 0x07) && (addr == 203))
				{
					// If this is the first transfer, the first 2 bytes will be the page offset.
					if (!firstTransferDone) {
						firstTransferDone = true;
						memcpy(&dfa_fw_buffer[writePos], &msg->data[2], msg->length-2);
						writePos += (msg->length-2);
					}
					else{
						memcpy(&dfa_fw_buffer[writePos], msg->data, msg->length);
						writePos += (msg->length);
					}
					remaining_bytes -= msg->length;
				}
			
				if (remaining_bytes <= 0)
				{
					currentSegment += 1;
						
					if (currentSegment == 16){
						// All done, next state
						dfa_sw_state = timer_for_uart;
					}
					else{
						dfa_sw_state = send_read_segment_command;
					}
				}
			}
		break;
		
		case timer_for_uart:
			// Todo: Wait for UART buffer to be empty
			TMR_vInit(&can_timeout, BSP_u16TmrGetTick, 1);
			TMR_vStart(&can_timeout, 500);
			dfa_sw_state = wait_for_uart_empty;
			
		break;
		
		case wait_for_uart_empty:
			// Check for timeout
			if (TMR_bExpired(&can_timeout)) {
				dfa_sw_state = idle;
				break;
			}
			else
			{
				if (SERMUX_vGetFreeSpace() > 540){
					dfa_sw_state = page_done;
				}
			}
		break;
		
		case page_done:
			// Send this page to the UART
			// This can only be sent in max of 256 bytes per. So send 250 bytes at a time
			// and split into 3 messages
			dfa_fw_buffer[DIR_idx] = READ;
			dfa_fw_buffer[LEN_idx] = 250;
			dfa_fw_buffer[ADDR_idx] = 0x02;
			SERMUX_vTransmitDirect(CAN_ENDPOINT_DFA_FW, dfa_fw_buffer, 250+3);
			
			dfa_fw_buffer[250+DIR_idx] = READ;
			dfa_fw_buffer[250+LEN_idx] = 250;
			dfa_fw_buffer[250+ADDR_idx] = 0x02;
			SERMUX_vTransmitDirect(CAN_ENDPOINT_DFA_FW, &dfa_fw_buffer[250], 250+3);
			
			dfa_fw_buffer[500+DIR_idx] = READ;
			dfa_fw_buffer[500+LEN_idx] = 12;
			dfa_fw_buffer[500+ADDR_idx] = 0x02;
			SERMUX_vTransmitDirect(CAN_ENDPOINT_DFA_FW, &dfa_fw_buffer[500], 12+3);
			
			startPage += 1;
			if (startPage == endPage){
				dfa_sw_state = idle;
				// Send a message on the other Endpoint, to indicate we are done
				
				uint8_t buff[8];
				buff[DIR_idx] = READ;
				buff[LEN_idx] = 4;
				buff[ADDR_idx] = 0x01;
				buff[DATA_idx] = endPage & 0xFF;
				buff[DATA_idx+1] = (endPage >> 8) & 0xFF;
				buff[DATA_idx+2] = endPage & 0xFF;
				buff[DATA_idx+3] = (endPage >> 8) & 0xFF;
				
				SERMUX_vTransmit(CAN_ENDPOINT_DFA_FW, buff, 7);
			}
			else{
				dfa_sw_state = setup_for_page_read;
			}
		break;
	}
}
	

void ep_can_cc2(const uint8_t target, const bool dirBit, const uint8_t msgId, const uint8_t * message, const uint8_t length)
{
	can_message_t msg;
	msg.fullheader = ((message[0] << 24) | (msgId << 16) | (u8CanAddress << 8) | (u8CanTarget << 0));
	msg.length = message[1];
	memcpy(msg.data, &message[2], msg.length);
	
	CAN_DRIVER_vSendMessage(msg);
	
	// Demo sending a message back
	/*
	uint8_t data[8];
	data[0] = 0x7; // Unknown msg type
	data[1] = 0x6; // Length
	data[2] =message[2];
	data[3] =message[3];
	data[4] =2;
	data[5] =3;
	data[6] =4;
	data[7] =5;
	SERMUX_v2_vSendMessage(u8CanEndpoint, msgId, data, 8);*/
}

