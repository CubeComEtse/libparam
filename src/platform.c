/*
 * Platform.c
 *
 * Created: 2024/11/28 09:23:41
 *  Author: Kolijn
 */ 
#include "platform.h"
#include "register_handler.h"

static ltc2992_device_t power_measure_1;
static ltc2992_device_t power_measure_2;
static ltc2499_device_t cs_board;

static gse_manager_t gse_manager;

static local_target_t local_target;
static i2c_target_t i2c_target;
static can_target_t can_target;
static uart_target_t uart_target;

static led_indicator_t led_indicator;
static sermux_v3_t sermux_v3;

static pc104_t pc104;

static rf_relay_config_t rf_relay_1;
static rf_relay_config_t rf_relay_2;
static multitester_t multitester;
static te_scanner_t te_scanner;

static platform_t platform;

/*
 * This function configures all the pointers and functions for the platform, 
 * but doesn't run any of the config functions yet.
 * 
 * Any setup performed in this function can configure modules in the micro, but
 * should not communicate with any external IC.
*/
void PLATFORM_vInit(bsp_t * bsp)
{
	platform.power_measure_1 = &power_measure_1;
	platform.power_measure_2 = &power_measure_2;
	platform.cs_board = &cs_board;
	platform.gse_manager = &gse_manager;
	platform.local_target = &local_target;
	platform.i2c_target = &i2c_target;
	platform.can_target = &can_target;
	platform.uart_target = &uart_target;
	platform.led_indicator = &led_indicator;
	platform.sermux_v3 = &sermux_v3;
	
	platform.pc104 = &pc104;

	
	uint8_t version = BSP_u8GetVersion();
	if (version == 0)
	{
		//The LTC2992's are independent of i2c functions, so setup them
		power_measure_1.i2c_write_function = ccd_i2c_driver_Write;
		power_measure_1.i2c_read_function = ccd_i2c_driver_Read;
		power_measure_1.i2c_handle = bsp->util_i2c;
		
		power_measure_2.i2c_write_function = ccd_i2c_driver_Write;
		power_measure_2.i2c_read_function = ccd_i2c_driver_Read;
		power_measure_2.i2c_handle = bsp->util_i2c;
		
	}
	if (version == 1){
		//The LTC2992's are independent of i2c functions, so setup them
		power_measure_1.i2c_write_function = ccd_i2c_driver_Write;
		power_measure_1.i2c_read_function = ccd_i2c_driver_Read;
		power_measure_1.i2c_handle = bsp->util_i2c;
		
	}

	cs_board.i2c_read_function = ccd_i2c_driver_Read;
	cs_board.i2c_write_function = ccd_i2c_driver_Write;
	
	gse_manager.power_measure_1  = &power_measure_1;
	gse_manager.power_measure_2 = &power_measure_2;
	gse_manager.cs_board = &cs_board;
	gse_manager.board_version = BSP_u8GetVersion(); 
	gse_manager.set_gpio_pin = &BSP_vSetPin;
	gse_manager.enable_3v3_pin = EN_3V3_BUS_PIN;
	gse_manager.enable_5v_pin = EN_5V_BUS_PIN;
	gse_manager.enable_vbat_pin = EN_VBAT_BUS_PIN;
	gse_manager.enable_vbatalt_pin = EN_VBATALT_BUS_PIN;
	GSE_MANAGER_Init(&gse_manager);
	
	LOCALTARGET_Init(&local_target);

	i2c_target.i2c_read = ccd_i2c_driver_Read;
	i2c_target.i2c_write = ccd_i2c_driver_Write;
	i2c_target.i2c_set_baud = ccd_i2c_driver_SetBaud;
	i2c_target.i2c_handle = bsp->bus_i2c;
	I2CTARGET_Init(&i2c_target);
	
	can_target.can_send = ccd_can_Send_message;
	can_target.can_receive = cc_can_Receive_message;
	can_target.can_handle = bsp->bus_can;
	can_target.radio_can_address = 0x26;
	// This has to align with the BSP version, otherwise issues.
	can_target.our_can_address = 0xE9;
	CANTARGET_Init(&can_target);
	
	// TODO: UART
	uart_target.uart_send = ccd_b_uart_Send_message;
	uart_target.uart_receive = ccd_b_uart_Receive_message;
	uart_target.uart_handle = bsp->bus_uart;
	uart_target.radio_uart_address = 0x26;
	uart_target.gse_uart_address = 0xE9;
	UARTTARGET_Init(&uart_target);
	
	sermux_v3.in_stream = bsp->telemetry_uart->uart_rx_buffer;
	sermux_v3.out_stream = bsp->telemetry_uart->uart_tx_buffer;
	SERMUX_V3_Init(&sermux_v3);
	
	pc104.set_pin = ioport_set_pin_level;
	pc104.ena_Pin = PC104_EN_PIN;
	pc104.nrst_Pin = PC104_nRST_PIN;
	platform.pc104 = &pc104;
	
	led_indicator.led_driver = bsp->led_driver;
	LEDIndicator_Setup(&led_indicator);
	platform.led_indicator = &led_indicator;
	LEDIndicator_SetStatic(&led_indicator);
	
	//Add Local Targets
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_GSE, local_target.incoming_messages, local_target.outgoing_messages);
	
	// Add I2C Targets
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC, i2c_target.incoming_messages, i2c_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_CHECKSUM, i2c_target.incoming_messages, i2c_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_2, i2c_target.incoming_messages, i2c_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_I2C_CC_3, i2c_target.incoming_messages, i2c_target.outgoing_messages);

	// Add CAN Targets
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_CAN_CC_2, can_target.incoming_messages, can_target.outgoing_messages);
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_CAN_CC_3, can_target.incoming_messages, can_target.outgoing_messages);
	
	// Add UART Targets
	SERMUX_V3_AddTarget(&sermux_v3, EP_V2_UART_CC_2, uart_target.incoming_messages, uart_target.outgoing_messages);
	
	REG_vSetPlatformPointer(&platform);
		
		
	platform.rf_relay_1 = &rf_relay_1;		
	rf_relay_1.i2c_write_function = ccd_i2c_driver_Write;
	rf_relay_1.i2c_read_function = ccd_i2c_driver_Read;
	RFRelay_Init(platform.rf_relay_1, 1);
	
	platform.rf_relay_2 = &rf_relay_2;
	rf_relay_2.i2c_write_function = ccd_i2c_driver_Write;
	rf_relay_2.i2c_read_function = ccd_i2c_driver_Read;
	RFRelay_Init(platform.rf_relay_2, 2);
		
	platform.multitester = &multitester;
	platform.multitester->i2c_read_function = ccd_i2c_driver_Read;
	platform.multitester->i2c_write_function = ccd_i2c_driver_Write;
	MULTI_Init(platform.multitester);
	
	
	if (version == 0){
		rf_relay_1.i2c_handle = bsp->bus_i2c;
		rf_relay_2.i2c_handle = bsp->bus_i2c;
		platform.multitester->i2c_handle = bsp->bus_i2c;
	}
	
	if (version == 1){
		rf_relay_1.i2c_handle = bsp->util_i2c;
		rf_relay_2.i2c_handle = bsp->util_i2c;
		platform.multitester->i2c_handle = bsp->util_i2c;
	}
	
	platform.te_scanner = &te_scanner;
	platform.te_scanner->i2c_read_function = ccd_i2c_driver_Read;
	platform.te_scanner->i2c_write_function = ccd_i2c_driver_Write;
	platform.te_scanner->i2c_handle = bsp->util_i2c;
	TE_Adaptors_Setup(platform.te_scanner);
	
	// Use the FreeRTOS tick count as a timer source
	// This does mean we can only use this timer from non-interrupt functions.
	TMR_vRegisterSource(TMR_SOURCE_SYSTICK, xTaskGetTickCount);
	
}

/*
 * This function should be ran after the PLATFORM_vInit function, and 
 * configures all the external devices. Basically, anything that will take some
 * time goes here.
*/
void PLATFORM_vConfigureAll(platform_t * handle){
	
	// GSE Local Power monitors
	uint8_t version = BSP_u8GetVersion();
	// Commented out until we get the correct ICs
	if (version == 0)
	{
		LTC2992_vNormalSetup(&power_measure_1, LTC2992_u8GenAddr(0, 0));
		LTC2992_vNormalSetup(&power_measure_2, LTC2992_u8GenAddr(0, 2));
	}
	if (version == 1)
	{
		LTC2992_vNormalSetup(&power_measure_1, LTC2992_u8GenAddr(0, 0));
	}
	
	// Current sensor board
	LTC2499_vInit(&cs_board);
}

/*
 * This function returns a pointer to the platform, which can be used to 
 * configure anything about the GSE
 */
platform_t * PLATFORM_get(void){
	return &platform;
}
