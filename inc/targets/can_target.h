/*
 * can_target.h
 *
 * Created: 2024/10/04 08:11:35
 *  Author: Kolijn
 */ 


#ifndef CAN_TARGET_H_
#define CAN_TARGET_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "FreeRTOS.h"
#include "message_buffer.h"
#include "stream_buffer.h"
#include "semphr.h"

typedef void (*can_send_message_t)(void * handle, uint32_t header, uint8_t * data, size_t data_len);
typedef bool (*can_receive_message_t)(void * handle, uint32_t * header, uint8_t * data, size_t * data_len);

typedef enum {
	CUBECOM_MODE = 0,
	PLAN_S_COMPATIBILITY = 1,
} can_mode_t;

typedef struct {
	// Used to communicate over i2c
	can_send_message_t can_send;
	can_receive_message_t can_receive;
	void * can_handle;
	SemaphoreHandle_t can_semaphore;
	
	// These values used to be set with a register. They are being deprecated
	uint8_t radio_can_address;
	uint8_t our_can_address;
	
	// These buffers are used to talk to the controller. The controller
	// can place messages for us to transmit in incoming_messages, and
	// We will place replies in outgoing_messages
	//
	// Strictly speaking we don't need to have an outgoing messages, but
	// this decouples us from the controller.
	MessageBufferHandle_t incoming_messages;
	MessageBufferHandle_t outgoing_messages;
	
	can_mode_t mode;
	
}can_target_t;

void CANTARGET_Init(can_target_t * handle);
void CANTARGET_TransmitTask(void * handle);
void CANTARGET_ReceiveTask(void * handle);

bool CANTARGET_SetBaud(can_target_t * handle, uint32_t baud);
bool CANTARGET_EnableRetries(can_target_t * handle, bool retries);
bool CANTARGET_SetMode(can_target_t * handle, can_mode_t mode);
bool CANTARGET_vSetAddress(can_target_t * pHandle, uint8_t new_address);

#endif /* CAN_TARGET_H_ */