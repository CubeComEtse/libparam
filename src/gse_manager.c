/*
 * The config endpoint is responsible for all the obc-controller settings.
 * It will report which boards are supported, and provide and interface to 
 * enable and measure power to the board.
 */ 
 
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "FreeRTOS.h"
#include "task.h"

#include "gse_manager.h"

#include "register_handler.h"


// Todo: This goes somewhere else
#define GSE_EN_3V3_BUS_PIN 0
#define GSE_EN_5_BUS_PIN 0
#define GSE_EN_VBAT_BUS_PIN 0
#define GSE_EN_VBATALT_BUS_PIN 0


void GSE_MANAGER_Init(gse_manager_t * handle)
{
	handle->bCSBoardenabled = false;
}

/*
 * Set a power rail on the GSE
*/
void GSE_MANAGER_SetPower(gse_manager_t * handle, const power_rail_id_t power, const bool setting) {

	if (power == POWER_3V3)
	{
		handle->set_gpio_pin(handle->gpio_handle, GSE_EN_3V3_BUS_PIN, setting);
	}
	if (power == POWER_5V)
	{
		handle->set_gpio_pin(handle->gpio_handle, GSE_EN_5_BUS_PIN, setting);
	}
	if (power == POWER_VBAT)
	{
		handle->set_gpio_pin(handle->gpio_handle, GSE_EN_VBAT_BUS_PIN, setting);
	}
	if (power == POWER_VBAT_ALT)
	{
		handle->set_gpio_pin(handle->gpio_handle, GSE_EN_VBATALT_BUS_PIN, setting);
	}
}


void GSE_MANAGER_Task(void * taskptr){
	gse_manager_t * hdl = (gse_manager_t *) taskptr;
	
	// Make sure all structs are initialized
	assert(hdl);
	if (hdl->board_version == 0){
		assert(hdl->power_measure_1);
		assert(hdl->power_measure_2);
	}
	if (hdl->board_version == 1){
		assert(hdl->power_measure_1);
	}
	
    uint32_t power1 = 0;
    uint32_t power2 = 0;
    uint16_t voltage1 = 0;
    uint16_t voltage2 = 0;
    uint16_t current1 = 0;
    uint16_t current2 = 0;
	
		
	while(1)
	{
		if (hdl->board_version == 0){
			LTC2992_vReadVoltage(hdl->power_measure_1, &voltage1, &voltage2);
			voltage1 = (uint16_t) ((double)voltage1 * 5.5);
			voltage2 = (uint16_t) ((double)voltage2 * 5.5);
			mm_setMeasureVI_V3_voltage(voltage1);
			mm_setMeasureVI_V5_voltage(voltage2);

			LTC2992_vReadVoltage(hdl->power_measure_2, &voltage1, &voltage2);
			//The VBat and VBalAlt rails use different resistor values, they need different scalers
			voltage1 = (uint16_t) ((double)voltage1 * 10.30392);
			voltage2 = (uint16_t) ((double)voltage2 * 10.30392);
			mm_setMeasureVI_VBat_voltage(voltage2);
			mm_setMeasureVI_VBatAlt_voltage(voltage2);
			
			LTC2992_vReadCurrent(hdl->power_measure_1, &current1, &current2);
			current1 = (uint16_t) ((double)current1 * 1.25);
			current2 = (uint16_t) ((double)current2 * 1.25);
			mm_setMeasureVI_V3_current(current1);
			mm_setMeasureVI_V5_current(current1);
			
			LTC2992_vReadCurrent(hdl->power_measure_2, &current1, &current2);
			current1 = (uint16_t) ((double)current1 * 1.25);
			current2 = (uint16_t) ((double)current2 * 1.25);
			mm_setMeasureVI_VBat_current(current2);
			mm_setMeasureVI_VBatAlt_current(current1);

			LTC2992_vReadPower(hdl->power_measure_1, &power1, &power2);
			power1 = (uint16_t) ((double)power1 * 31.875e-3);
			power2 = (uint16_t) ((double)power2 * 31.875e-3);
			mm_setMeasurePower_V3(power1);
			mm_setMeasurePower_V3(power2);

			LTC2992_vReadPower(hdl->power_measure_2, &power1, &power2);
			power1 = (uint16_t) ((double)power1 * 31.875e-3);
			power2 = (uint16_t) ((double)power2 * 31.875e-3);
			mm_setMeasurePower_VBatAlt(power1);
			mm_setMeasurePower_VBat(power2);
		}
		if (hdl->board_version == 1) 
		{
			//Todo: Want to use current & voltage conversion on the board!
			LTC2992_vReadVoltage(hdl->power_measure_1, &voltage1, &voltage2);
			voltage1 = (uint16_t) ((double)voltage1 * 5.5);
			voltage2 = (uint16_t) ((double)voltage2 * 10.30392);
			mm_setMeasureVI_V3_voltage(voltage1);
			mm_setMeasureVI_VBat_voltage(voltage2);
			
			LTC2992_vReadCurrent(hdl->power_measure_1, &current1, &current2);
			current1 = (uint16_t) ((double)current1 * 1.25);
			current2 = (uint16_t) ((double)current2 * 1.25);
			mm_setMeasureVI_V3_current(current1);
			mm_setMeasureVI_VBat_current(current1);
			
			LTC2992_vReadPower(hdl->power_measure_1, &power1, &power2);
			power1 = (uint16_t) ((double)power1 * 31.875e-3);
			power2 = (uint16_t) ((double)power2 * 31.875e-3);
			mm_setMeasurePower_V3_power(power1);
			mm_setMeasurePower_VBat(power2);
		}
	
		// Todo:
		// Task Sleep!
		
		//Todo:
		// Current Sense board
		
		if (hdl->bCSBoardenabled){
			LTC2499_getSample(hdl->cs_board);
		}
		
		// 5 times a second
		vTaskDelay(pdMS_TO_TICKS(200));
	}
}

/*
void CONFIG_SetCurrentSenseBoardEnabled(bool value){
	bCSBoardenabled = value;
}*/