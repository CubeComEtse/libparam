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

#define SPI1_SCK                PIO_PC24_IDX
#define SPI1_MOSI               PIO_PC27_IDX
#define SPI1_MISO               PIO_PC26_IDX

#define SPI_DEVICE              SPI1
#define SPI_DEVICE_ID           ID_SPI1

#define TELEMETRY_USART         USART2
#define TELEMETRY_ID_USART      ID_USART2
#define TELEMETRY_USART_HANDLER USART2_Handler
#define TELEMETRY_USART_IRQ     USART2_IRQn
#define TELEMERTY_USART_SPEED   921600
#define T_USART_RX_PIN          IOPORT_CREATE_PIN(PIOD, 15)
#define T_USART_TX_PIN          IOPORT_CREATE_PIN(PIOD, 16)
#define T_USART_RTS_PIN         IOPORT_CREATE_PIN(PIOD, 18)
#define T_USART_CTS_PIN         IOPORT_CREATE_PIN(PIOD, 19)

#define I2C_PC104_DEVICE        TWIHS0
#define I2C_PC104_DEVICE_ID     ID_TWIHS0
#define I2C_PC104_SDA_PIN       PIO_PA4_IDX
#define I2C_PC104_SDA_MUX       IOPORT_MODE_MUX_A
#define I2C_PC104_SCL_PIN       PIO_PA3_IDX
#define I2C_PC104_SCL_MUX       IOPORT_MODE_MUX_A
#define I2C_PC104_SPEED         60000

#define I2C_BOARD_DEVICE        TWIHS2
#define I2C_BOARD_DEVICE_ID     ID_TWIHS2
#define I2C_BOARD_SDA_PIN       PIO_PD27_IDX
#define I2C_BOARD_SDA_MUX       IOPORT_MODE_MUX_C
#define I2C_BOARD_SCL_PIN       PIO_PD28_IDX
#define I2C_BOARD_SCL_MUX       IOPORT_MODE_MUX_C
#define I2C_BOARD_SPEED         100000

#define LTC2992_1_DATARDY_PIN   PIO_PA24_IDX
#define LTC2992_1_ALERT_PIN     PIO_PA22_IDX
#define LTC2992_2_DATARDY_PIN   PIO_PA25_IDX
#define LTC2992_2_ALERT_PIN     PIO_PA23_IDX

#define EN_5V_BUS_PIN           PIO_PA21_IDX
#define EN_3V3_BUS_PIN          PIO_PA20_IDX
#define EN_VBAT_BUS_PIN         PIO_PA19_IDX
#define EN_VBATALT_BUS_PIN      PIO_PA18_IDX

#define USB_RESET_PIN           PIO_PD14_IDX

#define CAN_PIN_TX              IOPORT_CREATE_PIN(PIOB, 2)
#define CAN_PIN_TX_MUX          IOPORT_MODE_MUX_A
#define CAN_PIN_RX              IOPORT_CREATE_PIN(PIOB, 3)
#define CAN_PIN_RX_MUX          IOPORT_MODE_MUX_A

#define CAN_DEVICE              MCAN0
#define CAN_DEVICE_ID           ID_MCAN0
#define CAN_INTERRUPT           MCAN0_INT0_IRQn
#define CAN_HANDLER             MCAN0_INT0_Handler

// The XTX uses the bottom 8 bits as the address
#define XTX_CAN_MASK            0x00000FF
#define XTX_CAN_ADRESS          0x00000F4
#define OBC_CAN_ADRESS          0x00000E9
//#define MCAN_RX_EXTENDED_FILTER_ID_0_BUFFER_INDEX

// Test Pin
#define TEST_PIN                PIO_PD24_IDX

// H1.8
#define XTX_nRST_PIN            PIO_PC1_IDX
// H1.18
#define XTX_EN_PIN              PIO_PC0_IDX
// H1.7 
#define XTX_RDY_PIN             PIO_PC2_IDX
// H1.11
#define XTX_SS_PIN              SPI_CS_PIN_2

#endif /* OBC_CONTROLLER_REV_A_H_ */
