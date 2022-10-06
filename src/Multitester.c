/*
 * Multitester.c
 *
 * Created: 2022/08/15 11:40:55
 *  Author: Kolijn
 */ 

#include "Multitester.h"

#include "event.h"
#include "bsp.h"
#include "i2c_driver.h"
#include "i2c_endpoint.h"



// The I2C Expander has two ports, with 8 outputs each. Outputs 0-3 are for Position1, 4-7
// are the same but for port2. The pins are repeated in the same order, so we can use an offset
#define ENA_PIN			(1 << 0)
#define POWER_PIN		(1 << 1)
#define nRESET_PIN		(1 << 2)
#define FAN_PIN			(1 << 3)

#define PCA9555_CMD_IN_PORT0	0
#define PCA9555_CMD_IN_PORT1	1
#define PCA9555_CMD_OUT_PORT0	2
#define PCA9555_CMD_OUT_PORT1	3
#define PCA9555_CMD_PI_PORT0	4
#define PCA9555_CMD_PI_PORT1	5
#define PCA9555_CMD_CFG_PORT0	6
#define PCA9555_CMD_CFG_PORT1	7

#define PCA9555_ADDR 0b0100000
#define PCA9555_RFSWITCH_ADDR 0b0100001

static void MULTI_vSetPIN(channel_id_t channel, uint16_t pin_mask, bool ena);
static bool MULTI_bGetPIN(channel_id_t channel, uint16_t pin_mask);
static bool MULTI_bInitRFSwitch(void);
static void MULTI_vDeinitRFSwitch(void);
static bool MULTI_vSetRfSwitchChannel(uint8_t channel);

static uint16_t portbits;
// CurrentState of the MultiTester. 
// If it is enabled, desiredState is set, and the process loop will enable it.
static bool currentState = false;
static bool desiredState = false;

static bool autoClear = true;

static bool bitsUpdated = false;

static bool rfSwitchEnabled = true;
static bool rfSwitchDesiredState = true;
static uint8_t rfSwitchChannel = 0;
static uint8_t rfSwitchDesiredChannel = 0;

bool MULTI_vInit(void)
{
	uint8_t tx_buffer[] = {0x22, 0x22};
		
	// First, set ENA lines and Fan lines to 1
	I2C_DRIVER_bWritePlain(I2C_psGetDriver(), PCA9555_ADDR, PCA9555_CMD_OUT_PORT0, tx_buffer, 2);
	portbits = 0x2222;
	
	uint8_t rx_buffer[] = {0x00, 0x00};
	I2C_DRIVER_bReadPlain(I2C_psGetDriver(), PCA9555_ADDR, PCA9555_CMD_OUT_PORT0, rx_buffer, 2);
	
	if (!((rx_buffer[0] == tx_buffer[0]) && (rx_buffer[1] == tx_buffer[1])))
	{
		EVENT_AddEvent(EVENT_SECTION_MULTI, MULTITESTER_DID_NOT_RESPOND);
		return false;
	}
	
	tx_buffer[0] = 0x00;
	tx_buffer[1] = 0x00;
	
	// Then make all pins outputs
	I2C_DRIVER_bWritePlain(I2C_psGetDriver(), PCA9555_ADDR, PCA9555_CMD_CFG_PORT0, tx_buffer, 2);
	
	return true;
}

void MULTI_vDeinit(void)
{
	uint8_t tx_buffer[] = {0xFF, 0xFF};
	
	// Then make all pins inputs
	I2C_DRIVER_bWritePlain(I2C_psGetDriver(), PCA9555_ADDR, PCA9555_CMD_CFG_PORT0, tx_buffer, 2);
	
}

