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

// The DFA max length is 
#define CAN_STRUCT_MAX_MESSAGE_LENGTH 16


/*
struct ccCanMessage {
    uint8_t messageType;
	// When sending DFA CAN messages this field is unused
    uint8_t registerAddres;
    uint8_t dataLen;
    uint8_t data[CAN_STRUCT_MAX_MESSAGE_LENGTH];
    uint8_t targetAddres; // DFA calls this DestAddress
    uint8_t address; // DFA calls this SRCAddress
};

typedef union {
	uint32_t fullField;
	struct {
		uint8_t srcAddress;
		uint8_t dstAddress;
		uint8_t id;
		union {
			uint8_t messageType;
			struct {
				uint8_t frmType:2;
				uint8_t msgType:3;
				uint8_t unused:3;
		} __attribute__((__packed__));
	};
};
} __attribute__((__packed__)) DFCAN_IdentifierField_t;

struct xtxCanMessage {
	union {
		struct ccCanMessage;
		DFCAN_IdentifierField_t dfaCanMessage;
	};
};*/

typedef struct {
	union  {
		uint32_t fullheader;
		};
	uint8_t data[64];
	uint32_t length;
} can_message_t;

#define CAN_DFA_FRAME_SINGLE 0x00
#define CAN_DFA_ID_EVID_SYNTIME 0x00

typedef enum {
	CC_CAN_MODE = 0,
	DFA_CAN_MODE = 1,
	CC_CAN_2_MODE = 2,
} can_mode_t;


void CAN_DRIVER_vSetCanMode(const can_mode_t type);
// Endpoint interaction
void CAN_DRIVER_vSendMessage(can_message_t message);
bool CAN_DRIVER_bHasMessage(void);
can_message_t* CAN_DRIVER_sGetMessage(void);
void CAN_DRIVER_vClearMessage(void) ;

// Callback functions used by the interrupt
void CAN_DRIVER_vMessageInFifo0(struct mcan_rx_element_fifo_0 can_msg);
void CAN_DRIVER_vMessageInFifo1(struct mcan_rx_element_fifo_1 can_msg);

#endif /* CAN_DRIVER_H_ */