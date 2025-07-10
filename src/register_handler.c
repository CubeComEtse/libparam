#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "register_handler.h"

#include "event.h"
#include "Multitester.h"
#include "config.h"
#include "platform.h"


#include "gse_manager.h"
#include "register_map.h"
  
static uint32_t REG_CopyArrayToU32(const uint8_t* data);

static platform_t * platform;


/*
 * This module handles the register interface exposed to the outside.
*/

typedef mm_response_t (*readAddressFunction)(uint32_t * dest);
typedef struct {
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
	// Event conf handled seperately
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
		
	{ reg_RTOS_Status0_addr, mm_getRTOS_Status0},
};


void REG_vSetPlatformPointer(platform_t * handle){
	platform = handle;
}


/*
 * Checks if the provided register address is a valid one. Returns true if it 
 * is, false otherwise
*/
bool REG_CheckAddress(const uint8_t address){
    bool found = false;
    for (uint32_t i = 0; i < (sizeof(address_to_func_map) / sizeof(address_to_func_map[0])); i++) {
        if(address == address_to_func_map[i].address){
            found = true;
        }
    }   
    return found;
}

/*
Gets the register given by address, copies it's data into the data argument
Returns true if the address is valid, false otherwise.
*/
bool REG_vReadFromAddress(const uint32_t address, uint8_t * buff, uint8_t * size)
{
	uint32_t destination;
	bool return_value = false;

	// Loop through the entire array to find the correct function to call
	for (uint32_t i = 0; i < (sizeof(address_to_func_map) / sizeof(address_to_func_map[0])); i++)
	{
		if (((uint32_t) address_to_func_map[i].address) == address)
		{
			// Call the function
			uint32_t read_successful = address_to_func_map[i].readFunction(&destination);
			if (read_successful == mm_OK){
				// Copy into the buffer
				REG_Copyu32ToArray(destination, buff);
				*size = 4;

				return_value = true;

				// Set i to the limit, so that the next loop exits.
				i = sizeof(address_to_func_map) / sizeof(address_to_func_map[0]);
			}
			else{
				// An error reading this register - just return unknown error
				return_value = false;
			}
		}
	}

	// Special actions to take when reading a specific address
	switch (address) 
	{
		case reg_Uptime_addr:
			REG_Copyu32ToArray(BSP_GetUptime(), buff);
			*size = 4;
			return_value = true;
			break;
			
		case reg_Event_ConfA_addr:
		{
			// Update the event count
			mm_setEvent_ConfA_count(EVENT_EventCount());
			
			uint32_t read_successful = mm_getEvent_ConfA(&destination);
			if (read_successful == mm_OK){
				// Copy into the buffer
				REG_Copyu32ToArray(destination, buff);
				*size = 4;
				return_value = true;
			}
			else{
				// An error reading this register - just return unknown error
				return_value = false;
			}
		}
		break;
		case reg_Event_addr:
		{
			event_t current_event = {0};
			EVENT_GetEvent(&current_event);
			
			// Update the event from the buffer that is kept
			mm_setEvent_section(current_event.section);
			mm_setEvent_detail(current_event.detail);
			mm_setEvent_timestamp(current_event.timestamp);
			
			uint32_t read_successful = mm_getEvent(&destination);
			if (read_successful == mm_OK){
				// Copy into the buffer
				REG_Copyu32ToArray(destination, buff);
				*size = 4;
				return_value = true;
			}
			else{
				// An error reading this register - just return unknown error
				return_value = false;
			}
			
		}
		case reg_RTOS_Status0_addr:
			// This register gets cleared on read
			mm_setRTOS_Status0(0);
			
		break;
		
	}
	

    return return_value;
}

/*
 * Copy a given value into the buffer. Buffer should be big enough to handle the value
*/
void REG_Copyu32ToArray(const uint32_t value, uint8_t* data){
    data[0] = (uint8_t) ((value & 0x000000FF) >> 0);
    data[1] = (uint8_t) ((value & 0x0000FF00) >> 8);
    data[2] = (uint8_t) ((value & 0x00FF0000) >> 16);
    data[3] = (uint8_t) ((value & 0xFF000000) >> 24);
}

static uint32_t REG_CopyArrayToU32(const uint8_t* data){
    uint32_t res = (((uint32_t) data[0]) << 0) | (((uint32_t) data[1]) << 8) | (((uint32_t) data[2]) << 16) | (((uint32_t) data[3]) << 24);
    return res;
}


