/*
 * xsteer.c
 *
 * Created: 2021/08/04 11:25:27
 *  Author: Kolijn
 */ 
#include <stdint.h>
#include <stdbool.h>

#include "xsteer.h"

#include "obc_controller_rev_A.h"
#include "bsp.h"

#include "can_endpoint.h"
#include "endpoints.h"
#include "std_message.h"
#include "i2c_endpoint.h"
#include "register_handler.h"
#include "serial_multiplexer.h"


void XSteer_vConfig(void) {

    // Configure endpoints
    I2C_vInitEndpoint(I2C_ENDPOINT, XSTEER_ADRESS, REG_GetI2CSpeed());
    //CAN_vInitEndpoint(CAN_ENDPOINT, OBC_CAN_ADRESS, XSTEER_ADRESS);

    // Register them with the sermux
    SERMUX_vRegisterEndpoint(I2C_ENDPOINT, &I2C_bEndpoint);
    //SERMUX_vRegisterEndpoint(CAN_ENDPOINT, &CAN_bEndpoint);
}

void XSteer_vDeConfig(void)
{
    // De-register endpoints
    SERMUX_vDeRegisterEndpoint(I2C_ENDPOINT);
    //SERMUX_vDeRegisterEndpoint(CAN_ENDPOINT);
}