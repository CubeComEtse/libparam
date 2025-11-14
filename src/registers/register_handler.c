/*
* register_handler.c
*
* Created: 2021/08/03 14:34:22
*  Author: Kolijn
*/

#include "register_handler.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "event.h"
#include "Multitester.h"
#include "config.h"
#include "platform.h"

#include "gse_manager.h"
#include "register_map.h"

static uint32_t REG_CopyArrayToU32(const uint8_t * data);
static void REG_Copyu32ToArray(const uint32_t value, uint8_t * data);

static platform_t * platform;
static bsp_t * bsp;

/*
* This module handles the register interface exposed to the outside.
*/

typedef mm_response_t (*readAddressFunction)(uint32_t * dest);

typedef struct addres_to_func_map_s
{
    mm_register_address_t address;
    readAddressFunction readFunction;
} addres_to_func_map_t;

static addres_to_func_map_t address_to_func_map[] = {
    { reg_Board_ID_addr, mm_getBoard_ID},
    { reg_FW_Version_addr, mm_getFW_Version},
    { reg_HW_Version_addr, mm_getHW_Version},
    { reg_Scratchpad_addr, mm_getScratchpad},
    { reg_Configured_Boards_addr, mm_getConfigured_Boards},
    
    // Uptime handled separately
    // { reg_Uptime_addr, mm_getUptime},
    
    // Event conf handled separately
    // { reg_Event_ConfA_addr, mm_getEvent_ConfA},
    // { reg_Event_addr, mm_getEvent},
    
    { reg_ConfPower_addr, mm_getConfPower},
    
    { reg_MeasureVI_V3_addr, mm_getMeasureVI_V3},
    { reg_MeasurePower_V3_addr, mm_getMeasurePower_V3},
    { reg_MeasureVI_V5_addr, mm_getMeasureVI_V5},
    { reg_MeasurePower_V5_addr, mm_getMeasurePower_V5},
    { reg_MeasureVI_VBat_addr, mm_getMeasureVI_VBat},
    { reg_MeasurePower_VBat_addr, mm_getMeasurePower_VBat},
    { reg_MeasureVI_VBatAlt_addr, mm_getMeasureVI_VBatAlt},
    { reg_MeasurePower_VBatAlt_addr, mm_getMeasurePower_VBatAlt },
    
    { reg_I2CConfA_addr, mm_getI2CConfA },
    { reg_I2CConfB_addr, mm_getI2CConfB },
    { reg_MultiConf0_addr, mm_getMultiConf0 },
    { reg_ConfTempSense_addr, mm_getConfTempSense },
    { reg_CANConfA_addr, mm_getCANConfA },
    { reg_CANConfB_addr, mm_getCANConfB },
    { reg_PC104Pins_addr, mm_getPC104Pins },
    { reg_SerialConf_addr, mm_getSerialConf },
    
    { reg_RFRelaysConf_addr, mm_getRFRelaysConf },
    { reg_MultiConf1_Status_addr, mm_getMultiConf1_Status },
    
    { reg_CSBoard_T0_addr, mm_getCSBoard_T0 },
    { reg_CSBoard_T1_addr, mm_getCSBoard_T1 },
    { reg_CSBoard_T2_addr, mm_getCSBoard_T2 },
    { reg_CSBoard_T3_addr, mm_getCSBoard_T3 },
    { reg_CSBoard_T4_addr, mm_getCSBoard_T4 },
    { reg_CSBoard_T5_addr, mm_getCSBoard_T5 },
    { reg_CSBoard_T6_addr, mm_getCSBoard_T6 },
    { reg_CSBoard_T7_addr, mm_getCSBoard_T7 },
    { reg_CSBoard_Current0I0_addr, mm_getCSBoard_Current0I0},
    { reg_CSBoard_Current0I1_addr, mm_getCSBoard_Current0I1},
    { reg_CSBoard_Current0I2_addr, mm_getCSBoard_Current0I2},
    { reg_CSBoard_Current1I0_addr, mm_getCSBoard_Current1I0},
    { reg_CSBoard_Current1I1_addr, mm_getCSBoard_Current1I1},
    { reg_CSBoard_Current1I2_addr, mm_getCSBoard_Current1I2},
    { reg_CSBoard_Current2I0_addr, mm_getCSBoard_Current2I0},
    { reg_CSBoard_Current2I1_addr, mm_getCSBoard_Current2I1},
    { reg_CSBoard_Current2I2_addr, mm_getCSBoard_Current2I2},
    { reg_CSBoard_Current3I0_addr, mm_getCSBoard_Current3I0},
    { reg_CSBoard_Current3I1_addr, mm_getCSBoard_Current3I1},
    { reg_CSBoard_Current3I2_addr, mm_getCSBoard_Current3I2},
    { reg_CSBoard_Current4I0_addr, mm_getCSBoard_Current4I0},
    { reg_CSBoard_Current4I1_addr, mm_getCSBoard_Current4I1},
    { reg_CSBoard_Current4I2_addr, mm_getCSBoard_Current4I2},
    { reg_CSBoard_Current5I0_addr, mm_getCSBoard_Current5I0},
    { reg_CSBoard_Current5I1_addr, mm_getCSBoard_Current5I1},
    { reg_CSBoard_Current5I2_addr, mm_getCSBoard_Current5I2},
    { reg_CSBoard_Current6I0_addr, mm_getCSBoard_Current6I0},
    { reg_CSBoard_Current6I1_addr, mm_getCSBoard_Current6I1},
    { reg_CSBoard_Current6I2_addr, mm_getCSBoard_Current6I2},
    { reg_CSBoard_Current7I0_addr, mm_getCSBoard_Current7I0},
    { reg_CSBoard_Current7I1_addr, mm_getCSBoard_Current7I1},
    { reg_CSBoard_Current7I2_addr, mm_getCSBoard_Current7I2},
    { reg_TE_Addr_0_addr, mm_getTE_Addr_0},
    { reg_TE_Addr_1_addr, mm_getTE_Addr_1},
    { reg_TE_Addr_2_addr, mm_getTE_Addr_2},
    { reg_TE_Addr_3_addr, mm_getTE_Addr_3},
    
    { reg_MTC_Addr_0_addr, mm_getMTC_Addr_0},
    { reg_MTC_Addr_1_addr, mm_getMTC_Addr_1},
    { reg_MTC_Addr_2_addr, mm_getMTC_Addr_2},
    { reg_MTC_Addr_3_addr, mm_getMTC_Addr_3},
    
    { reg_RTOS_Status0_addr, mm_getRTOS_Status0},
    { reg_UtilI2CConfA_addr, mm_getUtilI2CConfA},
    { reg_UtilI2CStatus_addr, mm_getUtilI2CStatus },
    { reg_PreviousEndpoint_addr, mm_getPreviousEndpoint},
};

