/*
 * bsp.h
 *
 * Created: 2020/04/01 08:19:54
 *  Author: Kolijn
 */ 

#include <asf.h>

#include "bsp.h"
#include "obc_controller_rev_A.h"
#include "ioport.h"

// All interrupt mask.
#define ALL_INTERRUPT_MASK  0xffffffff

// Local functions
void BOARD_vInitTelemetryUart(void);

void BOARD_vInit(void) {

    // Setup pins for SPI select
    ioport_enable_pin(SPI_SELECT_PIN);
    ioport_set_pin_dir(SPI_SELECT_PIN, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(SPI_SELECT_PIN, 1);

    // Setup SPI
    ioport_enable_pin(SPI1_SCK);
    ioport_set_pin_dir(SPI1_SCK, IOPORT_DIR_OUTPUT);
    
    // Setup Telemetry UART
    BOARD_vInitTelemetryUart();
    // Configure and enable interrupt of USART.
    // NVIC_EnableIRQ(USART2_IRQn);

}


void BOARD_vInitTelemetryUart(void) {

    //usart_disable_interrupt(TELEMETRY_USART, ALL_INTERRUPT_MASK);

    // Setup pins
    ioport_set_pin_mode(T_USART_RX_PIN, IOPORT_MODE_MUX_B);
    ioport_disable_pin(T_USART_RX_PIN);

    ioport_set_pin_mode(T_USART_TX_PIN, IOPORT_MODE_MUX_B);
    ioport_disable_pin(T_USART_TX_PIN);

    // Enable Clock to this module
    sysclk_enable_peripheral_clock(TELEMETRY_ID_USART);

    // Setup for Telemetry USART
    sam_usart_opt_t sUsartOptions;
    sUsartOptions.baudrate = 115200;
    sUsartOptions.char_length = US_MR_CHRL_8_BIT;
    sUsartOptions.parity_type = US_MR_PAR_NO;
    sUsartOptions.stop_bits = US_MR_NBSTOP_1_BIT;
    sUsartOptions.channel_mode = US_MR_CHMODE_NORMAL;

    usart_init_rs232(TELEMETRY_USART, &sUsartOptions, sysclk_get_main_hz());

    usart_enable_tx(TELEMETRY_USART);
    usart_enable_rx(TELEMETRY_USART);

    //usart_enable_interrupt(TELEMETRY_USART, US_IER_TXRDY | US_IER_TXEMPTY);
}