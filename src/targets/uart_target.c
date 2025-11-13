/*
* uart_target.c
*
* Created: 2025/01/24
*  Author: Tené
*/

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "uart_target.h"

#include "FreeRTOS.h"
#include "task.h"

#include "csp/interfaces/csp_if_kiss.h"

#include "bsp.h"
#include "pc_messages.h"
#include "csp_usart_cc.h"
#include "register_map.h"

// Special characters:
#define FEND	0xC0 // 192
#define FESC    0xDB // 219
#define TFEND   0xDC // 220
#define TFESC   0xDD // 221

extern csp_usart_cc_context_t csp_usart_cc_ctx_bus;

/*
* Initialize the instance.
*
* Before calling this function the following should be set
*/
void UARTTARGET_Init(uart_target_t * handle)
{
    // Buffer was increase from 256 to 1024 - WE are dropping many messages
    // due to a slow transmit speed.
    handle->incoming_messages = xMessageBufferCreate(4096);
    handle->outgoing_messages = xMessageBufferCreate(1024);
    
    handle->uart_semaphore = xSemaphoreCreateMutex();
}

void UARTTARGET_TransmitTask(void * handle)
{
    assert(handle);
    uart_target_t * hnd = (uart_target_t *) handle;
    
    uint8_t rx_buffer[32];
    v2_msg_t in_message;
    
    bool decode_successfull;
    
    while(1)
    {
        // So...
        //
        // RS485 uses the same lines to transmit and receive. After we transmit a message, the radio
        // will respond. But there is no requirement on WHEN they respond. Additionally, there is no
        // support in the UART modules for "line busy" to detect when something else is communicating.
        // This means there can be collision at any time, undetectable.
        //
        // There might be complicated methods of solving this, changing when the interrupt routine
        // fires, wait a while after sending a message. Our solution:
        // Only send a message every 2ms. A message is roughly 0.8ms long (at 115200), so this gives
        // the radio ample time to respond. It does limit throughput quite a lot. I don't know why this
        // IC is so slow with UART.
        
        size_t rx_length = xMessageBufferReceive(hnd->incoming_messages, rx_buffer, 16, portMAX_DELAY); // TODO: Investigate why we are not using the full buffer???
        
        if (rx_length == 0)
        {
            continue;
        }
        
        decode_successfull = decode_v2_message(&in_message, rx_buffer, rx_length);
        
        if (!decode_successfull)
        {
            continue;
        }
        
        // UART Message Structure - KISS (GSE & Radio): uart_msg_kiss_packet
        // Byte 0   - Message Type
        // Byte 1   - Message ID
        // Byte 2   - Destination Address
        // Byte 3   - Source Address
        // Byte 4-5 - Register Address (2 bytes, MSB first)
        // Byte 6-9 - Optional Data (If it is a write)
        
        // UART Message Structure (PC & GSE): in_message
        // Head 0	- Total Length
        // Head 1	- Endpoint & Direction bit
        // Head 2	- Message ID
        // Byte 0	- Message Type
        // Byte 1	- Payload length (including address)
        // Byte 2...- Data (2&3 is address)
        
        // After decode_v2_message: in_message:
        // in_message.data points to msg_type (Byte 0)
        // in_message.data_len includes address
        
        if (in_message.target == EP_V2_UART_CC_2)
        {
            uint8_t uart_msg_kiss_packet[32] = {0};
            
            uart_msg_kiss_packet[0] = FEND;
            
            //uart_msg_kiss_packet[1] = in_message.msg_id;
            uart_msg_kiss_packet[1] = in_message.data[0]; // msg_type
            uart_msg_kiss_packet[2] = in_message.msg_id;
            uart_msg_kiss_packet[3] = hnd->gse_uart_address;
            uart_msg_kiss_packet[4] = hnd->radio_uart_address;
            uart_msg_kiss_packet[5] = in_message.data[2];
            uart_msg_kiss_packet[6] = in_message.data[3];
            
            // Read request
            if (in_message.is_read)
            {
                uart_msg_kiss_packet[7] = FEND;
                hnd->uart_send(hnd->uart_handle, uart_msg_kiss_packet, 8);
            }
            // Write request
            else
            {
                // Loop through data and replace special characters
                uint8_t processed_data[4];
                uint8_t processed_index = 0;
                for (uint8_t i = 0; i < 4; i++)
                {
                    if (in_message.data[4 + i] == FEND)
                    {
                        processed_data[processed_index++] = FESC;
                        processed_data[processed_index++] = TFEND;
                        continue;
                    }
                    if (in_message.data[4 + i] == FESC)
                    {
                        processed_data[processed_index++] = FESC;
                        processed_data[processed_index++] = TFESC;
                        continue;
                    }
                    processed_data[processed_index++] = in_message.data[4 + i];
                }
                
                memcpy(&uart_msg_kiss_packet[7], processed_data, processed_index);
                uart_msg_kiss_packet[7 + processed_index] = FEND;
                hnd->uart_send(hnd->uart_handle, uart_msg_kiss_packet, 8 + processed_index);
            }
        }
    }
}