/*
 * Process all the stored messages. This function should be called regularly.
*/
void REG_vWriteToAddress(const uint32_t address, const uint8_t * data, const size_t length)
{
	// First decode the array as a uint32_t
	uint32_t deserialized = REG_CopyArrayToU32(data);
        
	// Do something based on the message
	switch (address)
	{
		// Read-only registers. Can't write to them
		case reg_Board_ID_addr:
		case reg_FW_Version_addr:
		case reg_HW_Version_addr:
		case reg_Uptime_addr:
		case reg_Event_ConfA_addr:
		case reg_Event_addr:
		case reg_MeasureVI_V3_addr:
		case reg_MeasurePower_V3_addr:
		case reg_MeasureVI_V5_addr:
		case reg_MeasurePower_V5_addr:
		case reg_MeasureVI_VBat_addr:
		case reg_MeasurePower_VBat_addr:
		case reg_MeasureVI_VBatAlt_addr:
		case reg_MeasurePower_VBatAlt_addr:
		case reg_MultiConf1_Status_addr:
		case reg_CSBoard_T0_addr:
		case reg_CSBoard_T1_addr:
		case reg_CSBoard_T2_addr:
		case reg_CSBoard_T3_addr:
		case reg_CSBoard_T4_addr:
		case reg_CSBoard_T5_addr:
		case reg_CSBoard_T6_addr:
		case reg_CSBoard_T7_addr:
		case reg_CSBoard_Current0I0_addr:
		case reg_CSBoard_Current0I1_addr:
		case reg_CSBoard_Current0I2_addr:
		case reg_CSBoard_Current1I0_addr:
		case reg_CSBoard_Current1I1_addr:
		case reg_CSBoard_Current1I2_addr:
		case reg_CSBoard_Current2I0_addr:
		case reg_CSBoard_Current2I1_addr:
		case reg_CSBoard_Current2I2_addr:
		case reg_CSBoard_Current3I0_addr:
		case reg_CSBoard_Current3I1_addr:
		case reg_CSBoard_Current3I2_addr:
		case reg_CSBoard_Current4I0_addr:
		case reg_CSBoard_Current4I1_addr:
		case reg_CSBoard_Current4I2_addr:
		case reg_CSBoard_Current5I0_addr:
		case reg_CSBoard_Current5I1_addr:
		case reg_CSBoard_Current5I2_addr:
		case reg_CSBoard_Current6I0_addr:
		case reg_CSBoard_Current6I1_addr:
		case reg_CSBoard_Current6I2_addr:
		case reg_CSBoard_Current7I0_addr:
		case reg_CSBoard_Current7I1_addr:
		case reg_CSBoard_Current7I2_addr:
			break;
		case reg_Scratchpad_addr:
			mm_setScratchpad(deserialized);
		break;
		
		case reg_Configured_Boards_addr:
			mm_setConfigured_Boards(deserialized);
			break;
		
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
			
		}
		break;
				
		case reg_I2CConfA_addr:
		{
			// Set the module speed here. The other values in the register are read when they are needed
			uint8_t spd = 0;
			mm_getI2CConfA_SPDFrom(&spd, deserialized);
			if ((spd >= 1) && (spd <= 40)){
				I2CTARGET_SetBaud(platform->i2c_target, spd * 10000);
				
				mm_setI2CConfA_SPD(spd);
			}
			
			uint8_t wrdel = 0 ;
			mm_getI2CConfA_WRDELFrom(&wrdel, deserialized);
			platform->i2c_target->write_read_delay = wrdel;
			mm_setI2CConfA_WRDEL(wrdel);
				
			uint8_t trdel = 0 ;
			mm_getI2CConfA_TRDELFrom(&trdel, deserialized);
			platform->i2c_target->tr_delay = trdel;
			mm_setI2CConfA_TRDEL(trdel);
		}
			break;
				
		case reg_I2CConfB_addr:
		{
			uint8_t i2c_address = 0;
			mm_getI2CConfB_ADDRFrom(&i2c_address, deserialized);
			
			I2CTarget_SetLegacyAddress(platform->i2c_target, i2c_address);
			
			mm_setI2CConfB(deserialized);
		}
			break;
				
		case reg_MultiConf0_addr:
			{
				mm_enabled_t autoclear = reg_enabled_disabled;
				mm_getMultiConf0_AutoCLRFrom(&autoclear, deserialized);
				MULTI_SetAutoClear(platform->multitester, autoclear==reg_enabled_enabled);
				mm_setMultiConf0_AutoCLR(autoclear);
			
				mm_enabled_t scan_enabled = reg_enabled_disabled;
				mm_getMultiConf0_ScanEnabledFrom(&scan_enabled, deserialized);
				MULTI_SetScanEnabled(platform->multitester, scan_enabled==reg_enabled_enabled);
				mm_setMultiConf0_ScanEnabled(scan_enabled);
			}
			break;
			
		case reg_CANConfA_addr:
			{
				uint16_t baudrate_kbps = 0;
				mm_getCANConfA_BaudRateFrom(&baudrate_kbps, deserialized);
				if (CANTARGET_SetBaud(platform->can_target, ((uint32_t)baudrate_kbps) * 1000))
				{
					mm_setCANConfA_BaudRate( baudrate_kbps);
				}
				
				mm_enabled_t FlipCanBytes;
				mm_getCANConfA_FlipCanBytesFrom(&FlipCanBytes, deserialized);
				if (FlipCanBytes)
				{
					if (CANTARGET_SetMode(platform->can_target, PLAN_S_COMPATIBILITY)){
						mm_setCANConfA_FlipCanBytes(FlipCanBytes);
					}
				}
				else {
					if (CANTARGET_SetMode(platform->can_target, CUBECOM_MODE)){
						mm_setCANConfA_FlipCanBytes(FlipCanBytes);
					}
				}
				
				mm_enabled_t EnableRetries;
				mm_getCANConfA_EnableRetriesFrom(&EnableRetries, deserialized);
				if (CANTARGET_EnableRetries(platform->can_target, EnableRetries == reg_enabled_enabled))
				{
					mm_setCANConfA_EnableRetries(EnableRetries);
				}
			}
			break;
		case reg_CANConfB_addr:
			{
				uint8_t new_address = 0;
				mm_getCANConfB_AddressFrom(&new_address, deserialized);
				
				if (CANTARGET_vSetAddress(platform->can_target, new_address)){
					mm_setCANConfB_Address(new_address);	
				}
				
			}
			break;
		case reg_SerialConf_addr:
			{
				mm_serialmode_t SerialCommMode;
				mm_getSerialConf_SerialModeFrom(&SerialCommMode, deserialized);
				if(UARTTARGET_SetCommMode(platform->uart_target, SerialCommMode)){
					mm_setSerialConf_SerialMode(SerialCommMode);
				}			
			}
			break;
		case reg_PC104Pins_addr:
			{
				mm_enabled_t ena;
				mm_getPC104Pins_ENAFrom(&ena, deserialized);
				PC104_setEnaPin(platform->pc104, ena == reg_enabled_enabled);
				mm_setPC104Pins_ENA(ena);
				
				mm_getPC104Pins_nRSTFrom(&ena, deserialized);
				PC104_setnRstPin(platform->pc104, ena == reg_enabled_enabled);
				mm_setPC104Pins_nRST(ena);
			}
			
			break;
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
			}
			break;
		case reg_MultiConf1_Set_addr:
			// Register definition precisely matches the bits.
			// Don't set the register, it reads 0 when read.
			MULTI_SetBitsFrom(platform->multitester, deserialized);
			break;
		case reg_MultiConf1_Clear_addr:
			MULTI_ClearBitsFrom(platform->multitester, deserialized);
			break;
			
		case reg_TE_Addr_0_Set_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_SetScanEnabled(platform->te_scanner, 0);
				}
				
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_SetTeBits(platform->te_scanner, 0, (deserialized >> 16) & 0x0FFF);
			}
			break;
		case reg_TE_Addr_0_Clear_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_ClearScanEnabled(platform->te_scanner, 0);
				}
			
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_ClearTeBits(platform->te_scanner, 0, (deserialized >> 16) & 0x0FFF);
			}
			break;
			
		case reg_TE_Addr_1_Set_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_SetScanEnabled(platform->te_scanner, 1);
				}
				
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_SetTeBits(platform->te_scanner, 1, (deserialized >> 16) & 0x0FFF);
			}
			break;
		case reg_TE_Addr_1_Clear_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_ClearScanEnabled(platform->te_scanner, 1);
				}
			
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_ClearTeBits(platform->te_scanner, 1, (deserialized >> 16) & 0x0FFF);
			}
			break;
			
		case reg_TE_Addr_2_Set_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_SetScanEnabled(platform->te_scanner, 2);
				}
				
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_SetTeBits(platform->te_scanner, 2, (deserialized >> 16) & 0x0FFF);
			}
			break;
		case reg_TE_Addr_2_Clear_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_ClearScanEnabled(platform->te_scanner, 2);
				}
			
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_ClearTeBits(platform->te_scanner, 2, (deserialized >> 16) & 0x0FFF);
			}
			break;
			
			
		case reg_TE_Addr_3_Set_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_SetScanEnabled(platform->te_scanner, 2);
				}
				
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_SetTeBits(platform->te_scanner, 3, (deserialized >> 16) & 0x0FFF);
			}
			break;
		case reg_TE_Addr_3_Clear_addr:
			{
				mm_enabled_t scanEnabled;
				mm_getTE_Addr_0_ScanEnabledFrom(&scanEnabled, deserialized);
				if (scanEnabled == reg_enabled_enabled){
					TE_Adaptor_ClearScanEnabled(platform->te_scanner, 2);
				}
			
				// We have deliberately made the bits align perfectly so we could do this.
				TE_Adaptor_ClearTeBits(platform->te_scanner, 3, (deserialized >> 16) & 0x0FFF);
			}
			break;
					
	}        
}
