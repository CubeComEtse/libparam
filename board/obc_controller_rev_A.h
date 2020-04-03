/*
 * obc_controller_rev_A.h
 *
 * Created: 2020/04/01 08:23:14
 *  Author: Kolijn
 */ 


#ifndef OBC_CONTROLLER_REV_A_H_
#define OBC_CONTROLLER_REV_A_H_

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
#define T_USART_RX_PIN          IOPORT_CREATE_PIN(PIOD, 15)
#define T_USART_TX_PIN          IOPORT_CREATE_PIN(PIOD, 16)

#endif /* OBC_CONTROLLER_REV_A_H_ */