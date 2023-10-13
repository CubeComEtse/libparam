/*
 * bsp.h
 *
 * Created: 2020/04/01 08:19:54
 *  Author: Kolijn
 */ 

#include <asf.h>

#include "bsp.h"
#include "can_driver.h"
#include "genclk.h"
#include "i2c_driver.h"
#include "ioport.h"
#include "obc_controller_rev_A.h"
#include "spi.h"
#include "usart_buffer.h"
#include "i2c_endpoint.h"

// All interrupt mask.
#define ALL_INTERRUPT_MASK  0xffffffff

// Local functions
void BSP_vInitTelemetryUart(void);
void BSP_vInitSPI(void);
void BSP_vInitBoardI2C(void);
void BSP_vInitPowerSenseGPIO(void);
void BSP_vInitPowerGPIO(void);
void BSP_vInitCan(void);
void BSP_vInit1MsTimer(void);

// Local variables
static USART_data_t telemetryUsart;
static struct spi_device sSpiDevice;
static struct mcan_module sCanModule;
static volatile uint32_t fifo_receive_index = 0;

static struct i2c_driver_data board_i2c_driver;

void BSP_vInit(void) {

    ioport_init();
    delay_init(sysclk_get_cpu_hz());

    BSP_vInitTelemetryUart();
    BSP_vInitSPI();
    BSP_vInitBoardI2C();
    BSP_vInitPowerSenseGPIO();
    BSP_vInitPowerGPIO();
    BSP_vInitCan();

    BSP_vInit1MsTimer();

    
    ioport_enable_pin(USB_RESET_PIN);
    ioport_set_pin_level(USB_RESET_PIN, 0);
    ioport_set_pin_dir(USB_RESET_PIN, IOPORT_DIR_OUTPUT);
    
    BSP_vUsbReset();
    
    ioport_enable_pin(TEST_PIN_0);
    ioport_set_pin_dir(TEST_PIN_0, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(TEST_PIN_0, 0);
	
	ioport_enable_pin(TEST_PIN_1);
	ioport_set_pin_dir(TEST_PIN_1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(TEST_PIN_1, 0);
	
	ioport_enable_pin(TEST_PIN_2);
	ioport_set_pin_dir(TEST_PIN_2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(TEST_PIN_2, 0);
	
	ioport_enable_pin(TEST_PIN_3);
	ioport_set_pin_dir(TEST_PIN_3, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(TEST_PIN_3, 0);

    Enable_global_interrupt();

}

void BSP_vSetTestPin(bool level) {
    ioport_set_pin_level(TEST_PIN_0, level);
}

void BSP_vInitSPI(void) { 
    spi_disable_interrupt(SPI_DEVICE, ALL_INTERRUPT_MASK);
    
    // Setup pins for SPI select
    ioport_enable_pin(SPI_SELECT_PIN);
    ioport_set_pin_dir(SPI_SELECT_PIN, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(SPI_SELECT_PIN, 0);

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

    ioport_enable_pin(T_USART_RTS_PIN);
    ioport_set_pin_dir(T_USART_RTS_PIN, IOPORT_DIR_INPUT);
    ioport_enable_pin(T_USART_CTS_PIN);
    ioport_set_pin_dir(T_USART_CTS_PIN, IOPORT_DIR_OUTPUT);

    // Enable Clock to this module
    sysclk_enable_peripheral_clock(TELEMETRY_ID_USART);

    // Setup for Telemetry USART
    sam_usart_opt_t sUsartOptions;
    sUsartOptions.baudrate = TELEMERTY_USART_SPEED;
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

    BSP_vTelemetrySetCTS(false);
}

void BSP_vTelemetrySetCTS(bool dir){
    ioport_set_pin_level(T_USART_CTS_PIN, dir);
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
    i2cOptions.chip = 0x26;
    i2cOptions.smbus = 0;
    i2cOptions.master_clk = sysclk_get_peripheral_hz();
    i2cOptions.speed = I2C_BOARD_SPEED;
    twihs_master_init(I2C_BOARD_DEVICE, &i2cOptions);

    // Create the driver objects used by the I2C driver
    board_i2c_driver.p_twihs = I2C_BOARD_DEVICE;
}

struct i2c_driver_data*  BSP_psGetI2cDriver(void) {
	return &board_i2c_driver;
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
    I2C_DRIVER_bWriteLocal(&board_i2c_driver, chip_addr, mem_address, tx_buffer, length);
}

void BSP_vPowerSenseReadFunction(const uint8_t chip_addr, const uint8_t mem_address, uint8_t* rx_buffer, uint16_t length) {
    I2C_DRIVER_bReadLocal(&board_i2c_driver, chip_addr, mem_address, rx_buffer, length);
}

void BSP_vCurrentSenseReadFunction(const uint8_t chip_addr, const uint8_t * mem_address, const uint8_t mem_address_length, uint8_t* rx_buffer, const uint16_t length) {
	I2C_DRIVER_bReadCustom(I2C_psGetDriver(), chip_addr, mem_address, mem_address_length, rx_buffer, length);
}

void BSP_vCurrentSenseWriteFunction(const uint8_t chip_addr, const uint8_t * mem_address, const uint8_t mem_address_length, uint8_t* tx_buffer, const uint16_t length) {
	I2C_DRIVER_bWriteCustom(I2C_psGetDriver(), chip_addr, mem_address, mem_address_length, tx_buffer, length);
}


void BSP_vUsbReset(void) {
    ioport_set_pin_level(USB_RESET_PIN, 0);
    delay_ms(100);
    ioport_set_pin_level(USB_RESET_PIN, 1);
}

/*
* All functions for CAN operation
*/
void BSP_vInitCan(void) {

    // configure pins, disable gpio mode
    ioport_disable_pin(CAN_PIN_TX);
    ioport_set_pin_mode(CAN_PIN_TX, CAN_PIN_TX_MUX);
    ioport_disable_pin(CAN_PIN_RX);
    ioport_set_pin_mode(CAN_PIN_RX, CAN_PIN_RX_MUX);

    // Enable clock to CAN module
    // Peripheral clock controlls register set/get, etc.
    sysclk_enable_peripheral_clock(CAN_DEVICE_ID);

    // Enable and configure CAN module
    struct mcan_config sCanConfig;
    mcan_get_config_defaults(&sCanConfig);
    sCanConfig.automatic_retransmission = false;
    sCanConfig.nonmatching_frames_action_extended = MCAN_NONMATCHING_FRAMES_FIFO_1;
    mcan_init(&sCanModule, CAN_DEVICE, &sCanConfig);

    // The MCAN_init function sets the PCK 5 clock, to 30MHz
    // Enable PMC_PCK_5. This controls CAN clock generation
    // Prescaler = 300/ (14+1) = 20MHz
    
    //pmc_pck_set_prescaler(PMC_PCK_5, PMC_PCK_PRES(14));
    // Prescaler = 60 / (2+1) = 20Mhz
	
	// Prescaler = 300Mhz / (14+1) = 20mhz
    pmc_pck_set_prescaler(PMC_PCK_5, PMC_PCK_PRES(14));
    pmc_pck_set_source(PMC_PCK_5, PMC_PCK_CSS_PLLA_CLK);
    pmc_enable_pck(PMC_PCK_5);

    mcan_set_baudrate(CAN_DEVICE, 1000000);

    // Will set CCCR.INIT bit to 1, so configuration is possible,
    // mcan_enable_test_mode(&sCanModule);

    // Will set CCR.INIT bit to 0, so module runs
    mcan_start(&sCanModule);

    // Set up the filter for an extended message
    // We receive messages at OBC_CAN_ADRESS,
    // the XTX will receive messages on it's own address
	BSP_vCanSetAddressFilter(OBC_CAN_ADRESS, OBC_CAN_MASK);
	
    irq_register_handler(CAN_INTERRUPT, 1);
    mcan_enable_interrupt(&sCanModule, MCAN_RX_BUFFER_NEW_MESSAGE | MCAN_RX_FIFO_0_NEW_MESSAGE | MCAN_RX_FIFO_1_NEW_MESSAGE | MCAN_FORMAT_ERROR | MCAN_ACKNOWLEDGE_ERROR | MCAN_BUS_OFF);
}

void BSP_vCanSetAddressFilter(uint32_t filter, uint32_t mask){
	struct mcan_extended_message_filter_element et_filter;
	mcan_get_extended_message_filter_element_default(&et_filter);
	et_filter.F0.reg = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFID1(filter) | MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F0_EFEC(1);
	et_filter.F1.reg = MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFID2(mask) | MCAN_EXTENDED_MESSAGE_FILTER_ELEMENT_F1_EFT_CLASSIC;

	mcan_set_rx_extended_filter(&sCanModule, &et_filter, 0);
	mcan_set_rx_extended_filter(&sCanModule, &et_filter, 1);
}

struct mcan_module* BSP_psGetCanDriver(void) {
    return &sCanModule;
}

void BSP_vInitRTC(void){
    Rtc rtc0 = {0};
}

void RTC_HANDLER(void){

}

void CAN_HANDLER(void)
{
    volatile uint32_t status, i;
    status = mcan_read_interrupt_status(&sCanModule);

    if (status & MCAN_RX_BUFFER_NEW_MESSAGE ) {
        mcan_clear_interrupt_status(&sCanModule, MCAN_RX_BUFFER_NEW_MESSAGE);
        static struct mcan_rx_element_buffer rx_element_buffer;

        for (i = 0; i < CONF_MCAN0_RX_BUFFER_NUM; i++) {
            if (mcan_rx_get_buffer_status(&sCanModule, i)) {
                mcan_rx_clear_buffer_status(&sCanModule, i);
                mcan_get_rx_buffer_element(&sCanModule, &rx_element_buffer, i);
            }
        }
    }

    if (status & MCAN_RX_FIFO_0_NEW_MESSAGE) {
        struct mcan_rx_element_fifo_0 rx_element_fifo_0;
        mcan_get_rx_fifo_0_element(&sCanModule, &rx_element_fifo_0, fifo_receive_index);
		
		// Send message to driver
		CAN_DRIVER_vMessageInFifo0(rx_element_fifo_0);
		
		// Ack the message, Suspect this allows a new message to be received
        mcan_rx_fifo_acknowledge(&sCanModule, 0, fifo_receive_index);

        fifo_receive_index++;
        if(fifo_receive_index == CONF_MCAN0_RX_FIFO_0_NUM)
        {
            fifo_receive_index = 0;
        }
		
		// Finally, clear interupt flag
        mcan_clear_interrupt_status(&sCanModule, MCAN_RX_FIFO_0_NEW_MESSAGE);
    }

    if (status & MCAN_RX_FIFO_1_NEW_MESSAGE) {
        mcan_clear_interrupt_status(&sCanModule, MCAN_RX_FIFO_1_NEW_MESSAGE);
        mcan_rx_fifo_acknowledge(&sCanModule, 1, 0);

        struct mcan_rx_element_fifo_1 rx_element_fifo_1;

        mcan_get_rx_fifo_1_element(&sCanModule, &rx_element_fifo_1, 0);
        mcan_rx_fifo_acknowledge(&sCanModule, 0, 0);
    }

    if (status & MCAN_BUS_OFF) {
        mcan_clear_interrupt_status(&sCanModule, MCAN_BUS_OFF);
    }

    if (status & MCAN_ACKNOWLEDGE_ERROR) {
        mcan_clear_interrupt_status(&sCanModule, MCAN_ACKNOWLEDGE_ERROR);
    }

    if (status & MCAN_FORMAT_ERROR) {
        mcan_clear_interrupt_status(&sCanModule, MCAN_FORMAT_ERROR);
    }
}

void MCAN0_INT1_Handler(void){
    asm("nop");
};


void TELEMETRY_USART_HANDLER(void)
{
    uint32_t dw_status = usart_get_status(TELEMETRY_USART);

    // A Value is received
    if (dw_status & US_CSR_RXRDY) {
        uint32_t received_byte;

        usart_read(TELEMETRY_USART, &received_byte);
        
        if (!USART_BUFFER_Receive(&telemetryUsart, (uint8_t) received_byte)) {
            // Set CTS here, if buffer is full
            BSP_vTelemetrySetCTS(true);
        }
    }

    // TX Buffer and shift register empty
    if (dw_status & US_CSR_TXEMPTY) {
        uint8_t nextByte = 0;
        if (USART_BUFFER_Transmit(&telemetryUsart, &nextByte)) {
            // If true there is a value loaded
            usart_write(TELEMETRY_USART, nextByte);
        } else {
            // Disable the interrupt, re-enable later
            usart_disable_interrupt(TELEMETRY_USART, US_IER_TXEMPTY);
        }
    }
}

void BSP_vInit1MsTimer(void) {

    int32_t timerChannel = 0;

    // Setup timer
    // TC_CMR_TCCLKS_TIMER_CLOCK3 : Mclk/32
    // TC_CMR_CPCTRG : Set RC compare to trigger a timer counter reset
    sysclk_enable_peripheral_clock(ID_TC0);
    tc_init(TC0, timerChannel, TC_CMR_TCCLKS_TIMER_CLOCK3 | TC_CMR_CPCTRG);
    uint16_t prescaler = sysclk_get_main_hz() /64 / 1000;
    tc_write_rc(TC0, timerChannel, prescaler);

    tc_enable_interrupt(TC0, timerChannel, TC_IER_CPCS);

    // Actually enable the interupt
    NVIC_DisableIRQ(TC0_IRQn);
    NVIC_ClearPendingIRQ(TC0_IRQn);
    NVIC_SetPriority(TC0_IRQn, 0);
    NVIC_EnableIRQ(TC0_IRQn);
    
    tc_start(TC0, timerChannel);
}

// ToDo: Refactor
static uint64_t msTimeCounter;

void TC0_Handler(void)
{
    if (tc_get_status(TC0, 0) & TC_SR_CPCS) {
        msTimeCounter +=1;
    }
}

uint16_t BSP_u16TmrGetTick(void){
    return (uint16_t)msTimeCounter;
}

uint64_t BSP_u64GetTimestamp(void){
    return msTimeCounter;
}
