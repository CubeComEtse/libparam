/*
* This is the I2C Target. All messages that should be sent over I2C are
* received and processed here.
*
* This instance has a stream buffer which receives messages. A FreeRTOS
* task checks this buffer and sends messages if required. This instance
* requires function pointers to I2C read and write functions.
*
* Created: 2024/10/03 17:08:40
* Author: Kolijn
*/

#include "i2c_target.h"

#include <string.h>
#include <assert.h>
#include <task.h>

#include "delay.h"

#include "pc_messages.h"

/*
* Initialize the instance.
*
* Before calling this function the following should be set
*/
void I2CTARGET_Init(i2c_target_t * handle)
{
    configASSERT(handle->i2c_read != NULL);
    configASSERT(handle->i2c_write != NULL);
    
    // These buffer sizes were increased to hold enough messages between UART transmissions
    handle->incoming_messages = xMessageBufferCreate(1024);
    handle->outgoing_messages = xMessageBufferCreate(1024);
    
    handle->legacy_address = 0x26;
    handle->tr_delay = 0;
    handle->write_read_delay = 0;
}

void I2CTARGET_Task(void * handle)
{
    configASSERT(handle != NULL);
    i2c_target_t * pHandle = (i2c_target_t *) handle;
    
    uint8_t rx_buffer[32];
    v2_msg_t in_message;
    v2_msg_t out_message;
    
    bool decode_successfull;
    
    while(1)
    {
        // Wait indefinitely to receive a message
        size_t rx_length =  xMessageBufferReceive(pHandle->incoming_messages, rx_buffer, 32, portMAX_DELAY);
        
        if (rx_length == 0)
        {
            continue;
        }
        
        decode_successfull = decode_v2_message(&in_message, rx_buffer, rx_length);
        
        // TODO: We should probably keep track of invalid message count for debugging and reporting purposes...
        if (!decode_successfull)
        {
            continue;
        }

        // All I2C messages have the same structure:
        //   0 - I2C bus address,
        // 1-2 - Address, even the 1 byte mode
        //   3 - Length of read or data, depending
        
        // Create a buffer to read data into, and to hold the encoded message
        uint8_t read_buffer[32];
        uint8_t encoded[32];
        
        if (in_message.target == EP_V2_I2C_CC_CHECKSUM)
        {
            // This is a i2c message with "checksums". Used by the XTX
            if ((in_message.is_read))
            {
                memcpy(read_buffer, in_message.data, in_message.data_len);
                uint8_t reg_address = in_message.data[0];
                uint8_t read_length = in_message.data[1];
                
                out_message.data[0] = reg_address;
                out_message.data[1] = read_length;

                uint8_t address_with_checksum[3];
                address_with_checksum[0] = in_message.data[0];
                address_with_checksum[1] = in_message.data[0];
                address_with_checksum[2] = 0;
                
                if (pHandle->write_read_delay ==0)
                {
                    if (pHandle->i2c_read(pHandle->i2c_handle, pHandle->legacy_address, address_with_checksum, 3, &out_message.data[2], read_length + 2))
                    {
                        // Create the received message
                        out_message.target = in_message.target;
                        out_message.is_read = true;
                        out_message.msg_id = in_message.msg_id;
                        out_message.data_len = read_length + 2;
                        
                        size_t encoded_len = encode_v2_message(encoded, &out_message);
                        
                        if (encoded_len > 0)
                        {
                            xMessageBufferSend(pHandle->outgoing_messages, encoded, encoded_len, 0); //TODO: Handle dropped messages
                        }
                    }
                }
                else
                {
                    // Split the transaction into two parts, for isiSpace compatibility
                    // Write the address first, delay, then do a read.
                    pHandle->i2c_write(pHandle->i2c_handle, pHandle->legacy_address, address_with_checksum, 3);
                    
                    delay_us(pHandle->write_read_delay);
                    
                    if (pHandle->i2c_read(pHandle->i2c_handle, pHandle->legacy_address, address_with_checksum, 0, &out_message.data[2], read_length + 2))
                    {
                        // Create the received message
                        out_message.target = in_message.target;
                        out_message.is_read = true;
                        out_message.msg_id = in_message.msg_id;
                        out_message.data_len = read_length + 2;
                        
                        size_t encoded_len = encode_v2_message(encoded, &out_message);
                        
                        if (encoded_len > 0)
                        {
                            xMessageBufferSend(pHandle->outgoing_messages, encoded, encoded_len, 0); //TODO: Handle dropped messages
                        }
                    }
                }
            }
            else
            {
                // It's a write
                uint8_t data_length = in_message.data[1];
                
                // Construct the TX buffer
                uint8_t tx_buffer[32];
                tx_buffer[0] = in_message.data[0];
                memcpy(&tx_buffer[1], &in_message.data[2], data_length);
                
                // Calculate the checksum and just place it in the TX buffer. Should be fine.
                uint16_t checksum = 0;
                for (uint8_t i = 0 ; i < data_length + 1; i ++) {
                    checksum += (uint16_t) tx_buffer[i];
                }
                tx_buffer[data_length + 1] = checksum & 0xFF ;
                tx_buffer[data_length + 2] = (checksum << 8) & 0xFF;

                pHandle->i2c_write(pHandle->i2c_handle, pHandle->legacy_address, tx_buffer, data_length+3);
                
                if (pHandle->tr_delay > 0)
                {
                    vTaskDelay(pdMS_TO_TICKS(pHandle->tr_delay));
                }
            }
        }
        
        if (in_message.target == EP_V2_I2C_CC)
        {
            // This is an i2c message with either 1 or 2 address bytes, used by the HDRTX
            if (in_message.is_read & (in_message.data_len == 2))
            {
                uint8_t device_address = pHandle->legacy_address; // Hard coded, from a register
                uint8_t * address = &in_message.data[0];
                uint8_t read_length = in_message.data[1];
                
                // Copy the register address and length to the buffer
                memcpy(out_message.data, in_message.data, 2);

                if (pHandle->i2c_read(pHandle->i2c_handle, device_address, address, 1, &out_message.data[2], read_length))
                {
                    // Create the received message
                    out_message.target = in_message.target;
                    out_message.is_read = true;
                    out_message.msg_id = in_message.msg_id;
                    // Final length is the 3 bytes already in the header plus the (length) bytes we just read.
                    out_message.data_len = 2 + read_length;
                    
                    // encode the out message to a buffer, and transmit
                    size_t encoded_len = encode_v2_message(encoded, &out_message);
                    
                    if (encoded_len > 0)
                    {
                        xMessageBufferSend(pHandle->outgoing_messages, encoded, encoded_len, 0); //TODO: Handle dropped messages
                    }
                }
            }
            if (!in_message.is_read)
            {
                in_message.data[2] = in_message.data[1];
                pHandle->i2c_write(pHandle->i2c_handle, in_message.data[0], &in_message.data[1], in_message.data_len - 2);
            }
        }
        
        if (in_message.target == EP_V2_I2C_CC_2)
        {
            // This is an i2c message with either 1 or 2 address bytes, used by the HDRTX
            if (in_message.is_read & (in_message.data_len == 3))
            {
                uint8_t device_address = pHandle->legacy_address; // Hard coded, from a register
                
                // Byte 0 & Byte 1 - Address
                uint8_t * address = &in_message.data[0];
                
                // Byte 2 - Read length
                uint8_t read_length = in_message.data[2];
                
                // Copy the register address and length to the buffer
                memcpy(out_message.data, in_message.data, 2);

                if (pHandle->i2c_read(pHandle->i2c_handle, device_address, address, 2, &out_message.data[2], read_length))
                {
                    // Create the received message
                    out_message.target = in_message.target;
                    out_message.is_read = true;
                    out_message.msg_id = in_message.msg_id;
                    // Final length is the 2 bytes already in the header plus the (length) bytes we just read.
                    out_message.data_len = 2 + read_length;
                    
                    // encode the out message to a buffer, and transmit
                    size_t encoded_len = encode_v2_message(encoded, &out_message);
                    
                    if (encoded_len > 0)
                    {
                        xMessageBufferSend(pHandle->outgoing_messages, encoded, encoded_len, 0);
                        //Todo: Do something if buffer is full.
                    }
                }
            }
            if (!in_message.is_read)
            {
                uint8_t device_address = pHandle->legacy_address; // Hard coded, from a register
                
                if (in_message.target == EP_V2_I2C_CC_2)
                {
                    // Its a write, just do it directly. The address bytes and the data
                    // bytes are already next to each other.
                    pHandle->i2c_write(pHandle->i2c_handle, device_address, in_message.data, in_message.data_len);
                }
            }
        }
        
        if (in_message.target == EP_V2_I2C_CC_3)
        {
            // Version 3 is another upgrade on the i2c endpoint, with the i2c bus address
            // included in the message. The register address can be 1 or 2 bytes.
            uint8_t bus_address = in_message.data[0];
            uint8_t addres_length = 2;
            
            // This is an i2c message with either
            if (in_message.is_read)
            {
                // Copy the i2c header to the out message data
                memcpy(out_message.data, in_message.data, 3);
                
                if (pHandle->i2c_read(pHandle->i2c_handle, bus_address, &in_message.data[1], addres_length, &out_message.data[3], in_message.data[3]))
                {
                    // Create the received message
                    out_message.target = in_message.target;
                    out_message.is_read = true;
                    out_message.msg_id = in_message.msg_id;
                    out_message.data_len = in_message.data[3] + 3;
                    
                    // encode the out message to a buffer, and transmit
                    size_t encoded_len = encode_v2_message(encoded, &out_message);
                    
                    if (encoded_len > 0)
                    {
                        xMessageBufferSend(pHandle->outgoing_messages, encoded, encoded_len, 0); //TODO: Handle dropped messages
                    }
                }
            }
            if (!in_message.is_read)
            {
                // Its a write, just do it directly. The PC will place the address and data next to each other
                pHandle->i2c_write(pHandle->i2c_handle, bus_address, &in_message.data[1], in_message.data_len -1);
            }
        }
    }
}

/*
* Set the new baud of the I2C Device
*/
bool I2CTARGET_SetBaud(i2c_target_t * handle, uint32_t baud)
{
    if (handle->i2c_set_baud == NULL)
    {
        return false;
    }
    return handle->i2c_set_baud(handle->i2c_handle, baud);
}

/*
* Previous versions of the I2C Endpoint had a target bus address that was set
* using a register, and not transferred using the UART messages. This
* function allows you to still do that.
*/
void I2CTarget_SetLegacyAddress(i2c_target_t * handle, uint8_t new_address)
{
    handle->legacy_address = new_address;
}