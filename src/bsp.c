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
void BSP_vInitGPIO(void);
void BSP_vInitCan(void);
void BSP_vInit1MsTimer(void);




// Local variables
static struct spi_device sSpiDevice;
static struct mcan_module sCanModule;
static volatile uint32_t fifo_receive_index = 0;


// Post cleanup

// Local functions
static void BSP_vInitUART(bsp_t * bsp);
static void BSP_vInitBusI2C(bsp_t * bsp);
static void BSP_vInitUtilI2C(bsp_t * bsp);
static void BSP_InitRTC(void);

// Post cleanup
static ccd_uart_t telemetry_uart;
static ccd_i2c_t  util_i2c;
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

	BSP_vInitUART(bsp);
	BSP_vInitBusI2C(bsp);
	BSP_vInitUtilI2C(bsp);	

	BSP_vInitGPIO();
	
	BSP_InitRTC();


	
	/*
    BSP_vInitSPI();
    
    BSP_vInitCan();*/

    //BSP_vInit1MsTimer();
	

	
    
    
	

	// So - we used to reset the USB connection when we power cycle. I don't think this is needed anymore?
    //BSP_vUsbReset();
	
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


void inline BSP_vSetPin(uint32_t pin, bool value){
	ioport_set_pin_level(pin, value);
}


static void BSP_vInitUART(bsp_t * bsp){
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
}

static void BSP_vInitBusI2C(bsp_t * bsp){
	// Board I2C
	ioport_set_pin_mode(I2C_BUS_SDA_PIN, I2C_BUS_SDA_MUX);
	ioport_disable_pin(I2C_BUS_SDA_PIN);

	ioport_set_pin_mode(I2C_BUS_SCL_PIN, I2C_BUS_SCL_MUX);
	ioport_disable_pin(I2C_BUS_SCL_PIN);
	
	ccd_i2c_driver_Init(&bus_i2c, I2C_BUS_DEVICE);
	bsp->bus_i2c = &bus_i2c;
}

static void BSP_vInitUtilI2C(bsp_t * bsp){
	ioport_set_pin_mode(I2C_UTIL_SDA_PIN, I2C_UTIL_SDA_MUX);
	ioport_disable_pin(I2C_UTIL_SDA_PIN);

	ioport_set_pin_mode(I2C_UTIL_SCL_PIN, I2C_UTIL_SCL_MUX);
	ioport_disable_pin(I2C_UTIL_SCL_PIN);
	
	ccd_i2c_driver_Init(&util_i2c, I2C_UTIL_DEVICE);
	bsp->util_i2c = &util_i2c;
}

/*
 * Initialize all the general purpose GPIO pins
*/
void BSP_vInitGPIO(void) {
	
	if (BSP_u8GetVersion() == 0){
		// Version 0 had VBatAlt and 5V lines
		ioport_enable_pin(EN_VBATALT_BUS_PIN);
		ioport_set_pin_level(EN_VBATALT_BUS_PIN, 0);
		ioport_set_pin_dir(EN_VBATALT_BUS_PIN, IOPORT_DIR_OUTPUT);
		
		ioport_enable_pin(EN_5V_BUS_PIN);
		ioport_set_pin_level(EN_5V_BUS_PIN, 0);
		ioport_set_pin_dir(EN_5V_BUS_PIN, IOPORT_DIR_OUTPUT);
	}

	ioport_enable_pin(EN_3V3_BUS_PIN);
	ioport_set_pin_level(EN_3V3_BUS_PIN, 0);
	ioport_set_pin_dir(EN_3V3_BUS_PIN, IOPORT_DIR_OUTPUT);

	ioport_enable_pin(EN_VBAT_BUS_PIN);
	ioport_set_pin_level(EN_VBAT_BUS_PIN, 0);
	ioport_set_pin_dir(EN_VBAT_BUS_PIN, IOPORT_DIR_OUTPUT);
	
	// USB Reset pin	
	ioport_enable_pin(USB_RESET_PIN);
	ioport_set_pin_level(USB_RESET_PIN, 1);
	ioport_set_pin_dir(USB_RESET_PIN, IOPORT_DIR_OUTPUT);
	
	// GSE version 2 has 4 debug pins
	if (BSP_u8GetVersion() == 1){
		ioport_enable_pin(PIN_DEBUG_0);
		ioport_set_pin_level(PIN_DEBUG_0, 0);
		ioport_set_pin_dir(PIN_DEBUG_0, IOPORT_DIR_OUTPUT);
		
		ioport_enable_pin(PIN_DEBUG_1);
		ioport_set_pin_level(PIN_DEBUG_1, 0);
		ioport_set_pin_dir(PIN_DEBUG_1, IOPORT_DIR_OUTPUT);
		
		ioport_enable_pin(PIN_DEBUG_2);
		ioport_set_pin_level(PIN_DEBUG_2, 0);
		ioport_set_pin_dir(PIN_DEBUG_2, IOPORT_DIR_OUTPUT);
		
		ioport_enable_pin(PIN_DEBUG_3);
		ioport_set_pin_level(PIN_DEBUG_3, 0);
		ioport_set_pin_dir(PIN_DEBUG_3, IOPORT_DIR_OUTPUT);
	}
}