void MULTI_vProcess(void){
	if (desiredState && !currentState){
		// Turn on MultiTester
		if (MULTI_vInit())
		{
			currentState = desiredState;
		}
		else{
			desiredState = currentState;
		}
	}	
	if (!desiredState && currentState){
		// Turn off MultiTester
		MULTI_vDeinit();
		
		currentState = desiredState;
	}
	
	// If the rf switch is not on and we want it to be on
	if (rfSwitchEnabled == false && rfSwitchDesiredState == true){
		if (MULTI_bInitRFSwitch()){
			rfSwitchEnabled = true;
		}
		else{
			rfSwitchEnabled = false;
			rfSwitchDesiredState = false;
		}
	}
	if (rfSwitchEnabled == true && rfSwitchDesiredState == false){
		MULTI_vDeinitRFSwitch();
		rfSwitchEnabled = false;
	}
	if (rfSwitchEnabled && rfSwitchChannel != rfSwitchDesiredChannel){
		if (MULTI_vSetRfSwitchChannel(rfSwitchDesiredChannel))
		{
			rfSwitchChannel = rfSwitchDesiredChannel;
		}
		else{
			rfSwitchDesiredChannel = rfSwitchChannel;
		}
	}
	
	if (currentState && bitsUpdated){
		
		uint8_t tx_buffer[] = {(portbits & 0xFF), ((portbits>>8) & 0xFF)};
		
		// First, set all outputs 0
		I2C_DRIVER_bWritePlain(I2C_psGetDriver(), PCA9555_ADDR, PCA9555_CMD_OUT_PORT0, tx_buffer, 2);
		
		bitsUpdated = false;
	}
}

/*
 * Set/Clears the Enable line (XTX enable) for the given
*/
void MULTI_vSetChannelEnabled(channel_id_t channel, bool ena){
	MULTI_vSetPIN(channel, ENA_PIN, ena);
}

/*
 * Set/Clears the Power line, controlling the 3.3v line. This has a inverter in it
*/
void MULTI_vSetChannelPowerPins(const uint16_t pins){
	
	uint16_t prevState = MULTI_u32GetPins();
	
	// For each of the pins, set the output.
	// IF this pin is newly activate, disable the rest
	
	if (pins & (POWER_PIN << 0))
	{
		MULTI_vSetPIN(Position1, POWER_PIN, false);
		if (autoClear && !(prevState & (POWER_PIN << 0)))
		{				
			MULTI_vSetPIN(Position2, POWER_PIN, true);
			MULTI_vSetPIN(Position3, POWER_PIN, true);
			MULTI_vSetPIN(Position4, POWER_PIN, true);
			return;
		}
	}
	else{
		MULTI_vSetPIN(Position1, POWER_PIN, true);
	}
	
	
	if (pins & (POWER_PIN << 4))
	{
		MULTI_vSetPIN(Position2, POWER_PIN, false);
		if (autoClear &&  !(prevState & (POWER_PIN << 4)))
		{
			MULTI_vSetPIN(Position1, POWER_PIN, true);
			MULTI_vSetPIN(Position3, POWER_PIN, true);
			MULTI_vSetPIN(Position4, POWER_PIN, true);
			return;
		}
	}
	else{
		MULTI_vSetPIN(Position2, POWER_PIN, true);
	}
	
	if (pins & (POWER_PIN << 8))
	{
		MULTI_vSetPIN(Position3, POWER_PIN, false);
		if (autoClear &&  !(prevState & (POWER_PIN << 8)))
		{
			MULTI_vSetPIN(Position1, POWER_PIN, true);
			MULTI_vSetPIN(Position2, POWER_PIN, true);
			MULTI_vSetPIN(Position4, POWER_PIN, true);
			return;
		}
	}
	else{
		MULTI_vSetPIN(Position3, POWER_PIN, true);
	}
	
	if (pins & (POWER_PIN << 12))
	{
		MULTI_vSetPIN(Position4, POWER_PIN, false);
		if (autoClear &&  !(prevState & (POWER_PIN << 12)))
		{
			MULTI_vSetPIN(Position1, POWER_PIN, true);
			MULTI_vSetPIN(Position2, POWER_PIN, true);
			MULTI_vSetPIN(Position3, POWER_PIN, true);
			return;
		}
	}
	else{
		MULTI_vSetPIN(Position4, POWER_PIN, true);
	}

}

/*
 * Enable/Disable the nReset line.
*/
void MULTI_vSetChannelnReset(channel_id_t channel, bool ena){
	MULTI_vSetPIN(channel, nRESET_PIN, ena);
}

