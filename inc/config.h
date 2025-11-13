#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdbool.h>
#include <stdint.h>

#define SOFTWARE_VERSION_MAJOR      2
#define SOFTWARE_VERSION_MINOR      3
#define SOFTWARE_VERSION_PATCH      0

#define BOARD_IDENTIFIER            0x634F4243 // "cOBC"

#define SPI_DEVICE                  SPI1
#define SPI_DEVICE_ID               ID_SPI1

#define T_USART                     USART2
#define T_USART_SPEED               115200//921600

#define B_USART                     USART0
#define B_USART_SPEED               115200

#define I2C_BUS_DEFAULT_SPEED       400000
#define I2C_DEFAULT_ADDRESS         0x26

#define I2C_UTIL_SPEED              400000

#define XTX_CAN_ADRESS              0x26
#define XSTEER_CAN_ADRESS           0x27
#define XDC_ADDRESS                 0x28
#define HDRTX_CAN_ADRESS            0x41
#define OBC_CAN_ADRESS              0xE9

#ifdef DEBUG
#define DEBUG_TRACE_ENABLED         0 // Set to 1 to enable tracealyzer tracing
#define DEBUG_XTXG2_EN_ENABLED      0 // Set to 1 to enable automatic switch on of XTXG2 device (no need for OBC selection & enabling to power on)

// We override the software version to ensure we don't accidentally release a debug build
#define SOFTWARE_VERSION_MAJOR      99
#define SOFTWARE_VERSION_MINOR      99
#define SOFTWARE_VERSION_PATCH      99
#endif

#endif /* CONFIG_H_ */