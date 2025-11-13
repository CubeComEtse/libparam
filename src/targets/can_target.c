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

#include <string.h>

#include "csp/interfaces/csp_if_can.h"
#include "cants.h"

#include "csp_can_cc.h"
#include "pc_messages.h"
#include "ccd_can_driver.h"
#include "register_map.h"

#define CAN_TELECOMMAND_REQUEST     0x01
#define CAN_TELEMETRY_REQUEST       0x04

extern csp_can_cc_context_t csp_can_cc_ctx_bus;

/*
* Initialize the instance.
*
* Before calling this function the following should be set
*/
void CANTARGET_Init(can_target_t * pHandle)
{
    configASSERT(pHandle->can_send != NULL);
    
    // These buffers are for SERCOM messages
    // This buffer size is an initial guess. Feel free to update it later.
    pHandle->incoming_messages = xMessageBufferCreate(4096);
    pHandle->outgoing_messages = xMessageBufferCreate(4096);
    
    pHandle->can_semaphore = xSemaphoreCreateMutex();
    
    pHandle->mode = CUBECOM_MODE;
    ccd_can_SetAddress(pHandle->can_handle, pHandle->our_can_address, 0xFF);
}

void CANTARGET_TransmitTask(void * vHandle)
{
    configASSERT(vHandle != NULL);
    can_target_t * pHandle = (can_target_t *) vHandle;
    
    uint8_t rx_buffer[32];
    v2_msg_t in_message;
    
    bool decode_successfull;
    
    while(1)
    {
        // Wait indefinitely to receive a message
        size_t rx_length = xMessageBufferReceive(pHandle->incoming_messages, rx_buffer, 32, portMAX_DELAY);
        
        if (rx_length == 0)
        {
            continue;
        }
        
        decode_successfull = decode_v2_message(&in_message, rx_buffer, rx_length);
        
        if (!decode_successfull)
        {
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
            uint32_t can_header = 0;
            switch (pHandle->mode)
            {
                case CUBECOM_MODE:
                can_header = ((in_message.data[0] << 24) | (in_message.msg_id << 16) | (pHandle->our_can_address << 8) | (pHandle->radio_can_address << 0));
                break;
                case PLAN_S_COMPATIBILITY:
                can_header = ((in_message.data[0] << 24) | (pHandle->radio_can_address << 16) | (pHandle->our_can_address << 8) |  (in_message.msg_id));
                break;
            }

            pHandle->can_send(pHandle->can_handle, can_header, &in_message.data[2], in_message.data[1]);
        }
        if (in_message.target == EP_V2_CAN_CC_3)
        {
            // new CAN messages don't use the read bit, the message type that is set in the
            // header determines what the message does
            
            // 0 - CAN Address
            // 1 - MsgType (for header)
            // 2 - Length
            // 3 - Data. Data can contain the address
            
            uint32_t can_header = ((in_message.data[1] << 24) | (in_message.msg_id << 16) | (pHandle->our_can_address << 8) | (in_message.data[0] << 0));
            pHandle->can_send(pHandle->can_handle, can_header, &in_message.data[3], in_message.data[2]);
        }
    }
}

