#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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

struct OBC_RegisterData currentRegisters;

static size_t AddressesCount = 19;
static uint8_t Adresses[] = { OBC_REG_BOARD_ID, OBC_REG_FW_VERSION, OBC_REG_HW_VERSION, \
    OBC_REG_SCRATCHPAD, OBC_REG_SUPPORTED_BOARDS, OBC_REG_CONFIGURED_BOARDS, OBC_REG_CONFPOWER, \
    OBC_REG_MEASUREVI_V3, OBC_REG_MEASUREPOWER_V3, OBC_REG_MEASUREVI_V5, OBC_REG_MEASUREPOWER_V5, \
    OBC_REG_MEASUREVI_VBAT, OBC_REG_MEASUREPOWER_VBAT, OBC_REG_MEASUREVI_VBATALT, \
    OBC_REG_MEASUREPOWER_VBATALT, OBC_REG_I2CCONFA, OBC_REG_I2CCONFB,
    OBC_REG_XTXPINS,
    OBC_REG_XDCCONFIG};



void REG_vInit(){
    // Some values are fixed
    currentRegisters.board_id = 0x634F4243; //'cOBC'
    currentRegisters.fw_version = 0x00020102;
    currentRegisters.hw_version = 0x00000001;
    currentRegisters.supported_boards = 0x07;
    currentRegisters.i2cconfa = (0x5UL << OBC_REG_I2CCONFA_SPD_Pos) | (10UL << OBC_REG_I2CCONFA_TRDEL_Pos);

    currentRegisters.xdcconfig = 0x52 << OBC_REG_XDCCONFIG_ADDR_Pos;
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
    for (uint32_t i =0; i< AddressesCount; i++){
        if(address == Adresses[i]){
            found = true;
        }
    }   
    return found;
}