/*
 * Enable/Disable the fan
*/
void MULTI_vSetChannelFan(channel_id_t channel, bool ena){
	MULTI_vSetPIN(channel, FAN_PIN, ena);
}

bool MULTI_bGetChannelFan(const channel_id_t channel){
	uint8_t pin_offset =0;
	switch (channel){
		case Position1:
		pin_offset = 0;
		break;
		case Position2:
		pin_offset = 4;
		break;
		case Position3:
		pin_offset = 8;
		break;
		case Position4:
		pin_offset = 12;
		break;
	}
	
	return ((portbits >> pin_offset) & FAN_PIN)> 0;
}

static void MULTI_vSetPIN(channel_id_t channel, uint16_t pin_mask, bool ena){
	uint8_t pin_offset =0;
	switch (channel){
		case Position1:
		pin_offset = 0;
		break;
		case Position2:
		pin_offset = 4;
		break;
		case Position3:
		pin_offset = 8;
		break;
		case Position4:
		pin_offset = 12;
		break;
	}
	
	if (ena){
		portbits |= (pin_mask << pin_offset);
	}
	else{
		portbits &= ~(pin_mask << pin_offset);
	}
	
	bitsUpdated = true;
}

static bool MULTI_bGetPIN(channel_id_t channel, uint16_t pin_mask){
	uint8_t pin_offset =0;
	switch (channel){
		case Position1:
		pin_offset = 0;
		break;
		case Position2:
		pin_offset = 4;
		break;
		case Position3:
		pin_offset = 8;
		break;
		case Position4:
		pin_offset = 12;
		break;
	}

	return (portbits & (pin_mask << pin_offset)) > 0;
}

inline void MULTI_vSetEnabled(bool ena) 
{
	desiredState = ena;
}

inline bool MULTI_bGetEnabled(){
	return currentState;
}


inline void MULTI_vSetAutoClear(bool ena){
	autoClear = ena;
}

inline bool MULTI_bGetAutoClear(){
	return autoClear;
}

/*
Get all the pins.
*/

uint32_t MULTI_u32GetPins(){
	// We need to invert the power pins. 
	return portbits ^ ((POWER_PIN) | (POWER_PIN<<4) | (POWER_PIN<< 8)| (POWER_PIN<<12));
}



inline bool MULTI_bGetRfSwitchEnabled(void){
	return rfSwitchEnabled;
}

void MULTI_vSetRfSwitchEnabled(bool value){
	rfSwitchDesiredState = value;
}


inline uint8_t MULTI_u8GetRFSwitchChannel(void){
	return rfSwitchChannel;
}

void MULTI_vSetRFSwitchChannel(uint8_t channel){
	if (channel > 4){
		return;
	}
	rfSwitchDesiredChannel = channel;
}

/*
 * Initialize the RF Switch. Returns true if it answered.
 * This function will also set it to the desired channel.
*/
bool MULTI_bInitRFSwitch(void){
	
	// First try reading from the device - it should answer
	uint8_t rx_buffer[] = {0x00, 0x00};
	bool answer = I2C_DRIVER_bReadLocal(I2C_psGetDriver(), PCA9555_RFSWITCH_ADDR, PCA9555_CMD_OUT_PORT0, rx_buffer, 2);
	
	if (!answer){
		return false;
	}
	
	// Device answered - we can switch channel
	return MULTI_vSetRfSwitchChannel(rfSwitchDesiredChannel);

}

/*
 * Set the RF Control board to the specified channel. Returns true if the 
 * I2C Comms was successful - false otherwise
*/
bool MULTI_vSetRfSwitchChannel(uint8_t channel){
	uint8_t tx_buffer[] = {0x00, 0x00};
		
	if (rfSwitchDesiredChannel != 0){
		tx_buffer[0] = 0x1 << (rfSwitchDesiredChannel-1);
	}
		
	return I2C_DRIVER_bWritePlain(I2C_psGetDriver(), PCA9555_RFSWITCH_ADDR, PCA9555_CMD_OUT_PORT0, tx_buffer, 2);
}

void MULTI_vDeinitRFSwitch(void){
	MULTI_vSetRfSwitchChannel(0);
}