void REG_vSetPlatformPointer(platform_t * handle, bsp_t * bsp_handle)
{
    platform = handle;
    bsp = bsp_handle;
}

/*
* Checks if the provided register address is a valid one.
* Returns true if it is, false otherwise.
*/
bool REG_CheckAddress(const uint16_t address)
{
    for (uint32_t i = 0; i < (sizeof(address_to_func_map) / sizeof(address_to_func_map[0])); i++)
    {
        if(address == address_to_func_map[i].address)
        {
            return true;
        }
    }
    
    return false;
}

/*
* Gets the register given by address, copies it's data into the data argument
* Returns true if the address is valid, false otherwise.
*
* NOTE: Currently only 32-bit registers are supported by this function.
*       Hence, the buffer passed must be of length >= 4 for this operation to be safe.
*/
bool REG_ReadFromAddress(const uint16_t address, uint8_t * buff)
{
    uint32_t destination;

    // Loop through the entire array to find the correct function to call
    for (uint32_t i = 0; i < (sizeof(address_to_func_map) / sizeof(address_to_func_map[0])); i++)
    {
        if (((uint32_t) address_to_func_map[i].address) != address)
        {
            continue;
        }
        
        // Call the function
        if (address_to_func_map[i].readFunction(&destination) != mm_OK)
        {
            return false;
        }
        
        // Copy into the buffer
        REG_Copyu32ToArray(destination, buff);

        return true;
    }

    // Special actions to take when reading a specific addresses
    switch (address)
    {
        case reg_Uptime_addr:
        {
            REG_Copyu32ToArray(BSP_GetUptime(), buff);
            
            return true;
        }
        
        case reg_Event_ConfA_addr:
        {
            // Update the event count
            uint16_t event_count = EVENT_EventCount();
            mm_setEvent_ConfA_count(event_count);
            
            if (mm_getEvent_ConfA(&destination) != mm_OK)
            {
                return false;
            }
            
            // Copy into the buffer
            REG_Copyu32ToArray(destination, buff);
            
            return true;
        }
        
        case reg_Event_addr:
        {
            event_t current_event = {0};
            EVENT_GetEvent(&current_event);
            
            // Update the event from the buffer that is kept
            mm_setEvent_section(current_event.section);
            mm_setEvent_detail(current_event.detail);
            mm_setEvent_timestamp(current_event.timestamp);
            
            if (mm_getEvent(&destination) != mm_OK)
            {
                return false;
            }
            
            // Copy into the buffer
            REG_Copyu32ToArray(destination, buff);
            
            return true;
        }
        
        case reg_RTOS_Status0_addr:
        {
            // TODO: This does not seem to be set anywhere in the code? Should we be reading something here???
            if (mm_getRTOS_Status0(&destination) != mm_OK)
            {
                return false;
            }
            
            // Copy into the buffer
            REG_Copyu32ToArray(destination, buff);
            
            // This register gets cleared on read
            mm_setRTOS_Status0(0);
            
            return true;
        }
    }
    
    // Not found in function map nor is it a special case.
    return false;
}

