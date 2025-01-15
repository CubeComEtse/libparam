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


//Shiny, NEW!
#define CAN_DRIVER_BUF_SIZE 32

typedef struct {
	// There are many CAN functions that take the module, not the MCAN instance itself.
	// So store the struct here instead.
	struct mcan_module can_module;
	
	uint32_t baudrate;
	
	uint32_t gse_address;
	uint32_t gse_address_mask;
	
	uint32_t receivedMessageRead;
	uint32_t receivedMessageWrite;
	struct mcan_rx_element_fifo_0 rx_buffer[CAN_DRIVER_BUF_SIZE];
} ccd_can_t;


void ccd_can_Init(ccd_can_t * pHandle, Mcan * can_device);
void ccd_can_Send_message(void * vHandle, uint32_t header, uint8_t * data, size_t data_len);
void ccd_can_driver_ReceiveCallback(ccd_can_t* pHandle);

#endif /* CAN_DRIVER_H_ */