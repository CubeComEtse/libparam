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

#include "FreeRTOS.h"
#include "semphr.h"
#include "message_buffer.h"
#include "mcan.h"

#define MCAN_TXBUFFER_EMPTY(hw) ((hw->MCAN_TXFQS & MCAN_TXFQS_TFGI_Msk >> MCAN_TXFQS_TFGI_Pos) == (hw->MCAN_TXFQS & MCAN_TXFQS_TFQPI_Msk >> MCAN_TXFQS_TFQPI_Pos))


typedef struct {
	// There are many CAN functions that take the module, not the MCAN instance itself.
	// So store the struct here instead.
	struct mcan_module can_module;
	
	SemaphoreHandle_t driver_mutex;
	
	uint32_t baudrate;
	
	uint32_t gse_address;
	uint32_t gse_address_mask;
	
	MessageBufferHandle_t receiveMessageBuffer;
	
	// How long to wait (in ms) for the thread mutex before timing out
	uint32_t ioctl_timeout;
} ccd_can_t;


void ccd_can_Init(ccd_can_t * pHandle, Mcan * can_device);
bool ccd_can_SetAddress(void * vHandle, uint32_t filter, uint32_t mask);
bool ccd_can_SetRetries(void * vHandle, bool enabled);
bool ccd_can_SetBaudRate(void * vHandle, uint32_t baud);
void ccd_can_Send_message(void * vHandle, uint32_t header, uint8_t * data, size_t data_len);
bool ccd_can_Receive_message(void * vHandle, uint32_t * header, uint8_t ** data, size_t * data_len);
void ccd_can_InterruptCallback(ccd_can_t* pHandle);

#endif /* CAN_DRIVER_H_ */