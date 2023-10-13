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
void BSP_vCanSetAddressFilter(uint32_t filter, uint32_t mask);
struct mcan_module* BSP_psGetCanDriver(void);
void BSP_vEnableUartTXInterrupt(void);

void BSP_vSetPowerEn(power_pin_t pin, uint8_t level);
/* Callbacks used by the LTC2992 power sensors*/
void BSP_vPowerSenseWriteFunction(const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length);
void BSP_vPowerSenseReadFunction(const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, uint16_t length);

void BSP_vCurrentSenseReadFunction(const uint8_t chip_addr, const uint8_t * mem_address, const uint8_t mem_address_length, uint8_t* rx_buffer, const uint16_t length);
void BSP_vCurrentSenseWriteFunction(const uint8_t chip_addr, const uint8_t * mem_address, const uint8_t mem_address_length, uint8_t* tx_buffer, const uint16_t length);

uint16_t BSP_u16TmrGetTick(void);
uint64_t BSP_u64GetTimestamp(void);
void BSP_vUsbReset(void);

struct i2c_driver_data* BSP_psGetI2cDriver(void);

void BSP_vTelemetrySetCTS(bool dir);
void BSP_vSetTestPin(bool level);

// These should live in their own xtx file
void XTX_vConfigBoard(void);
#endif /* BSP_H_ */