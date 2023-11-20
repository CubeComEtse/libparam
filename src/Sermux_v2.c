/*
 * Sermux_v2.c
 *
 * Created: 2023/05/25 08:20:33
 *  Author: Kolijn
 */ 

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "Sermux_v2.h"
#include "can_endpoint.h"
#include "i2c_endpoint.h"
#include "serial_multiplexer_conf.h"

/*
 * V2 swaps receive buffers while it processes received messages 
*/

typedef enum {
	V2_WAITING_1,
	V2_WAITING_2,
	V2_STORE_VERSION,
	V2_STORE_LENGTH,
	V2_STORE_DATA,
	V2_STORE_CRC
} v2_states_t;

static v2_states_t state;

/* This struct holds the details of a block of messages that is either being received, 
 * already received, or being sent. The code maintains two instances of these structs
 * and they are swapped around as required.
 */
typedef struct {
	uint8_t version;
	uint8_t length;
	uint8_t rx_count;
	uint8_t buffer[200];
	uint8_t crc;
} v2_message_block_t;

/* Contains the data for RX and TX*/
static v2_message_block_t rx_block_a;
static v2_message_block_t rx_block_b;
static v2_message_block_t tx_block_a;

/* Points to the active blocks */
static v2_message_block_t * current_rx_block;
static v2_message_block_t * current_msg_block;

/* Indicates the msg block can be processed */
static bool v2_rx_buffer_ready;
static bool v2_tx_buffer_ready;

/* We return control in between processing messages, this tracks which message we are busy with*/
static uint8_t curr_msg_index = 0;


#define EP_V2_I2C_CC			0x30
#define EP_V2_I2C_CC_CHECKSUM	0x31
#define EP_V2_I2C_CC_2			0x32

#define EP_V2_CAN_CC			0x33
#define EP_V2_CAN_CC_2			0x34
#define EP_V2_CAN_DFA			0x35

void SERMUX_V2_vInit(void){
	current_rx_block  = &rx_block_a;
	current_msg_block = &rx_block_b;
	v2_rx_buffer_ready = false;
	state = V2_WAITING_1;
	
	tx_block_a.rx_count = 0;
}

/*
 V2 Messages run as their own separate state machines
 
*/
void SERMUX_vV2StateMachine(uint8_t rx_byte){
	switch (state){
		case V2_WAITING_1:
			if (rx_byte == 0xC3) {
				state = V2_WAITING_2;
			}
			break;
		case V2_WAITING_2:
			if (rx_byte == 0xA9) {
				state = V2_STORE_VERSION;
			}
			else{
				state = V2_WAITING_1;
			}
			break;
			
		case V2_STORE_VERSION:
			current_rx_block->version = rx_byte;
			state = V2_STORE_LENGTH;
			break;
			
		case V2_STORE_LENGTH:
			current_rx_block->length = rx_byte;
			current_rx_block->rx_count = 0;
			state = V2_STORE_DATA;
			break;
			
		case V2_STORE_DATA:
			current_rx_block->buffer[current_rx_block->rx_count] = rx_byte;
			current_rx_block->rx_count+= 1;
			if (current_rx_block->rx_count == current_rx_block->length){
				state = V2_STORE_CRC;
			}
			break;
		case V2_STORE_CRC:
			current_rx_block->crc = rx_byte;
			// Todo: Check the CRC!
			
			// Swap the buffers
			v2_message_block_t * temp;
			temp = current_rx_block;
			current_rx_block = current_msg_block;
			current_msg_block = temp;
			
			v2_rx_buffer_ready = true;
			state = V2_WAITING_1;
			break;
		default:
			state = V2_WAITING_1;
			break;
	}
	
}

/*
Returns true if we can receive a byte - there is a buffer that will accept it.
*/
bool SERMUX_vV2CanReceive(void)
{
	// If the RX buffer is empty, we can still receive.
	if (!v2_rx_buffer_ready){
		return true;
	}
	else{
		// This means the other buffer is still full (messages are still being processed)
		// Check if the (currently receiving) buffer is in its data section, and how far it is from its supposed length
		// About 10 bytes before that, stop.
		if (state == V2_STORE_DATA && (current_rx_block->length-current_rx_block->rx_count) < 10)
		{
			return false;
		}
	}
	
	return true;
}

/*
 * This function is called in an update loop. It checks if new messages are received and 
 * processes them.
*/
void SERMUX_v2_vProcess(void){
	
	if (v2_rx_buffer_ready){
		
		ioport_set_pin_level(TEST_PIN_0,1);
		// Process a messages
		uint8_t msg_len = current_msg_block->buffer[curr_msg_index +0];
		uint8_t msg_target = current_msg_block->buffer[curr_msg_index +1];
		bool dirBit = ((msg_target & 0x80) > 0);
		msg_target = msg_target & 0x7F;
		uint8_t msg_id = current_msg_block->buffer[curr_msg_index + 2];
			
			
		// This is a safety check. If this is true, the index will never be 
		// incremented, and we'll be stuck. So just abandon the block.
		// If this is true, it probably means previous messages  were malformed.
		if (msg_len == 0){
			curr_msg_index = current_msg_block->length;
		}
		else 
		{
			switch(msg_target & 0x7F)
			{
				case EP_V2_I2C_CC:
					break;
				case EP_V2_I2C_CC_CHECKSUM:
					break;
				case EP_V2_I2C_CC_2:
					ep_i2c_cc2(msg_target, dirBit, msg_id, &current_msg_block->buffer[curr_msg_index + 3], msg_len - 3);
					break;
				case EP_V2_CAN_CC:
					break;
				case EP_V2_CAN_CC_2:
					ep_can_cc2(msg_target, dirBit, msg_id, &current_msg_block->buffer[curr_msg_index + 3], msg_len - 3);
					break;
				case EP_V2_CAN_DFA:
					break;
			}
		}
		// Increment by the message count
		curr_msg_index += msg_len;
		
		if (curr_msg_index >= current_msg_block->length )
		{
			v2_rx_buffer_ready = false;
			curr_msg_index = 0;
		}
		ioport_set_pin_level(TEST_PIN_0,0);
	}	
	if (v2_tx_buffer_ready){
		// Send header
		SERMUX_vPutByte(0xC3);
		SERMUX_vPutByte(0xA9);
		
		// Send version
		SERMUX_vPutByte(0x02);
		
		//Send length
		SERMUX_vPutByte(tx_block_a.rx_count);
		
		for (int i = 0; i < tx_block_a.rx_count; i++){
			SERMUX_vPutByte(tx_block_a.buffer[i]);
		}
		
		// Todo Send CRC
		SERMUX_vPutByte(0xFF);
		
		v2_tx_buffer_ready = false;
		tx_block_a.rx_count = 0;
	}
}

void SERMUX_v2_vSendMessage(uint8_t endpoint, uint8_t id, uint8_t * data, uint8_t length){
	
	// Set the length
	tx_block_a.buffer[tx_block_a.rx_count] = length + 3;
	// Set the target/EP
	tx_block_a.buffer[tx_block_a.rx_count+1] = endpoint;
	// Set the message ID
	tx_block_a.buffer[tx_block_a.rx_count+2] = id;
	
	memcpy(&tx_block_a.buffer[tx_block_a.rx_count+3], data, length);
	
	tx_block_a.rx_count += length + 3;
	
	v2_tx_buffer_ready = true;
}