/*
 * obc_controller_rev_A.h
 *
 * Created: 2020/04/01 08:23:14
 *  Author: Kolijn
 */ 


#ifndef OBC_CONTROLLER_REV_A_H_
#define OBC_CONTROLLER_REV_A_H_

#include <asf.h>

#define SPI_SELECT_PIN          PIO_PC17_IDX

#define SPI_CS_PIN_0            IOPORT_CREATE_PIN(PIOC, 25)
#define SPI_CS_PIN_1            IOPORT_CREATE_PIN(PIOC, 28)
#define SPI_CS_PIN_2            IOPORT_CREATE_PIN(PIOC, 29)
#define SPI_CS_PIN_3            IOPORT_CREATE_PIN(PIOC, 30)
#define SPI_CS_PIN_4            IOPORT_CREATE_PIN(PIOC, 21)
#define SPI_CS_PIN_5            IOPORT_CREATE_PIN(PIOC, 20)
#define SPI_CS_PIN_6            IOPORT_CREATE_PIN(PIOC, 19)
#define SPI_CS_PIN_7            IOPORT_CREATE_PIN(PIOC, 18)

#define ETH_nRST				PIO_PA29_IDX

#define SPI1_SCK                PIO_PC24_IDX
#define SPI1_MOSI               PIO_PC27_IDX
#define SPI1_MISO               PIO_PC26_IDX

#define SPI_DEVICE              SPI1
#define SPI_DEVICE_ID           ID_SPI1


#define T_USART					USART2
#define T_USART_SPEED			921600
#define T_USART_RX_PIN          IOPORT_CREATE_PIN(PIOD, 15)
#define T_USART_TX_PIN          IOPORT_CREATE_PIN(PIOD, 16)
#define T_USART_RTS_PIN         IOPORT_CREATE_PIN(PIOD, 18)
#define T_USART_CTS_PIN         IOPORT_CREATE_PIN(PIOD, 19)

#define B_USART					USART0
#define B_USART_SPEED			115200
#define B_USART_RX_PIN			PIO_PB0_IDX
#define B_USART_TX_PIN			PIO_PB1_IDX


#define PIN_RS422_nRE			PIO_PC29_IDX
#define PIN_RS422_DE			PIO_PC30_IDX
#define PIN_RS485_DE			PIO_PB3_IDX


#define I2C_BUS_DEVICE			TWIHS0
#define I2C_BUS_DEVICE_ID		ID_TWIHS0
#define I2C_BUS_SDA_PIN			PIO_PA3_IDX
#define I2C_BUS_SDA_MUX			IOPORT_MODE_MUX_A
#define I2C_BUS_SCL_PIN			PIO_PA4_IDX
#define I2C_BUS_SCL_MUX			IOPORT_MODE_MUX_A
#define I2C_BUS_DEFAULT_SPEED   400000

#define I2C_DEFAULT_ADDRESS		(0x26)

#define I2C_UTIL_DEVICE			TWIHS2
#define I2C_UTIL_DEVICE_ID		ID_TWIHS2
#define I2C_UTIL_SDA_PIN		PIO_PD27_IDX
#define I2C_UTIL_SDA_MUX		IOPORT_MODE_MUX_C
#define I2C_UTIL_SCL_PIN		PIO_PD28_IDX
#define I2C_UTIL_SCL_MUX		IOPORT_MODE_MUX_C
#define I2C_UTIL_SPEED			400000


#define LTC2992_1_DATARDY_PIN   PIO_PA24_IDX
#define LTC2992_1_ALERT_PIN     PIO_PA22_IDX
#define LTC2992_2_DATARDY_PIN   PIO_PA25_IDX
#define LTC2992_2_ALERT_PIN     PIO_PA23_IDX

