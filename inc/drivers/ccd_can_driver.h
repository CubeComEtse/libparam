/*
 * can_driver.h
 *
 * Created: 2020/07/02 14:57:20
 *  Author: Kolijn
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

#include <stdint.h>
#include <stdbool.h>

#include "mcan.h"

#include "FreeRTOS.h"
#include "message_buffer.h"

typedef struct {
	// There are many CAN functions that take the module, not the MCAN instance itself.
	// So store the struct here instead.
	struct mcan_module can_module;
	
	uint32_t baudrate;
	
	uint32_t gse_address;
	uint32_t gse_address_mask;
	
	MessageBufferHandle_t receiveMessageBuffer;
} ccd_can_t;


void ccd_can_Init(ccd_can_t * pHandle, Mcan * can_device);
void ccd_can_SetAddress(void * vHandle, uint32_t filter, uint32_t mask);
void ccd_can_SetRetries(void * vHandle, bool enabled);
bool ccd_can_SetBaudRate(void * vHandle, uint32_t baud);
void ccd_can_Send_message(void * vHandle, uint32_t header, uint8_t * data, size_t data_len);
bool ccd_can_Receive_message(void * vHandle, uint32_t * header, uint8_t * data, size_t * data_len);
void ccd_can_ReceiveCallback(ccd_can_t* pHandle);

#endif /* CAN_DRIVER_H_ */