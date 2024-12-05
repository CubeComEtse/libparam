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
	ccd_i2c_t * util_i2c;
} bsp_t;



//Used in the NEW SHINY codebase
void BSP_Init(bsp_t * bsp);
uint8_t BSP_u8GetVersion(void);
void BSP_vSetPin(uint32_t pin, bool value);












struct spi_device* BSP_psGetSpiDriver(void);
void BSP_vCanSetAddressFilter(uint32_t filter, uint32_t mask);
struct mcan_module* BSP_psGetCanDriver(void);
void BSP_vEnableUartTXInterrupt(void);


uint16_t BSP_u16TmrGetTick(void);
uint64_t BSP_u64GetTimestamp(void);
void BSP_vUsbReset(void);

void BSP_vTelemetrySetCTS(bool dir);

// These should live in their own xtx file
void XTX_vConfigBoard(void);

#endif /* BSP_H_ */