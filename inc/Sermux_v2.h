/*
 * Sermux_v2.h
 *
 * Created: 2023/05/25 14:23:00
 *  Author: Kolijn
 */ 

/*
 * Sermux_v2.c
 *
 * Created: 2023/05/25 08:20:33
 *  Author: Kolijn
 */ 

#ifndef SERMUX_V2_H_
#define SERMUX_V2_H_

#include <stdint.h>
#include <stdbool.h>

#define EP_V2_I2C_CC			0x30
#define EP_V2_I2C_CC_CHECKSUM	0x31
#define EP_V2_I2C_CC_2			0x32

#define EP_V2_CAN_CC			0x33
#define EP_V2_CAN_CC_2			0x34
#define EP_V2_CAN_DFA			0x35

void SERMUX_V2_vInit(void);
void SERMUX_vV2StateMachine(uint8_t rx_byte);
bool SERMUX_vV2CanReceive(void);
void SERMUX_v2_vProcess(void);
void SERMUX_v2_vSendMessage(uint8_t endpoint, uint8_t id, uint8_t * data, uint8_t length);

#endif /* SERMUX_V2_H_ */