/*
 * gse_manager.h
 *
 * Created: 2024/10/04 08:14:58
 *  Author: Kolijn
 */ 


#ifndef GSE_MANAGER_H_
#define GSE_MANAGER_H_

#include "ltc2992.h"
#include "ltc2499.h"

typedef enum{
	POWER_3V3 = 1,
	POWER_5V,
	POWER_VBAT,
	POWER_VBAT_ALT,
	POWER_3V3_UTIL,
}power_rail_id_t;

typedef struct {
	// Pointers to devices on the GSE board
	ltc2992_device_t * power_measure_1;
	ltc2992_device_t * power_measure_2;
	ltc2499_device_t  * cs_board;
	
	void (*set_gpio_pin) (uint32_t pin, bool value);
	uint32_t enable_3v3_pin; // EGSE Version 2: 3v3 ext enable line
	uint32_t enable_5v_pin; // Not used in EGSE Version 2
	uint32_t enable_vbat_pin;
	uint32_t enable_vbatalt_pin; // Not used in EGSE Version 2
	
	// EGSE Version 2:
	uint32_t enable_3v3_util_pin;
	
	uint8_t board_version;
	
	bool bCSBoardenabled;
}gse_manager_t;


void GSE_MANAGER_Init(gse_manager_t * handle);
void GSE_MANAGER_SetBusPowerSwitch(gse_manager_t * handle, const power_rail_id_t power, const bool setting);
void GSE_MANAGER_SetBusPowerSwitch_V2(gse_manager_t * handle, const power_rail_id_t power, const bool setting);
void GSE_MANAGER_Task(void * taskptr);


#endif /* GSE_MANAGER_H_ */