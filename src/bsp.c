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
// ASF headers
#include "ioport.h"
#include "spi.h"
#include "i2c_driver.h"

// All interrupt mask.
#define ALL_INTERRUPT_MASK  0xffffffff

// Local functions
void BSP_vInitTelemetryUart(void);
void BSP_vInitSPI(void);
void BSP_vInitPC103I2C(void);
void BSP_vInitBoardI2C(void) ;
void BSP_vInitPowerSenseGPIO(void);
void BSP_vInitPowerGPIO(void);

// Local variables
static USART_data_t telemetryUsart;
static struct spi_device sSpiDevice;
static struct i2c_driver board_i2c_driver;

void BSP_vInit(void) {

    ioport_init();

    // Setup Telemetry UART
    BSP_vInitTelemetryUart();
    BSP_vInitSPI();
    BSP_vInitPC103I2C();
    BSP_vInitBoardI2C();
    BSP_vInitPowerSenseGPIO();
    BSP_vInitPowerGPIO();

    ioport_enable_pin(USB_RESET_PIN);
    ioport_set_pin_level(USB_RESET_PIN, 0);
    ioport_set_pin_dir(USB_RESET_PIN, IOPORT_DIR_OUTPUT);


    /*
    ioport_enable_pin(I2C_BOARD_SDA_PIN);
    ioport_set_pin_dir(I2C_BOARD_SDA_PIN, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(I2C_BOARD_SDA_PIN, 0);

    ioport_enable_pin(I2C_BOARD_SCL_PIN);
    ioport_set_pin_dir(I2C_BOARD_SCL_PIN, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(I2C_BOARD_SCL_PIN, 0);*/
    
    Enable_global_interrupt();
}

void BSP_vInitSPI(void) { 
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

void BSP_vInitTelemetryUart(void) {

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

/*
    Initialize the I2C for communication on the PC104
*/
void BSP_vInitPC103I2C(void) {
    sysclk_enable_peripheral_clock(I2C_PC104_DEVICE_ID);

    // Setup pins
    ioport_set_pin_mode(I2C_PC104_SDA_PIN, I2C_PC104_SDA_MUX);
    ioport_disable_pin(I2C_PC104_SDA_PIN);

    ioport_set_pin_mode(I2C_PC104_SCL_PIN, I2C_PC104_SCL_MUX);
    ioport_disable_pin(I2C_PC104_SCL_PIN);

    twihs_options_t i2cOptions;
    i2cOptions.master_clk = sysclk_get_peripheral_hz();
    i2cOptions.speed = I2C_PC104_SPEED;
    twihs_master_init(I2C_PC104_DEVICE, &i2cOptions);
}


void BSP_vEnableUartTXInterrupt(void) {
    usart_enable_interrupt(TELEMETRY_USART, US_IER_TXEMPTY);
}


USART_data_t* BSP_psGetTelemetryDriver(void) {
    return &telemetryUsart;
}

/*
    Initialize the I2C for on-board communications
*/
void BSP_vInitBoardI2C(void) {
    sysclk_enable_peripheral_clock(I2C_BOARD_DEVICE_ID);

    // Setup pins
    ioport_set_pin_mode(I2C_BOARD_SDA_PIN, I2C_BOARD_SDA_MUX);
    ioport_disable_pin(I2C_BOARD_SDA_PIN);

    ioport_set_pin_mode(I2C_BOARD_SCL_PIN, I2C_BOARD_SCL_MUX);
    ioport_disable_pin(I2C_BOARD_SCL_PIN);

    twihs_options_t i2cOptions;
    i2cOptions.master_clk = sysclk_get_peripheral_hz();
    i2cOptions.speed = I2C_BOARD_SPEED;
    twihs_master_init(I2C_BOARD_DEVICE, &i2cOptions);

    // Create the driver objects used by the I2C driver
    board_i2c_driver.p_twihs = I2C_BOARD_DEVICE;
}

void BSP_vInitPowerSenseGPIO(void) {
    // LTC2992 1 - U7
    ioport_enable_pin(LTC2992_1_DATARDY_PIN);
    ioport_set_pin_dir(LTC2992_1_DATARDY_PIN, IOPORT_DIR_INPUT);

    ioport_enable_pin(LTC2992_1_ALERT_PIN);
    ioport_set_pin_dir(LTC2992_1_ALERT_PIN, IOPORT_DIR_INPUT);

    // LTC2992 1 - U9
    ioport_enable_pin(LTC2992_2_DATARDY_PIN);
    ioport_set_pin_dir(LTC2992_2_DATARDY_PIN, IOPORT_DIR_INPUT);

    ioport_enable_pin(LTC2992_2_ALERT_PIN);
    ioport_set_pin_dir(LTC2992_2_ALERT_PIN, IOPORT_DIR_INPUT);
}

void BSP_vInitPowerGPIO(void) {
    uint32_t power_pins[] = {EN_5V_BUS_PIN, EN_3V3_BUS_PIN, EN_VBAT_BUS_PIN, EN_VBATALT_BUS_PIN};

    for (uint8_t i = 0; i < 4; i++) {
        ioport_enable_pin(power_pins[i]);
        ioport_set_pin_level(power_pins[i], 0);
        ioport_set_pin_dir(power_pins[i], IOPORT_DIR_OUTPUT);
    }
}

void BSP_vSetPowerEn(power_pin_t pin, uint8_t level) {
    
    ioport_set_pin_level(pin, level);
}

/*
 * Callback function used by the LTC2992 sensors.
*/
void BSP_vPowerSenseWriteFunction(const uint8_t chip_addr, const uint8_t mem_address, const uint8_t* tx_buffer, const uint16_t length) {
    I2C_DRIVER_bWriteTo(&board_i2c_driver, chip_addr, mem_address, tx_buffer, length);
}

void BSP_vPowerSenseReadFunction(const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, uint16_t length) {
    I2C_DRIVER_bReadFrom(&board_i2c_driver, chip_addr, mem_address, rx_buffer, length);
}

void BSP_vUsbReset(void) {
    ioport_set_pin_level(USB_RESET_PIN, 0);
    delay_ms(100);
    ioport_set_pin_level(USB_RESET_PIN, 1);
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