#define EN_5V_BUS_PIN           PIO_PA21_IDX
#define EN_3V3_BUS_PIN          PIO_PA20_IDX
#define EN_VBAT_BUS_PIN         PIO_PA19_IDX
#define EN_VBATALT_BUS_PIN      PIO_PA18_IDX
#define EN_3V3_EXT_PIN			PIO_PC18_IDX
#define EN_3V3_UTIL_PIN			PIO_PC19_IDX

#define USB_RESET_PIN           PIO_PD14_IDX

#define CAN_PIN_TX              IOPORT_CREATE_PIN(PIOB, 2)
#define CAN_PIN_TX_MUX          IOPORT_MODE_MUX_A
#define CAN_PIN_RX              IOPORT_CREATE_PIN(PIOB, 3)
#define CAN_PIN_RX_MUX          IOPORT_MODE_MUX_A

#define CAN_DEVICE              MCAN0
#define CAN_DEVICE_ID           ID_MCAN0
#define CAN_INTERRUPT           MCAN0_INT0_IRQn
#define CAN_HANDLER             MCAN0_INT0_Handler
#define CAN_HANDLER2            MCAN0_INT1_Handler

#define CAN_PIN_TX_V2           IOPORT_CREATE_PIN(PIOC, 14)
#define CAN_PIN_TX_MUX_V2       IOPORT_MODE_MUX_C
#define CAN_PIN_RX_V2           IOPORT_CREATE_PIN(PIOC, 12)
#define CAN_PIN_RX_MUX_V2       IOPORT_MODE_MUX_C

#define CAN_DEVICE_V2           MCAN1
#define CAN_DEVICE_ID_V2        ID_MCAN1
#define CAN_INTERRUPT_V2        MCAN1_INT0_IRQn
#define CAN_HANDLER_V2          MCAN1_INT0_Handler
#define CAN_HANDLER2_V2         MCAN1_INT1_Handler

// The XTX uses the bottom 8 bits as the address
#define XTX_CAN_ADRESS          0x0000026
#define HDRTX_CAN_ADRESS		(65)
#define XTX_CAN_MASK            0x00000FF
#define OBC_CAN_ADRESS          0x00000E9
#define OBC_CAN_MASK            0x00000FF
//#define MCAN_RX_EXTENDED_FILTER_ID_0_BUFFER_INDEX

#define RTC_HANDLER             RTC_Handler

// Test Pins
// Pin 55
#define TEST_PIN_0              PIO_PD24_IDX
// Pin 53
#define TEST_PIN_1              PIO_PD26_IDX
// Pin 52
#define TEST_PIN_2              PIO_PD25_IDX
// Pin 51
#define TEST_PIN_3              PIO_PA14_IDX

//Version Pins
#define PIN_VERSION_0			PIO_PC7_IDX
#define PIN_VERSION_1			PIO_PC8_IDX
#define PIN_VERSION_2			PIO_PC9_IDX

// H1.8
#define PC104_nRST_PIN          PIO_PC1_IDX
// H1.18
#define PC104_EN_PIN            PIO_PC0_IDX
// H1.7 
#define XTX_RDY_PIN             PIO_PC2_IDX
// H1.11
#define XTX_SS_PIN              SPI_CS_PIN_2

#define XSTEER_ADRESS           0x0000027

#define XDC_ADDRESS             0x0000028


#define PIN_BUS_GPIO0			PIO_PC0_IDX
#define PIN_BUS_GPIO1			PIO_PC1_IDX
#define PIN_BUS_GPIO2			PIO_PC2_IDX
#define PIN_BUS_GPIO3			PIO_PC3_IDX



#define PIN_DEBUG_0             PIO_PD20_IDX
#define PIN_DEBUG_1             PIO_PD21_IDX
#define PIN_DEBUG_2             PIO_PD25_IDX
#define PIN_DEBUG_3             PIO_PD26_IDX

#define PIN_XIN32				PIO_PA7_IDX
#define PIN_XOUT32				PIO_PA8_IDX


#endif /* OBC_CONTROLLER_REV_A_H_ */
