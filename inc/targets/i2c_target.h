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
typedef bool (*i2c_set_baud_function_f)(void * handle, uint32_t new_baud);

typedef struct {
	// Used to communicate over i2c
	i2c_read_function_t i2c_read;
	i2c_write_function_t i2c_write;
	i2c_set_baud_function_f i2c_set_baud;
	void * i2c_handle;
	
	// These buffers are used to talk to the controller. The controller
	// can place messages for us to transmit in incoming_messages, and
	// We will place replies in outgoing_messages
	//
	// Strictly speaking we don't need to have an outgoing messages, but
	// this decouples us from the controller.
	MessageBufferHandle_t incoming_messages;
	MessageBufferHandle_t outgoing_messages;
	
	//Previous versions of the I2C Endpoint had a target bus address that 
	// was set  using a register, and not transferred using the UART 
	// messages. This allows you to still do that.
	uint8_t legacy_address;
	
	// Delay between a write and a read. This was used for ISISpace's
	// non-repeated start config. A value of 0 means normal i2c config, so
	// using a repeated start. Any other value set the delay in ms between 
	// the write an read parts of the transaction.
	uint8_t write_read_delay;
	
	// This sets a delay after any transaction. It was required for the XTX,
	// which could not process that many messages quickly.
	uint8_t tr_delay;
	
	
} i2c_target_t;

void I2CTARGET_Init(i2c_target_t * handle);
void I2CTARGET_Task(void * handle);

bool I2CTARGET_SetBaud(i2c_target_t * handle, uint32_t baud);
void I2CTarget_SetLegacyAddress(i2c_target_t * handle, uint8_t new_address);

#endif /* I2C_TARGET_H_ */