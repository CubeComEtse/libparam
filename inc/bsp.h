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
#include "usart_buffer.h"
#include "obc_controller_rev_A.h"

typedef enum  {
    EN_5V_BUS = EN_5V_BUS_PIN,
    EN_3V3_BUS = EN_3V3_BUS_PIN,
    EN_VBAT_BUS = EN_VBAT_BUS_PIN,
    EN_VBATALT_BUS = EN_VBATALT_BUS_PIN,
}power_pin_t;

void BSP_vInit(void);
USART_data_t* BSP_psGetTelemetryDriver(void);
struct spi_device* BSP_psGetSpiDriver(void);
struct mcan_module* BSP_psGetCanDriver(void);
void BSP_vEnableUartTXInterrupt(void);

void BSP_vSetPowerEn(power_pin_t pin, uint8_t level);
/* Callbacks used by the LTC2992 power sensors*/
void BSP_vPowerSenseWriteFunction(const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length);
void BSP_vPowerSenseReadFunction(const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, uint16_t length);

void BSP_vUsbReset(void);

void BSP_vTelemetrySetCTS(bool dir);
void BSP_vSetTestPin(bool level);

// These should live in their own xtx file
void XTX_vConfigBoard(void);
void XTX_vSetEnable(bool enabled);
void XTX_SetNReset(bool reset);
bool XTX_bGetEnable(void);
#endif /* BSP_H_ */