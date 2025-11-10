/*
 * pc_messages.c
 *
 * Created: 2024/10/04 08:08:03
 *  Author: Kolijn
 */ 

#include "pc_messages.h"

#include <string.h>

bool decode_v2_message(v2_msg_t * dest, uint8_t * buffer, size_t buffer_len)
{
	if (buffer_len < 3)
    {
		return false;
	}
	
	dest->target = buffer[1] & 0x7F;            // endpoint
	dest->is_read = (buffer[1] & 0x80) > 0;     // read or write operation
	dest->msg_id = buffer[2];
	dest->data_len = buffer_len - 3;             // subtract header size
	if (dest->data_len > 16)
    {
		dest->data_len = 16;
	}

	memcpy(dest->data, &buffer[3], dest->data_len);
	
	return true;
}

size_t encode_v2_message(uint8_t * dest, v2_msg_t * message)
{
	dest[0] = 3 + message->data_len;
	dest[1] = message->target;
	if (message->is_read)
    {
		dest[1] |= 0x80;
	}
	dest[2] = message->msg_id;
	memcpy(&dest[3], message->data, message->data_len);
	
	return dest[0];
}