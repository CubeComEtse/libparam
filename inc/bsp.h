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

#include "ccd_i2c_driver.h"
#include "ccd_can_driver.h"
#include "ccd_uart_driver.h"
#include "ccd_can_driver.h"
#include "ccd_led_driver.h"

#include "obc_controller_rev_AB.h"

typedef struct bsp_s
{
	ccd_uart_t * telemetry_uart;
	ccd_uart_t * bus_uart;
    
	ccd_i2c_t * bus_i2c;
	ccd_i2c_t * util_i2c;
    
	ccd_can_t * bus_can;
    
	ccd_led_t * led_driver;
} bsp_t;

//Used in the NEW SHINY codebase
void BSP_Init(bsp_t * bsp);
uint8_t BSP_u8GetVersion(void);
void BSP_vSetPin(uint32_t pin, bool value);
uint32_t BSP_GetUptime(void);

void debug(uint8_t val);

struct spi_device* BSP_psGetSpiDriver(void);
void BSP_vCanSetAddressFilter(uint32_t filter, uint32_t mask);
void BSP_vEnableUartTXInterrupt(void);

uint64_t BSP_u64GetTimestamp(void);
void BSP_vUsbReset(void);

void BSP_vTelemetrySetCTS(bool dir);

// These should live in their own XTX file
void XTX_vConfigBoard(void);

#endif /* BSP_H_ */