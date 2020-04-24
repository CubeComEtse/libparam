/*
 * board_endpoint.c
 *
 * Created: 2020/04/24 13:30:49
 *  Author: Kolijn
 */ 

#include "config.h"
#include "bsp.h"
#include "ltc2992.h"
#include <stdbool.h>
#include <stdint.h>

// Local Variables
static struct ltc2992_device power_measure_1;
static struct ltc2992_device power_measure_2;

// Local functions
void CONFIG_vDecodePowerSetting(uint8_t val);


void CONFIG_vInit(void) {

    LTC2992_vNormalSetup(&power_measure_1, LTC2992_u8GenAddr(0, 0));
    LTC2992_vNormalSetup(&power_measure_2, LTC2992_u8GenAddr(0, 2));

    //Setup functions for LTC2992
    power_measure_1.i2c_write_function = BSP_vPowerSenseWriteFunction;
    power_measure_1.i2c_read_function = BSP_vPowerSenseReadFunction;

    power_measure_2.i2c_write_function = BSP_vPowerSenseWriteFunction;
    power_measure_2.i2c_read_function = BSP_vPowerSenseReadFunction;

}

bool CONFIG_bConfigEndpoint(const uint8_t* rx_buffer, const uint16_t rx_length, uint8_t* tx_buffer, uint16_t* tx_length)
{
    *tx_length = 0;
    
    // Discard this message if it is too short
    if (rx_length < 2) {
        return true;
    }

    switch(rx_buffer[0]) {
    case CONF_POWER:
        //Turn on voltage to pins
        break;
    case CONF_MEASURE:
        //Measure power on LTC ICs
        break;
    case CONF_SPI:
        // Configure SPI
        break;
    default: break;
    }
    return true;
}

void CONFIG_vDecodePowerSetting(uint8_t val) {
    BSP_vSetPowerEn(EN_5V_BUS, (val & CONF_POWER_5V_FLAG) > 0 );
    BSP_vSetPowerEn(EN_3V3_BUS, (val & CONF_POWER_3V3_FLAG) > 0 );
    BSP_vSetPowerEn(EN_VBAT_BUS, (val & CONF_POWER_VBAT_FLAG) > 0 );
    BSP_vSetPowerEn(EN_VBATALT_BUS, (val & CONF_POWER_VBATALT_FLAG) > 0 );
}