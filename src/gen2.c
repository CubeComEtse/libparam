/*
 * gen2.c
 *
 * Created: 2023/11/13 10:43:18
 *  Author: Kolijn
 */ 

#include "bsp.h"
#include "can_driver.h"
#include "endpoints.h"
#include "i2c_endpoint.h"
#include "can_endpoint.h"
#include "register_handler.h"
#include "serial_multiplexer.h"

#define GEN2_DEFAULT_I2C_SPEED 400000
#define GEN2_DEFAULT_I2C_ADDRESS 0x26

void GEN2_Config(){
	
	// The HDRTX also uses enable and nReset pins.
		
	// Setup XTXEn pin
	ioport_enable_pin(XTX_EN_PIN);
	ioport_set_pin_level(XTX_EN_PIN, 0);
	ioport_set_pin_dir(XTX_EN_PIN, IOPORT_DIR_OUTPUT);
		
	// Setup nReset
	ioport_enable_pin(XTX_nRST_PIN);
	ioport_set_pin_level(XTX_nRST_PIN, 0);
	ioport_set_pin_dir(XTX_nRST_PIN, IOPORT_DIR_OUTPUT);
}

void GEN2_vDeconfig(){
	
}