void BSP_vUsbReset(void) {
	ioport_set_pin_level(USB_RESET_PIN, 0);
	delay_ms(100);
	ioport_set_pin_level(USB_RESET_PIN, 1);
}

void BSP_InitRTC(void){
	// Configure the PIO lines to use the crystal
	ioport_disable_pin(PIN_XIN32);
	ioport_disable_pin(PIN_XOUT32);
	
	// The PIO crystal is connected to the Alternate function, this in not handled by 
	// the peripheral mux
    //ioport_set_pin_mode(PIN_XIN32, IOPORT_MODE_MUX_C);
	//ioport_set_pin_mode(PIN_XOUT32, IOPORT_MODE_MUX_C);
	
	// Switch to the crystal
	SUPC->SUPC_CR = SUPC_CR_XTALSEL | SUPC_CR_KEY_PASSWD;
	
	// Wait a number of cycles for the clock to be set
	while (!((SUPC->SUPC_SR & SUPC_SR_OSCSEL) && (PMC->PMC_SR & PMC_SR_OSCSELS))){
		//Todo: Timeout here!	
	}	
	
	// Reset all the RTC values
	// First wait for the SEC status bit
	while ((RTC->RTC_SR & RTC_SR_SEC) == 0){
		
	}
	
	// Stop the RTC, request update
	RTC->RTC_CR = RTC->RTC_CR | RTC_CR_UPDCAL | RTC_CR_UPDTIM;
	
	// Wait for the ACKUPD bit
	while ((RTC->RTC_SR & RTC_SR_ACKUPD) == 0){
	}
	// Clear the ACKUPD bit
	RTC->RTC_SCCR = RTC_SR_ACKUPD;
	
	//Clear values
	RTC->RTC_TIMR = 0;
	RTC->RTC_CALR = 0;
	
	// Clear update request bits
	RTC->RTC_CR = RTC->RTC_CR & ~(RTC_CR_UPDCAL | RTC_CR_UPDTIM);
}

uint32_t BSP_GetUptime(void){
	uint32_t seconds = ( (RTC->RTC_TIMR & RTC_TIMR_SEC_Msk) >> RTC_TIMR_SEC_Pos);
	uint32_t minutes = ( (RTC->RTC_TIMR & RTC_TIMR_MIN_Msk) >> RTC_TIMR_MIN_Pos);
	uint32_t hours = ( (RTC->RTC_TIMR & RTC_TIMR_HOUR_Msk) >> RTC_TIMR_HOUR_Pos);
	
	// Welcome to the most screwed-up method of storing numbers.
	// Stupid Binary Coded Decimal
	// Bottom four bits count to 9, then the top bit gets incremented.
	// This means displaying the hex as a string 'looks' correct.
	
	seconds = (seconds & 0xF) + ((seconds & 0xF0) >> 4) * 10;
	minutes = (minutes & 0xF) + ((minutes & 0xF0) >> 4) * 10;
	hours = (hours & 0xF) + ((hours & 0xF0) >> 4) * 10;
	
	return seconds + minutes*60 + hours *60 * 60;
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