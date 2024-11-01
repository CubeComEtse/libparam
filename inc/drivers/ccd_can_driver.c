/*
 * can_driver.c
 *
 * Created: 2020/07/02 14:57:03
 *  Author: Kolijn
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "bsp.h"
#include "ccd_can_driver.h"
#include "mcan.h"
// Refactor this out
#include "obc_controller_rev_A.h"

#define CAN_DRIVER_BUF_SIZE 32

// Store received CAN messages to be sent back via UART
can_message_t receivedMessages[CAN_DRIVER_BUF_SIZE];
static int receivedMessageRead = 0;
static int receivedMessageWrite = 0;



static can_mode_t canMessageMode = CC_CAN_MODE;
static uint8_t tx_buffer_counter = 0;


void CAN_DRIVER_vSetCanMode(const can_mode_t type){
	canMessageMode = type;
}

/**
* \brief Send a message
*/
void CAN_DRIVER_vSendMessage(can_message_t message)
{
	
    // Construct a message
    struct mcan_tx_element tx_element;
    mcan_get_tx_buffer_element_defaults(&tx_element);
	
	tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID(message.fullheader)| MCAN_TX_ELEMENT_T0_XTD;
	

	/*
	if (canMessageMode == CC_CAN_MODE){
		tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID(message.messageType  << 24 | message.registerAddres << 16 | message.address  << 8 | message.targetAddres ) | MCAN_TX_ELEMENT_T0_XTD;
	}
	if (canMessageMode == DFA_CAN_MODE) {
		tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID(message.messageType  << 26 | CAN_DFA_FRAME_SINGLE << 24 | CAN_DFA_ID_EVID_SYNTIME << 16| message.targetAddres << 8 | message.address) | MCAN_TX_ELEMENT_T0_XTD;
	}*/
    
    tx_element.T1.bit.DLC = message.length;
    
    uint8_t lenToCopy = min(32, message.length);
    memcpy(tx_element.data, message.data, lenToCopy);
	
	// Wait for the TX Buffer to be open
	while (((BSP_psGetCanDriver()->hw->MCAN_TXFQS) & MCAN_TXFQS_TFQF)  > 1);

	// tfqpi should indicate where to write to next, and what bit to set to send?
	// Datasheet 49.5.5.3 Tx FIFO, page 1416
	uint32_t tfqpi = ((BSP_psGetCanDriver()->hw->MCAN_TXFQS & MCAN_TXFQS_TFQPI_Msk) >> MCAN_TXFQS_TFQPI_Pos);
	
    mcan_set_tx_buffer_element(BSP_psGetCanDriver(), &tx_element, tfqpi);
	while (mcan_tx_transfer_request(BSP_psGetCanDriver(), 1 << tfqpi) == ERR_BUSY);  
	 
	tx_buffer_counter += 1;
	if (tx_buffer_counter >= 32)
	{
		tx_buffer_counter = 0;
	}
	
	// We have a weird message issue, where bytes from previous messages show
	// up. This delay checks if sending slower helps
}

bool CAN_DRIVER_bHasMessage(void) {
    return (receivedMessageRead != receivedMessageWrite);
}

/**
* \brief Return pointer to a received message
*
* \return Pointer to message. Don't modify
*/
can_message_t* CAN_DRIVER_sGetMessage(void)
{
    return &receivedMessages[receivedMessageRead];
}

/**
 * \brief Clears a message out of the buffer, if there is one
 */
void CAN_DRIVER_vClearMessage(void) {
    if (receivedMessageRead != receivedMessageWrite){
        receivedMessageRead = (receivedMessageRead+1) % CAN_DRIVER_BUF_SIZE;
    }
}

/**
 * \brief Callback function from interrupt. Parse the MCAN module can message
 *        into a xtxCanMessage and add to the buffer, so that the message can
 *        be processed outside of the interrupt
 *
 * \param message       The message received from the MCAN module
 *
 * \return none
 */
void CAN_DRIVER_vMessageInFifo0(struct mcan_rx_element_fifo_0 can_msg)
{
    // Todo: Add buffer check
	/*
	if (canMessageMode == CC_CAN_MODE)
	{
		// Top 4 bits is instruction type
		receivedMessages[receivedMessageWrite].messageType = (((message.R0.bit.ID) >> 24) & 0x1F);

		// Next byte is register address
		receivedMessages[receivedMessageWrite].registerAddres = (((message.R0.bit.ID) >> 16) & 0xFF);
	}
	if (canMessageMode == DFA_CAN_MODE)
	{
		// Top 3 bits is instruction type
		receivedMessages[receivedMessageWrite].messageType = (((message.R0.bit.ID) >> 26) & 0x7);
		
		// Other bits are ignored for now
	}*/
	
	receivedMessages[receivedMessageWrite].fullheader = can_msg.R0.reg;

    // Copy the message length and the data
    receivedMessages[receivedMessageWrite].length = can_msg.R1.bit.DLC;
    uint8_t lenToCopy = min(8, receivedMessages[receivedMessageWrite].length);
    memcpy(receivedMessages[receivedMessageWrite].data, can_msg.data, lenToCopy);

    receivedMessageWrite = (receivedMessageWrite + 1) % CAN_DRIVER_BUF_SIZE;
}

/**
 * \brief Callback function from interrupt. Parse the MCAN module can message
 *        into a xtxCanMessage and add to the buffer, so that the message can
 *        be processed outside of the interrupt
 *
 * \param message       The message received from the MCAN module
 *
 * \return none
 */
void CAN_DRIVER_vMessageInFifo1(struct mcan_rx_element_fifo_1 can_msg)
{
	/*
    // Todo: Add buffer check
    if (canMessageMode == CC_CAN_MODE)
    {
	    // Top 4 bits is instruction type
	    receivedMessages[receivedMessageWrite].messageType = (((message.R0.bit.ID) >> 24) & 0x1F);

	    // Next byte is register address
	    receivedMessages[receivedMessageWrite].registerAddres = (((message.R0.bit.ID) >> 16) & 0xFF);
    }
    if (canMessageMode == DFA_CAN_MODE)
    {
	    // Top 3 bits is instruction type
	    receivedMessages[receivedMessageWrite].messageType = (((message.R0.bit.ID) >> 26) & 0x7);
	    
	    // Other bits are ignored for now
    }

    // Copy the message length and the data
    receivedMessages[receivedMessageWrite].dataLen = message.R1.bit.DLC;
    uint8_t lenToCopy = min(8, receivedMessages[receivedMessageWrite].dataLen);
    memcpy(receivedMessages[receivedMessageWrite].data, message.data, lenToCopy);

    receivedMessageWrite += 1;*/
	
	receivedMessages[receivedMessageWrite].fullheader = can_msg.R0.reg;

	// Copy the message length and the data
	receivedMessages[receivedMessageWrite].length = can_msg.R1.bit.DLC;
	uint8_t lenToCopy = min(8, receivedMessages[receivedMessageWrite].length);
	memcpy(receivedMessages[receivedMessageWrite].data, can_msg.data, lenToCopy);

	receivedMessageWrite = (receivedMessageWrite + 1) % CAN_DRIVER_BUF_SIZE;
}


void ccd_can_Init(void * handle)
{
	
}

void ccd_can_Send_message(void * handle, uint32_t header, uint8_t * data, size_t data_len)
{
	//Todo:
}