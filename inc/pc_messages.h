/*
 * pc_messages.h
 *
 * Created: 2024/10/04 08:08:15
 *  Author: Kolijn
 */ 


#ifndef PC_MESSAGES_H_
#define PC_MESSAGES_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


#define EP_V2_GSE				0x20

#define EP_V2_I2C_CC			0x30
#define EP_V2_I2C_CC_CHECKSUM	0x31
#define EP_V2_I2C_CC_2			0x32

#define EP_V2_CAN_CC			0x33
#define EP_V2_CAN_CC_2			0x34
#define EP_V2_CAN_CC_3			0x36

#define EP_V2_I2C_CC_3			0x37

#define EP_V2_UART_CC_2			0x40		

typedef struct{
	uint8_t target;
	bool is_read;
	uint8_t msg_id;
	uint8_t data[16];
	uint8_t data_len;
	//uint8_t msg_type; //i2c doesn't have msg_type
} v2_msg_t;


bool decode_v2_message(v2_msg_t * dest, uint8_t * buffer, size_t buffer_len);
size_t encode_v2_message(uint8_t * dest, v2_msg_t * message);

#endif /* PC_MESSAGES_H_ */