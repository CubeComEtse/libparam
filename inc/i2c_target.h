/*
 * i2c_target.h
 *
 * Created: 2024/10/04 08:12:53
 *  Author: Kolijn
 */ 


#ifndef I2C_TARGET_H_
#define I2C_TARGET_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "FreeRTOS.h"
#include "message_buffer.h"

typedef bool (*i2c_write_function_t)(void * handle, const uint8_t dev_addr, const uint8_t * data, const size_t data_len);
typedef bool (*i2c_read_function_t)(void * handle, const uint8_t dev_addr, const uint8_t * addr, const size_t addr_len, uint8_t * read_buffer, size_t read_len);

typedef struct {
	// Used to communicate over i2c
	i2c_read_function_t i2c_read;
	i2c_write_function_t i2c_write;
	void * i2c_handle;
	
	// These buffers are used to talk to the controller. The controller
	// can place messages for us to transmit in incoming_messages, and
	// We will place replies in outgoing_messages
	//
	// Strictly speaking we don't need to have an outgoing messages, but
	// this decouples us from the controller.
	MessageBufferHandle_t incoming_messages;
	MessageBufferHandle_t outgoing_messages;
	
}i2c_target_t;

void I2CTARGET_Init(i2c_target_t * handle);
void I2CTARGET_Task(void * handle);

#endif /* I2C_TARGET_H_ */