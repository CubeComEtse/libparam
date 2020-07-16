/*
 * can_driver.h
 *
 * Created: 2020/07/02 14:57:20
 *  Author: Kolijn
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include "stdint.h"
#include "stdbool.h"
#include "mcan.h"

#define CAN_STRUCT_MAX_MESSAGE_LENGTH 8
struct xtxCanMessage {
    uint8_t messageType;
    uint8_t registerAddres;
    uint8_t dataLen;
    uint8_t data[CAN_STRUCT_MAX_MESSAGE_LENGTH];
    uint8_t targetAddres;
    uint8_t address;
};

// Endpoint interaction
void CAN_DRIVER_vSendMessage(struct xtxCanMessage message);
bool CAN_DRIVER_bHasMessage(void);
struct xtxCanMessage* CAN_DRIVER_sGetMessage(void);
void CAN_DRIVER_vClearMessage(void) ;

// Callback functions used by the interrupt
void CAN_DRIVER_vMessageInFifo0(struct mcan_rx_element_fifo_0 message);
void CAN_DRIVER_vMessageInFifo1(struct mcan_rx_element_fifo_1 message);

#endif /* CAN_DRIVER_H_ */