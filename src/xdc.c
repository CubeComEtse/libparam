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

void XDC_vConfig(void)
{
    uint8_t address = REG_GetXDCAddress();

    // Configure endpoints
    I2C_vInitEndpoint(I2C_ENDPOINT, address, REG_GetI2CSpeed());
    //CAN_vInitEndpoint(CAN_ENDPOINT, OBC_CAN_ADRESS, XSTEER_ADRESS);

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