void UARTTARGET_ReceiveTask(void * handle)
{
    uart_target_t * hnd = (uart_target_t *) handle;
    
    uint8_t rx_buffer[32];
    size_t rx_max_length = 32;
    uint8_t uart_msg_kiss_packet[32];
    size_t packet_index = 0;
    bool receiving = false;
    bool escaped = false;
    mm_comms_protocol_t comms_protocol;
    
    while(1)
    {
        size_t rx_length = hnd->uart_receive(hnd->uart_handle, rx_buffer, rx_max_length);
        
        if (rx_length == 0)
        {
            continue;
        }
        
        configASSERT(mm_getConfCommsProtocol_BUS_UART(&comms_protocol) == mm_OK);
        switch (comms_protocol)
        {
            case reg_comms_protocol_cubecom:
            {
                ioport_set_pin_level(PIN_DEBUG_0, 1);
                
                //3. disassemble kiss packet -> out_message
                for (size_t i = 0; i < rx_length; i++)
                {
                    uint8_t rx_byte = rx_buffer[i];
                    
                    //start receiving only when start byte (FEND) is received
                    if (!receiving)
                    {
                        if (rx_byte == FEND)
                        {
                            receiving = true;
                            packet_index = 0;
                            ioport_set_pin_level(PIN_DEBUG_1, 1);
                            continue;
                        }
                    }
                    else
                    {
                        if (rx_byte == FEND )
                        {
                            // End of packet received
                            ioport_set_pin_level(PIN_DEBUG_1, 0);
                            
                            if (packet_index == 0)
                            {
                                //We received an empty packet! Probably means we dropped a byte somewhere,
                                // and should actually start receiving now.
                                receiving = true;
                                packet_index = 0;
                                ioport_set_pin_level(PIN_DEBUG_1, 1);
                                continue;
                            }
                            
                            if (packet_index < 6)
                            {
                                // Invalid length, expecting (excluding the start&end FEND):
                                //[0] msg type
                                //[1] msg id
                                //[2] src address
                                //[3] dest address
                                //[4] reg. address msb
                                //[5] reg. address lsb
                                //[6-x] data

                                // "throw away" message, restart receiving
                                receiving = false;
                                continue;
                            }
                            
                            size_t kiss_message_size = packet_index - 4;
                            
                            // Full packet received
                            v2_msg_t out_message;
                            out_message.msg_id = uart_msg_kiss_packet[1];
                            out_message.target = EP_V2_UART_CC_2;
                            // Packet_index stores the entire kiss packet length. Subtract 4 for the kiss header (type, id, src, dest),
                            // Then add 2 for the EGSE UART header (Type + Length)
                            out_message.data_len = kiss_message_size + 2;
                            
                            out_message.data[0] = uart_msg_kiss_packet[0]; // msg type
                            out_message.data[1] = kiss_message_size; // msg length
                            memcpy(&out_message.data[2], &uart_msg_kiss_packet[4], kiss_message_size);
                            
                            uint8_t encoded[32];
                            size_t encoded_len = encode_v2_message(encoded, &out_message);
                            
                            xMessageBufferSend(hnd->outgoing_messages, encoded, encoded_len, 0); //TODO: Handle dropped messages
                            
                            receiving = false;
                            continue;
                        }
                        
                        // Handle escaping
                        if (rx_byte == FESC)
                        {
                            escaped = true;
                            continue;
                        }
                        
                        // fix
                        if (escaped)
                        {
                            if (rx_byte == TFEND)
                            {
                                rx_byte = FEND;
                            }
                            else if (rx_byte == TFESC)
                            {
                                rx_byte = FESC;
                            }
                            escaped = false;
                        }
                        
                        // Store received bytes
                        if (packet_index < sizeof(uart_msg_kiss_packet))
                        {
                            uart_msg_kiss_packet[packet_index] = rx_byte;
                            packet_index += 1;
                        }
                    }
                }
                
                ioport_set_pin_level(PIN_DEBUG_0, 0);
                
                break;
            }
            
            case reg_comms_protocol_csp:
            {
                csp_kiss_rx(&csp_usart_cc_ctx_bus.iface, rx_buffer, rx_length, NULL);
                break;
            }
            
            case reg_comms_protocol_cants:
            default:
            {
                configASSERT(false);
                break;
            }
        }
    }
}

