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
// void BSP_vInitSPI(void);

// Local variables
// static struct spi_device sSpiDevice;




// Post cleanup

// Local functions
static void BSP_vInitUART(bsp_t * bsp);
static void BSP_vInitBusI2C(bsp_t * bsp);
static void BSP_vInitUtilI2C(bsp_t * bsp);
static void BSP_vInitGPIO(void);
static void BSP_InitRTC(void);
static void BSP_vInitCan(bsp_t * bsp);
static void BSP_vInitLEDPWM(bsp_t * bsp);

// Post cleanup
static ccd_uart_t telemetry_uart;
static ccd_i2c_t  util_i2c;
static ccd_i2c_t  bus_i2c;
static ccd_can_t  bus_can;
static ccd_led_t led_driver;

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

	BSP_vInitCan(bsp);
	
	BSP_vInitLEDPWM(bsp);

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

void USART2_Handler(void){
	ccd_uart_InterruptHandler(&telemetry_uart);
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
		
		ioport_enable_pin(ETH_nRST);
		ioport_set_pin_level(ETH_nRST, 0);
		ioport_set_pin_dir(ETH_nRST, IOPORT_DIR_OUTPUT);
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
	
	if (BSP_u8GetVersion() == 0){
		ioport_set_pin_level(PC104_EN_PIN, 0);
		ioport_enable_pin(PC104_EN_PIN);
		ioport_set_pin_dir(PC104_EN_PIN, IOPORT_DIR_OUTPUT);
		
		ioport_set_pin_level(PC104_nRST_PIN, 0);
		ioport_enable_pin(PC104_nRST_PIN);
		ioport_set_pin_dir(PC104_nRST_PIN, IOPORT_DIR_OUTPUT);
		
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

void BSP_vInitCan(bsp_t * bsp) {

	// Configure pins, disable GPIO mode
	ioport_disable_pin(CAN_PIN_TX);
	ioport_set_pin_mode(CAN_PIN_TX, CAN_PIN_TX_MUX);
	ioport_disable_pin(CAN_PIN_RX);
	ioport_set_pin_mode(CAN_PIN_RX, CAN_PIN_RX_MUX);

	// Enable clock to CAN module
	sysclk_enable_peripheral_clock(CAN_DEVICE_ID);
	
	bus_can.gse_address = 0x26;
	bus_can.gse_address_mask = 0xFF;
	bus_can.baudrate = 1000000;
	ccd_can_Init(&bus_can, MCAN0);
	bsp->bus_can = &bus_can;
}


void MCAN0_INT0_Handler(void) {
	ccd_can_driver_ReceiveCallback(&bus_can);
}

void MCAN0_INT1_Handler(void) {
	asm("nop");
}


void BSP_vInitLEDPWM(bsp_t * bsp)
{
	// Setup GPIO pin
	// Pin PA15 - supports PWMC0_ PWML3 on Peripheral C
	PIOA->PIO_ABCDSR[0] &= ~PIO_ABCDSR_P15;
	PIOA->PIO_ABCDSR[1] |= PIO_ABCDSR_P15;

	// Set Pin to Peripheral mode
	PIOA->PIO_PDR |= PIO_PDR_P15;

	// Enable clock to PWM module
	PMC->PMC_PCER0 = PMC_PCER0_PID31;
	
	led_driver.uart_disable_fc = ccd_uart_StopFlowControl;
	led_driver.uart_enable_fc = ccd_uart_StartFlowControl;
	led_driver.uart_handle = bsp->telemetry_uart;
	ccd_led_driver_Init(&led_driver, PWM0);
	bsp->led_driver = &led_driver;
}





















/*

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
*/