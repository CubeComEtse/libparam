#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "event.h"
#include "Multitester.h"
#include "config.h"
#include "register_handler.h"
#include "i2c_endpoint.h"

#include "OBC.h"
#include "xtx.h"
  
static uint32_t REG_CopyArrayToU32(const uint8_t* data);

/*
 * This module handles the register interface exposed to the outside.
*/

struct register_change_message{
    uint8_t address;
    uint8_t data[4];
};
uint32_t messages_tail = 0;
uint32_t messages_head = 0;
#define messages_max_length 16
struct register_change_message messages[messages_max_length];



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
	{ reg_Supported_Boards_addr, mm_getSupported_Boards},
	{ reg_Configured_Boards_addr, mm_getConfigured_Boards},
	{ reg_Uptime_addr, mm_getUptime},
	{ reg_Event_ConfA_addr, mm_getEvent_ConfA},
	{ reg_Event_addr, mm_getEvent},
	{ reg_ConfPower_addr, mm_getConfPower},
	
	{ reg_MeasureVI_V3_addr, mm_getMeasureVI_V3},
	{ reg_MeasurePower_V3_addr, mm_getMeasurePower_V3},
	{ reg_MeasureVI_V5_addr, mm_getMeasureVI_V5},
	{ reg_MeasurePower_V5_addr, mm_getMeasurePower_V5},
	{ reg_MeasureVI_VBat_addr, mm_getMeasureVI_VBat},
	{ reg_MeasurePower_VBat_addr, mm_getMeasurePower_VBat},
	{ reg_MeasureVI_VBatAlt_addr, mm_getMeasureVI_VBatAlt},
	{ reg_MeasurePower_VBatAlt_addr, mm_getMeasurePower_VBatAlt },
	
	{ reg_I2CConfA_addr, mm_getI2CConfA},
	{ reg_I2CConfB_addr, mm_getI2CConfB},
	{ reg_ConfTempSense_addr, mm_getConfTempSense},
	
	{ reg_XTXpins_addr, mm_getXTXpins },
	{ reg_XTXMultitester_addr, mm_getXTXMultitester },
	{ reg_XDCConfig_addr, mm_getXDCConfig },
	
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
};


void REG_vInit(){
    // Some values are fixed
	mm_setBoard_ID(0x634F4243);
	mm_setFW_Version(0x00020203);
	mm_setHW_Version(0x00000001);
	
	mm_setSupported_Boards(reg_boardidentifier_xtx | reg_boardidentifier_xsteer | reg_boardidentifier_xdc |reg_boardidentifier_hdrtx_dfa | reg_boardidentifier_hdrtx);
	mm_setI2CConfA_SPD(0x5);
	mm_setI2CConfA_TRDEL(10);
	mm_setXDCConfig_ADDR(0x52);
	mm_setConfMulti(0x1111);
}


/*
Store any incoming messages. We don't want to perform SPI transactions while receiving I2C data,
So create this buffer between them.
*/
void REG_vAddMessage(const uint8_t address, const uint8_t* data){
    messages[messages_head].address = address;
    memcpy(messages[messages_head].data, data, 4);
     
    messages_head = (messages_head +1 ) % messages_max_length;
}

