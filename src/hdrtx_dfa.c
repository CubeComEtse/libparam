/*
 * hdrtx_dfa.c
 *
 * Created: 2022/11/30 07:57:14
 *  Author: Kolijn
 */ 

#include "bsp.h"
#include "endpoints.h"
#include "can_endpoint.h"
#include "serial_multiplexer.h"


void HDRTX_DFA_vConfig(){
	
	// Setup XTXEn pin
	ioport_enable_pin(XTX_EN_PIN);
	ioport_set_pin_level(XTX_EN_PIN, 0);
	ioport_set_pin_dir(XTX_EN_PIN, IOPORT_DIR_OUTPUT);
		
	// Setup nReset
	ioport_enable_pin(XTX_nRST_PIN);
	ioport_set_pin_level(XTX_nRST_PIN, 0);
	ioport_set_pin_dir(XTX_nRST_PIN, IOPORT_DIR_OUTPUT);
	
	BSP_vCanSetAddressFilter(OBC_CAN_ADRESS<<8, OBC_CAN_MASK<<8);
	
	// Configure endpoints
	// The 0 value is hard-coded, but corresponds to can_message_t.DFA_CAN_MODE
	CAN_vInitEndpoint(CAN_ENDPOINT_DFA, OBC_CAN_ADRESS, HDRTX_CAN_ADRESS, 1);
	
	//DFA format has the address at a different place
	BSP_vCanSetAddressFilter(OBC_CAN_ADRESS<<8, OBC_CAN_MASK<<8);

	// Register them with the sermux
	SERMUX_vRegisterEndpoint(CAN_ENDPOINT_DFA, &CAN_bEndpoint);
	SERMUX_vRegisterEndpoint(CAN_ENDPOINT_DFA_FW, &CAN_bDFAFirmwareEndpoint);
}

void HDRTX_DFA_vDeConfig(void){
	SERMUX_vDeRegisterEndpoint(CAN_ENDPOINT_DFA);
}

void HDRTX_DFA_vProcess(void){
	
}
