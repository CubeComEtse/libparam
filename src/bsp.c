/*
 * bsp.h
 *
 * Created: 2020/04/01 08:19:54
 *  Author: Kolijn
 */ 

#include <asf.h>

#include "bsp.h"

#include "genclk.h"
#include "ioport.h"
#include "obc_controller_rev_A.h"
#include "spi.h"

// All interrupt mask.
#define ALL_INTERRUPT_MASK  0xffffffff

// Local functions
void BSP_vInitSPI(void);
void BSP_vInitBoardI2C(void);
void BSP_vInitPowerSenseGPIO(void);
void BSP_vInitPowerGPIO(void);
void BSP_vInitCan(void);
void BSP_vInit1MsTimer(void);




// Local variables
static struct spi_device sSpiDevice;
static struct mcan_module sCanModule;
static volatile uint32_t fifo_receive_index = 0;


// Post cleanup
static ccd_uart_t telemetry_uart;
static ccd_i2c_t  bus_i2c;

// The version is only read and set once, during startup
static uint8_t version;

void BSP_Init(bsp_t * bsp) {

	// System Initialization
	sysclk_init();    
	
	wdt_disable(WDT);
	
	// General GPIO is handled here - not in a driver
	ioport_init();
	
	// Get the version. This is the first thing we do - it might affect the code later.
	ioport_set_pin_dir(PIN_VERSION_0, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(PIN_VERSION_1, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(PIN_VERSION_2, IOPORT_DIR_INPUT);
	
	ioport_set_pin_mode(PIN_VERSION_0, IOPORT_MODE_PULLDOWN);
	ioport_set_pin_mode(PIN_VERSION_1, IOPORT_MODE_PULLDOWN);
	ioport_set_pin_mode(PIN_VERSION_2, IOPORT_MODE_PULLDOWN);
	
	ioport_enable_pin(PIN_VERSION_0);
	ioport_enable_pin(PIN_VERSION_1);
	ioport_enable_pin(PIN_VERSION_2);
	
	delay_ms(1);
	version = (ioport_get_pin_level(PIN_VERSION_2) << 2) | (ioport_get_pin_level(PIN_VERSION_1) << 1) | ioport_get_pin_level(PIN_VERSION_0);


	//Telemetry UART
	ioport_set_pin_mode(T_USART_RX_PIN, IOPORT_MODE_MUX_B);
	ioport_disable_pin(T_USART_RX_PIN);

	ioport_set_pin_mode(T_USART_TX_PIN, IOPORT_MODE_MUX_B);
	ioport_disable_pin(T_USART_TX_PIN);

	ioport_enable_pin(T_USART_RTS_PIN);
	ioport_set_pin_dir(T_USART_RTS_PIN, IOPORT_DIR_INPUT);
	ioport_enable_pin(T_USART_CTS_PIN);
	ioport_set_pin_dir(T_USART_CTS_PIN, IOPORT_DIR_OUTPUT);
	telemetry_uart.cts_pin = T_USART_CTS_PIN;
	ccd_uart_Init(&telemetry_uart, T_USART, T_USART_SPEED);
	bsp->telemetry_uart = &telemetry_uart;

	// Board I2C
	ioport_set_pin_mode(I2C_BOARD_SDA_PIN, I2C_BOARD_SDA_MUX);
	ioport_disable_pin(I2C_BOARD_SDA_PIN);

	ioport_set_pin_mode(I2C_BOARD_SCL_PIN, I2C_BOARD_SCL_MUX);
	ioport_disable_pin(I2C_BOARD_SCL_PIN);
	ccd_i2c_driver_Init(&bus_i2c, I2C_BOARD_DEVICE);
	bsp->bus_i2c = &bus_i2c;
	bsp->local_i2c = &bus_i2c;



	

    BSP_vInitSPI();
    BSP_vInitPowerSenseGPIO();
    BSP_vInitPowerGPIO();
    BSP_vInitCan();

    //BSP_vInit1MsTimer();
	

	
    
    ioport_enable_pin(USB_RESET_PIN);
    ioport_set_pin_level(USB_RESET_PIN, 0);
    ioport_set_pin_dir(USB_RESET_PIN, IOPORT_DIR_OUTPUT);
    
    
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
	
	ioport_enable_pin(PIN_DEBUG_0);
	ioport_enable_pin(PIN_DEBUG_1);
	ioport_enable_pin(PIN_DEBUG_2);
	ioport_enable_pin(PIN_DEBUG_3);
	
	ioport_set_pin_level(PIN_DEBUG_0, 0);
	ioport_set_pin_level(PIN_DEBUG_1, 0);
	ioport_set_pin_level(PIN_DEBUG_2, 0);
	ioport_set_pin_level(PIN_DEBUG_3, 0);

	ioport_set_pin_dir(PIN_DEBUG_0, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIN_DEBUG_1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIN_DEBUG_2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(PIN_DEBUG_3, IOPORT_DIR_OUTPUT);

    BSP_vUsbReset();
	
	// Make all interrupt prioirty bits preempt bits, rather than sub-prioirty bits.
	// According to https://www.freertos.org/Documentation/02-Kernel/03-Supported-devices/04-Demos/ARM-Cortex/RTOS-Cortex-M3-M4
	NVIC_SetPriorityGrouping(4);
    Enable_global_interrupt();
	
	// Set the systick to the lowest possible interrupt level
    SysTick_Config(300000);
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) -1 );
}

uint8_t BSP_u8GetVersion(){
	return version;
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
    // Peripheral clock controls register set/get, etc.
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


void USART2_Handler(void){
	ccd_uart_InterruptHandler(&telemetry_uart);
}