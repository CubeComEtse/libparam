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
#include "can_driver.h"
#include "mcan.h"
// Refactor this out
#include "obc_controller_rev_A.h"

#define CAN_DRIVER_BUF_SIZE 8

// Store received CAN messages to be sent back via UART
struct xtxCanMessage receivedMessages[CAN_DRIVER_BUF_SIZE];
static int receivedMessageRead = 0;
static int receivedMessageWrite = 0;


/**
* \brief Send a message
*/
void CAN_DRIVER_vSendMessage(struct xtxCanMessage message)
{
    // Construct a message
    struct mcan_tx_element tx_element;
    mcan_get_tx_buffer_element_defaults(&tx_element);

    tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID(message.messageType  << 24 | message.registerAddres << 16 | message.address  << 8 | message.targetAddres ) | MCAN_TX_ELEMENT_T0_XTD;
    //tx_element.T0.reg = MCAN_TX_ELEMENT_T0_EXTENDED_ID( 0x55AA ) | MCAN_TX_ELEMENT_T0_XTD;
    
    tx_element.T1.bit.DLC = message.dataLen;
    
    uint8_t lenToCopy = min(8, message.dataLen);
    memcpy(tx_element.data, message.data, lenToCopy);

    mcan_set_tx_buffer_element(BSP_psGetCanDriver(), &tx_element, 0);
    mcan_tx_transfer_request(BSP_psGetCanDriver(), 1);
}

bool CAN_DRIVER_bHasMessage(void) {
    return (receivedMessageRead != receivedMessageWrite);
}

/**
* \brief Return pointer to a received message
*
* \return Pointer to message. Don't modify
*/
struct xtxCanMessage* CAN_DRIVER_sGetMessage(void)
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
void CAN_DRIVER_vMessageInFifo0(struct mcan_rx_element_fifo_0 message)
{
    // Todo: Add buffer check

    // Top 4 bits is instruction type
    receivedMessages[receivedMessageWrite].messageType = (((message.R0.bit.ID) >> 24) & 0xF);

    // Next byte is register address
    receivedMessages[receivedMessageWrite].registerAddres = (((message.R0.bit.ID) >> 16) & 0xFF);

    // Don't need the rest - they are CAN addresses

    // Copy the message length and the data
    receivedMessages[receivedMessageWrite].dataLen = message.R1.bit.DLC;
    uint8_t lenToCopy = min(8, receivedMessages[receivedMessageWrite].dataLen);
    memcpy(receivedMessages[receivedMessageWrite].data, message.data, lenToCopy);

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
void CAN_DRIVER_vMessageInFifo1(struct mcan_rx_element_fifo_1 message)
{
    // Todo: Add buffer check

    // Top 4 bits is instruction type
    receivedMessages[receivedMessageWrite].messageType = (((message.R0.bit.ID) >> 24) & 0xF);

    // Next byte is register address
    receivedMessages[receivedMessageWrite].registerAddres = (((message.R0.bit.ID) >> 16) & 0xFF);

    // Don't need the rest - they are CAN addresses

    // Copy the message length and the data
    receivedMessages[receivedMessageWrite].dataLen = message.R1.bit.DLC;
    uint8_t lenToCopy = min(8, receivedMessages[receivedMessageWrite].dataLen);
    memcpy(receivedMessages[receivedMessageWrite].data, message.data, lenToCopy);

    receivedMessageWrite += 1;
}