/*
Gets the register given by address, copies it's data into the data argument
Returns true if the address is valid, false otherwise.
*/
bool REG_vGet(const uint8_t address, uint8_t* data, uint8_t* length){
    bool copyResult = false;

    switch (address){
        case OBC_REG_BOARD_ID:
            REG_Copyu32ToArray(currentRegisters.board_id, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_FW_VERSION:
            REG_Copyu32ToArray(currentRegisters.fw_version, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_HW_VERSION:
            REG_Copyu32ToArray(currentRegisters.hw_version, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_SCRATCHPAD:
            REG_Copyu32ToArray(currentRegisters.scratchpad, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_SUPPORTED_BOARDS:
            REG_Copyu32ToArray(currentRegisters.supported_boards, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_CONFIGURED_BOARDS:
            REG_Copyu32ToArray(currentRegisters.configured_boards, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_CONFPOWER:
            REG_Copyu32ToArray(currentRegisters.confpower, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREVI_V3:
            REG_Copyu32ToArray(currentRegisters.measurevi_v3, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREPOWER_V3:
            REG_Copyu32ToArray(currentRegisters.measurepower_v3, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREVI_V5:
            REG_Copyu32ToArray(currentRegisters.measurevi_v5, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREPOWER_V5:
            REG_Copyu32ToArray(currentRegisters.measurepower_v5, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREVI_VBAT:
            REG_Copyu32ToArray(currentRegisters.measurevi_vbat, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREPOWER_VBAT:
            REG_Copyu32ToArray(currentRegisters.measurepower_vbat, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREVI_VBATALT:
            REG_Copyu32ToArray(currentRegisters.measurevi_vbatalt, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_MEASUREPOWER_VBATALT:
            REG_Copyu32ToArray(currentRegisters.measurepower_vbatalt, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_I2CCONFA:
            REG_Copyu32ToArray(currentRegisters.i2cconfa, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_I2CCONFB:
            REG_Copyu32ToArray(currentRegisters.i2cconfb, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_XTXPINS:
            // Shouldn't really be here, but fine for now
            
            currentRegisters.xtxpins = (currentRegisters.xtxpins & ~OBC_REG_XTXPINS_RDY_Msk) | ( ( (bool) XTX_bGetReady() ) << OBC_REG_XTXPINS_RDY_Pos );
            //currentRegisters.xtxpins = (currentRegisters.xtxpins & ~OBC_REG_XTXPINS_RDY_Msk) | (((uint32_t) ((bool) XTX_bGetReady())) << OBC_REG_XTXPINS_RDY_Pos);

            REG_Copyu32ToArray(currentRegisters.xtxpins, data);
            *length = 4;
            copyResult = true;
            break;
        case OBC_REG_XDCCONFIG:
            REG_Copyu32ToArray(currentRegisters.xdcconfig, data);
            *length = 4;
            copyResult = true;
            break;
        default:
            copyResult = false;
    }

    return copyResult;
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
        uint32_t bit = 0;
        
        // Do something based on the message
        switch (messages[messages_tail].address)
        {
            // Read-only registers. Can't write to them
            case OBC_REG_BOARD_ID:
            case OBC_REG_FW_VERSION:
            case OBC_REG_HW_VERSION:
            case OBC_REG_SUPPORTED_BOARDS:
            case OBC_REG_MEASUREVI_V3:
            case OBC_REG_MEASUREPOWER_V3:
            case OBC_REG_MEASUREVI_V5:
            case OBC_REG_MEASUREPOWER_V5:
            case OBC_REG_MEASUREVI_VBAT:
            case OBC_REG_MEASUREPOWER_VBAT:
            case OBC_REG_MEASUREVI_VBATALT:
            case OBC_REG_MEASUREPOWER_VBATALT:
                break;

            case OBC_REG_SCRATCHPAD:
                currentRegisters.scratchpad = deserialized;
                break;

            case OBC_REG_CONFIGURED_BOARDS:
                currentRegisters.configured_boards = deserialized;
                CONFIG_vDecodeBoardSet(0, (uint8_t) deserialized);
                break;

            case OBC_REG_CONFPOWER:
                currentRegisters.confpower = deserialized;
                CONFIG_vDecodePower((uint8_t) deserialized);
                break;
            case OBC_REG_I2CCONFA:
                // Set the module speed here. The other values in the register are read when they are needed
                I2C_SetEndpointSpeed( (uint32_t) ((deserialized & OBC_REG_I2CCONFA_SPD_Msk) >> OBC_REG_I2CCONFA_SPD_Pos) * 10000);
                currentRegisters.i2cconfa = deserialized;
                break;
            case OBC_REG_I2CCONFB:
                I2C_SetEndpointAddress((deserialized & OBC_REG_I2CCONFB_ADDR_Msk) >> OBC_REG_I2CCONFB_ADDR_Pos);
                currentRegisters.i2cconfb = deserialized;
                break;
            case OBC_REG_XTXPINS:
                currentRegisters.xtxpins = deserialized;
                bit = (deserialized & OBC_REG_XTXPINS_ENA_Msk) >> OBC_REG_XTXPINS_ENA_Pos;
                XTX_vSetEnable(bit);
                bit = (deserialized & OBC_REG_XTXPINS_NRST_Msk) >> OBC_REG_XTXPINS_NRST_Pos;
                XTX_SetNReset(bit);
                break;
            case OBC_REG_XDCCONFIG:
                currentRegisters.xdcconfig = deserialized;
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

void REG_UpdateVoltagePins(uint8_t newValue){
    currentRegisters.confpower = newValue;
}

void REG_UpdateVoltage(uint8_t channel, uint16_t value){
    switch (channel){
        case CHANNEL_3:
            currentRegisters.measurevi_v3 = (currentRegisters.measurevi_v3 & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_VOLTAGE_Pos);
            break;
        case CHANNEL_5:
            currentRegisters.measurevi_v5 = (currentRegisters.measurevi_v5 & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_VOLTAGE_Pos);
            break;    
        case CHANNEL_vBat:
            currentRegisters.measurevi_vbat = (currentRegisters.measurevi_vbat & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_VOLTAGE_Pos);
            break;    
        case CHANNEL_vBatAlt:
            currentRegisters.measurevi_vbatalt = (currentRegisters.measurevi_vbatalt & ~OBC_REG_MEASUREVI_VOLTAGE_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_VOLTAGE_Pos);
            break;
    }
}


void REG_UpdateCurrent(uint8_t channel, uint16_t value){
    switch (channel){
        case CHANNEL_3:
        currentRegisters.measurevi_v3 = (currentRegisters.measurevi_v3 & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_CURRENT_Pos);
        break;
        case CHANNEL_5:
        currentRegisters.measurevi_v5 = (currentRegisters.measurevi_v5 & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_CURRENT_Pos);
        break;
        case CHANNEL_vBat:
        currentRegisters.measurevi_vbat = (currentRegisters.measurevi_vbat & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_CURRENT_Pos);
        break;
        case CHANNEL_vBatAlt:
        currentRegisters.measurevi_vbatalt = (currentRegisters.measurevi_vbatalt & ~OBC_REG_MEASUREVI_CURRENT_Msk) | (((uint32_t) value) << OBC_REG_MEASUREVI_CURRENT_Pos);
        break;
    }
}


void REG_UpdatePower(uint8_t channel, uint32_t value){
    switch (channel)
    {
        case CHANNEL_3:
        currentRegisters.measurepower_v3 = value;
        break;
        case CHANNEL_5:
        currentRegisters.measurepower_v5 = value;
        break;
        case CHANNEL_vBat:
        currentRegisters.measurepower_vbat = value;
        break;
        case CHANNEL_vBatAlt:
        currentRegisters.measurepower_vbatalt = value;
        break;
    }
}

/*
 * Returns the current I2C Speed
*/
inline uint8_t REG_GetI2CSpeed(void){
    return (currentRegisters.i2cconfa & OBC_REG_I2CCONFA_SPD_Msk) >> OBC_REG_I2CCONFA_SPD_Pos;
}


/*
 * Updates the I2C speed in the register data and updates the module settings
*/
void REG_SetI2CSpeed(uint32_t newSpeed)
{
    currentRegisters.i2cconfa = (currentRegisters.i2cconfa & ~OBC_REG_I2CCONFA_SPD_Msk) | ( ((uint32_t) newSpeed / 10000) << OBC_REG_I2CCONFA_SPD_Pos);
    I2C_SetEndpointSpeed(newSpeed);
}

/*
 * Get the current I2C Address
*/
inline uint32_t REG_GetI2CAddress(void)
{
    return ((currentRegisters.i2cconfb & OBC_REG_I2CCONFB_ADDR_Msk) >> OBC_REG_I2CCONFB_ADDR_Pos);
}

/*
 * Update the address in the register data, and update the I2C module to use 
 * the new setting
*/
void REG_vSetI2CAddress(uint8_t address)
{
    currentRegisters.i2cconfb = (currentRegisters.i2cconfb & ~OBC_REG_I2CCONFB_ADDR_Msk) | ( ((uint32_t) address) << OBC_REG_I2CCONFB_ADDR_Pos);

    I2C_SetEndpointAddress(address);
}
