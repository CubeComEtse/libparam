/*
 * hdrtx.c
 *
 * Created: 2023/03/04 20:15:32
 *  Author: Kolijn
 */ 

#include "hdrtx.h"

#include "bsp.h"
#include "can_driver.h"
#include "endpoints.h"
#include "i2c_endpoint.h"
#include "can_endpoint.h"
#include "register_handler.h"
#include "serial_multiplexer.h"

#define HDRTX_DEFAULT_I2C_SPEED 400000
#define HDRTX_DEFAULT_I2C_ADDRESS 0x26


void HDRTX_vConfig(){
	
	// The HDRTX also uses enable and nReset pins.
	
	// Setup XTXEn pin
	ioport_enable_pin(XTX_EN_PIN);
	ioport_set_pin_level(XTX_EN_PIN, 0);
	ioport_set_pin_dir(XTX_EN_PIN, IOPORT_DIR_OUTPUT);
	    
	// Setup nReset
	ioport_enable_pin(XTX_nRST_PIN);
	ioport_set_pin_level(XTX_nRST_PIN, 0);
	ioport_set_pin_dir(XTX_nRST_PIN, IOPORT_DIR_OUTPUT);

	// Setting these values in the Register_Handler will also set the values in the I2C module
	REG_SetI2CSpeed(HDRTX_DEFAULT_I2C_SPEED);
	REG_vSetI2CAddress(HDRTX_DEFAULT_I2C_ADDRESS);

	// Configure endpoints
	// The 0 value is hard-coded, but corresponds to can_message_t.CC_CAN_MODE
	CAN_vInitEndpoint(CAN_ENDPOINT_V2, OBC_CAN_ADRESS, HDRTX_DEFAULT_I2C_ADDRESS, CC_CAN_2_MODE);
	BSP_vCanSetAddressFilter(OBC_CAN_ADRESS, OBC_CAN_MASK);
	

	// Register them with the sermux
	SERMUX_vRegisterEndpoint(CAN_ENDPOINT_V2, &CAN_bEndpoint);
	//SERMUX_vRegisterEndpoint(I2C_ENDPOINT_CHKSM, &I2C_bEndpointNoChecksum);
	
	// Don't think we need to register i2c endpoint
	
}

void HDRTX_vDeConfig(void){
	SERMUX_vDeRegisterEndpoint(CAN_ENDPOINT_V2);
	// SERMUX_vDeRegisterEndpoint(CAN_ENDPOINT);
}

void HDRTX_vProcess(void){
	
}

/*
bool HDRTX_vConEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length) {
	if (rx_buffer[DIR_idx] == WRITE) {
		switch(rx_buffer[ADDR_idx]) {
			case XTX_ENABLED:
			XTX_vSetEnable(rx_buffer[DATA_idx]);
			break;
			case XTX_NRESET:
			XTX_SetNReset(rx_buffer[DATA_idx]);
			break;
		}
	}
	else {
		switch(rx_buffer[ADDR_idx]) {
			case XTX_ENABLED:
			tx_buffer[DATA_idx] = XTX_bGetEnable();
			break;
			case XTX_NRESET:
			tx_buffer[DATA_idx] = XTX_bGetNReset();
			break;
			case XTX_RDY:
			XTX_vProcess();
			tx_buffer[DATA_idx] = XTX_bGetReady();
			break;
			default:
			// Return before message is constructed
			return false;
		}
		tx_buffer[ADDR_idx] = rx_buffer[ADDR_idx];
		tx_buffer[DIR_idx] = rx_buffer[DIR_idx];
		tx_buffer[LEN_idx] = 1;
		*tx_length = 4;
		return true;
	}
	return false;
}
*/