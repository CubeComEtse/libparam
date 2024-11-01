/*
 * bsp.h
 *
 * Created: 2020/04/01 08:19:42
 *  Author: Kolijn
 */ 


#ifndef BSP_H_
#define BSP_H_

#include <stdint.h>
#include <stdbool.h>
#include "obc_controller_rev_A.h"

#include "ccd_i2c_driver.h"
#include "ccd_can_driver.h"
#include "ccd_uart_driver.h"


typedef struct {
	ccd_uart_t * telemetry_uart;
	ccd_i2c_t * bus_i2c;
	ccd_i2c_t * local_i2c;
} bsp_t;




typedef enum  {
    EN_5V_BUS = EN_5V_BUS_PIN,
    EN_3V3_BUS = EN_3V3_BUS_PIN,
    EN_VBAT_BUS = EN_VBAT_BUS_PIN,
    EN_VBATALT_BUS = EN_VBATALT_BUS_PIN,
}power_pin_t;

void BSP_Init(bsp_t * bsp);

struct spi_device* BSP_psGetSpiDriver(void);
void BSP_vCanSetAddressFilter(uint32_t filter, uint32_t mask);
struct mcan_module* BSP_psGetCanDriver(void);
void BSP_vEnableUartTXInterrupt(void);

void BSP_vSetPowerEn(power_pin_t pin, uint8_t level);

uint16_t BSP_u16TmrGetTick(void);
uint64_t BSP_u64GetTimestamp(void);
void BSP_vUsbReset(void);

void BSP_vTelemetrySetCTS(bool dir);
void BSP_vSetTestPin(bool level);

// These should live in their own xtx file
void XTX_vConfigBoard(void);
#endif /* BSP_H_ */