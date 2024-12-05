/*
 * Platform.h
 *
 * Created: 2024/11/28 09:23:50
 *  Author: Kolijn
 */ 

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <stdbool.h>

#include "bsp.h"

#include "register_map.h"
#include "ltc2499.h"
#include "ltc2992.h"
#include "gse_manager.h"
#include "sermux_v3.h"
#include "pc_messages.h"
#include "led_driver.h"

#include "can_target.h"
#include "i2c_target.h"
#include "local_target.h"

#include "Multitester.h"

typedef struct
{
	ltc2992_device_t * power_measure_1;
	ltc2992_device_t * power_measure_2;
	ltc2499_device_t * cs_board;

	gse_manager_t * gse_manager;

	local_target_t * local_target;
	i2c_target_t * i2c_target;
	can_target_t * can_target;

	led_driver_t * led_driver;
	
	
	sermux_v3_t * sermux_v3;
	
	rf_relay_config_t * rf_relay_1;
	rf_relay_config_t * rf_relay_2;
	multitester_t * multitester;

}platform_t;


void PLATFORM_vInit(bsp_t * bsp);
void PLATFORM_vConfigureAll(platform_t * handle);
platform_t * PLATFORM_get(void);

#endif /* PLATFORM_H */
