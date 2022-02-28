/*
 * xdc.c
 *
 * Created: 2021/09/03 09:34:56
 *  Author: Kolijn
 */ 

#include "obc_controller_rev_A.h"
#include "bsp.h"

#include "can_endpoint.h"
#include "endpoints.h"
#include "std_message.h"
#include "i2c_endpoint.h"
#include "serial_multiplexer.h"
#include "register_handler.h"

#include "xdc.h"

#define XDC_DEFAULT_I2C_ADDRESS 0x52
#define XDC_DEFAULT_I2C_SPEED 400000UL

void XDC_vConfig(void)
{
    // Configure I2C Settings
    REG_SetI2CSpeed(XDC_DEFAULT_I2C_SPEED);
    REG_vSetI2CAddress(XDC_DEFAULT_I2C_ADDRESS);
    
    // Register them with the sermux
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT, &I2C_bEndpoint);
    //SERMUX_vRegisterEndpoint(CAN_ENDPOINT, &CAN_bEndpoint);
}


void XDC_vDeConfig(void)
{
    // De-register endpoints
    SERMUX_vDeRegisterEndpoint(I2C_ENDPOINT);
    //SERMUX_vDeRegisterEndpoint(CAN_ENDPOINT);
}