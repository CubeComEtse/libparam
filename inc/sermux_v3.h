/*
 * sermux_v3.h
 *
 * Created: 2024/10/04 08:23:08
 *  Author: Kolijn
 */ 

#ifndef SERMUX_V3_H_
#define SERMUX_V3_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "FreeRTOS.h"
#include "stream_buffer.h"
#include "message_buffer.h"
#include "register_map.h"

#include "crc8.h"

typedef enum {
	V2_WAITING_1,
	V2_WAITING_2,
	V2_STORE_VERSION,
	V2_STORE_LENGTH,
	V2_STORE_DATA,
	V2_STORE_CRC
} v3_states_t;

/* 
 * This struct holds the details of a block of messages that is either being received, 
 * already received, or being sent.
 */
typedef struct {
	uint8_t version;
	uint8_t length;
	uint8_t rx_count;
	uint8_t buffer[200];
	uint8_t crc;
} v2_message_block_t;


typedef mm_response_t (*set_overflow_flag_t)(bool flagValue);

typedef struct {
	uint8_t number;
	MessageBufferHandle_t out;
	MessageBufferHandle_t in;
	set_overflow_flag_t set_overflow_flag;
	
} target_definition_t;


// We should never have this many targets
#define MAX_NUMBER_OF_TARGETS 32

typedef struct {
	// Incoming data from the UART
	StreamBufferHandle_t in_stream;
	StreamBufferHandle_t out_stream;
	
	// Uart handle
	void * uart_handle;
	
	// This is where we store incoming data until the whole thing is received
	v2_message_block_t rx_block;
	v2_message_block_t tx_block;
	
	// State management
	v3_states_t state;
	
	// Targets to send messages to
	target_definition_t targets[MAX_NUMBER_OF_TARGETS];
	size_t num_targets;
	
	crc_module_t crc_checker;
}sermux_v3_t;

void SERMUX_V3_Init(sermux_v3_t * handle);
void SERMUX_V3_AddTarget(sermux_v3_t * handle, const uint8_t number, MessageBufferHandle_t in, MessageBufferHandle_t out, set_overflow_flag_t overflow_flag_function);
void SERMUX_V3_ReceiveTask(void * handle);
void SERMUX_V3_TransmitTask(void * handle);

#endif /* SERMUX_V3_H_ */