void REG_vReadFromAddress(const uint16_t address, void * value)
{
    uint8_t buff[4] = { 0 };
    if (!REG_ReadFromAddress(address, buff))
    {
        // TODO: We need to handle this better... Currently returning uint32_t max value if this fails. Really shouldn't fail.
        *((uint32_t *)value) = 0xFFFFFFFF;
    }
    *((uint32_t *)value) = REG_CopyArrayToU32(buff);
}

/*
* Sets the register given by address.
* Returns true if executed successfully (register exists and is write-enabled), 
* false if not (register does not exist, or is read-only).
*
* NOTE: Currently only 32-bit registers are supported by this function.
*       Hence, the buffer passed must be of length >= 4 for this operation to be safe.
*/
bool REG_WriteToAddress(const uint16_t address, const uint8_t * buff)
{
    uint32_t deserialized = REG_CopyArrayToU32(buff);
    
    // NOTE: All addresses not handled here are assumed to be read-only
    switch (address)
    {
        case reg_Scratchpad_addr:
        {
            mm_setScratchpad(deserialized);
            return true;
        }
        
        case reg_Configured_Boards_addr:
        {
            mm_setConfigured_Boards(deserialized);
            return true;
        }
        
        case reg_ConfPower_addr:
        {
            mm_enabled_t powerEn = reg_enabled_disabled;
            
            // Only V0 has these pins
            if (BSP_u8GetVersion() == 0)
            {
                mm_getConfPower_voltage5ToggleFrom(&powerEn, deserialized);
                GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_5V, powerEn == reg_enabled_enabled);
                mm_setConfPower_voltage5Toggle(powerEn);
                
                mm_getConfPower_voltageVBatAltToggleFrom(&powerEn, deserialized);
                GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_VBAT_ALT, powerEn == reg_enabled_enabled);
                mm_setConfPower_voltageVBatAltToggle(powerEn);
            }
            
            mm_getConfPower_voltage3ToggleFrom(&powerEn, deserialized);
            GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_3V3, powerEn == reg_enabled_enabled);
            mm_setConfPower_voltage3Toggle(powerEn);
            
            
            mm_getConfPower_voltageVBatToggleFrom(&powerEn, deserialized);
            GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_VBAT, powerEn == reg_enabled_enabled);
            mm_setConfPower_voltageVBatToggle(powerEn);
            
            // Only version 2 has these pins
            if (BSP_u8GetVersion() == 2)
            {
                mm_getConfPower_voltage3UtilToggleFrom(&powerEn, deserialized);
                GSE_MANAGER_SetBusPowerSwitch(platform->gse_manager, POWER_3V3_UTIL, powerEn == reg_enabled_enabled);
                mm_setConfPower_voltage3UtilToggle(powerEn);
            }
            
            return true;
        }
        
        case reg_I2CConfA_addr:
        {
            // Set the module speed here. The other values in the register are read when they are needed
            uint8_t spd = 0;
            mm_getI2CConfA_SPDFrom(&spd, deserialized);
            if ((spd >= 1) && (spd <= 40))
            {
                if (I2CTARGET_SetBaud(platform->i2c_target, spd * 10000))
                {
                    mm_setI2CConfA_SPD(spd);
                }
            }
            
            uint8_t wrdel = 0 ;
            mm_getI2CConfA_WRDELFrom(&wrdel, deserialized);
            platform->i2c_target->write_read_delay = wrdel;
            mm_setI2CConfA_WRDEL(wrdel);
            
            uint8_t trdel = 0 ;
            mm_getI2CConfA_TRDELFrom(&trdel, deserialized);
            platform->i2c_target->tr_delay = trdel;
            mm_setI2CConfA_TRDEL(trdel);
            
            return true;
        }
        
        case reg_I2CConfB_addr:
        {
            uint8_t i2c_address = 0;
            mm_getI2CConfB_ADDRFrom(&i2c_address, deserialized);
            
            I2CTarget_SetLegacyAddress(platform->i2c_target, i2c_address);
            
            mm_setI2CConfB(deserialized);
            
            return true;
        }
        
        case reg_CANConfA_addr:
        {
            uint16_t baudrate_kbps = 0;
            mm_getCANConfA_BaudRateFrom(&baudrate_kbps, deserialized);
            if (CANTARGET_SetBaud(platform->can_target, ((uint32_t)baudrate_kbps) * 1000))
            {
                mm_setCANConfA_BaudRate( baudrate_kbps);
            }
            
            mm_enabled_t flip_can_bytes;
            mm_getCANConfA_FlipCanBytesFrom(&flip_can_bytes, deserialized);
            if (flip_can_bytes)
            {
                if (CANTARGET_SetMode(platform->can_target, PLAN_S_COMPATIBILITY))
                {
                    mm_setCANConfA_FlipCanBytes(flip_can_bytes);
                }
            }
            else
            {
                if (CANTARGET_SetMode(platform->can_target, CUBECOM_MODE))
                {
                    mm_setCANConfA_FlipCanBytes(flip_can_bytes);
                }
            }
            
            mm_enabled_t enable_retries;
            mm_getCANConfA_EnableRetriesFrom(&enable_retries, deserialized);
            if (CANTARGET_EnableRetries(platform->can_target, enable_retries == reg_enabled_enabled))
            {
                mm_setCANConfA_EnableRetries(enable_retries);
            }
            
            return true;
        }
        
        case reg_CANConfB_addr:
        {
            uint8_t new_address = 0;
            mm_getCANConfB_AddressFrom(&new_address, deserialized);
            
            if (CANTARGET_vSetAddress(platform->can_target, new_address))
            {
                mm_setCANConfB_Address(new_address);
            }
            
            return true;
        }
        
        case reg_SerialConf_addr:
        {
            mm_serialmode_t serial_comm_mode;
            mm_getSerialConf_SerialModeFrom(&serial_comm_mode, deserialized);
            if(UARTTARGET_SetCommMode(platform->uart_target, serial_comm_mode))
            {
                mm_setSerialConf_SerialMode(serial_comm_mode);
            }
            
            mm_enabled_t parity_enabled;
            mm_getSerialConf_ParityEnabledFrom(&parity_enabled, deserialized);
            if(UARTTARGET_SetParityEnabled(platform->uart_target, parity_enabled))
            {
                mm_setSerialConf_ParityEnabled(parity_enabled);
            }
            
            mm_paritymodes_t parity_mode;
            mm_getSerialConf_ParityModeFrom(&parity_mode, deserialized);
            if(UARTTARGET_SetParityMode(platform->uart_target, parity_mode))
            {
                mm_setSerialConf_ParityMode(parity_mode);
            }
            
            mm_usart_baudrates_t baud_rate;
            mm_getSerialConf_BaudRatesFrom(&baud_rate, deserialized);
            if(UARTTARGET_SetBaudRate(platform->uart_target, baud_rate))
            {
                mm_setSerialConf_BaudRates(baud_rate);
            }
            
            return true;
        }
        
        case reg_PC104Pins_addr:
        {
            mm_enabled_t ena;
            mm_getPC104Pins_ENAFrom(&ena, deserialized);
            PC104_setEnaPin(platform->pc104, ena == reg_enabled_enabled);
            mm_setPC104Pins_ENA(ena);
            
            mm_getPC104Pins_nRSTFrom(&ena, deserialized);
            PC104_setnRstPin(platform->pc104, ena == reg_enabled_enabled);
            mm_setPC104Pins_nRST(ena);
            
            return true;
        }
        
        case reg_RFRelaysConf_addr:
        {
            mm_enabled_t scan_enabled = reg_enabled_disabled;
            mm_getRFRelaysConf_ScanEnabledFrom(&scan_enabled, deserialized);
            RFRelay_SetScanEnabled(platform->rf_relay_1, scan_enabled == reg_enabled_enabled);
            RFRelay_SetScanEnabled(platform->rf_relay_2, scan_enabled == reg_enabled_enabled);
            mm_setRFRelaysConf_ScanEnabled(scan_enabled);
            
            uint8_t rf1_channel = 0;
            uint8_t rf2_channel = 0;
            mm_getRFRelaysConf_RfSw1ChanFrom(&rf1_channel, deserialized);
            mm_getRFRelaysConf_RfSw2ChanFrom(&rf2_channel, deserialized);
            
            RFRelay_SetDesiredChannel(platform->rf_relay_1, rf1_channel);
            RFRelay_SetDesiredChannel(platform->rf_relay_2, rf2_channel);
            
            return true;
        }
        
        case reg_TE_Addr_0_Set_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_SetScanEnabled(platform->te_scanner, 0);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_SetTeBits(platform->te_scanner, 0, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        case reg_TE_Addr_0_Clear_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_ClearScanEnabled(platform->te_scanner, 0);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_ClearTeBits(platform->te_scanner, 0, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        case reg_TE_Addr_1_Set_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_SetScanEnabled(platform->te_scanner, 1);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_SetTeBits(platform->te_scanner, 1, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        case reg_TE_Addr_1_Clear_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_ClearScanEnabled(platform->te_scanner, 1);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_ClearTeBits(platform->te_scanner, 1, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        case reg_TE_Addr_2_Set_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_SetScanEnabled(platform->te_scanner, 2);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_SetTeBits(platform->te_scanner, 2, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        case reg_TE_Addr_2_Clear_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_ClearScanEnabled(platform->te_scanner, 2);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_ClearTeBits(platform->te_scanner, 2, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        case reg_TE_Addr_3_Set_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_SetScanEnabled(platform->te_scanner, 2);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_SetTeBits(platform->te_scanner, 3, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        case reg_TE_Addr_3_Clear_addr:
        {
            mm_enabled_t scanEnabled;
            mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
            if (scanEnabled == reg_enabled_enabled)
            {
                TE_Adaptor_ClearScanEnabled(platform->te_scanner, 2);
            }
            
            // We have deliberately made the bits align perfectly so we could do this.
            TE_Adaptor_ClearTeBits(platform->te_scanner, 3, (deserialized >> 16) & 0x0FFF);
            
            return true;
        }
        
        // Multitester V2
        case reg_MTC_Addr_0_Set_addr:
        {
            MTCV2_SetBits(platform->multitester, 0, deserialized);
            return true;
        }
        
        case reg_MTC_Addr_1_Set_addr:
        {
            MTCV2_SetBits(platform->multitester, 1, deserialized);
            return true;
        }
        
        case reg_MTC_Addr_2_Set_addr:
        {
            MTCV2_SetBits(platform->multitester, 2, deserialized);
            return true;
        }
        
        case reg_MTC_Addr_3_Set_addr:
        {
            MTCV2_SetBits(platform->multitester, 3, deserialized);
            return true;
        }
        
        case reg_MTC_Addr_0_Clear_addr:
        {
            MTCV2_ClearBits(platform->multitester, 0, deserialized);
            return true;
        }
        
        case reg_MTC_Addr_1_Clear_addr:
        {
            MTCV2_ClearBits(platform->multitester, 1, deserialized);
            return true;
        }
        
        case reg_MTC_Addr_2_Clear_addr:
        {
            MTCV2_ClearBits(platform->multitester, 2, deserialized);
            return true;
        }
        
        case reg_MTC_Addr_3_Clear_addr:
        {
            MTCV2_ClearBits(platform->multitester, 3, deserialized);
            return true;
        }
        
        case reg_UtilI2CConfA_addr:
        {
            uint8_t new_speed;
            mm_getUtilI2CConfA_SPDFrom(&new_speed, deserialized);
            
            if ((new_speed >= 1) && (new_speed <= 40))
            {
                // There are many different things using the same I2C device.
                // So we can't set the baud through one of them, instead just
                // set the driver directly. This will still lock the mutex
                if (ccd_i2c_driver_SetBaud(bsp->util_i2c, (uint32_t)new_speed * 10000))
                {
                    mm_setUtilI2CConfA_SPD(new_speed);
                }
            }
            
            bool should_reset;
            mm_getUtilI2CConfA_ResetFrom(&should_reset, deserialized);
            cc_i2c_driver_ReInit(bsp->util_i2c);
            
            return true;
        }
        
        case reg_PreviousEndpoint_addr:
        {
            mm_setPreviousEndpoint(deserialized);
            
            return true;
        }
        
        case reg_ConfCommsProtocol_addr:
        {
            mm_comms_protocol_t comms_protocol;
            
            mm_getConfCommsProtocol_BUS_CANFrom(&comms_protocol, deserialized);
            mm_setConfCommsProtocol_BUS_CAN(comms_protocol);
            
            mm_getConfCommsProtocol_TEL_UARTFrom(&comms_protocol, deserialized);
            mm_setConfCommsProtocol_TEL_UART(comms_protocol);
            
            mm_getConfCommsProtocol_BUS_UARTFrom(&comms_protocol, deserialized);
            mm_setConfCommsProtocol_BUS_UART(comms_protocol);
            
            return true;
        }
        
        default:
        {
            return false;
        }
    }
}

void REG_vWriteToAddress(const uint16_t address, const void * value)
{
    uint8_t buff[4];
    REG_Copyu32ToArray(*((uint32_t *)value), buff);
    if (!REG_WriteToAddress(address, (const uint8_t *) buff))
    {
        // TODO: Handle failed writes. Really shouldn't fail.
    }
}

/*
* Copy a given value into the buffer. Buffer should be big enough to handle the value
*/
static void REG_Copyu32ToArray(const uint32_t value, uint8_t* data)
{
    data[0] = (uint8_t) (value >> 0);
    data[1] = (uint8_t) (value >> 8);
    data[2] = (uint8_t) (value >> 16);
    data[3] = (uint8_t) (value >> 24);
}

static uint32_t REG_CopyArrayToU32(const uint8_t* data)
{
    uint32_t res = 0;
    
    res |= (uint32_t) data[3] << 24;
    res |= (uint32_t) data[2] << 16;
    res |= (uint32_t) data[1] << 8;
    res |= (uint32_t) data[0] << 0;
    
    return res;
}
