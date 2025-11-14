/*
 * cants_handlers.c
 *
 * Created: 11/12/2025 3:20:45 PM
 *  Author: Adriaan van der West
 */

#include "cants.h"

#include "config.h"
#include "ccd_can_driver.h"
#include "register_handler.h"

extern ccd_can_t bus_can;

/**
 * @brief Filter incoming CAN-TS messages.
 * @param [in] msg CAN-TS message to receive
 * @retval non-zero if message is should be processed further, 0 otherwise
 */
uint8_t cants_filter_msg(struct cants_msg *msg)
{
    if (msg->destination == CANTS_NODE_ID ||
        msg->destination == CANTS_TIME_ID ||
        msg->destination == CANTS_KEEPALIVE_ID ||
        msg->destination == CANTS_ERROR_ID ||
        msg->destination == CANTS_WARNING_ID)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief Send CAN-TS message.
 * @param [in] msg CAN-TS message to send
 * @param [in] wait_allowed 0 if blocking is not allowed, any other value means allowed
 * @retval 0 if message was not send successfully, any other value means success
 */
uint8_t cants_send_msg(struct cants_msg *msg, uint8_t wait_allowed)
{
    uint32_t header = cants_construct_id(msg);
    
    // TODO: Currently this will always have some blocking behavior - waiting for CAN driver to be ready
    ccd_can_Send_message(&bus_can, header, msg->data, msg->length);
    
    return 1;
}

/**
 * @brief Time Sync handler.
 * @param [in] length length of data array
 * @param [in] data Time Sync data
 * @retval None
 */
void cants_time_sync_handler(uint8_t length, uint8_t *data)
{
    // TODO: Implement
}

/**
 * @brief Unsolicited Telemetry handler.
 * @param [in] msg CAN-TS message with unsolicited telemetry
 * @retval None
 */
void cants_unsolicited_handler(const struct cants_msg *msg)
{
    uint8_t channel = msg->command & 0xFF;
    
    switch (channel)
    {
        case CANTS_CHANNEL_KEEP_ALIVE:
        {
            // No data parsing for this at the moment, continue as usual.
            break;
        }
        case CANTS_CHANNEL_PARAMETERS:
        {
            // We don't currently expect this, so just continue on.
            break;
        }
        default:
        {
            // Continue on as usual - no error here to allow future channel forward compatibility.
            break;
        }
    }
}

/**
 * @brief Telecommand handler.
 * @param [in] src Source node ID
 * @param [in] dst Destination node ID
 * @param [in] channel Telecommand channel
 * @param [in] length Length of telecommand data
 * @param [in] data Telecommand data
 * @retval positive value if telemetry was processed successfully, negative to ignore it and 0 to reject it
 */
int8_t cants_telecommand_handler(uint8_t src, uint8_t dst, uint8_t channel, uint8_t length, uint8_t *data)
{
    switch (channel)
    {
        case CANTS_CHANNEL_PARAMETERS: // TODO: Perhaps do this through local target interface...
        {
            if (length < 6)
            {
                return 0; // reject
            }
            
            uint16_t addr = ((uint16_t) data[0] << 8) | ((uint16_t) data[1] << 0);
            if (!REG_CheckAddress(addr))
            {
                return 0; // reject
            }
            
            if (!REG_WriteToAddress(addr, &data[2]))
            {
                return 0; // reject
            }
            
            return 1; // success
        }
        default:
        {
            return 0; // reject
        }
    }
}

/**
 * @brief Telemetry handler.
 * @param [in] src Source node ID
 * @param [in] dst Destination node ID
 * @param [in] channel Telemetry channel
 * @param [in] length Length of telemetry data
 * @param [out] data Telemetry data
 * @retval positive value if telemetry was processed successfully, negative to ignore it and 0 to reject it
 */
int8_t cants_telemetry_handler(uint8_t src, uint8_t dst, uint8_t channel, uint8_t *length, uint8_t *data)
{
    // We need to populate the keep alive message data, but only when it originates from us and is on the correct channel
    if (src == CANTS_NODE_ID)
    {
        if (dst != CANTS_KEEPALIVE_ID)
        {
            return -1; // ignore
        }
        
        if (channel != CANTS_CHANNEL_KEEP_ALIVE)
        {
            return -1; // ignore
        }
        
        *length = 0;
        data = NULL; // No data in keep alive message as of yet
        return 1; // success
    }
    
    // This would mean that the filtering has somehow failed
    if (dst != CANTS_NODE_ID)
    {
        #if DEBUG
        configASSERT(false);
        #else
        return -1; // ignore
        #endif
    }
    
    switch (channel)
    {
        case CANTS_CHANNEL_PARAMETERS:
        {
            if (*length < 6)
            {
                return 0; // reject
            }
            
            uint16_t addr = ((uint16_t) data[0] << 8) | ((uint16_t) data[1] << 0);
            if (!REG_CheckAddress(addr))
            {
                return 0; // reject
            }
            
            if (!REG_ReadFromAddress(addr, &data[2]))
            {
                return 0; // reject
            }
            
            return 1; // success
        }
        
        default:
        {
            return -1; // ignore
        }
    }
}

/**
 * @brief Set Block address validation function.
 * @param [in] src Source node ID
 * @param [in] dst Destination node ID
 * @param [in] address Set Block destination address
 * @param [in] size Amount of data to write at specified address
 * @retval non-zero value if address is valid, 0 otherwise
 */
uint8_t cants_validate_write_address(uint8_t src, uint8_t dst, ADDRESS_TYPE address, uint16_t size)
{
    // TODO: Implement
    return 0;
}

/**
 * @brief Set Block handler.
 * @param [in] src Source node ID
 * @param [in] dst Destination node ID
 * @param [in] address Set Block destination address
 * @param [in] buffer Buffer, which holds data to write
 * @param [in] size Size of the buffer
 * @param [in,out] success Address of success flag, which must be set to non-zero value when data processing has succeeded.
 * @param [out] finished Address of finished flag, which must be set to non-zero value when data processing has been finished.
 * @param [in] cookie \p success and \p finished should be set only if \p success contain same value as \p cookie.
 * @retval non-zero value if data processing has started successfully, 0 otherwise
 */
uint8_t cants_write_block_handler(uint8_t src, uint8_t dst, ADDRESS_TYPE address, uint8_t *buffer, uint16_t size, uint8_t *success, uint8_t *finished, uint8_t cookie)
{
    // TODO: Implement
    return 0;
}

/**
 * @brief Read Block handler.
 * @param [in] src Source node ID
 * @param [in] dst Destination node ID
 * @param [in] address Set Block source address
 * @param [out] buffer Buffer into which data is read
 * @param [out] size Size of the request data
 * @retval non-zero if data was read into buffer, 0 otherwise
 */
uint8_t cants_read_block_handler(uint8_t src, uint8_t dst, ADDRESS_TYPE address, uint8_t *buffer, uint16_t size)
{
    // TODO: Implement
    return 0;
}