bool UARTTARGET_SetCommMode(uart_target_t * pHandle, uart_comm_mode_t CommMode)
{
    // TODO: Should we wait for the buffer to be empty?
    
    if(!xSemaphoreTake(pHandle->uart_semaphore, pdMS_TO_TICKS(200)))
    {
        return false;
    }
    
    ccd_uart_setCommMode(pHandle->uart_handle, CommMode);
    pHandle->uart_mode = CommMode;
    
    xSemaphoreGive(pHandle->uart_semaphore); // TODO: Handle semaphore release failure
    
    return true;
}

bool UARTTARGET_SetParityEnabled(uart_target_t * pHandle, uart_parity_enabled_t ParityEnabled)
{
    // TODO: Should we wait for the buffer to be empty?
    
    if(!xSemaphoreTake(pHandle->uart_semaphore, pdMS_TO_TICKS(200)))
    {
        return false;
    }
    
    ccd_uart_setParityEnabled(pHandle->uart_handle, ParityEnabled);
    
    xSemaphoreGive(pHandle->uart_semaphore); // TODO: Handle semaphore release failure
    
    return true;
}

bool UARTTARGET_SetParityMode(uart_target_t * pHandle, uart_parity_mode_t ParityMode)
{
    // TODO: Should we wait for the buffer to be empty?
    
    if(!xSemaphoreTake(pHandle->uart_semaphore, pdMS_TO_TICKS(200)))
    {
        return false;
    }
    
    ccd_uart_setParityMode(pHandle->uart_handle, ParityMode);
    
    xSemaphoreGive(pHandle->uart_semaphore); // TODO: Handle semaphore release failure
    
    return true;
}

bool UARTTARGET_SetBaudRate(uart_target_t * pHandle, uart_baud_rates_t BaudRate)
{
    // TODO: Should we wait for the buffer to be empty?
    
    if(!xSemaphoreTake(pHandle->uart_semaphore, pdMS_TO_TICKS(200)))
    {
        return false;
    }
    
    ccd_uart_setBaudRate(pHandle->uart_handle, BaudRate);
    
    xSemaphoreGive(pHandle->uart_semaphore); // TODO: Handle semaphore release failure
    
    return true;
}
