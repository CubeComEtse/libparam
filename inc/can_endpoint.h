/*
 * can_endpoint.h
 *
 * Created: 2020/06/26 12:38:39
 *  Author: Kolijn
 */ 

#ifndef CAN_ENDPOINT_H_
#define CAN_ENDPOINT_H_

#include <stdint.h>
#include <stdbool.h>

#include "can_driver.h"

void CAN_vInitEndpoint(uint8_t endpoint, uint8_t can_address, uint8_t can_target, uint8_t mode);
bool CAN_bEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);
void CAN_vProcess(void);
bool CAN_bEndpoint_DFA(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);


bool CAN_bDFAFirmwareEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length);
void CAN_vDFAFirmwareProcess(can_message_t* msg);
#endif /* CAN_ENDPOINT_H_ */