void CANTARGET_ReceiveTask(void * vHandle)
{
    configASSERT(vHandle != NULL);
    can_target_t * p_can_target_handle = (can_target_t *) vHandle;
    
    uint32_t header;
    uint8_t data[8];
    size_t receive_size;
    mm_comms_protocol_t comms_protocol;
    
    while(1)
    {
        // Wait for a message to be received over CAN
        if (!p_can_target_handle->can_receive(p_can_target_handle->can_handle, &header, data, &receive_size))
        {
            continue;
        }
        configASSERT(receive_size <= 8);
        
        configASSERT(mm_getConfCommsProtocol_BUS_CAN(&comms_protocol) == mm_OK);
        switch (comms_protocol)
        {
            case reg_comms_protocol_cubecom:
            {
                v2_msg_t out_message;
                size_t sent_size;
                uint8_t encoded[20];
                size_t encoded_size;
                
                out_message.is_read = false;
                out_message.data_len = 2 + receive_size;
                out_message.target = EP_V2_CAN_CC_2;
                
                out_message.data[0] = (uint8_t) ((header >> 24) & 0x1F);    // CAN MsgType
                out_message.data[1] = (uint8_t) receive_size;               // Message Length
                memcpy(&out_message.data[2], data, receive_size);
                
                if (p_can_target_handle->mode == CUBECOM_MODE)
                {
                    out_message.msg_id = (uint8_t) ((header >> 16) & 0xFF);
                }
                if (p_can_target_handle->mode == PLAN_S_COMPATIBILITY)
                {
                    out_message.msg_id = (uint8_t) ((header) & 0xFF);
                }
                
                encoded_size = encode_v2_message(encoded, &out_message);
                
                sent_size = xMessageBufferSend(p_can_target_handle->outgoing_messages, &encoded, encoded_size, pdMS_TO_TICKS(20));
                configASSERT(sent_size == encoded_size); // TODO: Handle this more gracefully
                
                break;
            }
            case reg_comms_protocol_csp:
            {
                csp_can_rx(&csp_can_cc_ctx_bus.iface, header, data, receive_size, NULL); // TODO: Handle errors
                break;
            }
            case reg_comms_protocol_cants:
            {
                struct cants_msg msg;
                uint8_t cants_ret;
                
                cants_parse_id(&msg, header);
                msg.length = receive_size;
                memcpy(msg.data, data, receive_size);
                cants_ret = cants_dispatch(&msg, pdMS_TO_TICKS(10));
                configASSERT(cants_ret); // TODO: Handle this more gracefully
                
                break;
            }
            default:
            {
                configASSERT(false);
                break;
            }
        }
    }
    
    configASSERT(false);
}

bool CANTARGET_SetBaud(can_target_t * pHandle, uint32_t baud)
{
    // TODO: Should we wait for the buffer to be empty?
    // TODO: Why are we still continuing even if the semaphore is not obtained?
    
    if (xSemaphoreTake(pHandle->can_semaphore, pdMS_TO_TICKS(200)) != pdTRUE)
    {
        return false;
    }
    
    bool retval = ccd_can_SetBaudRate(pHandle->can_handle, baud);
    
    xSemaphoreGive(pHandle->can_semaphore); // TODO: Handle semaphore release failure
    
    return retval;
}

bool CANTARGET_EnableRetries(can_target_t * pHandle, bool retries)
{
    // TODO: Should we wait for the buffer to be empty?
    
    if (xSemaphoreTake(pHandle->can_semaphore, pdMS_TO_TICKS(200)) != pdTRUE)
    {
        return false;
    }
    
    ccd_can_SetRetries(pHandle->can_handle, retries);
    
    xSemaphoreGive(pHandle->can_semaphore); // TODO: Handle semaphore release failure
    
    return true;
}

bool CANTARGET_SetMode(can_target_t * pHandle, can_mode_t mode)
{
    // TODO: Should we wait for the buffer to be empty?
    
    if (xSemaphoreTake(pHandle->can_semaphore, pdMS_TO_TICKS(200)) != pdTRUE)
    {
        return false;
    }
    
    switch (mode)
    {
        case CUBECOM_MODE:
        {
            pHandle->mode = CUBECOM_MODE;
            // Change the address filter as well
            ccd_can_SetAddress(pHandle->can_handle, pHandle->our_can_address, 0xFF);
            break;
        }
        case PLAN_S_COMPATIBILITY:
        {
            pHandle->mode = PLAN_S_COMPATIBILITY;
            ccd_can_SetAddress(pHandle->can_handle, pHandle->our_can_address << 16, 0xFF << 16);
            break;
        }
    }
    
    xSemaphoreGive(pHandle->can_semaphore); // TODO: Handle semaphore release failure
    
    return true;
}

bool CANTARGET_vSetAddress(can_target_t * pHandle, uint8_t new_address)
{
    if (xSemaphoreTake(pHandle->can_semaphore, pdMS_TO_TICKS(500)) != pdTRUE)
    {
        return false;
    }
    
    pHandle->radio_can_address = new_address;
    
    xSemaphoreGive(pHandle->can_semaphore); // TODO: Handle semaphore release failure
    
    return true;
}
