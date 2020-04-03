/*
 * bsp.h
 *
 * Created: 2020/04/01 08:19:54
 *  Author: Kolijn
 */ 

#include <asf.h>

#include "bsp.h"
#include "obc_controller_rev_A.h"
#include "usart_buffer.h"
#include "ioport.h"
#include "spi.h"

// All interrupt mask.
#define ALL_INTERRUPT_MASK  0xffffffff

// Local functions
void BOARD_vInitTelemetryUart(void);
void BOARD_vInitSPI(void);

// Local variables
static USART_data_t telemetryUsart;
static struct spi_device sSpiDevice;

void BSP_vInit(void) {

    ioport_init();

    // Setup Telemetry UART
    BOARD_vInitTelemetryUart();
    BOARD_vInitSPI();
    
    Enable_global_interrupt();
}

void BOARD_vInitSPI(void) { 
    spi_disable_interrupt(SPI_DEVICE, ALL_INTERRUPT_MASK);
    
    // Setup pins for SPI select
    ioport_enable_pin(SPI_SELECT_PIN);
    ioport_set_pin_dir(SPI_SELECT_PIN, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(SPI_SELECT_PIN, 1);

    // Setup SPI
    ioport_disable_pin(SPI1_SCK);
    ioport_set_pin_dir(SPI1_SCK, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(SPI1_SCK, 1);
    ioport_set_pin_mode(SPI1_SCK, IOPORT_MODE_MUX_C);

    ioport_disable_pin(SPI1_MOSI);
    ioport_set_pin_dir(SPI1_MOSI, IOPORT_DIR_OUTPUT);
    ioport_set_pin_mode(SPI1_MOSI, IOPORT_MODE_MUX_C);

    ioport_disable_pin(SPI1_MISO);
    ioport_set_pin_dir(SPI1_MISO, IOPORT_DIR_INPUT);
    ioport_set_pin_mode(SPI1_MISO, IOPORT_MODE_MUX_C);

    ioport_enable_pin(SPI_CS_PIN_7);
    ioport_set_pin_dir(SPI_CS_PIN_7, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(SPI_CS_PIN_7, 1);

    spi_master_init(SPI_DEVICE);
    spi_master_setup_device(SPI_DEVICE, &sSpiDevice, SPI_MODE_0, 400000, 0);
    spi_enable(SPI_DEVICE);
}

struct spi_device* BSP_psGetSpiDriver(void) {
    return &sSpiDevice; 
}

void BOARD_vInitTelemetryUart(void) {

    // Disable the Interrupts while configuring the usart
    usart_disable_interrupt(TELEMETRY_USART, ALL_INTERRUPT_MASK);

    // Setup pins
    ioport_set_pin_mode(T_USART_RX_PIN, IOPORT_MODE_MUX_B);
    ioport_disable_pin(T_USART_RX_PIN);

    ioport_set_pin_mode(T_USART_TX_PIN, IOPORT_MODE_MUX_B);
    ioport_disable_pin(T_USART_TX_PIN);

    // Enable Clock to this module
    sysclk_enable_peripheral_clock(TELEMETRY_ID_USART);

    // Setup for Telemetry USART
    sam_usart_opt_t sUsartOptions;
    sUsartOptions.baudrate = 57600;
    sUsartOptions.char_length = US_MR_CHRL_8_BIT;
    sUsartOptions.parity_type = US_MR_PAR_NO;
    sUsartOptions.stop_bits = US_MR_NBSTOP_1_BIT;
    sUsartOptions.channel_mode = US_MR_CHMODE_NORMAL;

    usart_init_rs232(TELEMETRY_USART, &sUsartOptions, sysclk_get_peripheral_hz());

    usart_enable_tx(TELEMETRY_USART);
    usart_enable_rx(TELEMETRY_USART);

    USART_BUFFER_vInitialize(&telemetryUsart);

    // Re-enable Interrupts
    usart_enable_interrupt(TELEMETRY_USART, US_IER_RXRDY | US_IER_TXEMPTY);
    
    NVIC_EnableIRQ(TELEMETRY_USART_IRQ);
}


void BSP_vEnableUartTXInterrupt(void) {
    usart_enable_interrupt(TELEMETRY_USART, US_IER_TXEMPTY);
}


USART_data_t* BSP_psGetTelemetryDriver(void) {
    return &telemetryUsart;
}


void TELEMETRY_USART_HANDLER(void)
{
    uint32_t dw_status = usart_get_status(TELEMETRY_USART);

    // A Value is received
    if (dw_status & US_CSR_RXRDY) {
        uint32_t received_byte;

        usart_read(TELEMETRY_USART, &received_byte);
        if (USART_BUFFER_Receive(&telemetryUsart, (uint8_t) received_byte)) {
            //Possibly set CTS/RTS pins here,
        }
    }

    // TX Buffer and shift register empty
    if (dw_status & US_CSR_TXEMPTY) {
        uint8_t nextByte = 0;
        if (USART_BUFFER_Transmit(&telemetryUsart, &nextByte)) {
            // If true there is a value loaded
            usart_write(TELEMETRY_USART, nextByte);
        }
        else {
            // Disable the interrupt, re-enable later
            usart_disable_interrupt(TELEMETRY_USART, US_IER_TXEMPTY);
        }
    }
}