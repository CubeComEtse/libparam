/*
 * This is the CAN Target. All messages that should be sent over CAN are 
 * received and processed here.
 * 
 * This instance has a message buffer which receives messages. A FreeRTOS 
 * task checks this buffer and sends messages if required. This instance
 * requires function pointers to CAN to send messages.
 *
 */ 

#include "can_target.h"
#include <assert.h>
#include "pc_messages.h"

#define CAN_TELECOMMAND_REQUEST 0x01
#define CAN_TELEMETRY_REQUEST 0x04

/*
 * Initialize the instance. 
 *
 * Before calling this function the following should be set
*/
void CANTARGET_Init(can_target_t * handle)
{
	assert(handle->can_send);
	// Do not assert the handle, it might be void. 
	
	// These buffers are for SERCOM messages
	// This buffer size is an initial guess. Feel free to update it later.
	handle->incoming_messages = xMessageBufferCreate(256);
	handle->outgoing_messages = xMessageBufferCreate(256);
	
}

void CANTARGET_TxTask(void * handle)
{
	assert(handle);
	can_target_t * hnd = (can_target_t *) handle;
	
	uint8_t rx_buffer[32];
	v2_msg_t in_message;
	
	bool decode_successfull;
	
	while(1){
		// Wait indefinitely to receive a message 
		size_t rx_length = xMessageBufferReceive(hnd->incoming_messages, rx_buffer, 16, portMAX_DELAY);
		
		if (rx_length == 0){
			continue;
		}
		
		decode_successfull = decode_v2_message(&in_message, rx_buffer, rx_length);
		
		if (!decode_successfull){
			continue;
		}
		
		
		// So: At the moment the different CAN endpoints all use the same position in the header
		// for the address. This means the CAN driver does not need to be re-configured between
		// modes. However. The CAN target still needs to know what endpoint we're using, since
		// otherwise it would not know how to send the message back to the PC. So unfortunately
		// we are stuck with only supporting one mode at a time.
		//
		// It is possible to send messages in any mode, so do that. On the receive side, only 
		// receive in the format that we're set up for.
		if (in_message.target == EP_V2_CAN_CC)
		{
			/*
			uint8_t destination_address = in_message.data[0];
			
			uint32_t can_header = 0;
			can_header |= hnd->our_can_address << 8;
			can_header |= in_message.data[0];
			if (in_message.is_read)
			{
				can_header |= CAN_TELEMETRY_REQUEST << 24;
			}
			else
			{
				can_header |= CAN_TELECOMMAND_REQUEST << 24;
			}*/
		}
		if (in_message.target == EP_V2_CAN_CC_2)
		{
			// In this message format the destination CAN address was set in a separate register
			// 0 - MsgType
			// 1 - Length
			// 2 - Data (containing register address)
			uint32_t can_header = ((in_message.data[0] << 24) | (in_message.msg_id << 16) | (hnd->our_can_address << 8) | (hnd->radio_can_address << 0));

			hnd->can_send(hnd->can_handle, can_header, &in_message.data[2], in_message.data[1]);
		}
		if (in_message.target == EP_V2_CAN_CC_3)
		{
			// new CAN messages don't use the read bit, the message type that is set in the 
			// header determines what the message does
			
			// 0 - CAN Address
			// 1 - MsgType (for header)
			// 2 - Length
			// 3 - Data. Data can contain the address
			
			uint32_t can_header = ((in_message.data[1] << 24) | (in_message.msg_id << 16) | (hnd->our_can_address << 8) | (in_message.data[0] << 0));
			hnd->can_send(hnd->can_handle, can_header, &in_message.data[3], in_message.data[2]);
		}
	}
}


void CANTARGET_RxTask(void * vHandle)
{
	assert(vHandle);
	can_target_t * pHandle = (can_target_t *) vHandle;
		
	while(1){
		
		// Wait for a message to be received over CAN
		uint32_t header;
		uint8_t data[16];
		size_t receive_size;
		uint8_t * ptr = &data[2];
		if (pHandle->can_receive(pHandle->can_handle, &header, &ptr, &receive_size))
		{
			
			v2_msg_t out_message;
			out_message.msg_id = (uint8_t) ((header >> 16) & 0xFF);
			out_message.is_read = false;
			out_message.data = data;
			out_message.data_len = 2 + receive_size;
			
			{
				out_message.target = EP_V2_CAN_CC_2;
			
				// CAN MsgType
				data[0] = (uint8_t) ((header >> 24) & 0x1F);
				//
				data[1] = (uint8_t) receive_size;
			}
			
			uint8_t encoded[20];
			size_t encoded_size = encode_v2_message(encoded, &out_message);
			
			//Todo: What to do if a message is dropped?
			xMessageBufferSend(pHandle->outgoing_messages, &encoded, encoded_size, 0);			
			
		}
	
	}
}