/*
 * Checks if the provided register address is a valid one. Returns true if it 
 * is, false otherwise
*/
bool REG_CheckAddress(const uint8_t address){
    bool found = false;
    for (int i = 0; i < (sizeof(address_to_func_map) / sizeof(address_to_func_map[0])); i++) {
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
bool REG_vGet(const uint32_t address, uint8_t * buff, uint8_t * size)
{
	uint32_t destination;
	bool return_value = false;

	// Loop through the entire array to find the correct function to call
	for (int i = 0; i < (sizeof(address_to_func_map) / sizeof(address_to_func_map[0])); i++)
	{
		if (((uint32_t) address_to_func_map[i].address) == address)
		{
			// Call the function
			uint32_t read_successful = address_to_func_map[i].readFunction(&destination);
			if (read_successful == mm_OK){
				// Copy into the buffer
				REG_Copyu32ToArray(destination, buff);
				// buff[0] = ( destination & 0xFF);
				// buff[1] = ((destination >> 8 ) & 0xFF);
				// buff[2] = ((destination >> 16) & 0xFF);
				// buff[3] = ((destination >> 24) & 0xFF);
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

	switch (address)
	{
		
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
		break;
		
		case reg_ConfMulti_addr: 
		{
			// Update bits
			mm_setConfMulti_MEnabled(MULTI_bGetEnabled());
			mm_setConfMulti_AutoCLR(MULTI_bGetAutoClear());
			
			mm_setConfMulti_FanPos1(MULTI_bGetChannelFan(Position1));
			mm_setConfMulti_FanPos2(MULTI_bGetChannelFan(Position2));
			mm_setConfMulti_FanPos3(MULTI_bGetChannelFan(Position3));
			mm_setConfMulti_FanPos4(MULTI_bGetChannelFan(Position4));
			
			mm_setConfMulti_RfSwENA(MULTI_bGetRfSwitchEnabled());
			mm_setConfMulti_RfSwChan(MULTI_u8GetRFSwitchChannel());
			
			
			uint32_t read_successful = mm_getConfMulti(&destination);
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
				
		case reg_XTXpins_addr: 
		{
			// Shouldn't really be here, but fine for now
			mm_setXTXpins_RDY(XTX_bGetReady());

			uint32_t read_successful = mm_getXTXpins(&destination);
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
void REG_vProcessMessages(void){
    // Only allow one message per call
    if (messages_tail != messages_head)
    {
        // First decode the array as a uint32_t
        uint32_t deserialized = REG_CopyArrayToU32(messages[messages_tail].data);
        
        // Do something based on the message
        switch (messages[messages_tail].address)
        {
            // Read-only registers. Can't write to them
            case reg_Board_ID_addr:
            case reg_FW_Version_addr:
            case reg_HW_Version_addr:
            case reg_Supported_Boards_addr:
            case reg_Uptime_addr:
            case reg_MeasureVI_V3_addr:
            case reg_MeasurePower_V3_addr:
            case reg_MeasureVI_V5_addr:
            case reg_MeasurePower_V5_addr:
            case reg_MeasureVI_VBat_addr:
            case reg_MeasurePower_VBat_addr:
            case reg_MeasureVI_VBatAlt_addr:
            case reg_MeasurePower_VBatAlt_addr:
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
                CONFIG_vDecodeBoardSet(0, (uint8_t) deserialized);
                break;

            case reg_ConfPower_addr:
				mm_setConfPower(deserialized);
                CONFIG_vDecodePower((uint8_t) deserialized);
                break;
				
            case reg_I2CConfA_addr:
			{
                // Set the module speed here. The other values in the register are read when they are needed
				uint8_t spd = 0;
				mm_getI2CConfA_SPDFrom(&spd, deserialized);
				
                I2C_SetEndpointSpeed( (uint32_t) (spd) * 10000);
                mm_setI2CConfA(deserialized);
			}
                break;
				
            case reg_I2CConfB_addr:
			{
				uint8_t address = 0;
				mm_getI2CConfB_ADDRFrom(&address, deserialized);
                I2C_SetEndpointAddress(address);
				mm_setI2CConfB(deserialized);
			}
                break;
				
			case reg_ConfMulti_addr:
			{
				mm_enabled_t multiEnabled = reg_enabled_disabled;
				mm_enabled_t autoClear = reg_enabled_disabled;
				mm_getConfMulti_MEnabledFrom(&multiEnabled, deserialized);
				mm_getConfMulti_AutoCLRFrom(&multiEnabled, deserialized);
				
				MULTI_vSetEnabled(multiEnabled==reg_enabled_enabled);
				MULTI_vSetAutoClear(autoClear==reg_enabled_enabled);
				
				mm_enabled_t fanEnabled;
				mm_getConfMulti_FanPos1From(&fanEnabled, deserialized);
				MULTI_vSetChannelFan(Position1, fanEnabled == reg_enabled_enabled);
				
				mm_getConfMulti_FanPos2From(&fanEnabled, deserialized);
				MULTI_vSetChannelFan(Position2, fanEnabled == reg_enabled_enabled);
				
				mm_getConfMulti_FanPos3From(&fanEnabled, deserialized);
				MULTI_vSetChannelFan(Position3, fanEnabled == reg_enabled_enabled);
				
				mm_getConfMulti_FanPos4From(&fanEnabled, deserialized);
				MULTI_vSetChannelFan(Position4, fanEnabled == reg_enabled_enabled);
				
				mm_enabled_t RfSwEna;
				mm_getConfMulti_RfSwENAFrom(&RfSwEna, deserialized);
				MULTI_vSetRfSwitchEnabled(RfSwEna == reg_enabled_enabled);
				
				mm_enabled_t RfSwChan;
				mm_getConfMulti_RfSwENAFrom(&RfSwChan, deserialized);
				MULTI_vSetRFSwitchChannel(RfSwChan == reg_enabled_enabled);
				
				mm_setConfMulti(deserialized);
			}
				break;
				
            case reg_XTXpins_addr: 
				mm_setXTXpins(deserialized);
				
				mm_enabled_t val;
				mm_getXTXpins_ENAFrom(&val, deserialized);
                XTX_vSetEnable(val == reg_enabled_enabled);
				
                mm_getXTXpins_nRSTFrom(&val, deserialized);
                XTX_SetNReset(val == reg_enabled_enabled);
                break;
				
			case reg_XTXMultitester_addr: 
				mm_setXTXMultitester(deserialized);
				
				mm_enabled_t dest;
				mm_getXTXMultitester_POS1_XTX_EN(&dest);
				MULTI_vSetChannelEnabled(Position1, dest);
				
				mm_getXTXMultitester_POS2_XTX_EN(&dest);
				MULTI_vSetChannelEnabled(Position2, dest);
				
				mm_getXTXMultitester_POS3_XTX_EN(&dest);
				MULTI_vSetChannelEnabled(Position3, dest);
				
				mm_getXTXMultitester_POS4_XTX_EN(&dest);
				MULTI_vSetChannelEnabled(Position4, dest);
				
				
				mm_getXTXMultitester_POS1_XTX_nReset(&dest);
				MULTI_vSetChannelnReset(Position1, dest);
				
				mm_getXTXMultitester_POS2_XTX_nReset(&dest);
				MULTI_vSetChannelnReset(Position2, dest);
				
				mm_getXTXMultitester_POS3_XTX_nReset(&dest);
				MULTI_vSetChannelnReset(Position3, dest);
				
				mm_getXTXMultitester_POS4_XTX_nReset(&dest);
				MULTI_vSetChannelnReset(Position4, dest);
				
				// Set all the pins in one shot
				MULTI_vSetChannelPowerPins(deserialized);
				
				mm_setXTXMultitester(MULTI_u32GetPins());
				
				break;
            case reg_XDCConfig_addr: 
                mm_setXDCConfig(deserialized);
                // If already configured, configure again
                if (CONFIG_GetCurrentBoardconfig() == CONF_BOARD_XDC){
                    XDC_vConfig();
                }
                break;
        }        

        // The message has been handled
        messages_tail = (messages_tail + 1 ) % messages_max_length;
    }
}


/*
 * Returns the current I2C Speed
*/
inline uint8_t REG_GetI2CSpeed(void){
	uint8_t speed;
	mm_getI2CConfA_SPD(&speed);
    return speed;
}


/*
 * Updates the I2C speed in the register data and updates the module settings
*/
void REG_SetI2CSpeed(uint32_t newSpeed)
{
	mm_setI2CConfA_SPD(newSpeed / 10000);
    I2C_SetEndpointSpeed(newSpeed);
}

/*
 * Get the current I2C Address
*/
inline uint32_t REG_GetI2CAddress(void)
{
	uint8_t addr;
	mm_getI2CConfB_ADDR(&addr);
    return addr;
}

/*
 * Update the address in the register data, and update the I2C module to use 
 * the new setting
*/
void REG_vSetI2CAddress(uint8_t address)
{
	mm_setI2CConfB_ADDR(address);
    I2C_SetEndpointAddress(address);
}